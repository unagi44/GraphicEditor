#pragma once
#include "afxwin.h"
#include "afxcmn.h"

// CThickness ��ȭ �����Դϴ�.

class CThickness : public CDialog
{
	DECLARE_DYNAMIC(CThickness)

public:
	CThickness(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
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
