// Flip.cpp : ���� �����Դϴ�.
//
#include "stdafx.h"
#include "viewer.h"
#include "Flip.h"
#include "afxdialogex.h"
#include "viewerDlg.h"


// CFlip ��ȭ �����Դϴ�.

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


// CFlip �޽��� ó�����Դϴ�.


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
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_ESCAPE)
		return TRUE;
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN)
		return TRUE;
	return CDialogEx::PreTranslateMessage(pMsg);
}
