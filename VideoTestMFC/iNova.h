#pragma once
#include <opencv2/imgcodecs.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>

#include <WS2tcpip.h>
#include <winsock2.h>
#include <vector>
#include <string>
#include <sstream>

#pragma comment(lib,"ws2_32.lib")
#define MAX_JPEG_SIZE (500*1024)


class iNova {
private:
protected:
public:
	SOCKET connectCamera(char* szServerName, WORD portNum);
	int get_ImgSize(SOCKET& Socket);
	cv::Mat get_Image(SOCKET Socket, int imgSize);
	std::vector<std::string> SendCommand(char* server, std::string message);
};

