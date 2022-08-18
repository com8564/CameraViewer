
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

	rgbBuffer = new unsigned char[width * height * bpp];
	unsigned char* grayBuffer = new unsigned char[width * height];
	int y = 0;
	clock_t startTime = clock();
	
	while (m_keepGrab)
	{
		//Draw camera image
		int imgSize = get_ImgSize(videoSocket);
		get_Image(videoSocket, imgSize, rgbBuffer);

		if (m_checkSharpen.GetCheck() == 1) {
			Sharpen(rgbBuffer);
		}

		if (m_checkGray.GetCheck() == 0) {			
			// Draw the buffer on window.
			DrawImage(pView, width, height, 3, rgbBuffer);
		}

		else {
			for (int y = 0; y < height - 1; y++) {
				int i = 0;
				for (int x = 0; x < (width - 1) * bpp; x += bpp) {
					unsigned char r, g, b;
					r = rgbBuffer[(y * width * 3) + x + 2];
					g = rgbBuffer[(y * width * 3) + x + 1];
					b = rgbBuffer[(y * width * 3) + x + 0];
					grayBuffer[(width * y) + (x - (2 * i))] = 0.299 * r + 0.587 * g + 0.114 * b;
					i++;
				}
			}
			DrawImage(pView, width, height, 1, grayBuffer);
		}

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
		::Sleep(10); // need this to avoid tight-loop.
		count = 0;
		startTime = endTime;
	}

	delete[] rgbBuffer;
	delete[] grayBuffer;
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
	videoSocket = connectToServer(server, 1334);
	if (videoSocket == NULL) { return; }

	std::vector<CString> recv = SendCommand(server, L"GetALC"); //Get camera setting
	if (recv[0] != "OK") { return; }

	//Exposure state
	if (recv[1] == "ON") {
		m_ExposureSlider.EnableWindow(0);
		m_autoEXP.SetCheck(1);
		m_expVal.SendMessage(EM_SETREADONLY, (WPARAM)TRUE, (LPARAM)0);
	}
	else {
		m_ExposureSlider.EnableWindow(1);
		m_autoEXP.SetCheck(0);
		m_expVal.SendMessage(EM_SETREADONLY, (WPARAM)FALSE, (LPARAM)0);
	}

	//Gain state
	if (recv[2] == "ON") {
		m_gainSlider.EnableWindow(0);
		m_autoGain.SetCheck(1);
		m_gainVal.SendMessage(EM_SETREADONLY, (WPARAM)TRUE, (LPARAM)0);
	}
	else {
		m_gainSlider.EnableWindow(1);
		m_autoGain.SetCheck(0);
		m_gainVal.SendMessage(EM_SETREADONLY, (WPARAM)FALSE, (LPARAM)0);
	}

	CString command;
	if (m_autoEXP.GetCheck() == 1) { //exposure is not automatic
		CWnd* win = GetDlgItem(IDC_EDIT_EXP_VAL);
		CString item;
		win->GetWindowTextW(item);
		command = L"SetExposure ";
		command += item;
		
	}
	if (m_autoGain.GetCheck() == 1) { //gain is not automatic
		CWnd* win = GetDlgItem(IDC_EDIT_GAIN_VAL);
		CString item;
		win->GetWindowTextW(item);

		command = L"SetTotalGain ";
		command += item;
	}

	SendCommand(server, command);
	recv = SendCommand(server, L"GetSerialNumber");

	if (recv[0] == "OK") {
		SetDlgItemText(IDC_STATIC_SERIAL, recv[1]);
	}

	m_keepGrab = true;
	pThread = AfxBeginThread(GrabThreadProc, this);
}

// "stop" is pressed
void CVideoTestMFCDlg::OnBnClickedButton4()
{
	if (!m_keepGrab) return; // thread not running?

	m_keepGrab = false;
	m_threadFinished.Wait(1000);
	// TODO: Insert your clean up code for camera, codec, etc.
	// CloseCamera()...
	closesocket(videoSocket);
	WSACleanup();
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
	std::vector<CString> success = SendCommand(server, item);
	if (success[0]=="OK") { MessageBox(L"success"); }
	else { MessageBox(L"Fail"); }
}

SOCKET CVideoTestMFCDlg::connectToServer(char* szServerName, WORD portNum)
{
	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
		printf("WSAStartup failed.\n");
		system("pause");
	}

	struct hostent* host;
	unsigned int addr;
	struct sockaddr_in server;
	SOCKET conn;

	conn = socket(AF_INET, SOCK_STREAM, 0);
	if (conn == INVALID_SOCKET) { return NULL; }

	InetPton(AF_INET, CA2CT(szServerName), &server.sin_addr.s_addr); //inet_addr() is only supporting IPv4 but InetPton() support both IPv4 and IPv6 
	server.sin_family = AF_INET;
	server.sin_port = htons(portNum);

	if (connect(conn, (SOCKADDR*)&server, sizeof(server))) {
		closesocket(conn);
		return NULL;
	}

	return conn;
}

int CVideoTestMFCDlg::get_ImgSize(SOCKET& Socket) {
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

bool CVideoTestMFCDlg::get_Image(SOCKET Socket, int imgSize, unsigned char* buffer) {
	int count = 0;
	long rc;
	if (imgSize < 0 || imgSize > MAX_JPEG_SIZE) { return false; }

	unsigned char* jpegImgbuf = new unsigned char[imgSize];

	while (count < imgSize) {
		rc = recv(Socket, (char*)jpegImgbuf + count, imgSize - count, 0);
		if (rc > 0) { count += rc; }
		else { continue; }
	}
	bool result = false;

	if (jpegImgbuf[imgSize - 2] == 0xff && jpegImgbuf[imgSize - 1] == 0xd9) {
		Mat rawData(1, imgSize, CV_8UC1, (void*)jpegImgbuf);
		Mat decodedImage = imdecode(rawData, 1);
		memcpy(buffer, decodedImage.data, width * height * bpp);
		result = true;
	}

	delete[] jpegImgbuf;
	return result;
}

std::vector<CString> CVideoTestMFCDlg::SendCommand(char* server, CString message) {
	commandSocket = connectToServer(server, 1335);
	message += "\r\n";
	char commandMSG[100];
	strcpy_s(commandMSG, sizeof(commandMSG), CT2CA(message));

	char recvbuf[100];
	memset(recvbuf, 0, 100);
	send(commandSocket, commandMSG, message.GetLength(), 0);
	recv(commandSocket, recvbuf, sizeof(recvbuf), 0);
	std::vector<CString> result;

	CString temp;
	int i = 0;
	while (recvbuf[i]!=0) {
		AfxExtractSubString(temp, (CString)recvbuf, i, ' ');
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
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.

	if (m_keepGrab && m_autoEXP.GetCheck() == 0) {
		CWnd* win = GetDlgItem(IDC_EDIT_EXP_VAL);
		CString item;
		win->GetWindowTextW(item);

		CString command = L"SetExposure ";
		command += item;
		SendCommand(server, command);
	}
}

void CVideoTestMFCDlg::OnBnClickedCheckAutoExp()
{
	if (m_keepGrab) {//camera is running
		CString command = NULL;
		
		if (m_autoEXP.GetCheck() == 1) {//exposure is auto
			m_ExposureSlider.EnableWindow(0);
			m_expVal.SendMessage(EM_SETREADONLY, (WPARAM)TRUE, (LPARAM)0);

			if (m_autoGain.GetCheck() == 1) {//gain is auto
				command = L"SetALC ON ON 90 43 33021 0.00000 13.9000 15.0 OFF";
			}
			else {
				command = L"SetALC ON OFF 90 43 33021 0.00000 13.9000 15.0 OFF";
			}
		}

		else {
			m_ExposureSlider.EnableWindow(1);
			m_expVal.SendMessage(EM_SETREADONLY, (WPARAM)FALSE, (LPARAM)0);

			if (m_autoGain.GetCheck() == 1) {
				command = L"SetALC OFF ON 90 43 33021 0.00000 13.9000 15.0 OFF";
			}
			else {
				command = L"SetALC OFF OFF 90 43 33021 0.00000 13.9000 15.0 OFF";
			}
		}

		SendCommand(server, command);
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
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (m_keepGrab) {
		CString command = NULL;
		if (m_autoGain.GetCheck() == 1) {
			m_gainSlider.EnableWindow(0);
			m_gainVal.SendMessage(EM_SETREADONLY, (WPARAM)TRUE, (LPARAM)0);
			if (m_autoEXP.GetCheck() == 1) {
				command = L"SetALC ON ON 90 43 33021 0.00000 13.9000 15.0 OFF";
			}
			else {
				command = L"SetALC OFF ON 90 43 33021 0.00000 13.9000 15.0 OFF";
			}
		}

		else {
			m_gainSlider.EnableWindow(1);
			m_gainVal.SendMessage(EM_SETREADONLY, (WPARAM)FALSE, (LPARAM)0);
			if (m_autoEXP.GetCheck() == 1) {
				command = L"SetALC ON OFF 90 43 33021 0.00000 13.9000 15.0 OFF";
			}
			else {
				command = L"SetALC OFF OFF 90 43 33021 0.00000 13.9000 15.0 OFF";
			}
		}

		SendCommand(server, command);
	}
}

void CVideoTestMFCDlg::OnEnChangeEditGainVal()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.

	if (m_keepGrab && m_autoGain.GetCheck() == 0) {
		CWnd* win;
		CString item;

		win = GetDlgItem(IDC_EDIT_GAIN_VAL);
		win->GetWindowTextW(item);

		CString command = L"SetTotalGain ";
		command += item;
		SendCommand(server, command);
	}
}

bool CVideoTestMFCDlg::Sharpen(uchar* rgbImage) {
	unsigned char* sharpenImage = new unsigned char[width * height * bpp];

	memcpy(sharpenImage, rgbImage, width * height * bpp);
	for (int row = 1; row < height - 1; row++) {

		const uchar* previous = rgbImage + width * (row - 1) * bpp;
		const uchar* current = rgbImage + width * (row) * bpp;
		const uchar* next = rgbImage +  width * (row + 1) * bpp;
		uchar* output = sharpenImage + width * row * bpp;

		for (int col = 0; col <= 3 * (width - 1); col++) {
			*output = saturate_cast<uchar>(
				(5 * current[col] - current[col - bpp] - current[col + bpp])
				- (previous[col])
				- (next[col])
				);
			output++;
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