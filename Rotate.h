#pragma once


// CRotate 대화 상자입니다.

class CRotate : public CDialogEx
{
	DECLARE_DYNAMIC(CRotate)

public:
	CRotate(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CRotate();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ROTATE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnClickedRotateLeft();
	afx_msg void OnClickedRotateRight();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
