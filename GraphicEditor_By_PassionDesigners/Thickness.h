#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include "GraphicEditorView.h"
// CThickness ��ȭ �����Դϴ�.

class CThickness : public CDialog
{
	DECLARE_DYNAMIC(CThickness)

public:
	CThickness(CGraphicEditorView *VIewCWnd);   // ǥ�� �������Դϴ�.
	virtual ~CThickness();
	int GetThickness () ;

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.
	int Thickness;

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
};
