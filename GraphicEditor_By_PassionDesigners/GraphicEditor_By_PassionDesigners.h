
// GraphicEditor_By_PassionDesigners.h : GraphicEditor_By_PassionDesigners ���� ���α׷��� ���� �� ��� ����
//
#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"       // �� ��ȣ�Դϴ�.


// CGraphicEditor_By_PassionDesignersApp:
// �� Ŭ������ ������ ���ؼ��� GraphicEditor_By_PassionDesigners.cpp�� �����Ͻʽÿ�.
//

class CGraphicEditor_By_PassionDesignersApp : public CWinAppEx
{
public:
	CGraphicEditor_By_PassionDesignersApp();


// �������Դϴ�.
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// �����Դϴ�.
	UINT  m_nAppLook;
	BOOL  m_bHiColorIcons;

	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CGraphicEditor_By_PassionDesignersApp theApp;
