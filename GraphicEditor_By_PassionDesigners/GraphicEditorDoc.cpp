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
		}

		E_Ellipse.Serialize (ar) ;	// �� �׸��� �迭 ����
		R_Color.Serialize (ar) ;	// �簢���� �� �� ���� ���� ����
		E_Color.Serialize (ar) ;	// ���� �� �� ���� ���� ����
		R_FillColor.Serialize (ar) ;	// �簢���� �� ä��� ���� ���� ����
		E_FillColor.Serialize (ar) ;	// ���� �� ä��� ���� ���� ����
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
		}

		E_Ellipse.Serialize (ar) ;	// �� �׸��� �迭 �ҷ�����
		R_Color.Serialize (ar) ;	// �簢���� �� �� ���� ���� �ҷ�����
		E_Color.Serialize (ar) ;	// �簢���� �� �� ���� ���� �ҷ�����
		R_FillColor.Serialize (ar) ;	// �簢���� �� ä��� ���� ���� �ҷ�����
		E_FillColor.Serialize (ar) ;	// ���� �� ä��� ���� ���� �ҷ�����
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
