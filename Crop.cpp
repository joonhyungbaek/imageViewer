// Crop.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "viewer.h"
#include "Crop.h"
#include "afxdialogex.h"
#include "viewerDlg.h"

// CCrop 대화 상자입니다.

IMPLEMENT_DYNAMIC(CCrop, CDialogEx)

CCrop::CCrop(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_CROP, pParent)
{

}

CCrop::~CCrop()
{
}

void CCrop::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CCrop, CDialogEx)
	ON_BN_CLICKED(IDC_CROP_BUTTON, &CCrop::OnClickedCropButton)
END_MESSAGE_MAP()


// CCrop 메시지 처리기입니다.


void CCrop::OnClickedCropButton()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CviewerDlg* pViewer = new CviewerDlg;
	pViewer->DoCrop();
}
