// Resize.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "viewer.h"
#include "Resize.h"
#include "afxdialogex.h"
#include "viewerDlg.h"


// CResize 대화 상자입니다.

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


// CResize 메시지 처리기입니다.


void CResize::OnClickedButtonResize()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CWnd* pEditControlW = GetDlgItem(IDC_EDIT_RESIZE_W);
	CWnd* pEditControlH = GetDlgItem(IDC_EDIT_RESIZE_H);
	// Edit Control의 텍스트 가져오기
	CString h, w;
	pEditControlH->GetWindowText(h);
	pEditControlW->GetWindowText(w);

	if (h.IsEmpty() || w.IsEmpty()) {
		AfxMessageBox(_T("변경 할 사이즈 입력"));
		return;
	}

	if (h.FindOneOf(_T("0123456789")) == -1) {
		// 숫자가 아닌 문자가 없는 경우 메시지 박스 출력
		AfxMessageBox(_T("세로 입력이 올바르지 않습니다."));
		return;
	}
	if (w.FindOneOf(_T("0123456789")) == -1) {
		// 숫자가 아닌 문자가 없는 경우 메시지 박스 출력
		AfxMessageBox(_T("가로 입력이 올바르지 않습니다."));
		return;
	}


	CviewerDlg* pViewer = new CviewerDlg;
	pViewer->Resize(_ttoi(h), _ttoi(w));
}


BOOL CResize::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_ESCAPE)
		return TRUE;
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN)
		return TRUE;
	return CDialogEx::PreTranslateMessage(pMsg);
}
