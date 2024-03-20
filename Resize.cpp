// Resize.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "viewer.h"
#include "Resize.h"
#include "afxdialogex.h"
#include "viewerDlg.h"


// CResize ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CResize, CDialogEx)

CResize::CResize(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_RESIZE, pParent)
{

}

CResize::~CResize()
{
}

void CResize::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CResize, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_RESIZE, &CResize::OnClickedButtonResize)
END_MESSAGE_MAP()


// CResize �޽��� ó�����Դϴ�.


void CResize::OnClickedButtonResize()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CWnd* pEditControlW = GetDlgItem(IDC_EDIT_RESIZE_W);
	CWnd* pEditControlH = GetDlgItem(IDC_EDIT_RESIZE_H);
	// Edit Control�� �ؽ�Ʈ ��������
	CString h, w;
	pEditControlH->GetWindowText(h);
	pEditControlW->GetWindowText(w);

	if (h.IsEmpty() || w.IsEmpty()) {
		AfxMessageBox(_T("���� �� ������ �Է�"));
		return;
	}

	if (h.FindOneOf(_T("0123456789")) == -1) {
		// ���ڰ� �ƴ� ���ڰ� ���� ��� �޽��� �ڽ� ���
		AfxMessageBox(_T("���� �Է��� �ùٸ��� �ʽ��ϴ�."));
		return;
	}
	if (w.FindOneOf(_T("0123456789")) == -1) {
		// ���ڰ� �ƴ� ���ڰ� ���� ��� �޽��� �ڽ� ���
		AfxMessageBox(_T("���� �Է��� �ùٸ��� �ʽ��ϴ�."));
		return;
	}


	CviewerDlg* pViewer = new CviewerDlg;
	pViewer->Resize(_ttoi(h), _ttoi(w));
}


BOOL CResize::PreTranslateMessage(MSG* pMsg)
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_ESCAPE)
		return TRUE;
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN)
		return TRUE;
	return CDialogEx::PreTranslateMessage(pMsg);
}
