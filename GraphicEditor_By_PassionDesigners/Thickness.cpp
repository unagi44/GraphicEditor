// Thickness.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "GraphicEditor.h"
#include "Thickness.h"
#include "afxdialogex.h"


// CThickness 대화 상자입니다.

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

// 두께를 리턴 합니다.
int CThickness::GetThickness () {
	return Thickness ;
}

BEGIN_MESSAGE_MAP(CThickness, CDialog)
END_MESSAGE_MAP()


// CThickness 메시지 처리기입니다.


BOOL CThickness::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}
