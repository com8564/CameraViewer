
// VideoTestMFCDlg.h : header file
//
#pragma once
#include <opencv2/imgcodecs.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <WS2tcpip.h>
#include <winsock2.h>
#include <vector>
#pragma comment(lib,"ws2_32.lib")
using namespace cv;

namespace novitec
{
	class Event
	{
	public:
		Event() { m_hEvent = ::CreateEvent(NULL, FALSE, FALSE, NULL); }
		~Event() { ::CloseHandle(m_hEvent); }
		void Set(void) { ::SetEvent(m_hEvent); }
		void Reset(void) { ::ResetEvent(m_hEvent); }
		bool Wait(int timeout) { return (::WaitForSingleObject(m_hEvent, timeout) == 0); }
	private:
		HANDLE m_hEvent;
	};
}

// CVideoTestMFCDlg dialog
class CVideoTestMFCDlg : public CDialogEx
{
// Construction
public:
	CVideoTestMFCDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_VIDEOTESTMFC_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;
	bool m_keepGrab = false;
	novitec::Event m_threadFinished;
	SOCKET videoSocket, commandSocket;
	unsigned char* rgbBuffer = NULL;
	Mutex m;
	bool m_clickedSaveImage = false;
	char server[35];
	int count;
	int height = 1080, width = 1920, bpp = 3;

	CButton m_autoEXP;
	CSliderCtrl m_ExposureSlider;
	CEdit m_expVal;

	CButton m_autoGain;
	CSliderCtrl m_gainSlider;
	CEdit m_gainVal;
	CButton m_checkGray, m_checkSharpen;

	static unsigned int GrabThreadProc(void *param);
	int GrabLoop(void);
	void DrawImage(CWnd *wnd, int width, int height, int bpp, const unsigned char *buffer);
	SOCKET connectToServer(char* szServerName, WORD portNum);
	int get_ImgSize(SOCKET& Socket);
	bool get_Image(SOCKET Socket, int imgSize, unsigned char* decodedImageData);
	std::vector<CString> SendCommand(char* server,CString message);
	BOOL PreTranslateMessage(MSG* pMsg);
	bool Sharpen(uchar* rgbImage);
	bool SaveBMP24(const char* filename, int height, int width, int bpp, unsigned char* pBmpImage);

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton2();
	CWinThread* pThread;
	afx_msg void OnBnClickedButton5();
	afx_msg void OnNMCustomdrawSlider1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnEnChangeEdit3();
	afx_msg void OnBnClickedCheckAutoExp();
	afx_msg void OnNMCustomdrawSliderGainSlider(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBnClickedCheckAutoGain();
	afx_msg void OnEnChangeEditGainVal();
};
