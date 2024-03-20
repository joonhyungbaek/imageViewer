// Crop.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "viewer.h"
#include "Crop.h"
#include "afxdialogex.h"
#include "viewerDlg.h"

// CCrop ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CCrop, CDialogEx)

CCrop::CCrop(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_CROP, pParent)
{

}

CCrop::~CCrop()
{
}

void CCrop::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CCrop, CDialogEx)
	ON_BN_CLICKED(IDC_CROP_BUTTON, &CCrop::OnClickedCropButton)
END_MESSAGE_MAP()


// CCrop �޽��� ó�����Դϴ�.


void CCrop::OnClickedCropButton()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CviewerDlg* pViewer = new CviewerDlg;
	pViewer->DoCrop();
}
