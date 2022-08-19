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

bool iNova::connectCamera(char* szServerName) {
	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
		printf("WSAStartup failed.\n");
		system("pause");
	}
	bool success = true;

	streamingSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (streamingSocket == INVALID_SOCKET) { return false; }

	struct sockaddr_in streamingserver;
	inet_pton(AF_INET, szServerName, &streamingserver.sin_addr.s_addr); //inet_addr() is only supporting IPv4 but inet_pton() support both IPv4 and IPv6 
	//server.sin_addr.s_addr = inet_addr(szServerName);
	streamingserver.sin_family = AF_INET;
	streamingserver.sin_port = htons(1334);

	if (connect(streamingSocket, (SOCKADDR*)&streamingserver, sizeof(streamingserver))) {
		closesocket(streamingSocket);
		success = false;
	}

	commandSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (commandSocket == INVALID_SOCKET) { return false; }

	struct sockaddr_in commandserver;
	inet_pton(AF_INET, szServerName, &commandserver.sin_addr.s_addr); //inet_addr() is only supporting IPv4 but inet_pton() support both IPv4 and IPv6 
	//server.sin_addr.s_addr = inet_addr(szServerName);
	commandserver.sin_family = AF_INET;
	commandserver.sin_port = htons(1335);

	if (connect(commandSocket, (SOCKADDR*)&commandserver, sizeof(commandserver))) {
		closesocket(commandSocket);
		success = false;
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

bool iNova::GetALC(bool AEC, bool AGC) {
	std::vector<std::string> res = SendCommand("GetALC");
	if (res[0] != "OK") {
		return false;
	}
	res[1] == "ON" ? AEC = true : AEC = false;
	res[2] == "ON" ? AGC = true : AGC = false;

	return true;
}

bool iNova::SetExposure(int val) {
	std::string value = std::to_string(val);
	std::vector<std::string> res = SendCommand("SetExposure " + value);
	if (res[0] != "OK") { return false; }

	return true;
}

bool iNova::SetTotalGain(int val) {
	std::string value = std::to_string(val);
	std::vector<std::string> res = SendCommand("SetTotalGain " + value);
	if (res[0] != "OK") { return false; }

	return true;
}

bool iNova::GetExposure(std::string& exposureVal) {
	std::vector<std::string> res = SendCommand("GetExposure");
	if (res[0] != "OK") { return false; }
	exposureVal = res[1];

	return true;
}