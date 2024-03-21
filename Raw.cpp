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
	ON_CBN_SELCHANGE(IDC_COMBO_RAW_TYPE, &CRaw::OnSelchangeComboRawType)
END_MESSAGE_MAP()


// CRaw �޽��� ó�����Դϴ�.


void CRaw::OnClickedButtonRaw()
{
	CString strWidth, strHeight;
	// Edit Control���� �ʺ�� ���� ���� ��������
	GetDlgItemText(IDC_EDIT_RAW_WIDTH, strWidth);
	GetDlgItemText(IDC_EDIT_RAW_HEIGHT, strHeight);

	// ComboBox Control���� ä�� ���� ��������
	CComboBox* pCombo = (CComboBox*)GetDlgItem(IDC_COMBO_RAW_TYPE);
	nType = pCombo->GetCurSel(); // ���õ� �׸��� �ε���


	if (nType <= 1) {
		nChannel = 1; // ù ��° �׸��� ���õ� ���, ä�� ���� 1
	}
	else if (nType == 2) {
		nChannel = 3; 
	}
	else {
		// ��ȿ���� ���� ������ ��� ���� �޽��� ǥ��
		AfxMessageBox(_T("��ȿ�� Ÿ�� ���� �������ּ���."), MB_ICONERROR);
		return;
	}

	// �ʺ�� ���� ���� ������ ��ȯ
	nWidth = _ttoi(strWidth);
	nHeight = _ttoi(strHeight);

	// �ʺ�, ���� �� ä�� ���� ��ȿ�� �˻�
	if (nWidth <= 0 || nHeight <= 0) {
		AfxMessageBox(_T("�ʺ�, ����, ä�� ���� ��� 0���� Ŀ�� �մϴ�."), MB_ICONERROR);
		return; // �Լ� ����
	}

	OnOK(); // ��� ���� ��ȿ�� ��� ���� �ܰ�� ����
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


BOOL CRaw::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	CComboBox* pCombo = (CComboBox*)GetDlgItem(IDC_COMBO_RAW_TYPE);
	pCombo->SetCurSel(0);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}

void CRaw::OnSelchangeComboRawType()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CComboBox* pCombo1 = (CComboBox*)GetDlgItem(IDC_COMBO_RAW_TYPE);
	int nIndex = pCombo1->GetCurSel();

	if (nIndex == 2)
	{
		CStatic* pStatic = (CStatic*)GetDlgItem(IDC_RAW_STATIC_C);
		// Static Control�� �ؽ�Ʈ�� �����մϴ�.
		pStatic->SetWindowText(_T("3"));
	}
	else {
		CStatic* pStatic = (CStatic*)GetDlgItem(IDC_RAW_STATIC_C);
		// Static Control�� �ؽ�Ʈ�� �����մϴ�.
		pStatic->SetWindowText(_T("1"));
	}
}
