
// VideoTestMFCDlg.h : header file
//
#pragma once
#include "iNova.h"

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
	bool m_clickedSaveImage = false, m_keepGrab = false;
	novitec::Event m_threadFinished;
	SOCKET videoSocket, commandSocket;
	Mutex m;
	char server[35];
	int height = 1080, width = 1920, bpp = 3;
	int m_left, m_right, m_top, m_bottom;

	bool aec, agc;
	int min_exp, max_exp;
	float min_gain, max_gain;

	CSliderCtrl m_gainSlider, m_ExposureSlider;
	CEdit m_gainVal, m_expVal;
	CButton m_autoEXP, m_autoGain, m_checkGray, m_checkSharpen, m_mosaic, m_play, m_stop;
	iNova inova;
	CStatic m_cameraView;
	CEdit m_minexp, m_maxexp, m_mingain, m_maxgain;

	static unsigned int GrabThreadProc(void *param);
	int GrabLoop(void);
	void DrawImage(CWnd *wnd, int width, int height, int bpp, const unsigned char *buffer);
	bool SaveBMP24(const char* filename, int height, int width, int bpp, unsigned char* pBmpImage);
	BOOL PreTranslateMessage(MSG* pMsg);
	
	bool Sharpen(uchar* rgbImage);
	bool Mosaic(uchar* rgbImage, int size);
	bool GrayScale(uchar* rgbImage);

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

public:
	CWinThread* pThread;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnNMCustomdrawSlider1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnEnChangeEdit3();
	afx_msg void OnBnClickedCheckAutoExp();
	afx_msg void OnNMCustomdrawSliderGainSlider(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBnClickedCheckAutoGain();
	afx_msg void OnEnChangeEditGainVal();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	
	afx_msg void OnEnChangeEditMinexp();
};
