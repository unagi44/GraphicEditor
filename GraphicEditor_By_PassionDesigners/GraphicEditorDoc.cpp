//**************************************************************************************************************
// public of Passion Designers
// GraphicEditor program
// 2010253009 �̰迬
// 2010253026 ������
//**************************************************************************************************************
// GraphicEditorDoc.cpp : CGraphicEditorDoc Ŭ������ ����
//

#include "stdafx.h"
// SHARED_HANDLERS�� �̸� ����, ����� �׸� �� �˻� ���� ó���⸦ �����ϴ� ATL ������Ʈ���� ������ �� ������
// �ش� ������Ʈ�� ���� �ڵ带 �����ϵ��� �� �ݴϴ�.
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


// CGraphicEditorDoc ����/�Ҹ�

CGraphicEditorDoc::CGraphicEditorDoc()
{
	// TODO: ���⿡ ��ȸ�� ���� �ڵ带 �߰��մϴ�.
	L_Count = 0 ;
	R_Count = 0 ;
	P_Count = 0 ;
	E_Count = 0 ;
	T_Count = 0 ;
	RT_Count = 0 ;
	RightT_Count = 0 ;
	RRightT_Count = 0 ;
	LTRT_Count = 0 ;
	RTLT_Count = 0 ;
	Text_Count = 0 ;
}

CGraphicEditorDoc::~CGraphicEditorDoc()
{
}

BOOL CGraphicEditorDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: ���⿡ ���ʱ�ȭ �ڵ带 �߰��մϴ�.
	// SDI ������ �� ������ �ٽ� ����մϴ�.

	return TRUE;
}




// CGraphicEditorDoc serialization

void CGraphicEditorDoc::Serialize(CArchive& ar)
{
	// �׸� ��� ��ü���� ����, �ҷ����⸦ �����ϰ� �մϴ�.
	if (ar.IsStoring())
	{
		// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.
		L_Line.Serialize (ar) ;	// �� �׸��� �迭 ����
		R_Rec.Serialize (ar) ;	// ���� �׸��� �迭 ����
		
		// PolyLine �׸��� �迭 ����
		CPolyCount = P_Poly.GetCount () ;
		ar << CPolyCount ;
		for ( int i = 0 ; i < P_Poly.GetCount () ; i++ ) {
			P_Poly.GetAt (i).Poly_point.Serialize (ar) ;
			ar << P_Poly.GetAt (i).P_Color ;
			ar << P_Poly.GetAt (i).thickness ;
		}

		E_Ellipse.Serialize (ar) ;	// �� �׸��� �迭 ����
		T_Triangle.Serialize (ar) ;	// ���� �׸��� �迭 ����
		RT_Triangle.Serialize (ar) ;// �� �ﰢ�� �׸��� �迭 ����
		R_Color.Serialize (ar) ;	// �簢���� �� �� ���� ���� ����
		E_Color.Serialize (ar) ;	// ���� �� �� ���� ���� ����
		R_FillColor.Serialize (ar) ;	// �簢���� �� ä��� ���� ���� ����
		E_FillColor.Serialize (ar) ;	// ���� �� ä��� ���� ���� ����
		T_Color.Serialize (ar) ;		// ���� �� ���� ���� ����
		T_FillColor.Serialize (ar) ;	// ���� ä��� ���� ���� ����
		RT_Color.Serialize (ar) ;		// �� �ﰢ�� �� ���� ���� ����
		RT_FillColor.Serialize (ar) ;	// �� �ﰢ�� ä��� ���� ���� ����
		RightT_Triangle.Serialize (ar) ;	// ���� �ﰢ�� �׸��� �迭 ����
		RRightT_Triangle.Serialize (ar) ;	// �� ���� �ﰢ�� �׸��� �迭 ����
		RightT_Color.Serialize (ar) ;		// ���� �ﰢ�� �� ���� ���� ����
		RightT_FillColor.Serialize (ar) ;	// ���� �ﰢ�� ä��� ���� ���� ����
		RRightT_Color.Serialize (ar) ;		// �� ���� �ﰢ�� �� ���� ���� ����
		RRightT_FillColor.Serialize (ar) ;	// �� ���� �ﰢ�� ä��� ���� ���� ����

		R_Thickness.Serialize (ar) ;		// ������ �� �β��� ����
		E_Thickness.Serialize (ar) ;		// ���� �� �β��� ����
		T_Thickness.Serialize (ar) ;		// ������ �� �β��� ����
		RT_Thickness.Serialize (ar) ;		// �� �ﰢ���� �� �β��� ����
		RightT_Thickness.Serialize (ar) ;	// ���� �ﰢ���� �� �β��� ����
		RRightT_Thickness.Serialize (ar) ;	// �� ���� �ﰢ���� �� �β��� ����
		RTLT_Triangle.Serialize (ar) ;		// ������ -> ���� �ﰢ�� �׸��� �迭 ����
		LTRT_Triangle.Serialize (ar) ;		// ���� -> ������ �ﰢ�� �׸��� �迭 ����
		RTLT_Color.Serialize (ar) ;			// ������ -> ���� �ﰢ�� �� �� ����
		RTLT_FillColor.Serialize (ar) ;		// ������ -> ���� �ﰢ�� ä��� �� ����
		RTLT_Thickness.Serialize (ar) ;		// ������ -> ���� �ﰢ�� �β� ����
		LTRT_Color.Serialize (ar) ;			// ���� -> ������ �ﰢ�� �� �� ����
		LTRT_FillColor.Serialize (ar) ;		// ���� -> ������ �ﰢ�� ä��� �� ����
		LTRT_Thickness.Serialize (ar) ;		// ���� -> ������ �ﰢ�� �β� ����
		What.Serialize (ar) ;
		Text_Text.Serialize (ar) ;			// �ؽ�Ʈ ��ü ����

		ar << L_Count ;
		ar << R_Count ;
		ar << P_Count ;
		ar << E_Count ;
		ar << T_Count ;
		ar << RT_Count ;
		ar << RightT_Count ;
		ar << RRightT_Count ;
		ar << LTRT_Count ;
		ar << RTLT_Count ;
		ar << Text_Count ;
	}
	else
	{
		// TODO: ���⿡ �ε� �ڵ带 �߰��մϴ�.
		L_Line.Serialize (ar) ;	// �� �׸��� �迭 �ҷ�����
		R_Rec.Serialize (ar) ;	// ���� �׸��� �迭 �ҷ�����

		// PolyLine  �׸��� �迭 �ҷ�����
		ar >> CPolyCount ;
		P_Poly.SetSize ( CPolyCount ) ;
		for ( int i = 0 ; i < CPolyCount ; i++ ) {
			P_Poly.GetAt (i).Poly_point.Serialize (ar) ;
			ar >> P_Poly.GetAt (i).P_Color ;
			ar >> P_Poly.GetAt (i).thickness ;
		}

		E_Ellipse.Serialize (ar) ;	// �� �׸��� �迭 �ҷ�����
		T_Triangle.Serialize (ar) ;	// ���� �׸��� �迭 �ҷ�����
		RT_Triangle.Serialize (ar) ;// �� �ﰢ�� �׸��� �迭 �ҷ�����
		R_Color.Serialize (ar) ;	// �簢���� �� �� ���� ���� �ҷ�����
		E_Color.Serialize (ar) ;	// �簢���� �� �� ���� ���� �ҷ�����
		R_FillColor.Serialize (ar) ;	// �簢���� �� ä��� ���� ���� �ҷ�����
		E_FillColor.Serialize (ar) ;	// ���� �� ä��� ���� ���� �ҷ�����
		T_Color.Serialize (ar) ;		// ���� �� �� ���� ���� �ҷ�����
		T_FillColor.Serialize (ar) ;	// ���� �� ä��� ���� ���� �ҷ�����
		RT_Color.Serialize (ar) ;		// �� �ﰢ�� �� ���� ���� �ҷ�����
		RT_FillColor.Serialize (ar) ;	// �� �ﰢ�� ä��� ���� ���� �ҷ�����
		RightT_Triangle.Serialize (ar) ;	// ���� �ﰢ�� �׸��� �迭 �ҷ�����
		RRightT_Triangle.Serialize (ar) ;	// �� ���� �ﰢ�� �׸��� �迭 �ҷ�����
		RightT_Color.Serialize (ar) ;		// ���� �ﰢ�� �� ���� ���� �ҷ�����
		RightT_FillColor.Serialize (ar) ;	// ���� �ﰢ�� ä��� ���� ���� �ҷ�����
		RRightT_Color.Serialize (ar) ;		// �� ���� �ﰢ�� �� ���� ���� �ҷ�����
		RRightT_FillColor.Serialize (ar) ;	// �� ���� �ﰢ�� ä��� ���� ���� �ҷ�����

		R_Thickness.Serialize (ar) ;		// ������ �� �β� �ҷ�����
		E_Thickness.Serialize (ar) ;		// ���� �� �β� �ҷ�����
		T_Thickness.Serialize (ar) ;		// ������ �� �β� �ҷ�����
		RT_Thickness.Serialize (ar) ;		// �� �ﰢ���� �� �β� �ҷ�����
		RightT_Thickness.Serialize (ar) ;	// ���� �ﰢ���� �� �β� �ҷ�����
		RRightT_Thickness.Serialize (ar) ;	// �� ���� �ﰢ���� �� �β� �ҷ�����
		RTLT_Triangle.Serialize (ar) ;		// ������ -> ���� �ﰢ�� �׸��� �迭 �ҷ�����
		LTRT_Triangle.Serialize (ar) ;		// ���� -> ������ �ﰢ�� �׸��� �迭 �ҷ�����
		RTLT_Color.Serialize (ar) ;			// ������ -> ���� �ﰢ�� �� �� �ҷ�����
		RTLT_FillColor.Serialize (ar) ;		// ������ -> ���� �ﰢ�� ä��� �� �ҷ�����
		RTLT_Thickness.Serialize (ar) ;		// ������ -> ���� �ﰢ�� �β� �ҷ�����
		LTRT_Color.Serialize (ar) ;			// ���� -> ������ �ﰢ�� �� �� �ҷ�����
		LTRT_FillColor.Serialize (ar) ;		// ���� -> ������ �ﰢ�� ä��� �� �ҷ�����
		LTRT_Thickness.Serialize (ar) ;		// ���� -> ������ �ﰢ�� �β� �ҷ�����
		What.Serialize (ar) ;
		Text_Text.Serialize (ar) ;			// �ؽ�Ʈ ��ü �ҷ�����

		ar >> L_Count ;
		ar >> R_Count ;
		ar >> P_Count ;
		ar >> E_Count ;
		ar >> T_Count ;
		ar >> RT_Count ;
		ar >> RightT_Count ;
		ar >> RRightT_Count ;
		ar >> LTRT_Count ;
		ar >> RTLT_Count ;
		ar >> Text_Count ;
	}
}

#ifdef SHARED_HANDLERS

// ����� �׸��� �����մϴ�.
void CGraphicEditorDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// ������ �����͸� �׸����� �� �ڵ带 �����Ͻʽÿ�.
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

// �˻� ó���⸦ �����մϴ�.
void CGraphicEditorDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// ������ �����Ϳ��� �˻� �������� �����մϴ�.
	// ������ �κ��� ";"�� ���еǾ�� �մϴ�.

	// ��: strSearchContent = _T("point;rectangle;circle;ole object;");
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

// CGraphicEditorDoc ����

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


// CGraphicEditorDoc ���
