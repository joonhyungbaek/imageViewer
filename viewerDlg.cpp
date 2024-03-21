
// viewerDlg.cpp : ���� ����
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

// ���� ���α׷� ������ ���Ǵ� CAboutDlg ��ȭ �����Դϴ�.



class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

// �����Դϴ�.
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


// CviewerDlg �޽��� ó����

BOOL CviewerDlg::OnInitDialog()
{

	CDialogEx::OnInitDialog();

	// �ý��� �޴��� "����..." �޴� �׸��� �߰��մϴ�.

	// IDM_ABOUTBOX�� �ý��� ��� ������ �־�� �մϴ�.
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

	// �� ��ȭ ������ �������� �����մϴ�.  ���� ���α׷��� �� â�� ��ȭ ���ڰ� �ƴ� ��쿡��
	//  �����ӿ�ũ�� �� �۾��� �ڵ����� �����մϴ�.
	SetIcon(m_hIcon, TRUE);			// ū �������� �����մϴ�.
	SetIcon(m_hIcon, FALSE);		// ���� �������� �����մϴ�.

	// TODO: ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.

	pPicControl = (CStatic*)AfxGetMainWnd()->GetDlgItem(IDC_PC_VIEW);
	pPicControl->GetClientRect(&rect); // Picture Control�� ũ�� ���

	m_tabFlip.Create(IDD_FLIP, &m_tabControl);
	m_tabRotate.Create(IDD_ROTATE, &m_tabControl);
	m_tabResize.Create(IDD_RESIZE, &m_tabControl);
	m_tabCrop.Create(IDD_CROP, &m_tabControl);

	m_tabControl.InsertItem(0, _T("������"));		// �� ����
	m_tabControl.InsertItem(1, _T("ȸ ��"));
	m_tabControl.InsertItem(2, _T("ũ�� ����"));
	m_tabControl.InsertItem(3, _T("�ڸ���"));
	m_tabControl.InsertItem(4, _T("�� Ȯ��/���"));

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
	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
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

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸�����
//  �Ʒ� �ڵ尡 �ʿ��մϴ�.  ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
//  �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.

void CviewerDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �׸��⸦ ���� ����̽� ���ؽ�Ʈ�Դϴ�.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Ŭ���̾�Ʈ �簢������ �������� ����� ����ϴ�.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);

		CRect rect2;
		GetClientRect(&rect2);

		int x = (rect2.Width() - cxIcon + 1) / 2;
		int y = (rect2.Height() - cyIcon + 1) / 2;

		// �������� �׸��ϴ�.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// ����ڰ� �ּ�ȭ�� â�� ���� ���ȿ� Ŀ���� ǥ�õǵ��� �ý��ۿ���
//  �� �Լ��� ȣ���մϴ�.
HCURSOR CviewerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CviewerDlg::ShowRawImage(cv::Mat& mat) {

	CImage cImage;
	// 16��Ʈ �̹����� 8��Ʈ�� ��ȯ (������ ���, ���� ��� �ÿ��� ������ �����ϸ� ���)
	cv::Mat convertedMat;
	mat.convertTo(convertedMat, CV_8U, 1.0 / 256.0);

	// CImage ��ü �ʱ�ȭ
	cImage.Create(convertedMat.cols, convertedMat.rows, 24);

	// CImage�� ������ ����
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

				//t�� 0�� ��� 8��Ʈ, 1�ϰ�� 16��Ʈ 
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
				// raw ���� �о����
				std::ifstream input_file(path, std::ios::binary);
				if (!input_file) {
					AfxMessageBox(_T("�̹����� �ҷ��� �� �����ϴ�."));
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

			if (m_matImage.empty()) // �̹����� ����� �ҷ����� ���� ���
			{
				AfxMessageBox(_T("�̹����� �ҷ��� �� �����ϴ�."));
				return;
			}

			// Picture Control�� ũ�⿡ �°� �̹��� ����
			ResizeImageForControl(m_matImage, m_matImage);

			// Picture Control�� �̹��� ǥ��
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
		// 16��Ʈ �̹����� 8��Ʈ�� ��ȯ (������ ���, ���� ��� �ÿ��� ������ �����ϸ� ���)
		if (!is8bit) {
			cv::Mat convertedMat;
			img.convertTo(convertedMat, CV_8U, 1.0 / 256.0);
			cImage.Create(convertedMat.cols, convertedMat.rows, 24);

			// CImage�� ������ ����
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

			// �̹����� 8��Ʈ�� ��ȯ���� �ʰ� �״�� ���
			img.copyTo(convertedMat);

			cImage.Create(convertedMat.cols, convertedMat.rows, 24);

			// CImage�� ������ ����
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
		// CImage�� �̹��� ������ �Ҵ��� ���� �ʱ�ȭ
		cImage.Create(img.cols, img.rows, 24);

		// cv::Mat���� CImage�� ������ ����
		for (int i = 0; i < img.rows; i++)
		{
			for (int j = 0; j < img.cols; j++)
			{
				cv::Vec3b pixel = img.at<cv::Vec3b>(i, j);

				// BGR ������ ��� (OpenCV�� �⺻)
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
		// ������ ǥ�õ� �̹����� �ִٸ� ����
		pPic->ModifyStyle(0xF, SS_BITMAP, SWP_NOSIZE);
		HBITMAP hBitmap = cImage.Detach(); // CImage���� HBITMAP ���
		pPic->SetBitmap(hBitmap); // Picture Control�� ��Ʈ�� ����
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

	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	if (m_matImage.empty()) return;
	m_matImage = m_matImage_origin.clone();
	DisplayImageInPictureControl(m_matImage, IDC_PC_VIEW);

}


void CviewerDlg::OnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
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
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
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

	// cv::Rect ����
	cv::Rect roi(cvStart, cvEnd);

	m_matImage = m_matImage(roi);
	ResizeImageForControl(m_matImage, m_matImage);
	DisplayImageInPictureControl(m_matImage, IDC_PC_VIEW);

	m_ptStart.x = m_ptStart.y = m_ptLastEnd.x = m_ptLastEnd.y = 0;
}


void CviewerDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	if (!rect.PtInRect(point))
		return;

	if (m_tabControl.GetCurSel() == 3) {

		Invalidate();
		m_bDragging = true;

		m_ptStart = point;
		m_ptLastEnd = point;  // �ʱ� �������� �������� �����ϰ� ����
		SetCapture();  // ���콺 �̺�Ʈ�� ���� ������� ĸó
	}
}


void CviewerDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	if (!rect.PtInRect(point))
		return;

	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	if (m_tabControl.GetCurSel() == 3) {
		if (m_bDragging)
		{
			m_bDragging = false;
			ReleaseCapture();  // ���콺 ĸó ����

			CClientDC dc(this);
			CPen pen(PS_SOLID, 2, RGB(0, 0, 0));  // �簢�� �׵θ��� �� ����
			CBrush* pOldBrush = (CBrush*)dc.SelectStockObject(NULL_BRUSH);  // ���θ� ä���� ����
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
			// �ӽ� DC�� ����Ͽ� ���� �簢���� �׸��� ���� ���� �簢���� ����ϴ�.
			CClientDC dc(this);
			CPen pen(PS_SOLID, 1, RGB(0, 0, 0));  // �簢�� �׵θ��� �� ����
			CBrush* pOldBrush = (CBrush*)dc.SelectStockObject(NULL_BRUSH);  // ���θ� ä���� ����
			CPen* pOldPen = dc.SelectObject(&pen);

			// XOR ��带 ����Ͽ� ���� �簢���� ����� �� �簢���� �׸��ϴ�.
			dc.SetROP2(R2_NOTXORPEN);

			// ���� �簢�� �����
			dc.Rectangle(m_ptStart.x, m_ptStart.y, m_ptLastEnd.x, m_ptLastEnd.y);
			// �� �簢�� �׸���
			dc.Rectangle(m_ptStart.x, m_ptStart.y, point.x, point.y);

			// ������ ������ ������Ʈ
			m_ptLastEnd = point;

			dc.SelectObject(pOldBrush);
			dc.SelectObject(pOldPen);
		}
	}
}


BOOL CviewerDlg::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	if (m_bWheel) {
		double scaleFactor = 1.1; // ���ϴ� ������ ����
		cv::Size currentSize = m_matImage.size();
		cv::Size newSize(currentSize.width * scaleFactor, currentSize.height * scaleFactor);

		if (zDelta > 0) {
			// ���� ���� ��ũ���� �� Ȯ��
			if (newSize.width > rect.Width() || newSize.height > rect.Height())
				return 1;
			cv::resize(m_matImage, m_matImage, cv::Size(), scaleFactor, scaleFactor);
		}
		else {
			// ���� �Ʒ��� ��ũ���� �� ���
			cv::resize(m_matImage, m_matImage, cv::Size(), 1 / scaleFactor, 1 / scaleFactor);
		}
		DisplayImageInPictureControl(m_matImage, IDC_PC_VIEW);
		// ���콺 �� �̺�Ʈ�� �θ� Ŭ������ �����մϴ�.
		return CDialogEx::OnMouseWheel(nFlags, zDelta, pt);
	}
}

