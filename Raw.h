#pragma once


// CRaw ��ȭ �����Դϴ�.

class CRaw : public CDialogEx
{
	DECLARE_DYNAMIC(CRaw)

public:
	CRaw(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CRaw();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_RAW };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnClickedButtonRaw();
	int nWidth, nHeight, nChannel;
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
