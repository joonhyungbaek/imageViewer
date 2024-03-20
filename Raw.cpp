// Raw.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "viewer.h"
#include "Raw.h"
#include "afxdialogex.h"


// CRaw ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CRaw, CDialogEx)

CRaw::CRaw(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_RAW, pParent)
{

}

CRaw::~CRaw()
{
}

void CRaw::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CRaw, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_RAW, &CRaw::OnClickedButtonRaw)
END_MESSAGE_MAP()


// CRaw �޽��� ó�����Դϴ�.


void CRaw::OnClickedButtonRaw()
{
	CString strWidth, strHeight, strChannel;
	

	// Edit Control���� ���� ��������
	GetDlgItemText(IDC_EDIT_RAW_WIDTH, strWidth);
	GetDlgItemText(IDC_EDIT_RAW_HEIGHT, strHeight);
	GetDlgItemText(IDC_EDIT_RAW_CHANNEL, strChannel);

	// ������ ���� ������ ��ȯ
	nWidth = _ttoi(strWidth);
	nHeight = _ttoi(strHeight);
	nChannel = _ttoi(strChannel);

	OnOK();
}


BOOL CRaw::PreTranslateMessage(MSG* pMsg)
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_ESCAPE)
		return TRUE;
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN)
		return TRUE;
	return CDialogEx::PreTranslateMessage(pMsg);
}
