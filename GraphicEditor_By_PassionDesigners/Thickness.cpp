// Thickness.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "GraphicEditor.h"
#include "Thickness.h"
#include "afxdialogex.h"


// CThickness ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CThickness, CDialog)

CThickness::CThickness(CGraphicEditorView *View)
	: CDialog(CThickness::IDD, NULL)
	, Thickness(View->m_Thickness)
{
}

CThickness::~CThickness()
{
}

void CThickness::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_SelectThickness, Thickness);
	DDV_MinMaxInt(pDX, Thickness, 1, 100);
}

// �β��� ���� �մϴ�.
int CThickness::GetThickness () {
	return Thickness ;
}

BEGIN_MESSAGE_MAP(CThickness, CDialog)
END_MESSAGE_MAP()


// CThickness �޽��� ó�����Դϴ�.


BOOL CThickness::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.

	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}
