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
	ON_CBN_SELCHANGE(IDC_COMBO_RAW_TYPE, &CRaw::OnSelchangeComboRawType)
END_MESSAGE_MAP()


// CRaw 메시지 처리기입니다.


void CRaw::OnClickedButtonRaw()
{
	CString strWidth, strHeight;
	// Edit Control에서 너비와 높이 값을 가져오기
	GetDlgItemText(IDC_EDIT_RAW_WIDTH, strWidth);
	GetDlgItemText(IDC_EDIT_RAW_HEIGHT, strHeight);

	// ComboBox Control에서 채널 값을 가져오기
	CComboBox* pCombo = (CComboBox*)GetDlgItem(IDC_COMBO_RAW_TYPE);
	nType = pCombo->GetCurSel(); // 선택된 항목의 인덱스


	if (nType <= 1) {
		nChannel = 1; // 첫 번째 항목이 선택된 경우, 채널 값은 1
	}
	else if (nType == 2) {
		nChannel = 3; 
	}
	else {
		// 유효하지 않은 선택인 경우 에러 메시지 표시
		AfxMessageBox(_T("유효한 타입 값을 선택해주세요."), MB_ICONERROR);
		return;
	}

	// 너비와 높이 값을 정수로 변환
	nWidth = _ttoi(strWidth);
	nHeight = _ttoi(strHeight);

	// 너비, 높이 및 채널 값의 유효성 검사
	if (nWidth <= 0 || nHeight <= 0) {
		AfxMessageBox(_T("너비, 높이, 채널 값은 모두 0보다 커야 합니다."), MB_ICONERROR);
		return; // 함수 종료
	}

	OnOK(); // 모든 값이 유효한 경우 다음 단계로 진행
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


BOOL CRaw::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	CComboBox* pCombo = (CComboBox*)GetDlgItem(IDC_COMBO_RAW_TYPE);
	pCombo->SetCurSel(0);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CRaw::OnSelchangeComboRawType()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CComboBox* pCombo1 = (CComboBox*)GetDlgItem(IDC_COMBO_RAW_TYPE);
	int nIndex = pCombo1->GetCurSel();

	if (nIndex == 2)
	{
		CStatic* pStatic = (CStatic*)GetDlgItem(IDC_RAW_STATIC_C);
		// Static Control의 텍스트를 변경합니다.
		pStatic->SetWindowText(_T("3"));
	}
	else {
		CStatic* pStatic = (CStatic*)GetDlgItem(IDC_RAW_STATIC_C);
		// Static Control의 텍스트를 변경합니다.
		pStatic->SetWindowText(_T("1"));
	}
}
