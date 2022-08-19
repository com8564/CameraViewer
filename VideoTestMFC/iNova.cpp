#include "pch.h"
#include "iNova.h"

bool iNova::connectCamera(char* szServerName, WORD streamingPort, WORD commandPort) {
	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
		printf("WSAStartup failed.\n");
		system("pause");
	}

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
			return false;
		}
	}

	if (commandPort != 0) {
		commandSocket = socket(AF_INET, SOCK_STREAM, 0);
		if (commandSocket == INVALID_SOCKET) { return false; }

		struct sockaddr_in server;
		inet_pton(AF_INET, szServerName, &server.sin_addr.s_addr); //inet_addr() is only supporting IPv4 but inet_pton() support both IPv4 and IPv6 
		//server.sin_addr.s_addr = inet_addr(szServerName);
		server.sin_family = AF_INET;
		server.sin_port = htons(streamingPort);

		if (connect(commandSocket, (SOCKADDR*)&server, sizeof(server))) {
			closesocket(commandSocket);
			return false;
		}
	}

	return true;
}

bool iNova::disconnectCamera() {
	if (streamingSocket != 0) {
		closesocket(streamingSocket);
	}
	if (commandSocket != 0) {
		closesocket(commandSocket);
	}

	WSACleanup();
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

uchar* iNova::get_ImageBuf(SOCKET Socket) {
	int count = 0;
	long rc;
	cv::Mat decodedImage;
	if (imgSize < 0 || imgSize > MAX_JPEG_SIZE) { return decodedImage.data; }

	unsigned char* jpegImgbuf = new unsigned char[imgSize];
	
	while (count < imgSize) {
		rc = recv(Socket, (char*)jpegImgbuf + count, imgSize - count, 0);
		if (rc > 0) { count += rc; }
		else { continue; }
	}

	if (jpegImgbuf[imgSize - 2] == 0xff && jpegImgbuf[imgSize - 1] == 0xd9) {
		cv::Mat rawData(1, imgSize, CV_8UC1, (void*)jpegImgbuf);
		decodedImage = cv::imdecode(rawData, 1);
	}

	imgSize = -1;
	delete[] jpegImgbuf;

	return decodedImage.data;
}

uchar* iNova::get_Image() {
	get_ImgSize(streamingSocket);
	return get_ImageBuf(streamingSocket);
}

std::vector<std::string> iNova::SendCommand(std::string message) {
	std::vector<std::string> result;
	if (commandSocket == 0) {
		result.push_back("NG");
		return result;
	}

	message += "\r\n";
	char commandMSG[100];
	strcpy_s(commandMSG, 100, message.c_str());

	char recvbuf[100];
	memset(recvbuf, 0, 100);
	send(commandSocket, commandMSG, message.length(), 0);
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
			std::replace(result.begin(), result.end(), std::string("\r\n"), std::string(""));
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