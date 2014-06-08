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
#include "CText.h"		// Text ������ �ϱ� ���� ������� ����
#include "CGroup.h"

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
	CArray < CText, CText& > Text_Text ;		// �ؽ�Ʈ ���� �迭
	CArray < CGroup, CGroup& > G_Group ;		// �׷�ȭ �迭
	CArray < CGroup, CGroup& > G_InGroup ;		// ���ӵ� �׷�ȭ �迭

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
	CArray < int, int > L_Location ;			// �׸� ��� ��ü �� �� ��ü�� �� Index
	CArray < int, int > R_Location ;			// �׸� ��� ��ü �� ���� ��ü�� �� Index
	CArray < int, int > P_Location ;			// �׸� ��� ��ü �� PolyLine ��ü�� �� Index
	CArray < int, int > E_Location ;			// �׸� ��� ��ü �� �� ��ü�� �� Index
	CArray < int, int > T_Location ;			// �׸� ��� ��ü �� ���� ��ü�� �� Index
	CArray < int, int > RT_Location ;			// �׸� ��� ��ü �� �� �ﰢ�� ��ü�� �� Index
	CArray < int, int > G_Location ;			// ���� ��� �׷�ȭ ��ü�� �� index
	CArray < int, int > RightT_Location ;		// �׸� ��� ��ü �� ���� �ﰢ�� ��ü�� �� Index
	CArray < int, int > RRightT_Location ;		// �׸� ��� ��ü �� �� ���� �ﰢ�� ��ü�� �� Index
	CArray < int, int > LTRT_Location ;			// �׸� ��� ��ü �� ���� -> ������ �ﰢ�� ��ü�� �� Index
	CArray < int, int > RTLT_Location ;			// �׸� ��� ��ü �� ������ -> ���� �ﰢ�� ��ü�� �� Index
	CArray < int, int > Text_Location ;			// �׸� ��� ��ü �� Text ��ü�� �� Index

	CArray < char, char > R_IsNoFill ;
	CArray < char, char > E_IsNoFill ;
	CArray < char, char > T_IsNoFill ;
	CArray < char, char > RT_IsNoFill ;
	CArray < char, char > RightT_IsNoFill ;		// ä��� ������ ������ Ȯ�����ִ� ����
	CArray < char, char > RRightT_IsNoFill ;
	CArray < char, char > LTRT_IsNoFill ;
	CArray < char, char > RTLT_IsNoFill ;

	CArray < int, int > R_FillPattern ;
	CArray < int, int > E_FillPattern ;
	CArray < int, int > T_FillPattern ;
	CArray < int, int > RT_FillPattern ;
	CArray < int, int > RightT_FillPattern ;		// ä��� ������ �������� Ȯ�����ִ� ����
	CArray < int, int > RRightT_FillPattern ;
	CArray < int, int > LTRT_FillPattern ;
	CArray < int, int > RTLT_FillPattern ;

	CArray < int, int > R_LinePattern ;
	CArray < int, int > E_LinePattern ;
	CArray < int, int > T_LinePattern ;
	CArray < int, int > RT_LinePattern ;
	CArray < int, int > RightT_LinePattern ;		// �� ������ �������� Ȯ�����ִ� ����
	CArray < int, int > RRightT_LinePattern ;
	CArray < int, int > LTRT_LinePattern ;
	CArray < int, int > RTLT_LinePattern ;

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
	int Text_Count ;		// �ؽ�Ʈ ��ü�� ����
	int G_Count ;			// �׷�ȭ ����
	int G_InCount ;			// ���ӵ� �׷�ȭ ����

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
