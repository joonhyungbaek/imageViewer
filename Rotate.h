#pragma once


// CRotate ��ȭ �����Դϴ�.

class CRotate : public CDialogEx
{
	DECLARE_DYNAMIC(CRotate)

public:
	CRotate(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CRotate();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ROTATE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnClickedRotateLeft();
	afx_msg void OnClickedRotateRight();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
