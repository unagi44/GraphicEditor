
// GraphicEditor_By_PassionDesignersDoc.h : CGraphicEditor_By_PassionDesignersDoc Ŭ������ �������̽�
//


#pragma once


class CGraphicEditor_By_PassionDesignersDoc : public CDocument
{
protected: // serialization������ ��������ϴ�.
	CGraphicEditor_By_PassionDesignersDoc();
	DECLARE_DYNCREATE(CGraphicEditor_By_PassionDesignersDoc)

// Ư���Դϴ�.
public:

// �۾��Դϴ�.
public:

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
	virtual ~CGraphicEditor_By_PassionDesignersDoc();
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
