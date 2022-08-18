#include "pch.h"
#include "iNova.h"

SOCKET iNova::connectCamera(char* szServerName, WORD portNum) {
	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
		printf("WSAStartup failed.\n");
		system("pause");
	}

	SOCKET conn;
	conn = socket(AF_INET, SOCK_STREAM, 0);
	if (conn == INVALID_SOCKET) { return NULL; }

	struct sockaddr_in server;
	inet_pton(AF_INET, szServerName, &server.sin_addr.s_addr); //inet_addr() is only supporting IPv4 but inet_pton() support both IPv4 and IPv6 
	//server.sin_addr.s_addr = inet_addr(szServerName);
	server.sin_family = AF_INET;
	server.sin_port = htons(portNum);

	if (connect(conn, (SOCKADDR*)&server, sizeof(server))) {
		closesocket(conn);
		return NULL;
	}
	return conn;
}

int iNova::get_ImgSize(SOCKET& Socket) {
	unsigned char recvbuf[2000];
	int imgSize = -1;

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

	return imgSize;
}

cv::Mat iNova::get_Image(SOCKET Socket, int imgSize) {
	int count = 0;
	long rc;
	cv::Mat decodedImage;
	if (imgSize < 0 || imgSize > MAX_JPEG_SIZE) { return decodedImage; }

	unsigned char* jpegImgbuf = new unsigned char[imgSize];

	while (count < imgSize) {
		rc = recv(Socket, (char*)jpegImgbuf + count, imgSize - count, 0);
		if (rc > 0) { count += rc; }
		else { continue; }
	}
	bool result = false;

	if (jpegImgbuf[imgSize - 2] == 0xff && jpegImgbuf[imgSize - 1] == 0xd9) {
		cv::Mat rawData(1, imgSize, CV_8UC1, (void*)jpegImgbuf);
		decodedImage = imdecode(rawData, 1);
	}

	delete[] jpegImgbuf;
	return decodedImage;
}

std::vector<std::string> iNova::SendCommand(char* server, std::string message) {
	SOCKET commandSocket = connectCamera(server, 1335);
	message += "\r\n";
	char commandMSG[100];
	strcpy(commandMSG, message.c_str());

	char recvbuf[100];
	memset(recvbuf, 0, 100);
	send(commandSocket, commandMSG, message.length(), 0);
	recv(commandSocket, recvbuf, sizeof(recvbuf), 0);
	std::string recv_msg(recvbuf);

	std::vector<std::string> result;
	std::string temp;

	int i = 0;
	while (1) {
		getline(ss, strBuffer, ' ')
		if (temp == "") { break; }
		result.push_back(temp);
		i++;
	}

	if (result.size() > 0) {//Erase CRLF
		result[result.size() - 1].Replace(L"\r\n", L"");
	}

	closesocket(commandSocket);
	return result;
}