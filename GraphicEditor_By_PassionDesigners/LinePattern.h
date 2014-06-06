#pragma once
#include "afxwin.h"


// LinePattern 대화 상자입니다.

class LinePattern : public CDialog
{
	DECLARE_DYNAMIC(LinePattern)

public:
	LinePattern(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~LinePattern();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_DIALOG3 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

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
