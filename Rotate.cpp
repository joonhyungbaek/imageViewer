// Rotate.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "viewer.h"
#include "Rotate.h"
#include "afxdialogex.h"
#include "viewerDlg.h"


// CRotate 대화 상자입니다.

IMPLEMENT_DYNAMIC(CRotate, CDialogEx)

CRotate::CRotate(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_ROTATE, pParent)
{

}

CRotate::~CRotate()
{
}

void CRotate::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CRotate, CDialogEx)
	ON_BN_CLICKED(IDC_ROTATE_LEFT, &CRotate::OnClickedRotateLeft)
	ON_BN_CLICKED(IDC_ROTATE_RIGHT, &CRotate::OnClickedRotateRight)
END_MESSAGE_MAP()


// CRotate 메시지 처리기입니다.


void CRotate::OnClickedRotateLeft()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CviewerDlg* pViewer = new CviewerDlg;
	pViewer->RotateLeft();
}


void CRotate::OnClickedRotateRight()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CviewerDlg* pViewer = new CviewerDlg;
	pViewer->RotateRight();
}


BOOL CRotate::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_ESCAPE)
		return TRUE;
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN)
		return TRUE;
	return CDialogEx::PreTranslateMessage(pMsg);
}
