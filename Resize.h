#pragma once


// CResize ��ȭ �����Դϴ�.

class CResize : public CDialogEx
{
	DECLARE_DYNAMIC(CResize)

public:
	CResize(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CResize();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_RESIZE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnClickedButtonResize();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
