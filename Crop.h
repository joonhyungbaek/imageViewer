#pragma once


// CCrop ��ȭ �����Դϴ�.

class CCrop : public CDialogEx
{
	DECLARE_DYNAMIC(CCrop)

public:
	CCrop(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CCrop();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CROP };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnClickedCropButton();
};
