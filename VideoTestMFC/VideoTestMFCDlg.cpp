
// VideoTestMFCDlg.cpp : implementation file
//
#include "pch.h"
#include "framework.h"
#include "VideoTestMFC.h"
#include "VideoTestMFCDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#include <afxpriv.h>
#include <fstream>

// CAboutDlg dialog used for App About
#define MAX_JPEG_SIZE (500 * 1024)

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CVideoTestMFCDlg dialog



CVideoTestMFCDlg::CVideoTestMFCDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_VIDEOTESTMFC_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

}

void CVideoTestMFCDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SLIDER1, m_ExposureSlider);
	DDX_Control(pDX, IDC_CHECK_AUTO_EXP, m_autoEXP);
	DDX_Control(pDX, IDC_CHECK_AUTO_GAIN, m_autoGain);
	DDX_Control(pDX, IDC_EDIT_EXP_VAL, m_expVal);
	DDX_Control(pDX, IDC_SLIDER_GAIN_SLIDER, m_gainSlider);
	DDX_Control(pDX, IDC_EDIT_GAIN_VAL, m_gainVal);
	DDX_Control(pDX, IDC_CHECK_GRAY, m_checkGray);
	DDX_Control(pDX, IDC_CHECK_SHARPEN, m_checkSharpen);
	DDX_Control(pDX, IDC_CHECK_MOSAIC, m_mosaic);
	DDX_Control(pDX, IDC_BUTTON_PLAY, m_play);
	DDX_Control(pDX, IDC_BUTTON_STOP, m_stop);
	DDX_Control(pDX, IDC_CAMERA_VIEW, m_cameraView);
	DDX_Control(pDX, IDC_EDIT_MINEXP, m_minexp);
	DDX_Control(pDX, IDC_EDIT_MAXEXP, m_maxexp);
	DDX_Control(pDX, IDC_EDIT_MINGAIN, m_mingain);
	DDX_Control(pDX, IDC_EDIT_MAXGAIN, m_maxgain);
}

BEGIN_MESSAGE_MAP(CVideoTestMFCDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CVideoTestMFCDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON4, &CVideoTestMFCDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON2, &CVideoTestMFCDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON5, &CVideoTestMFCDlg::OnBnClickedButton5)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER1, &CVideoTestMFCDlg::OnNMCustomdrawSlider1)
	ON_EN_CHANGE(IDC_EDIT_EXP_VAL, &CVideoTestMFCDlg::OnEnChangeEdit3)
	ON_BN_CLICKED(IDC_CHECK_AUTO_EXP, &CVideoTestMFCDlg::OnBnClickedCheckAutoExp)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_GAIN_SLIDER, &CVideoTestMFCDlg::OnNMCustomdrawSliderGainSlider)
	ON_BN_CLICKED(IDC_CHECK_AUTO_GAIN, &CVideoTestMFCDlg::OnBnClickedCheckAutoGain)
	ON_EN_CHANGE(IDC_EDIT_GAIN_VAL, &CVideoTestMFCDlg::OnEnChangeEditGainVal)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_EN_CHANGE(IDC_EDIT_MINEXP, &CVideoTestMFCDlg::OnEnChangeEditMinexp)
END_MESSAGE_MAP()


// CVideoTestMFCDlg message handlers

BOOL CVideoTestMFCDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	CWnd *win = GetDlgItem(IDC_EDIT1);
	win->SetWindowTextW(L"192.168.0.156");
	win = GetDlgItem(IDC_EDIT2);
	win->SetWindowTextW(L"Enter Command");
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CVideoTestMFCDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CVideoTestMFCDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CVideoTestMFCDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

unsigned int CVideoTestMFCDlg::GrabThreadProc(void *param)
{
	((CVideoTestMFCDlg*)param)->GrabLoop();
	return 0;
}

int CVideoTestMFCDlg::GrabLoop(void)
{
	CWnd *pView = GetDlgItem(IDC_CAMERA_VIEW);
	CDC *pDC = pView->GetDC();

	uchar* rgbBuffer = new unsigned char[width * height * bpp];
	int y = 0;
	clock_t startTime = clock();

	while (m_keepGrab)
	{
		//Draw camera image
		inova.Get_Image(rgbBuffer);

		if (m_checkSharpen.GetCheck() == 1) {
			Sharpen(rgbBuffer);
		}

		if (m_mosaic.GetCheck() == 1) {
			Mosaic(rgbBuffer);
		}

		if (m_checkGray.GetCheck() == 1) {			
			GrayScale(rgbBuffer);
		}

		DrawImage(pView, width, height, 3, rgbBuffer);

		if (m_clickedSaveImage) {
			SaveBMP24("../save.bmp", height, width, 3, rgbBuffer);
			m_clickedSaveImage = false;
		}

		clock_t endTime = clock();
		clock_t tempTime = 1000.0f / (float)(endTime - startTime);
		tempTime /= 1.0f;

		CString fps;
		fps.Format(_T("%d"), tempTime);
		SetDlgItemText(IDC_STATIC_FPS, fps);
		startTime = endTime;
	}

	delete[] rgbBuffer;
	// Tell main thread that this thread is finished.
	m_threadFinished.Set();
	return 0;
}


void CVideoTestMFCDlg::DrawImage(CWnd *wnd, int width, int height, int bpp, const unsigned char *buffer)
{
	RECT rect;
	wnd->GetWindowRect(&rect);
	CDC *dc = wnd->GetDC();

	if (bpp == 3) // BGR
	{
		BITMAPINFO bmpinfo;

		memset(&bmpinfo, 0, sizeof(bmpinfo));
		bmpinfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
		bmpinfo.bmiHeader.biBitCount = 24;
		bmpinfo.bmiHeader.biClrImportant = 0;
		bmpinfo.bmiHeader.biClrUsed = 0;
		bmpinfo.bmiHeader.biCompression = BI_RGB;
		bmpinfo.bmiHeader.biWidth = width;
		bmpinfo.bmiHeader.biHeight = -height;
		bmpinfo.bmiHeader.biPlanes = 1;
		bmpinfo.bmiHeader.biSizeImage = 0;
		bmpinfo.bmiHeader.biXPelsPerMeter = 100;
		bmpinfo.bmiHeader.biYPelsPerMeter = 100;

		::SetStretchBltMode(dc->GetSafeHdc(), COLORONCOLOR);
		::StretchDIBits(dc->GetSafeHdc(),
			0,
			0,
			rect.right - rect.left,
			rect.bottom - rect.top,
			0,
			0,
			width,
			height,
			buffer,
			&bmpinfo,
			DIB_RGB_COLORS,
			SRCCOPY);
	}
	else if (bpp == 1) // monochrome.
	{
		char bitmapInfoBuf[sizeof(BITMAPINFO) + 4 * 256];
		BITMAPINFO* pBmpInfo = (BITMAPINFO*)bitmapInfoBuf;

		memset(pBmpInfo, 0, sizeof(BITMAPINFO) + 4 * 256);
		pBmpInfo->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
		pBmpInfo->bmiHeader.biWidth = width;
		pBmpInfo->bmiHeader.biHeight = -height;
		pBmpInfo->bmiHeader.biCompression = BI_RGB;
		pBmpInfo->bmiHeader.biPlanes = 1;
		pBmpInfo->bmiHeader.biBitCount = 8;

		for (int i = 0; i < 256; i++)
		{
			pBmpInfo->bmiColors[i].rgbBlue = i;
			pBmpInfo->bmiColors[i].rgbGreen = i;
			pBmpInfo->bmiColors[i].rgbRed = i;
			pBmpInfo->bmiColors[i].rgbReserved = 255;
		}

		::SetStretchBltMode(dc->GetSafeHdc(), COLORONCOLOR);
		::StretchDIBits(dc->GetSafeHdc(),
			0,
			0,
			rect.right - rect.left,
			rect.bottom - rect.top,
			0,
			0,
			width,
			height,
			buffer,
			pBmpInfo,
			DIB_RGB_COLORS,
			SRCCOPY);
	}

	wnd->ReleaseDC(dc);
}

// "Play" is pressed.
void CVideoTestMFCDlg::OnBnClickedButton1()
{
	// TODO: Insert your initialization for camera, codec, etc.
	CWnd* win = GetDlgItem(IDC_EDIT1);
	CString item;
	win->GetWindowTextW(item);
	USES_CONVERSION;
	strcpy_s(server, sizeof(server), CT2CA(item));
	inova.connectCamera(server);
	
	bool AEC = true;
	bool ALC = true;
	if (inova.GetALC(AEC, ALC, min_exp, max_exp, min_gain, max_gain)) {
		//Exposure state
		if (AEC) {
			m_ExposureSlider.EnableWindow(0);
			m_autoEXP.SetCheck(1);
			m_expVal.SendMessage(EM_SETREADONLY, (WPARAM)TRUE, (LPARAM)0);
			m_minexp.SendMessage(EM_SETREADONLY, (WPARAM)TRUE, (LPARAM)0);
			m_maxexp.SendMessage(EM_SETREADONLY, (WPARAM)TRUE, (LPARAM)0);
		}
		else {
			m_ExposureSlider.EnableWindow(1);
			m_autoEXP.SetCheck(0);
			m_expVal.SendMessage(EM_SETREADONLY, (WPARAM)FALSE, (LPARAM)0);
			m_minexp.SendMessage(EM_SETREADONLY, (WPARAM)FALSE, (LPARAM)0);
			m_maxexp.SendMessage(EM_SETREADONLY, (WPARAM)FALSE, (LPARAM)0);
		}

		//Gain state
		if (ALC) {
			m_gainSlider.EnableWindow(0);
			m_autoGain.SetCheck(1);
			m_gainVal.SendMessage(EM_SETREADONLY, (WPARAM)TRUE, (LPARAM)0);
			m_mingain.SendMessage(EM_SETREADONLY, (WPARAM)TRUE, (LPARAM)0);
			m_maxgain.SendMessage(EM_SETREADONLY, (WPARAM)TRUE, (LPARAM)0);
		}
		else {
			m_gainSlider.EnableWindow(1);
			m_autoGain.SetCheck(0);
			m_gainVal.SendMessage(EM_SETREADONLY, (WPARAM)FALSE, (LPARAM)0);
			m_mingain.SendMessage(EM_SETREADONLY, (WPARAM)FALSE, (LPARAM)0);
			m_maxgain.SendMessage(EM_SETREADONLY, (WPARAM)FALSE, (LPARAM)0);
		}
	}

	if (m_autoEXP.GetCheck() == 0) { //exposure is not automatic
		CWnd* win = GetDlgItem(IDC_EDIT_EXP_VAL);
		CString item;
		win->GetWindowTextW(item);
		int val = _ttoi(item);
		inova.SetExposure(val);
	}

	if (m_autoGain.GetCheck() == 0) { //gain is not automatic
		CWnd* win = GetDlgItem(IDC_EDIT_GAIN_VAL);
		CString item;
		win->GetWindowTextW(item);
		int val = _ttoi(item);
		inova.SetTotalGain(val);

		
	}

	CString str_minexp, str_maxexp;
	str_minexp.Format(_T("%d"), min_exp); //Convert int to CStirng
	m_minexp.SetWindowTextW(str_minexp);
	str_maxexp.Format(_T("%d"), max_exp);
	m_maxexp.SetWindowTextW(str_maxexp);

	CString str_mingain, str_maxgain;
	str_mingain.Format(_T("%f"), min_gain); //Convert float to CStirng
	m_mingain.SetWindowTextW(str_mingain);
	str_maxgain.Format(_T("%f"), max_gain);
	m_maxgain.SetWindowTextW(str_maxgain);

	std::string serialNumber;
	if (inova.GetSerialNumber(serialNumber)) {
		//Convert std::string to LPCTSRT
		std::wstring temp = std::wstring(serialNumber.begin(), serialNumber.end());
		LPCTSTR wideString = temp.c_str();

		SetDlgItemText(IDC_STATIC_SERIAL, wideString);
	}

	int exposureVal;
	if (inova.GetExposure(exposureVal)) {
		//Convert std::string to LPCTSRT
		CString strNum; 
		strNum.Format(_T("%d"), exposureVal);
		SetDlgItemText(IDC_EDIT_EXP_VAL, strNum);

		inova.SetExposure(exposureVal);
		m_ExposureSlider.SetPos(exposureVal);
	}

	//unenable play button , enable stop button
	GetDlgItem(IDC_BUTTON_PLAY)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_STOP)->EnableWindow(TRUE);

	m_keepGrab = true;
	pThread = AfxBeginThread(GrabThreadProc, this);
}

// "stop" is pressed
void CVideoTestMFCDlg::OnBnClickedButton4()
{
	if (!m_keepGrab) return; // thread not running?

	m_keepGrab = false;
	m_threadFinished.Wait(1000);

	//enable play button, unenable stop button
	GetDlgItem(IDC_BUTTON_PLAY)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_STOP)->EnableWindow(FALSE);
	inova.disconnectCamera();
}

// Param1 "Set" is pressed
void CVideoTestMFCDlg::OnBnClickedButton2()
{
	// TODO: Add your control notification handler code here
	CWnd* win;
	CString item;

	win = GetDlgItem(IDC_EDIT2);
	win->GetWindowTextW(item);

	//send command message
	/*std::vector<CString> success = SendCommand(server, item);
	if (success[0]=="OK") { MessageBox(L"success"); }
	else { MessageBox(L"Fail"); }*/
}

void CVideoTestMFCDlg::OnBnClickedButton5()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_clickedSaveImage = true;
}


void CVideoTestMFCDlg::OnNMCustomdrawSlider1(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_ExposureSlider.SetRange(43, 33021);
	int iPos;
	iPos = m_ExposureSlider.GetPos();
	SetDlgItemInt(IDC_EDIT_EXP_VAL, iPos);

	*pResult = 0;
}


void CVideoTestMFCDlg::OnEnChangeEdit3()
{
	if (m_keepGrab && m_autoEXP.GetCheck() == 0) {
		CWnd* win = GetDlgItem(IDC_EDIT_EXP_VAL);
		CString item;
		win->GetWindowTextW(item);
		int val = _ttoi(item);
		inova.SetExposure(val);
	}
}

void CVideoTestMFCDlg::OnBnClickedCheckAutoExp()
{
	if (m_keepGrab) {//camera is running
		if (m_autoEXP.GetCheck() == 1) {//exposure is auto
			m_ExposureSlider.EnableWindow(0);
			m_expVal.SendMessage(EM_SETREADONLY, (WPARAM)TRUE, (LPARAM)0);
			m_minexp.SendMessage(EM_SETREADONLY, (WPARAM)TRUE, (LPARAM)0);
			m_maxexp.SendMessage(EM_SETREADONLY, (WPARAM)TRUE, (LPARAM)0);
			aec = true;

			if (m_autoGain.GetCheck() == 1) {//gain is auto
				agc = true;
			}
			else {
				m_mingain.SendMessage(EM_SETREADONLY, (WPARAM)FALSE, (LPARAM)0);
				m_maxgain.SendMessage(EM_SETREADONLY, (WPARAM)FALSE, (LPARAM)0);
				agc = false;

				CString str_mingain, str_maxgain;
				str_mingain.Format(_T("%d"), min_exp); //Convert int to CStirng
				m_minexp.SetWindowTextW(str_mingain);

				str_maxgain.Format(_T("%d"), max_exp);
				m_maxexp.SetWindowTextW(str_maxgain);
			}
		}

		else {
			m_ExposureSlider.EnableWindow(1);
			m_expVal.SendMessage(EM_SETREADONLY, (WPARAM)FALSE, (LPARAM)0);
			m_minexp.SendMessage(EM_SETREADONLY, (WPARAM)FALSE, (LPARAM)0);
			m_maxexp.SendMessage(EM_SETREADONLY, (WPARAM)FALSE, (LPARAM)0);

			CString str_minexp, str_maxexp;
			str_minexp.Format(_T("%d"), min_exp); //Convert int to CStirng
			m_minexp.SetWindowTextW(str_minexp);

			str_maxexp.Format(_T("%d"), max_exp);
			m_maxexp.SetWindowTextW(str_maxexp);

			aec = false;

			if (m_autoGain.GetCheck() == 1) {
				agc = true;
			}
			else {
				m_mingain.SendMessage(EM_SETREADONLY, (WPARAM)FALSE, (LPARAM)0);
				m_maxgain.SendMessage(EM_SETREADONLY, (WPARAM)FALSE, (LPARAM)0);
				agc = false;

				CString str_mingain, str_maxgain;
				str_mingain.Format(_T("%d"), min_exp); //Convert int to CStirng
				m_minexp.SetWindowTextW(str_mingain);

				str_maxgain.Format(_T("%d"), max_exp);
				m_maxexp.SetWindowTextW(str_maxgain);				
			}
		}

		CString val;
		m_minexp.GetWindowTextW(val);
		min_exp = _ttoi(val);
		m_maxexp.GetWindowTextW(val);
		max_exp = _ttoi(val);

		m_mingain.GetWindowTextW(val);
		min_gain = _ttof(val);
		m_maxgain.GetWindowTextW(val);
		max_gain = _ttof(val);

		inova.SetALC(aec, agc, min_exp, max_exp, min_gain, max_gain);
	}
}

BOOL CVideoTestMFCDlg::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_KEYDOWN && (pMsg->wParam == VK_ESCAPE || pMsg->wParam == VK_RETURN)) {
		if (m_keepGrab && m_autoEXP.GetCheck() == 0) {
			CString value;
			m_expVal.GetWindowTextW(value);
			int iPos = _ttoi(value);
			m_ExposureSlider.SetPos(iPos);
		}

		if (m_keepGrab && m_autoGain.GetCheck() == 0) {
			CString value;
			m_gainVal.GetWindowTextW(value);
			int iPos = _tstof(value);
			m_gainSlider.SetPos(iPos);
		}

		if (GetDlgItem(IDC_EDIT_MINEXP) == GetFocus())
		{
			CString val;
			m_minexp.GetWindowTextW(val);
			min_exp = _ttoi(val);
			inova.SetALC(aec, agc, min_exp, max_exp, min_gain, max_gain);
		}

		if (GetDlgItem(IDC_EDIT_MAXEXP) == GetFocus())
		{
			CString val;
			m_maxexp.GetWindowTextW(val);
			max_exp = _ttoi(val);
			inova.SetALC(aec, agc, min_exp, max_exp, min_gain, max_gain);
		}

		if (GetDlgItem(IDC_EDIT_MINGAIN) == GetFocus())
		{
			CString val;
			m_mingain.GetWindowTextW(val);
			min_gain = _ttoi(val);
			inova.SetALC(aec, agc, min_exp, max_exp, min_gain, max_gain);
		}

		if (GetDlgItem(IDC_EDIT_MAXGAIN) == GetFocus())
		{
			CString val;
			m_maxgain.GetWindowTextW(val);
			max_gain = _ttoi(val);
			inova.SetALC(aec, agc, min_exp, max_exp, min_gain, max_gain);
		}
		return TRUE;
	}
		
	return CDialog::PreTranslateMessage(pMsg);
}

void CVideoTestMFCDlg::OnNMCustomdrawSliderGainSlider(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	m_gainSlider.SetRange(0.00000, 13.90000);
	int iPos;
	iPos = m_gainSlider.GetPos();
	SetDlgItemInt(IDC_EDIT_GAIN_VAL, iPos);

	*pResult = 0;
}

void CVideoTestMFCDlg::OnBnClickedCheckAutoGain()
{
	//// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (m_keepGrab) {
		if (m_autoGain.GetCheck() == 1) {//gain is auto
			m_gainSlider.EnableWindow(0);
			m_gainVal.SendMessage(EM_SETREADONLY, (WPARAM)TRUE, (LPARAM)0);
			m_mingain.SendMessage(EM_SETREADONLY, (WPARAM)TRUE, (LPARAM)0);
			m_maxgain.SendMessage(EM_SETREADONLY, (WPARAM)TRUE, (LPARAM)0);
			agc = true;

			if (m_autoEXP.GetCheck() == 1) {//exp is auto
				aec = true; 
			}
			else {
				m_minexp.SendMessage(EM_SETREADONLY, (WPARAM)FALSE, (LPARAM)0);
				m_maxexp.SendMessage(EM_SETREADONLY, (WPARAM)FALSE, (LPARAM)0);
				aec = false;

				CString str_minexp, str_maxexp;
				str_minexp.Format(_T("%d"), min_exp); //Convert int to CStirng
				m_minexp.SetWindowTextW(str_minexp);

				str_maxexp.Format(_T("%d"), max_exp);
				m_maxexp.SetWindowTextW(str_maxexp);
			}
		}

		else {
			m_gainSlider.EnableWindow(1);
			m_gainVal.SendMessage(EM_SETREADONLY, (WPARAM)FALSE, (LPARAM)0);
			m_mingain.SendMessage(EM_SETREADONLY, (WPARAM)FALSE, (LPARAM)0);
			m_maxgain.SendMessage(EM_SETREADONLY, (WPARAM)FALSE, (LPARAM)0);
			agc = false;

			CString str_mingain, str_maxgain;
			str_mingain.Format(_T("%f"), min_gain); //Convert int to CStirng
			m_mingain.SetWindowTextW(str_mingain);

			str_maxgain.Format(_T("%f"), max_gain);
			m_maxgain.SetWindowTextW(str_maxgain);

			if (m_autoEXP.GetCheck() == 1) {
				aec = true;
			}
			else {
				m_minexp.SendMessage(EM_SETREADONLY, (WPARAM)FALSE, (LPARAM)0);
				m_maxexp.SendMessage(EM_SETREADONLY, (WPARAM)FALSE, (LPARAM)0);
				aec = false;

				CString str_minexp, str_maxexp;
				str_minexp.Format(_T("%d"), min_exp); //Convert int to CStirng
				m_minexp.SetWindowTextW(str_minexp);

				str_maxexp.Format(_T("%d"), max_exp);
				m_maxexp.SetWindowTextW(str_maxexp);
			}
		}

		CString val;
		m_minexp.GetWindowTextW(val);
		min_exp = _ttoi(val);
		m_maxexp.GetWindowTextW(val);
		max_exp = _ttoi(val);

		m_mingain.GetWindowTextW(val);
		min_gain = _ttof(val);
		m_maxgain.GetWindowTextW(val);
		max_gain = _ttof(val);

		inova.SetALC(aec, agc, min_exp, max_exp, min_gain, max_gain);
	}
}

void CVideoTestMFCDlg::OnEnChangeEditGainVal()
{
	if (m_keepGrab && m_autoGain.GetCheck() == 0) {
		CWnd* win;
		CString item;

		win = GetDlgItem(IDC_EDIT_GAIN_VAL);
		win->GetWindowTextW(item);

		//Convert CString to std::string
		CT2CA convertedString(item);
		std::string val = std::string(convertedString);

		inova.SetTotalGain(stoi(val));
	}
}

bool CVideoTestMFCDlg::Sharpen(uchar* rgbImage) {
	unsigned char* sharpenImage = new unsigned char[width * height * bpp];

	memcpy(sharpenImage, rgbImage, width * height * bpp);
	for (int y = 1; y < height - 1; y++) {
		const uchar* previous = rgbImage + width * (y - 1) * bpp;
		const uchar* current = rgbImage + width * (y) * bpp;
		const uchar* next = rgbImage +  width * (y + 1) * bpp;

		uchar* output = sharpenImage + width * y * bpp;
		for (int x = 0; x <= bpp * (width - 1); x++) {
			if (x < bpp) {
				output++;
			}
			else {
				*output = saturate_cast<uchar>(
					(5 * current[x] - current[x - bpp] - current[x + bpp])
					- (previous[x])
					- (next[x])
					);
				output++;
			}
		}
	}
	memcpy(rgbImage, sharpenImage, width * height * bpp);

	delete[] sharpenImage;
	return true;
}

bool CVideoTestMFCDlg::SaveBMP24(const char* filename, int height, int width, int bpp, unsigned char* pBmpImage) {
	if (bpp != 1 && bpp != 3 && bpp != 4) {
		return false;
	}

	FILE* fp = NULL;
	BITMAPFILEHEADER bfh;
	BITMAPINFOHEADER bih;
	memset(&bfh, 0, sizeof(BITMAPFILEHEADER));
	memset(&bih, 0, sizeof(BITMAPINFOHEADER));

	int paddingSize = width % 4;

	bfh.bfType = 0x4d42;
	bfh.bfSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + (width * height * bpp + height * paddingSize);
	bfh.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
	if (bpp == 1)
	{
		bfh.bfSize += (256 * 4);
		bfh.bfOffBits += (256 * 4);
	}
	bih.biSize = sizeof(BITMAPINFOHEADER);
	bih.biWidth = width;
	bih.biHeight = -height;
	bih.biPlanes = 1;
	bih.biBitCount = bpp * 8;
	bih.biSizeImage = (width * height * bpp + height * paddingSize);
	bih.biXPelsPerMeter = 2834;
	bih.biYPelsPerMeter = 2834;

	if (fopen_s(&fp, filename, "wb") != 0) {
		return false;
	}
	fwrite(&bfh, sizeof(BITMAPFILEHEADER), 1, fp);
	fwrite(&bih, sizeof(BITMAPINFOHEADER), 1, fp);

	if (paddingSize == 0) {
		fwrite(pBmpImage, width * height * bpp, 1, fp);
	}
	else {
		unsigned char arrPad[3] = { 0,0,0 };
		int widthInBytes = width * 3;

		for (int i = 0; i < height; i++) {
			fwrite(pBmpImage + (i * widthInBytes), 3, bih.biWidth, fp);
			fwrite(arrPad, paddingSize, 1, fp);
		}
	}
	fclose(fp);
	return true;
}

void CVideoTestMFCDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CRect m_Pic;
	GetDlgItem(IDC_CAMERA_VIEW)->GetWindowRect(m_Pic);
	ScreenToClient(m_Pic);
	if (m_keepGrab && m_mosaic.GetCheck() == 1) {
		if (m_Pic.left < point.x && m_Pic.top < point.y && m_Pic.right > point.x && m_Pic.bottom > point.y) {
			m_left = point.x;
			m_top = point.y;
		}
	}
	else if (m_keepGrab && m_mosaic.GetCheck() == 0) {
		m_right = 0;
		m_bottom = 0;
	}

	CDialogEx::OnLButtonDown(nFlags, point);
}

void CVideoTestMFCDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CRect m_Pic;
	GetDlgItem(IDC_CAMERA_VIEW)->GetWindowRect(m_Pic);
	ScreenToClient(m_Pic);
	if (m_keepGrab && m_mosaic.GetCheck()==1) {
		if (m_Pic.left < point.x && m_Pic.top < point.y && m_Pic.right > point.x && m_Pic.bottom > point.y) {
			m_right = point.x;
			m_bottom = point.y;
		}
		else {
			m_right = m_Pic.right;
			m_bottom = m_Pic.bottom;
		}
	}
	else if(m_keepGrab && m_mosaic.GetCheck()==0){
		m_right = 0;
		m_bottom = 0;
	}

	CDialogEx::OnLButtonUp(nFlags, point);
}

bool CVideoTestMFCDlg::Mosaic(uchar* rgbImage) {
	unsigned char* mosaicImage = new unsigned char[width * height * bpp];
	CRect m_Pic;
	GetDlgItem(IDC_CAMERA_VIEW)->GetWindowRect(m_Pic);
	ScreenToClient(m_Pic);

	int y_ratio = height / (m_Pic.bottom - m_Pic.top);
	int x_ratio = width / (m_Pic.right - m_Pic.left);

	memcpy(mosaicImage, rgbImage, width * height * bpp);
	for (int y = (m_top - m_Pic.top) * y_ratio; y < (m_bottom - m_Pic.top - 1) * y_ratio; y++) {
		int x_col = (m_left - m_Pic.left) * 3 * x_ratio;
		x_col -= x_col % 3;
		for (int x = x_col; x <= bpp * (m_right - m_Pic.left - 1) * x_ratio; x+=3) {

			for (int j = y; j < y+3; j++) {
				for (int i = x; i < x+3; i++) {
					mosaicImage[j * width * bpp + i];
					mosaicImage[j * width * bpp + i + 1];
					mosaicImage[j * width * bpp + i + 2];
				}
			}

		}
	}
	memcpy(rgbImage, mosaicImage, width * height * bpp);

	delete[] mosaicImage;
	return true;
}

bool CVideoTestMFCDlg::GrayScale(uchar* rgbImage) {
	unsigned char* grayImage = new unsigned char[width * height * bpp];
	for (int y = 0; y < height - 1; y++) {
		for (int x = 0; x < (width - 1) * bpp; x += bpp) {
			unsigned char r, g, b;
			r = rgbImage[(y * width * 3) + x + 2];
			g = rgbImage[(y * width * 3) + x + 1];
			b = rgbImage[(y * width * 3) + x + 0];

			unsigned char val = (0.299 * r) + (0.587 * g) + (0.114 * b);
			grayImage[(y * width * 3) + x + 0] = val;
			grayImage[(y * width * 3) + x + 1] = val;

			grayImage[(y * width * 3) + x + 2] = val;
		}
	}
	memcpy(rgbImage, grayImage, width * height * bpp);

	delete[] grayImage;
	return true;
}

void CVideoTestMFCDlg::OnEnChangeEditMinexp()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
}
