#pragma once
// CFlip 대화 상자입니다.
class CFlip : public CDialogEx
{
	DECLARE_DYNAMIC(CFlip)

public:
	CFlip(CWnd* pParent = NULL);   // 표준 생성자입니다.

	virtual ~CFlip();
// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_FLIP };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnClickedFlipHori();
	afx_msg void OnClickedFlipVert();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
