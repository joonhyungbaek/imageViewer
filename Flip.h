#pragma once
// CFlip ��ȭ �����Դϴ�.
class CFlip : public CDialogEx
{
	DECLARE_DYNAMIC(CFlip)

public:
	CFlip(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.

	virtual ~CFlip();
// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_FLIP };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnClickedFlipHori();
	afx_msg void OnClickedFlipVert();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
