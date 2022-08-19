#pragma once
#include <opencv2/imgcodecs.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <WS2tcpip.h>
#include <winsock2.h>
#include <vector>
#include <string>
#include <format>

#pragma comment(lib,"ws2_32.lib")
#define MAX_JPEG_SIZE (500*1024)

class iNova {
private:
	int imgSize;
	SOCKET streamingSocket;
	SOCKET commandSocket;

	void get_ImgSize(SOCKET Socket);
protected:
	std::vector<std::string> SendCommand(std::string message);
public:
	iNova();
	~iNova();

	bool connectCamera(char* szServerName, WORD streamingPort=0, WORD commandPort=0);
	bool disconnectCamera();
	bool Get_Image(uchar* rgbBuffer);
	bool GetAutoExposureMode(std::string& exposureMode);
	bool GetAutoGainMode(std::string& gainMode);
	bool GetFirmwareVersion(std::string& firmwareVersion);
	bool GetSerialNumber(std::string& serialNumber);
	bool SetALC(bool AEC, bool AGC);
	bool GetALC(std::string& AEC, std::string& AGC);
	bool SetExposure(std::string value);
	bool SetTotalGain(std::string value);
};

