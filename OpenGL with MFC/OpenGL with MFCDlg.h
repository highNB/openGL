
// OpenGL with MFCDlg.h : ��� ����
//

#pragma once
#include "afxwin.h"

//����η� ��������� �����մϴ�.
#include "include/GL/glew.h"
#include "include/GL/wglew.h"

//����� ���̺귯���� �������ݴϴ�.
#pragma comment(lib, "OpenGL32.lib")
#pragma comment(lib, "./lib/glew32.lib")


// COpenGLwithMFCDlg ��ȭ ����
class COpenGLwithMFCDlg : public CDialogEx
{
// �����Դϴ�.
public:
	COpenGLwithMFCDlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_OPENGLWITHMFC_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �����Դϴ�.


// �����Դϴ�.
protected:
	HICON m_hIcon;

	// ������ �޽��� �� �Լ�
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CStatic m_picture;
	afx_msg void OnDestroy();
	afx_msg void OnTimer(UINT_PTR nIDEvent);

protected:
	virtual BOOL GetOldStyleRenderingContext(void);
	virtual BOOL SetupPixelFormat(void);

private:
	//OpenGL Setup
	BOOL GetRenderingContext();
	//Rendering Context and Device Context Pointers
	HGLRC     m_hRC;
	CDC*      m_pDC;

	GLuint vao;
	void defineVAO(GLuint &vao, GLuint &shaderProgram);
	GLuint create_program();



	//tmp
	GLfloat dotSize = 5.0f;
	boolean dotDirection = true; // true: + , false: -
};
