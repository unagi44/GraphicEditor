// LinePattern.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "GraphicEditor.h"
#include "LinePattern.h"
#include "afxdialogex.h"


// LinePattern 대화 상자입니다.

IMPLEMENT_DYNAMIC(LinePattern, CDialog)

LinePattern::LinePattern(CWnd* pParent /*=NULL*/)
	: CDialog(LinePattern::IDD, pParent)
	, IsPattern1(false)
	, IsPattern2(false)
	, IsPattern3(false)
	, IsPattern4(false)
	, IsPattern5(false)
{
	Pattern = 1 ;
}

LinePattern::~LinePattern()
{
}

void LinePattern::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_Pattern1Box, LinePattern1);
	DDX_Control(pDX, IDC_Pattern2Box, LinePattern2);
	DDX_Control(pDX, IDC_Pattern3Box, LinePattern3);
	DDX_Control(pDX, IDC_Pattern4Box, LinePattern4);
	DDX_Control(pDX, IDC_Pattern5Box, LinePattern5);
}


BEGIN_MESSAGE_MAP(LinePattern, CDialog)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_RadioPattern1, &LinePattern::OnBnClickedRadiopattern1)
	ON_BN_CLICKED(IDC_RadioPattern2, &LinePattern::OnBnClickedRadiopattern2)
	ON_BN_CLICKED(IDC_RadioPattern3, &LinePattern::OnBnClickedRadiopattern3)
	ON_BN_CLICKED(IDC_RadioPattern4, &LinePattern::OnBnClickedRadiopattern4)
	ON_BN_CLICKED(IDC_RadioPattern5, &LinePattern::OnBnClickedRadiopattern5)
END_MESSAGE_MAP()

int LinePattern::GetPattern () {
	if ( IsPattern1 == true )
		return 1 ;
	else if ( IsPattern2 == true )
		return 2 ;
	else if ( IsPattern3 == true )
		return 3 ;
	else if ( IsPattern4 == true )
		return 4 ;
	else if ( IsPattern5 == true )
		return 5 ;
	else
		return 1 ;
}

void LinePattern::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	// 그리기 메시지에 대해서는 CDialog::OnPaint()을(를) 호출하지 마십시오.

	CDC memDC ;
	memDC.CreateCompatibleDC ( LinePattern1.GetDC () ) ;
	CBitmap bitmap ;
	bitmap.LoadBitmap ( IDB_LinePattern1 ) ;
	memDC.SelectObject ( &bitmap ) ;

	CStatic *staticSize = ( CStatic *) GetDlgItem ( IDC_Pattern1Box ) ;
	CRect rect ;
	staticSize -> GetClientRect ( rect ) ;
	int iWidth = rect.Width () ;
	int iHeight = rect.Height () ;
	LinePattern1.GetDC () -> StretchBlt (0,0,iWidth,iHeight,&memDC,0,0,140,30,SRCCOPY) ;

	CDC memDC2 ;
	memDC2.CreateCompatibleDC ( LinePattern2.GetDC () ) ;
	CBitmap bitmap2 ;
	bitmap2.LoadBitmap ( IDB_LinePattern2 ) ;
	memDC2.SelectObject ( &bitmap2 ) ;

	CStatic *staticSize2 = ( CStatic *) GetDlgItem ( IDC_Pattern2Box ) ;
	CRect rect2 ;
	staticSize2 -> GetClientRect ( rect2 ) ;
	int iWidth2 = rect2.Width () ;
	int iHeight2 = rect2.Height () ;
	LinePattern2.GetDC () -> StretchBlt (0,0,iWidth2,iHeight2,&memDC2,0,0,140,30,SRCCOPY) ;

	CDC memDC3 ;
	memDC3.CreateCompatibleDC ( LinePattern3.GetDC () ) ;
	CBitmap bitmap3 ;
	bitmap3.LoadBitmap ( IDB_LinePattern3 ) ;
	memDC3.SelectObject ( &bitmap3 ) ;

	CStatic *staticSize3 = ( CStatic *) GetDlgItem ( IDC_Pattern3Box ) ;
	CRect rect3 ;
	staticSize3 -> GetClientRect ( rect3 ) ;
	int iWidth3 = rect2.Width () ;
	int iHeight3 = rect2.Height () ;
	LinePattern3.GetDC () -> StretchBlt (0,0,iWidth3,iHeight3,&memDC3,0,0,140,30,SRCCOPY) ;

	CDC memDC4 ;
	memDC4.CreateCompatibleDC ( LinePattern4.GetDC () ) ;
	CBitmap bitmap4 ;
	bitmap4.LoadBitmap ( IDB_LinePattern4 ) ;
	memDC4.SelectObject ( &bitmap4 ) ;

	CStatic *staticSize4 = ( CStatic *) GetDlgItem ( IDC_Pattern4Box ) ;
	CRect rect4 ;
	staticSize4 -> GetClientRect ( rect4 ) ;
	int iWidth4 = rect2.Width () ;
	int iHeight4 = rect2.Height () ;
	LinePattern4.GetDC () -> StretchBlt (0,0,iWidth4,iHeight4,&memDC4,0,0,140,30,SRCCOPY) ;

	CDC memDC5 ;
	memDC5.CreateCompatibleDC ( LinePattern5.GetDC () ) ;
	CBitmap bitmap5 ;
	bitmap5.LoadBitmap ( IDB_LinePattern5 ) ;
	memDC5.SelectObject ( &bitmap5 ) ;

	CStatic *staticSize5 = ( CStatic *) GetDlgItem ( IDC_Pattern5Box ) ;
	CRect rect5 ;
	staticSize5 -> GetClientRect ( rect5 ) ;
	int iWidth5 = rect2.Width () ;
	int iHeight5 = rect2.Height () ;
	LinePattern5.GetDC () -> StretchBlt (0,0,iWidth5,iHeight5,&memDC5,0,0,140,30,SRCCOPY) ;
}

BOOL LinePattern::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void LinePattern::OnBnClickedRadiopattern1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if ( IsPattern1 == false ) {
		IsPattern1 = true ;
		IsPattern2 = false ;
		IsPattern3 = false ;
		IsPattern4 = false ;
		IsPattern5 = false ;
	}
	else
		IsPattern1 = false ;
}


void LinePattern::OnBnClickedRadiopattern2()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if ( IsPattern2 == false ) {
		IsPattern1 = false ;
		IsPattern2 = true ;
		IsPattern3 = false ;
		IsPattern4 = false ;
		IsPattern5 = false ;
	}
	else
		IsPattern2 = false ;
}


void LinePattern::OnBnClickedRadiopattern3()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if ( IsPattern3 == false ) {
		IsPattern3 = true ;
		IsPattern2 = false ;
		IsPattern1 = false ;
		IsPattern4 = false ;
		IsPattern5 = false ;
	}
	else
		IsPattern3 = false ;
}


void LinePattern::OnBnClickedRadiopattern4()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if ( IsPattern4 == false ) {
		IsPattern4 = true ;
		IsPattern2 = false ;
		IsPattern3 = false ;
		IsPattern1 = false ;
		IsPattern5 = false ;
	}
	else
		IsPattern4 = false ;
}


void LinePattern::OnBnClickedRadiopattern5()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if ( IsPattern5 == false ) {
		IsPattern5 = true ;
		IsPattern2 = false ;
		IsPattern3 = false ;
		IsPattern4 = false ;
		IsPattern1 = false ;
	}
	else
		IsPattern5 = false ;
}
