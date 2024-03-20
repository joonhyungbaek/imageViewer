// Raw.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "viewer.h"
#include "Raw.h"
#include "afxdialogex.h"


// CRaw 대화 상자입니다.

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


// CRaw 메시지 처리기입니다.


void CRaw::OnClickedButtonRaw()
{
	CString strWidth, strHeight, strChannel;
	

	// Edit Control에서 값을 가져오기
	GetDlgItemText(IDC_EDIT_RAW_WIDTH, strWidth);
	GetDlgItemText(IDC_EDIT_RAW_HEIGHT, strHeight);
	GetDlgItemText(IDC_EDIT_RAW_CHANNEL, strChannel);

	// 가져온 값을 정수로 변환
	nWidth = _ttoi(strWidth);
	nHeight = _ttoi(strHeight);
	nChannel = _ttoi(strChannel);

	OnOK();
}


BOOL CRaw::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_ESCAPE)
		return TRUE;
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN)
		return TRUE;
	return CDialogEx::PreTranslateMessage(pMsg);
}
