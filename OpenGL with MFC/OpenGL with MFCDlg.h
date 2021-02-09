
// OpenGL with MFCDlg.h : ��� ����
//

#pragma once
#include "afxwin.h"


//��������������� user custom (���� �ؾ���) �������������������
#define WIDTH_TEST 3
#define HEIGHT_TEST 3

//����η� ��������� �����մϴ�.
#include "include/GL/glew.h"
#include "include/GL/wglew.h"

//����� ���̺귯���� �������ݴϴ�.
#pragma comment(lib, "OpenGL32.lib")
#pragma comment(lib, "./lib/glew32.lib")

//license exception �߻�..?
//using namespace Euresys::Open_eVision_2_5;

//��������������� user custom (���� �ؾ���) �������������������

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


	//��������������� user custom (���� �ؾ���) �������������������

	//tmp �����Ҵ�
	float* pPosition;
	float* pColor;
	int iWidth;
	int iHeight;

	//tmp
	GLfloat dotSize = 5.0f;
	boolean dotDirection = true; // true: + , false: -

	// �̹��� ó���� (Open eVision) (�迭�̳� Matrix��� �ӵ��� �̵��� �ֳ�?)
	// (���� ����: �ӵ��� �𸣰ڰ� Height, Width���ϱ�� ������)
	// eVision ���̼��� ��������..
	//EImageBW8 EBW8Image1; // EImageBW8 instance
	

	CImage imageT1;
	
public:
	afx_msg void OnBnClickedButton2();
	CStatic m_picRight1;
};
