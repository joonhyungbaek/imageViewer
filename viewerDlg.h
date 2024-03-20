
// viewerDlg.h : 헤더 파일
//

#pragma once
#include "afxcmn.h"
#include "Flip.h"
#include "Rotate.h"
#include "Resize.h"
#include "Crop.h"
#include "afxwin.h"
#include "Raw.h"

using namespace cv;
// CviewerDlg 대화 상자

class CviewerDlg : public CDialogEx
{
// 생성입니다.
public:
	CviewerDlg(CWnd* pParent = NULL);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_VIEWER_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.

// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

public:
	CFlip m_tabFlip;
	CRotate m_tabRotate;
	CResize m_tabResize;
	CCrop m_tabCrop;

	CTabCtrl m_tabControl;
	static CRect rect;
	CStatic* pPicControl;
	afx_msg void OnClickedButtonOpen();
	Mat m_matImage_origin;
	void ResizeImageForControl(Mat& srcImg, Mat& dstImg);
	void DisplayImageInPictureControl(Mat& img, UINT nID);
	void FlipHori();
	void FlipVert();

	static Mat m_matImage;

	afx_msg void OnClickedButtonRestore();
	afx_msg void OnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult);
	void RotateLeft();
	void RotateRight();
	void Resize(int h, int w);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	void DoCrop();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	bool m_bDragging;
	static CPoint m_ptStart;
	static CPoint m_ptLastEnd;
	static bool isRaw;

	bool m_bWheel;
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	
	CRaw raw;

	void CviewerDlg::ShowRawImage(cv::Mat& mat);


	CStatic m_stPicture;
};
