
// OpenGL with MFC.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// COpenGLwithMFCApp:
// �� Ŭ������ ������ ���ؼ��� OpenGL with MFC.cpp�� �����Ͻʽÿ�.
//

class COpenGLwithMFCApp : public CWinApp
{
public:
	COpenGLwithMFCApp();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern COpenGLwithMFCApp theApp;