#pragma once
#include "afxwin.h"


// LinePattern ��ȭ �����Դϴ�.

class LinePattern : public CDialog
{
	DECLARE_DYNAMIC(LinePattern)

public:
	LinePattern(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~LinePattern();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_DIALOG3 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	bool IsPattern1;
	bool IsPattern2;
	bool IsPattern3;
	bool IsPattern4;
	bool IsPattern5;
	CStatic LinePattern1;
	CStatic LinePattern2;
	CStatic LinePattern3;
	CStatic LinePattern4;
	CStatic LinePattern5;
	int Pattern ;
	int GetPattern () ;
	afx_msg void OnPaint();
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedRadiopattern1();
	afx_msg void OnBnClickedRadiopattern2();
	afx_msg void OnBnClickedRadiopattern3();
	afx_msg void OnBnClickedRadiopattern4();
	afx_msg void OnBnClickedRadiopattern5();
};
