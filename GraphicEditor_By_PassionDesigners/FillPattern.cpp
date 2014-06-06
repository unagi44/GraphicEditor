// FillPattern.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "GraphicEditor.h"
#include "FillPattern.h"
#include "afxdialogex.h"


// CFillPattern 대화 상자입니다.

IMPLEMENT_DYNAMIC(CFillPattern, CDialog)

CFillPattern::CFillPattern(CWnd* pParent /*=NULL*/)
	: CDialog(CFillPattern::IDD, pParent)
	, IsPattern1(false)
	, IsPattern2(false)
	, IsPattern3(false)
	, IsPattern4(false)
	, IsPattern5(false)
	, IsPattern6(false)
	, IsPattern7(false)
{
	Pattern = 1 ;
}

CFillPattern::~CFillPattern()
{
}

void CFillPattern::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_Pattern1Box, FillPattern1);
	DDX_Control(pDX, IDC_Pattern2Box, FillPattern2);
	DDX_Control(pDX, IDC_Pattern3Box, FillPattern3);
	DDX_Control(pDX, IDC_Pattern4Box, FillPattern4);
	DDX_Control(pDX, IDC_Pattern5Box, FillPattern5);
	DDX_Control(pDX, IDC_Pattern6Box, FillPattern6);
	DDX_Control(pDX, IDC_Pattern7Box, FillPattern7);
}


BEGIN_MESSAGE_MAP(CFillPattern, CDialog)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_RadioPattern1, &CFillPattern::OnBnClickedRadiopattern1)
	ON_BN_CLICKED(IDC_RadioPattern2, &CFillPattern::OnBnClickedRadiopattern2)
	ON_BN_CLICKED(IDC_RadioPattern3, &CFillPattern::OnBnClickedRadiopattern3)
	ON_BN_CLICKED(IDC_RadioPattern4, &CFillPattern::OnBnClickedRadiopattern4)
	ON_BN_CLICKED(IDC_RadioPattern5, &CFillPattern::OnBnClickedRadiopattern5)
	ON_BN_CLICKED(IDC_RadioPattern6, &CFillPattern::OnBnClickedRadiopattern6)
	ON_BN_CLICKED(IDC_RadioPattern7, &CFillPattern::OnBnClickedRadiopattern7)
END_MESSAGE_MAP()

void CFillPattern::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	// 그리기 메시지에 대해서는 CDialog::OnPaint()을(를) 호출하지 마십시오.
	CDC memDC ;
	memDC.CreateCompatibleDC ( FillPattern1.GetDC () ) ;
	CBitmap bitmap ;
	bitmap.LoadBitmap ( IDB_FillPattern1 ) ;
	memDC.SelectObject ( &bitmap ) ;

	CStatic *staticSize = ( CStatic *) GetDlgItem ( IDC_Pattern1Box ) ;
	CRect rect ;
	staticSize -> GetClientRect ( rect ) ;
	int iWidth = rect.Width () ;
	int iHeight = rect.Height () ;
	FillPattern1.GetDC () -> StretchBlt (0,0,iWidth,iHeight,&memDC,0,0,140,30,SRCCOPY) ;

	CDC memDC2 ;
	memDC2.CreateCompatibleDC ( FillPattern2.GetDC () ) ;
	CBitmap bitmap2 ;
	bitmap2.LoadBitmap ( IDB_FillPattern2 ) ;
	memDC2.SelectObject ( &bitmap2 ) ;

	CStatic *staticSize2 = ( CStatic *) GetDlgItem ( IDC_Pattern2Box ) ;
	CRect rect2 ;
	staticSize2 -> GetClientRect ( rect2 ) ;
	int iWidth2 = rect2.Width () ;
	int iHeight2 = rect2.Height () ;
	FillPattern2.GetDC () -> StretchBlt (0,0,iWidth2,iHeight2,&memDC2,0,0,140,30,SRCCOPY) ;

	CDC memDC3 ;
	memDC3.CreateCompatibleDC ( FillPattern3.GetDC () ) ;
	CBitmap bitmap3 ;
	bitmap3.LoadBitmap ( IDB_FillPattern3 ) ;
	memDC3.SelectObject ( &bitmap3 ) ;

	CStatic *staticSize3 = ( CStatic *) GetDlgItem ( IDC_Pattern3Box ) ;
	CRect rect3 ;
	staticSize3 -> GetClientRect ( rect3 ) ;
	int iWidth3 = rect2.Width () ;
	int iHeight3 = rect2.Height () ;
	FillPattern3.GetDC () -> StretchBlt (0,0,iWidth3,iHeight3,&memDC3,0,0,140,30,SRCCOPY) ;

	CDC memDC4 ;
	memDC4.CreateCompatibleDC ( FillPattern4.GetDC () ) ;
	CBitmap bitmap4 ;
	bitmap4.LoadBitmap ( IDB_FillPattern4 ) ;
	memDC4.SelectObject ( &bitmap4 ) ;

	CStatic *staticSize4 = ( CStatic *) GetDlgItem ( IDC_Pattern4Box ) ;
	CRect rect4 ;
	staticSize4 -> GetClientRect ( rect4 ) ;
	int iWidth4 = rect2.Width () ;
	int iHeight4 = rect2.Height () ;
	FillPattern4.GetDC () -> StretchBlt (0,0,iWidth4,iHeight4,&memDC4,0,0,140,30,SRCCOPY) ;

	CDC memDC5 ;
	memDC5.CreateCompatibleDC ( FillPattern5.GetDC () ) ;
	CBitmap bitmap5 ;
	bitmap5.LoadBitmap ( IDB_FillPattern5 ) ;
	memDC5.SelectObject ( &bitmap5 ) ;

	CStatic *staticSize5 = ( CStatic *) GetDlgItem ( IDC_Pattern5Box ) ;
	CRect rect5 ;
	staticSize5 -> GetClientRect ( rect5 ) ;
	int iWidth5 = rect2.Width () ;
	int iHeight5 = rect2.Height () ;
	FillPattern5.GetDC () -> StretchBlt (0,0,iWidth5,iHeight5,&memDC5,0,0,140,30,SRCCOPY) ;

	CDC memDC6 ;
	memDC6.CreateCompatibleDC ( FillPattern6.GetDC () ) ;
	CBitmap bitmap6 ;
	bitmap6.LoadBitmap ( IDB_FillPattern6 ) ;
	memDC6.SelectObject ( &bitmap6 ) ;

	CStatic *staticSize6 = ( CStatic *) GetDlgItem ( IDC_Pattern6Box ) ;
	CRect rect6 ;
	staticSize6 -> GetClientRect ( rect6 ) ;
	int iWidth6 = rect6.Width () ;
	int iHeight6 = rect6.Height () ;
	FillPattern6.GetDC () -> StretchBlt (0,0,iWidth6,iHeight6,&memDC6,0,0,140,30,SRCCOPY) ;

	CDC memDC7 ;
	memDC7.CreateCompatibleDC ( FillPattern7.GetDC () ) ;
	CBitmap bitmap7 ;
	bitmap7.LoadBitmap ( IDB_FillPattern7 ) ;
	memDC7.SelectObject ( &bitmap7 ) ;

	CStatic *staticSize7 = ( CStatic *) GetDlgItem ( IDC_Pattern7Box ) ;
	CRect rect7 ;
	staticSize7 -> GetClientRect ( rect7 ) ;
	int iWidth7 = rect6.Width () ;
	int iHeight7 = rect6.Height () ;
	FillPattern7.GetDC () -> StretchBlt (0,0,iWidth7,iHeight7,&memDC7,0,0,140,30,SRCCOPY) ;

}


BOOL CFillPattern::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CFillPattern::OnBnClickedRadiopattern1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if ( IsPattern1 == false ) {
		IsPattern1 = true ;
		IsPattern2 = false ;
		IsPattern3 = false ;
		IsPattern4 = false ;
		IsPattern5 = false ;
		IsPattern6 = false ;
		IsPattern7 = false ;
	}
	else
		IsPattern1 = false ;
}


void CFillPattern::OnBnClickedRadiopattern2()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if ( IsPattern2 == false ) {
		IsPattern2 = true ;
		IsPattern1 = false ;
		IsPattern3 = false ;
		IsPattern4 = false ;
		IsPattern5 = false ;
		IsPattern6 = false ;
		IsPattern7 = false ;
	}
	else
		IsPattern2 = false ;
}


void CFillPattern::OnBnClickedRadiopattern3()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if ( IsPattern3 == false ) {
		IsPattern3 = true ;
		IsPattern2 = false ;
		IsPattern1 = false ;
		IsPattern4 = false ;
		IsPattern5 = false ;
		IsPattern6 = false ;
		IsPattern7 = false ;
	}
	else
		IsPattern3 = false ;
}


void CFillPattern::OnBnClickedRadiopattern4()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if ( IsPattern4 == false ) {
		IsPattern4 = true ;
		IsPattern2 = false ;
		IsPattern3 = false ;
		IsPattern1 = false ;
		IsPattern5 = false ;
		IsPattern6 = false ;
		IsPattern7 = false ;
	}
	else
		IsPattern4 = false ;
}


void CFillPattern::OnBnClickedRadiopattern5()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if ( IsPattern5 == false ) {
		IsPattern5 = true ;
		IsPattern2 = false ;
		IsPattern3 = false ;
		IsPattern4 = false ;
		IsPattern1 = false ;
		IsPattern6 = false ;
		IsPattern7 = false ;
	}
	else
		IsPattern5 = false ;
}


void CFillPattern::OnBnClickedRadiopattern6()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if ( IsPattern6 == false ) {
		IsPattern6 = true ;
		IsPattern2 = false ;
		IsPattern3 = false ;
		IsPattern4 = false ;
		IsPattern5 = false ;
		IsPattern1 = false ;
		IsPattern7 = false ;
	}
	else
		IsPattern6 = false ;
}


void CFillPattern::OnBnClickedRadiopattern7()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if ( IsPattern7 == false ) {
		IsPattern7 = true ;
		IsPattern2 = false ;
		IsPattern3 = false ;
		IsPattern4 = false ;
		IsPattern5 = false ;
		IsPattern6 = false ;
		IsPattern1 = false ;
	}
	else
		IsPattern7 = false ;
}

int CFillPattern::GetPattern () {
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
	else if ( IsPattern6 == true )
		return 6 ;
	else if ( IsPattern7 == true )
		return 7 ;
	else
		return 1 ;
}