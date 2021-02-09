
// OpenGL with MFCDlg.h : 헤더 파일
//

#pragma once
#include "afxwin.h"


//▼▼▼▼▼▼▼▼▼▼▼▼▼▼ user custom (정리 해야함) ▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼
#define WIDTH_TEST 3
#define HEIGHT_TEST 3

//상대경로로 헤더파일을 지정합니다.
#include "include/GL/glew.h"
#include "include/GL/wglew.h"

//사용할 라이브러리를 지정해줍니다.
#pragma comment(lib, "OpenGL32.lib")
#pragma comment(lib, "./lib/glew32.lib")

//license exception 발생..?
//using namespace Euresys::Open_eVision_2_5;

//▲▲▲▲▲▲▲▲▲▲▲▲▲▲ user custom (정리 해야함) ▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲

// COpenGLwithMFCDlg 대화 상자
class COpenGLwithMFCDlg : public CDialogEx
{
// 생성입니다.
public:
	COpenGLwithMFCDlg(CWnd* pParent = NULL);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_OPENGLWITHMFC_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
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


	//▼▼▼▼▼▼▼▼▼▼▼▼▼▼ user custom (정리 해야함) ▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼

	//tmp 동적할당
	float* pPosition;
	float* pColor;
	int iWidth;
	int iHeight;

	//tmp
	GLfloat dotSize = 5.0f;
	boolean dotDirection = true; // true: + , false: -

	// 이미지 처리용 (Open eVision) (배열이나 Matrix대비 속도에 이득이 있나?)
	// (쓰는 이유: 속도는 모르겠고 Height, Width구하기는 좋을듯)
	// eVision 라이센스 에러인지..
	//EImageBW8 EBW8Image1; // EImageBW8 instance
	

	CImage imageT1;
	
public:
	afx_msg void OnBnClickedButton2();
	CStatic m_picRight1;
};
