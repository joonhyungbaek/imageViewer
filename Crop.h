#pragma once


// CCrop 대화 상자입니다.

class CCrop : public CDialogEx
{
	DECLARE_DYNAMIC(CCrop)

public:
	CCrop(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CCrop();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CROP };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnClickedCropButton();
};
