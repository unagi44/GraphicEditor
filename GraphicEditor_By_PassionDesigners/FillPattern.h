#pragma once
#include "afxwin.h"


// CFillPattern 대화 상자입니다.

class CFillPattern : public CDialog
{
	DECLARE_DYNAMIC(CFillPattern)

public:
	CFillPattern(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CFillPattern();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_DIALOG2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CStatic FillPattern1;
	CStatic FillPattern2;
	CStatic FillPattern3;
	CStatic FillPattern4;
	CStatic FillPattern5;
	CStatic FillPattern6;
	CStatic FillPattern7;
	afx_msg void OnPaint();
	bool IsPattern1;
	bool IsPattern2;
	bool IsPattern3;
	bool IsPattern4;
	bool IsPattern5;
	bool IsPattern6;
	bool IsPattern7;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedRadiopattern1();
	afx_msg void OnBnClickedRadiopattern2();
	afx_msg void OnBnClickedRadiopattern3();
	afx_msg void OnBnClickedRadiopattern4();
	afx_msg void OnBnClickedRadiopattern5();
	afx_msg void OnBnClickedRadiopattern6();
	afx_msg void OnBnClickedRadiopattern7();
	int Pattern ;
	int GetPattern () ;
};
