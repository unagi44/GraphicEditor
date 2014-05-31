//**************************************************************************************************************
// public of Passion Designers
// GraphicEditor program
// 2010253009 이계연
// 2010253026 박현태
//**************************************************************************************************************
// GraphicEditorDoc.cpp : CGraphicEditorDoc 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "GraphicEditor.h"
#endif

#include "GraphicEditorDoc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CGraphicEditorDoc

IMPLEMENT_DYNCREATE(CGraphicEditorDoc, CDocument)

BEGIN_MESSAGE_MAP(CGraphicEditorDoc, CDocument)
END_MESSAGE_MAP()


// CGraphicEditorDoc 생성/소멸

CGraphicEditorDoc::CGraphicEditorDoc()
{
	// TODO: 여기에 일회성 생성 코드를 추가합니다.
}

CGraphicEditorDoc::~CGraphicEditorDoc()
{
}

BOOL CGraphicEditorDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 여기에 재초기화 코드를 추가합니다.
	// SDI 문서는 이 문서를 다시 사용합니다.

	return TRUE;
}




// CGraphicEditorDoc serialization

void CGraphicEditorDoc::Serialize(CArchive& ar)
{
	// 그린 모든 객체들을 저장, 불러오기를 가능하게 합니다.
	if (ar.IsStoring())
	{
		// TODO: 여기에 저장 코드를 추가합니다.
		L_Line.Serialize (ar) ;	// 선 그리기 배열 저장
		R_Rec.Serialize (ar) ;	// 상자 그리기 배열 저장
		
		// PolyLine 그리기 배열 저장
		CPolyCount = P_Poly.GetCount () ;
		ar << CPolyCount ;
		for ( int i = 0 ; i < P_Poly.GetCount () ; i++ ) {
			P_Poly.GetAt (i).Poly_point.Serialize (ar) ;
			ar << P_Poly.GetAt (i).P_Color ;
		}

		E_Ellipse.Serialize (ar) ;	// 원 그리기 배열 저장
		R_Color.Serialize (ar) ;	// 사각형의 각 생상 정보 저장
		E_Color.Serialize (ar) ;	// 원의 각 생상 정보 저장
	}
	else
	{
		// TODO: 여기에 로딩 코드를 추가합니다.
		L_Line.Serialize (ar) ;	// 선 그리기 배열 불러오기
		R_Rec.Serialize (ar) ;	// 상자 그리기 배열 불러오기

		// PolyLine  그리기 배열 불러오기
		ar >> CPolyCount ;
		P_Poly.SetSize ( CPolyCount ) ;
		for ( int i = 0 ; i < CPolyCount ; i++ ) {
			P_Poly.GetAt (i).Poly_point.Serialize (ar) ;
			ar >> P_Poly.GetAt (i).P_Color ;
		}

		E_Ellipse.Serialize (ar) ;	// 원 그리기 배열 불러오기
		R_Color.Serialize (ar) ;	// 사각형의 각 생상 정보 불러오기
		E_Color.Serialize (ar) ;	// 사각형의 각 생상 정보 불러오기
	}
}

#ifdef SHARED_HANDLERS

// 축소판 그림을 지원합니다.
void CGraphicEditorDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// 문서의 데이터를 그리려면 이 코드를 수정하십시오.
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// 검색 처리기를 지원합니다.
void CGraphicEditorDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// 문서의 데이터에서 검색 콘텐츠를 설정합니다.
	// 콘텐츠 부분은 ";"로 구분되어야 합니다.

	// 예: strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CGraphicEditorDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CGraphicEditorDoc 진단

#ifdef _DEBUG
void CGraphicEditorDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CGraphicEditorDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CGraphicEditorDoc 명령
