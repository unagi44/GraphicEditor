//**************************************************************************************************************
// public of Passion Designers
// GraphicEditor program
// 2010253009 �̰迬
// 2010253026 ������
//**************************************************************************************************************
// GraphicEditorDoc.h : CGraphicEditorDoc Ŭ������ �������̽�
//
#include "CLine.h"	// ���� �׸��� ���� ������� ����
#include "CPolyLine.h"	// PolyLine�� �׸��� ���� ������� ����

#pragma once

class CGraphicEditorDoc : public CDocument
{
protected: // serialization������ ��������ϴ�.
	CGraphicEditorDoc();
	DECLARE_DYNCREATE(CGraphicEditorDoc)

// Ư���Դϴ�.
public:
	CArray < CLine, CLine& > L_Line ;	// �� �׸��� �迭
	CArray < CRect, CRect& > R_Rec ;	// ���� �׸��� �迭
	CArray < CPolyLine, CPolyLine& > P_Poly ;	// PolyLine �׸��� �迭
	int CPolyCount ;
	CArray < CRect, CRect& > E_Ellipse ;		// �� �׸��� �迭
	CArray < CRect, CRect& > T_Triangle ;		// ���� �׸��� �迭
	CArray < CRect, CRect& > RT_Triangle ;		// �� �ﰢ�� �׸��� �迭
	CArray < CRect, CRect& > RightT_Triangle ;	// ���� �ﰢ�� �׸��� �迭
	CArray < CRect, CRect& > RRightT_Triangle ;	// �� ���� �ﰢ�� �׸��� �迭
	CArray < CRect, CRect& > RTLT_Triangle ;	// ������ -> ���� �ﰢ�� �׸��� �迭
	CArray < CRect, CRect& > LTRT_Triangle ;	// ���� -> ������ �ﰢ�� �׸��� �迭
// �۾��Դϴ�.
public:
	CArray < int, int > R_Color ;		// ���� �� ��
	CArray < int, int > R_FillColor ;	// ���� ä��� ��
	CArray < int, int > E_Color ;		// �� �� ��
	CArray < int, int > E_FillColor ;	// �� ä��� ��
	CArray < int, int > T_Color ;		// ���� �� ��
	CArray < int, int > T_FillColor ;	// ���� ä��� ��
	CArray < int, int > RT_Color ;		// �� �ﰢ�� �� ��
	CArray < int, int > RT_FillColor ;	// �� �ﰢ�� ä��� ��
	CArray < int, int > RightT_Color ;	// ���� �ﰢ�� �� ��
	CArray < int, int > RightT_FillColor ;	// ���� �ﰢ�� ä��� ��
	CArray < int, int > RRightT_Color ;		// �� ���� �ﰢ�� �� ��
	CArray < int, int > RRightT_FillColor ;	// �� ���� �ﰢ�� ä��� ��
	CArray < int, int > R_Thickness ;			// ������ �� �β�
	CArray < int, int > E_Thickness ;			// ���� �� �β�
	CArray < int, int > T_Thickness ;			// ������ �� �β�
	CArray < int, int > RT_Thickness ;			// �� �ﰢ���� �� �β�
	CArray < int, int > RightT_Thickness ;		// ���� �ﰢ���� �� �β�
	CArray < int, int > RRightT_Thickness ;		// �� ���� �ﰢ���� �� �β�
	CArray < int, int > RTLT_Color ;			// ������ -> ���� �ﰢ�� �� ��
	CArray < int, int > RTLT_FillColor ;		// ������ -> ���� �ﰢ�� ä��� ��
	CArray < int, int > RTLT_Thickness ;		// ������ -> ���� �ﰢ�� �β�
	CArray < int, int > LTRT_Color ;			// ���� -> ������ �ﰢ�� �� ��
	CArray < int, int > LTRT_FillColor ;		// ���� -> ������ �ﰢ�� ä��� ��
	CArray < int, int > LTRT_Thickness ;		// ���� -> ������ �ﰢ�� �β�
public:
	CArray < CString, CString > What ;
	int L_Count ;			// �� ��ü�� ����
	int P_Count ;			// PolyLine ��ü�� ����
	int R_Count ;			// ���� ��ü�� ����
	int E_Count ;			// �� ��ü�� ����
	int T_Count ;			// ���� ��ü�� ����
	int RT_Count ;			// �� �ﰢ�� ��ü�� ����
	int RightT_Count ;		// ���� �ﰢ�� ��ü�� ����
	int RRightT_Count ;		// ���� �� �ﰢ�� ��ü�� ����
	int LTRT_Count ;		// ���� -> ������ �ﰢ�� ��ü�� ����
	int RTLT_Count ;		// ������ -> ���� ��ü�� ����

// �������Դϴ�.
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// �����Դϴ�.
public:
	virtual ~CGraphicEditorDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ������ �޽��� �� �Լ�
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// �˻� ó���⿡ ���� �˻� �������� �����ϴ� ����� �Լ�
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};
