#pragma once


// CRaw 대화 상자입니다.

class CRaw : public CDialogEx
{
	DECLARE_DYNAMIC(CRaw)

public:
	CRaw(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CRaw();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_RAW };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnClickedButtonRaw();
	int nWidth, nHeight, nChannel;
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
