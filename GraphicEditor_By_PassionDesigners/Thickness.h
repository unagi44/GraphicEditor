#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include "GraphicEditorView.h"
// CThickness 대화 상자입니다.

class CThickness : public CDialog
{
	DECLARE_DYNAMIC(CThickness)

public:
	CThickness(CGraphicEditorView *VIewCWnd);   // 표준 생성자입니다.
	virtual ~CThickness();
	int GetThickness () ;

// 대화 상자 데이터입니다.
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	int Thickness;

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
};
