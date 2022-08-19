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
	int imgSize = -1;
	SOCKET streamingSocket;
	SOCKET commandSocket;

	void get_ImgSize(SOCKET Socket);
	uchar* get_ImageBuf(SOCKET Socket);
protected:
	std::vector<std::string> SendCommand(std::string message);

public:
	bool connectCamera(char* szServerName, WORD streamingPort=0, WORD commandPort=0);
	bool disconnectCamera();
	uchar* get_Image();
	bool GetAutoExposureMode(std::string& exposureMode);
	bool GetAutoGainMode(std::string& gainMode);

};

