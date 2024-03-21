
// viewerDlg.cpp : 구현 파일
//

#include "stdafx.h"
#include "viewer.h"
#include "viewerDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

Mat CviewerDlg::m_matImage;
CRect CviewerDlg::rect;
CPoint CviewerDlg::m_ptStart;
CPoint CviewerDlg::m_ptLastEnd;
bool CviewerDlg::isRaw = false;
bool CviewerDlg::is8bit = false;

// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.



class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
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


CviewerDlg::CviewerDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_VIEWER_DIALOG, pParent)
	, m_bDragging(false)
	, m_bWheel(false)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CviewerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB1, m_tabControl);
	DDX_Control(pDX, IDC_PC_VIEW, m_stPicture);
}

BEGIN_MESSAGE_MAP(CviewerDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_OPEN, &CviewerDlg::OnClickedButtonOpen)
	ON_BN_CLICKED(IDC_BUTTON_RESTORE, &CviewerDlg::OnClickedButtonRestore)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, &CviewerDlg::OnSelchangeTab1)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_MOUSEWHEEL()
END_MESSAGE_MAP()


// CviewerDlg 메시지 처리기

BOOL CviewerDlg::OnInitDialog()
{

	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
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

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.

	pPicControl = (CStatic*)AfxGetMainWnd()->GetDlgItem(IDC_PC_VIEW);
	pPicControl->GetClientRect(&rect); // Picture Control의 크기 얻기

	m_tabFlip.Create(IDD_FLIP, &m_tabControl);
	m_tabRotate.Create(IDD_ROTATE, &m_tabControl);
	m_tabResize.Create(IDD_RESIZE, &m_tabControl);
	m_tabCrop.Create(IDD_CROP, &m_tabControl);

	m_tabControl.InsertItem(0, _T("뒤집기"));		// 탭 생성
	m_tabControl.InsertItem(1, _T("회 전"));
	m_tabControl.InsertItem(2, _T("크기 조절"));
	m_tabControl.InsertItem(3, _T("자르기"));
	m_tabControl.InsertItem(4, _T("휠 확대/축소"));

	m_tabControl.SetCurSel(0);

	CRect rect2;
	m_tabFlip.GetWindowRect(rect2);

	m_tabFlip.MoveWindow(20, 40, rect2.Width(), rect2.Height());
	m_tabFlip.ShowWindow(SW_SHOW);

	m_tabRotate.MoveWindow(20, 40, rect2.Width(), rect2.Height());
	m_tabRotate.ShowWindow(SW_HIDE);

	m_tabResize.MoveWindow(20, 40, rect2.Width(), rect2.Height());
	m_tabResize.ShowWindow(SW_HIDE);

	m_tabCrop.MoveWindow(70, 60, rect2.Width(), rect2.Height());
	m_tabCrop.ShowWindow(SW_HIDE);

	m_tabControl.ShowWindow(SW_HIDE);
	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CviewerDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CviewerDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);

		CRect rect2;
		GetClientRect(&rect2);

		int x = (rect2.Width() - cxIcon + 1) / 2;
		int y = (rect2.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CviewerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CviewerDlg::ShowRawImage(cv::Mat& mat) {

	CImage cImage;
	// 16비트 이미지를 8비트로 변환 (간단한 방법, 실제 사용 시에는 적절한 스케일링 고려)
	cv::Mat convertedMat;
	mat.convertTo(convertedMat, CV_8U, 1.0 / 256.0);

	// CImage 객체 초기화
	cImage.Create(convertedMat.cols, convertedMat.rows, 24);

	// CImage에 데이터 복사
	for (int y = 0; y < convertedMat.rows; y++) {
		char* srcRow = convertedMat.ptr<char>(y);
		for (int x = 0; x < convertedMat.cols; x++) {
			unsigned char val = srcRow[x];
			cImage.SetPixel(x, y, RGB(val, val, val));
		}
	}

	m_stPicture.ModifyStyle(0xF, SS_BITMAP, SWP_NOSIZE);
	HBITMAP hBitmap = (HBITMAP)cImage.Detach();
	m_stPicture.SetBitmap(hBitmap);
}

void CviewerDlg::OnClickedButtonOpen()
{
	CFileDialog fileDlg(TRUE, NULL, NULL, OFN_READONLY, _T("image file(*.jpg;*.bmp;*.png;*.raw;)|*.jpg;*.bmp;*.png;*.raw;|All Files(*.*)|*.*||"));
	if (fileDlg.DoModal() == IDOK)
	{
		CString path = fileDlg.GetPathName();
		CString extension = path.Right(4);
		extension.MakeLower();

		if (extension == _T(".raw"))
		{
			if (raw.DoModal() == IDOK) {

				int h = raw.nHeight;
				int w = raw.nWidth;
				int c = raw.nChannel;
				int t = raw.nType;
				int type;

				//t가 0일 경우 8비트, 1일경우 16비트 
				if (t == 0) {
					is8bit = true;
					if (c == 1) type = CV_8U;
				}
				else if (t == 1) {
					is8bit = false;
					if (c == 1) type = CV_16UC1;
				}else{
					is8bit = true;
					type = CV_8UC3;
				}
				

				cv::Mat image(h, w, type);
				// raw 파일 읽어오기
				std::ifstream input_file(path, std::ios::binary);
				if (!input_file) {
					AfxMessageBox(_T("이미지를 불러올 수 없습니다."));
					return;
				}
				isRaw = true;
				if (t == 0)
					input_file.read(reinterpret_cast<char*>(image.data), w*h * sizeof(uint8_t));
				if (t == 1)
					input_file.read(reinterpret_cast<char*>(image.data), w*h * sizeof(uint16_t));
				m_matImage = image.clone();
				ResizeImageForControl(m_matImage, m_matImage);

				DisplayImageInPictureControl(m_matImage, IDC_PC_VIEW);
			}

		}
		else {
			CT2CA pszString(path);
			std::string strPath(pszString);

			m_matImage = imread(strPath, IMREAD_COLOR);

			if (m_matImage.empty()) // 이미지가 제대로 불러지지 않은 경우
			{
				AfxMessageBox(_T("이미지를 불러올 수 없습니다."));
				return;
			}

			// Picture Control의 크기에 맞게 이미지 조정
			ResizeImageForControl(m_matImage, m_matImage);

			// Picture Control에 이미지 표시
			DisplayImageInPictureControl(m_matImage, IDC_PC_VIEW);
			isRaw = false;
		}
		m_matImage_origin = m_matImage.clone();
		m_tabControl.ShowWindow(SW_SHOW);

	}
}


void CviewerDlg::ResizeImageForControl(Mat& srcImg, Mat& dstImg)
{
	resize(srcImg, dstImg, cv::Size(rect.Width(), rect.Height()));
}


void CviewerDlg::DisplayImageInPictureControl(Mat& img, UINT nID)
{
	CImage cImage;
	if (isRaw == true) {
		// 16비트 이미지를 8비트로 변환 (간단한 방법, 실제 사용 시에는 적절한 스케일링 고려)
		if (!is8bit) {
			cv::Mat convertedMat;
			img.convertTo(convertedMat, CV_8U, 1.0 / 256.0);
			cImage.Create(convertedMat.cols, convertedMat.rows, 24);

			// CImage에 데이터 복사
			for (int y = 0; y < convertedMat.rows; y++) {
				char* srcRow = convertedMat.ptr<char>(y);
				for (int x = 0; x < convertedMat.cols; x++) {
					unsigned char val = srcRow[x];
					cImage.SetPixel(x, y, RGB(val, val, val));
				}
			}
		}
		else {
			cv::Mat convertedMat;

			// 이미지를 8비트로 변환하지 않고 그대로 사용
			img.copyTo(convertedMat);

			cImage.Create(convertedMat.cols, convertedMat.rows, 24);

			// CImage에 데이터 복사
			for (int y = 0; y < convertedMat.rows; y++) {
				char* srcRow = convertedMat.ptr<char>(y);
				for (int x = 0; x < convertedMat.cols; x++) {
					unsigned char val = srcRow[x];
					cImage.SetPixel(x, y, RGB(val, val, val));
				}
			}
		}
	}
	else {
		// CImage에 이미지 데이터 할당을 위해 초기화
		cImage.Create(img.cols, img.rows, 24);

		// cv::Mat에서 CImage로 데이터 복사
		for (int i = 0; i < img.rows; i++)
		{
			for (int j = 0; j < img.cols; j++)
			{
				cv::Vec3b pixel = img.at<cv::Vec3b>(i, j);

				// BGR 포맷을 사용 (OpenCV의 기본)
				BYTE* pDest = reinterpret_cast<BYTE*>(cImage.GetPixelAddress(j, i));
				pDest[0] = pixel[0]; // Blue
				pDest[1] = pixel[1]; // Green
				pDest[2] = pixel[2]; // Red
			}
		}

	}
	CStatic* pPic = (CStatic*)AfxGetMainWnd()->GetDlgItem(nID);

	if (pPic != nullptr)
	{
		// 기존에 표시된 이미지가 있다면 제거
		pPic->ModifyStyle(0xF, SS_BITMAP, SWP_NOSIZE);
		HBITMAP hBitmap = cImage.Detach(); // CImage에서 HBITMAP 얻기
		pPic->SetBitmap(hBitmap); // Picture Control에 비트맵 설정
	}

}


void CviewerDlg::FlipHori()
{
	flip(m_matImage, m_matImage, 1);
	DisplayImageInPictureControl(m_matImage, IDC_PC_VIEW);
}


void CviewerDlg::FlipVert()
{
	flip(m_matImage, m_matImage, 0);
	DisplayImageInPictureControl(m_matImage, IDC_PC_VIEW);
}

void CviewerDlg::OnClickedButtonRestore()
{

	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (m_matImage.empty()) return;
	m_matImage = m_matImage_origin.clone();
	DisplayImageInPictureControl(m_matImage, IDC_PC_VIEW);

}


void CviewerDlg::OnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int nCurSel = m_tabControl.GetCurSel();

	switch (nCurSel)
	{
	case 0:
		m_tabFlip.ShowWindow(SW_SHOW);
		m_tabRotate.ShowWindow(SW_HIDE);
		m_tabResize.ShowWindow(SW_HIDE);
		m_tabCrop.ShowWindow(SW_HIDE);
		m_bWheel = false;
		break;

	case 1:
		m_tabFlip.ShowWindow(SW_HIDE);
		m_tabRotate.ShowWindow(SW_SHOW);
		m_tabResize.ShowWindow(SW_HIDE);
		m_tabCrop.ShowWindow(SW_HIDE);
		m_bWheel = false;
		break;

	case 2:
		m_tabFlip.ShowWindow(SW_HIDE);
		m_tabRotate.ShowWindow(SW_HIDE);
		m_tabResize.ShowWindow(SW_SHOW);
		m_tabCrop.ShowWindow(SW_HIDE);
		m_bWheel = false;
		break;
	case 3:
		m_tabFlip.ShowWindow(SW_HIDE);
		m_tabRotate.ShowWindow(SW_HIDE);
		m_tabResize.ShowWindow(SW_HIDE);
		m_tabCrop.ShowWindow(SW_SHOW);
		m_bWheel = false;
		break;
	case 4:
		m_tabFlip.ShowWindow(SW_HIDE);
		m_tabRotate.ShowWindow(SW_HIDE);
		m_tabResize.ShowWindow(SW_HIDE);
		m_tabCrop.ShowWindow(SW_HIDE);
		m_bWheel = true;
		break;

	}
	*pResult = 0;
}


void CviewerDlg::RotateLeft()
{
	rotate(m_matImage, m_matImage, cv::ROTATE_90_COUNTERCLOCKWISE);
	ResizeImageForControl(m_matImage, m_matImage);
	DisplayImageInPictureControl(m_matImage, IDC_PC_VIEW);
}


void CviewerDlg::RotateRight()
{
	rotate(m_matImage, m_matImage, cv::ROTATE_90_CLOCKWISE);
	ResizeImageForControl(m_matImage, m_matImage);
	DisplayImageInPictureControl(m_matImage, IDC_PC_VIEW);
}


void CviewerDlg::Resize(int h, int w)
{
	if (h <= 0) h = 1;
	if (h > rect.Height()) h = rect.Height();
	if (w <= 0) w = 1;
	if (w > rect.Width()) w = rect.Width();

	resize(m_matImage, m_matImage, cv::Size(w, h));
	DisplayImageInPictureControl(m_matImage, IDC_PC_VIEW);
}


BOOL CviewerDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_ESCAPE)
		return TRUE;
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN)
		return TRUE;
	return CDialogEx::PreTranslateMessage(pMsg);
}


void CviewerDlg::DoCrop()
{
	if (m_ptStart.x == m_ptLastEnd.x || m_ptStart.y == m_ptLastEnd.y) return;
	cv::Point cvStart(m_ptStart.x, m_ptStart.y);
	cv::Point cvEnd(m_ptLastEnd.x, m_ptLastEnd.y);

	// cv::Rect 생성
	cv::Rect roi(cvStart, cvEnd);

	m_matImage = m_matImage(roi);
	ResizeImageForControl(m_matImage, m_matImage);
	DisplayImageInPictureControl(m_matImage, IDC_PC_VIEW);

	m_ptStart.x = m_ptStart.y = m_ptLastEnd.x = m_ptLastEnd.y = 0;
}


void CviewerDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (!rect.PtInRect(point))
		return;

	if (m_tabControl.GetCurSel() == 3) {

		Invalidate();
		m_bDragging = true;

		m_ptStart = point;
		m_ptLastEnd = point;  // 초기 종료점도 시작점과 동일하게 설정
		SetCapture();  // 마우스 이벤트를 현재 윈도우로 캡처
	}
}


void CviewerDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	if (!rect.PtInRect(point))
		return;

	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (m_tabControl.GetCurSel() == 3) {
		if (m_bDragging)
		{
			m_bDragging = false;
			ReleaseCapture();  // 마우스 캡처 해제

			CClientDC dc(this);
			CPen pen(PS_SOLID, 2, RGB(0, 0, 0));  // 사각형 테두리용 펜 생성
			CBrush* pOldBrush = (CBrush*)dc.SelectStockObject(NULL_BRUSH);  // 내부를 채우지 않음
			CPen* pOldPen = dc.SelectObject(&pen);

			m_ptLastEnd = point;

			dc.Rectangle(m_ptStart.x, m_ptStart.y, m_ptLastEnd.x, m_ptLastEnd.y);
			dc.SelectObject(pOldBrush);
			dc.SelectObject(pOldPen);
		}
	}
}


void CviewerDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	if (!rect.PtInRect(point))
		return;
	if (m_tabControl.GetCurSel() == 3) {
		if (m_bDragging)
		{
			// 임시 DC를 사용하여 현재 사각형을 그리기 전에 이전 사각형을 지웁니다.
			CClientDC dc(this);
			CPen pen(PS_SOLID, 1, RGB(0, 0, 0));  // 사각형 테두리용 펜 생성
			CBrush* pOldBrush = (CBrush*)dc.SelectStockObject(NULL_BRUSH);  // 내부를 채우지 않음
			CPen* pOldPen = dc.SelectObject(&pen);

			// XOR 모드를 사용하여 이전 사각형을 지우고 새 사각형을 그립니다.
			dc.SetROP2(R2_NOTXORPEN);

			// 이전 사각형 지우기
			dc.Rectangle(m_ptStart.x, m_ptStart.y, m_ptLastEnd.x, m_ptLastEnd.y);
			// 새 사각형 그리기
			dc.Rectangle(m_ptStart.x, m_ptStart.y, point.x, point.y);

			// 마지막 종료점 업데이트
			m_ptLastEnd = point;

			dc.SelectObject(pOldBrush);
			dc.SelectObject(pOldPen);
		}
	}
}


BOOL CviewerDlg::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (m_bWheel) {
		double scaleFactor = 1.1; // 원하는 배율로 설정
		cv::Size currentSize = m_matImage.size();
		cv::Size newSize(currentSize.width * scaleFactor, currentSize.height * scaleFactor);

		if (zDelta > 0) {
			// 휠을 위로 스크롤할 때 확대
			if (newSize.width > rect.Width() || newSize.height > rect.Height())
				return 1;
			cv::resize(m_matImage, m_matImage, cv::Size(), scaleFactor, scaleFactor);
		}
		else {
			// 휠을 아래로 스크롤할 때 축소
			cv::resize(m_matImage, m_matImage, cv::Size(), 1 / scaleFactor, 1 / scaleFactor);
		}
		DisplayImageInPictureControl(m_matImage, IDC_PC_VIEW);
		// 마우스 휠 이벤트를 부모 클래스에 전달합니다.
		return CDialogEx::OnMouseWheel(nFlags, zDelta, pt);
	}
}

