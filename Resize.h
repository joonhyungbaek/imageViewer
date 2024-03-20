#pragma once


// CResize 대화 상자입니다.

class CResize : public CDialogEx
{
	DECLARE_DYNAMIC(CResize)

public:
	CResize(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CResize();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_RESIZE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnClickedButtonResize();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
