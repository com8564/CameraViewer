#include "pch.h"
#include "iNova.h"
#include <format>

iNova::iNova() {
	imgSize = -1;
	streamingSocket = 0;
	commandSocket = 0;
}

iNova::~iNova() {
	closesocket(streamingSocket);
	closesocket(commandSocket);
	WSACleanup();
}

bool iNova::connectCamera(char* szServerName, WORD streamingPort, WORD commandPort) {
	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
		printf("WSAStartup failed.\n");
		system("pause");
	}
	bool success = true;
	if (streamingPort != 0) {
		streamingSocket = socket(AF_INET, SOCK_STREAM, 0);
		if (streamingSocket == INVALID_SOCKET) { return false; }

		struct sockaddr_in server;
		inet_pton(AF_INET, szServerName, &server.sin_addr.s_addr); //inet_addr() is only supporting IPv4 but inet_pton() support both IPv4 and IPv6 
		//server.sin_addr.s_addr = inet_addr(szServerName);
		server.sin_family = AF_INET;
		server.sin_port = htons(streamingPort);

		if (connect(streamingSocket, (SOCKADDR*)&server, sizeof(server))) {
			closesocket(streamingSocket);
			success = false;
		}
	}

	if (commandPort != 0) {
		commandSocket = socket(AF_INET, SOCK_STREAM, 0);
		if (commandSocket == INVALID_SOCKET) { return false; }

		struct sockaddr_in server;
		inet_pton(AF_INET, szServerName, &server.sin_addr.s_addr); //inet_addr() is only supporting IPv4 but inet_pton() support both IPv4 and IPv6 
		//server.sin_addr.s_addr = inet_addr(szServerName);
		server.sin_family = AF_INET;
		server.sin_port = htons(commandPort);

		if (connect(commandSocket, (SOCKADDR*)&server, sizeof(server))) {
			closesocket(commandSocket);
			success = false;
		}
	}

	return success;
}

bool iNova::disconnectCamera() {
	if (streamingSocket != 0) {
		closesocket(streamingSocket);
	}
	if (commandSocket != 0) {
		closesocket(commandSocket);
	}

	WSACleanup();
	return true;
}

void iNova::get_ImgSize(SOCKET Socket) {
	unsigned char recvbuf[2000];
	long rc;
	while (1) {
		rc = recv(Socket, (char*)&recvbuf, sizeof(recvbuf), 0);
		if (rc == 4) {
			imgSize = ntohl(*(int*)recvbuf);
			break;
		}
		else {
			memset(recvbuf, 0, 2000);
			continue;
		}
	}
}

bool iNova::Get_Image(uchar* rgbBuffer) {
	get_ImgSize(streamingSocket);
	if (imgSize < 0 || imgSize > MAX_JPEG_SIZE) { imgSize = -1;  return false; }

	int count = 0;
	long rc;
	cv::Mat decodedImage;
	unsigned char* jpegImgbuf = new unsigned char[imgSize];

	while (count < imgSize) {
		rc = recv(streamingSocket, (char*)jpegImgbuf + count, imgSize - count, 0);
		if (rc > 0) { count += rc; }
		else { continue; }
	}

	if (jpegImgbuf[imgSize - 2] == 0xff && jpegImgbuf[imgSize - 1] == 0xd9) {
		cv::Mat rawData(1, imgSize, CV_8UC1, (void*)jpegImgbuf);
		decodedImage = cv::imdecode(rawData, 1);
		memcpy(rgbBuffer, decodedImage.data, _msize(rgbBuffer));
	}

	imgSize = -1;
	delete[] jpegImgbuf;
	return true;
}

std::vector<std::string> iNova::SendCommand(std::string message) {
	std::vector<std::string> result;

	if (commandSocket == 0) {
		result.push_back("NG");
		return result;
	}
	message += "\r\n";

	char recvbuf[100];
	memset(recvbuf, 0, 100);
	send(commandSocket, message.c_str(), message.length(), 0);
	recv(commandSocket, recvbuf, sizeof(recvbuf), 0);

	if (recvbuf[0] == 'O' || recvbuf[0] == 'N') {
		std::stringstream recv_msg(recvbuf);
		std::string temp;
		int i = 0;
		while (std::getline(recv_msg, temp, ' ')) {
			if (temp == "") { break; }
			result.push_back(temp);
			i++;
		}

		if (result.size() > 0) {//Erase CRLF
			int pos = result[result.size() - 1].find('\r');
			result[result.size() - 1] = result[result.size() - 1].substr(0, pos);
		}
	}

	return result;
}

bool iNova::GetAutoExposureMode(std::string& exposureMode) {
	std::vector<std::string> res = SendCommand("GetALC");
	if (res[0] != "OK") {
		return false;
	}
	exposureMode = res[1];

	return true;
}

bool iNova::GetAutoGainMode(std::string& gainMode) {
	std::vector<std::string> res = SendCommand("GetALC");
	if (res[0] != "OK") {
		return false;
	}
	gainMode = res[2];

	return true;
}

bool iNova::GetFirmwareVersion(std::string& firmwareVersion) {
	std::vector<std::string> res = SendCommand("GetFirmwareVersion");
	if (res[0] != "OK") {
		return false;
	}
	firmwareVersion = res[1];

	return true;
}

bool iNova::GetSerialNumber(std::string& serialNumber) {
	std::vector<std::string> res = SendCommand("GetSerialNumber");
	if (res[0] != "OK") {
		return false;
	}
	serialNumber = res[1];

	return true;
}

bool iNova::SetALC(bool AEC, bool AGC) {
	std::string s_AEC, s_AGC;
	AEC ? s_AEC = "ON" : s_AEC = "OFF";
	AGC ? s_AGC = "ON" : s_AGC = "OFF";
	
	std::string message = "SetALC " + s_AEC + " " + s_AGC + " 90 43 33021 0.00000 13.9000 15.0 OFF";
	SendCommand(message);

	return true;
}

bool iNova::GetALC(std::string& AEC, std::string& AGC) {
	std::vector<std::string> res = SendCommand("GetALC");
	if (res[0] != "OK") {
		return false;
	}
	AEC = res[1];
	AGC = res[2];

	return true;
}

bool iNova::SetExposure(std::string value) {
	std::vector<std::string> res = SendCommand("SetExposure " + value);
	if (res[0] != "OK") { return false; }

	return true;
}

bool iNova::SetTotalGain(std::string value) {
	std::vector<std::string> res = SendCommand("SetTotalGain " + value);
	if (res[0] != "OK") { return false; }

	return true;
}