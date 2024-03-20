// Flip.cpp : 구현 파일입니다.
//
#include "stdafx.h"
#include "viewer.h"
#include "Flip.h"
#include "afxdialogex.h"
#include "viewerDlg.h"


// CFlip 대화 상자입니다.

IMPLEMENT_DYNAMIC(CFlip, CDialogEx)

CFlip::CFlip(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_FLIP, pParent)
{}


CFlip::~CFlip()
{
}

void CFlip::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}




BEGIN_MESSAGE_MAP(CFlip, CDialogEx)
	//ON_BN_CLICKED(IDC_FLIP_HORI, &CFlip::OnClickedFlipHori)
	ON_BN_CLICKED(IDC_FLIP_HORI, &CFlip::OnClickedFlipHori)
	ON_BN_CLICKED(IDC_FLIP_VERT, &CFlip::OnClickedFlipVert)
END_MESSAGE_MAP()


// CFlip 메시지 처리기입니다.


void CFlip::OnClickedFlipHori()
{
	CviewerDlg* pViewer = new CviewerDlg;
	pViewer->FlipHori();
}


void CFlip::OnClickedFlipVert()
{
	CviewerDlg* pViewer = new CviewerDlg;
	pViewer->FlipVert();
}


BOOL CFlip::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_ESCAPE)
		return TRUE;
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN)
		return TRUE;
	return CDialogEx::PreTranslateMessage(pMsg);
}
