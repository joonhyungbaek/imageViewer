// Rotate.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "viewer.h"
#include "Rotate.h"
#include "afxdialogex.h"
#include "viewerDlg.h"


// CRotate ��ȭ �����Դϴ�.

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


// CRotate �޽��� ó�����Դϴ�.


void CRotate::OnClickedRotateLeft()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CviewerDlg* pViewer = new CviewerDlg;
	pViewer->RotateLeft();
}


void CRotate::OnClickedRotateRight()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CviewerDlg* pViewer = new CviewerDlg;
	pViewer->RotateRight();
}


BOOL CRotate::PreTranslateMessage(MSG* pMsg)
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_ESCAPE)
		return TRUE;
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN)
		return TRUE;
	return CDialogEx::PreTranslateMessage(pMsg);
}
