
// OpenGL with MFCDlg.cpp : ���� ����
//

#include "stdafx.h"
#include "OpenGL with MFC.h"
#include "OpenGL with MFCDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// ���� ���α׷� ������ ���Ǵ� CAboutDlg ��ȭ �����Դϴ�.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

// �����Դϴ�.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// COpenGLwithMFCDlg ��ȭ ����


COpenGLwithMFCDlg::COpenGLwithMFCDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_OPENGLWITHMFC_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void COpenGLwithMFCDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PICTURE, m_picture);
	DDX_Control(pDX, IDC_PIC_RIGHT1, m_picRight1);
	DDX_Control(pDX, IDC_STAT_TEST, m_textCurStat);
}

BEGIN_MESSAGE_MAP(COpenGLwithMFCDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_DESTROY()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON2, &COpenGLwithMFCDlg::OnBnClickedButton2)
//	ON_WM_KEYDOWN()
//	ON_WM_KEYUP()
END_MESSAGE_MAP()


// COpenGLwithMFCDlg �޽��� ó����

BOOL COpenGLwithMFCDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// �ý��� �޴��� "����..." �޴� �׸��� �߰��մϴ�.

	// IDM_ABOUTBOX�� �ý��� ��� ������ �־�� �մϴ�.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);


	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// �� ��ȭ ������ �������� �����մϴ�.  ���� ���α׷��� �� â�� ��ȭ ���ڰ� �ƴ� ��쿡��
	//  �����ӿ�ũ�� �� �۾��� �ڵ����� �����մϴ�.
	SetIcon(m_hIcon, TRUE);			// ū �������� �����մϴ�.
	SetIcon(m_hIcon, FALSE);		// ���� �������� �����մϴ�.

	// TODO: ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.


	iWidth = WIDTH_TEST;
	iHeight = HEIGHT_TEST;


	//OpenGL context ����
	if (!GetRenderingContext())
	{
		AfxMessageBox(CString("OpenGL �ʱ�ȭ�� ������ �߻��Ͽ� ���α׷��� ������ �� �����ϴ�."));
		return -1;
	}
	
	GLuint shaderProgram;
	defineVAO(vao, shaderProgram);

	glUseProgram(shaderProgram);
	glBindVertexArray(vao);

	SetTimer(1000, 15, NULL); //15 =: 60 FPS / 30 =: 30FPS

	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
}

void COpenGLwithMFCDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸�����
//  �Ʒ� �ڵ尡 �ʿ��մϴ�.  ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
//  �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.

void COpenGLwithMFCDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �׸��⸦ ���� ����̽� ���ؽ�Ʈ�Դϴ�.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Ŭ���̾�Ʈ �簢������ �������� ����� ����ϴ�.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �������� �׸��ϴ�.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// ����ڰ� �ּ�ȭ�� â�� ���� ���ȿ� Ŀ���� ǥ�õǵ��� �ý��ۿ���
//  �� �Լ��� ȣ���մϴ�.
HCURSOR COpenGLwithMFCDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void COpenGLwithMFCDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.

	glDeleteVertexArrays(1, &vao);

	if (FALSE == ::wglDeleteContext(m_hRC))
	{
		AfxMessageBox(CString("wglDeleteContext failed"));
	}
}


void COpenGLwithMFCDlg::OnTimer(UINT_PTR nIDEvent)
{
	CDialogEx::OnTimer(nIDEvent);

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	//
	//				����Ʈ ������ ����
	//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@//@@@
	//�ǽð����� �׽����غ� (������4��)				 //@@@
	if (dotDirection) dotSize += 0.5f;				 //@@@
	else dotSize -= 0.5f;							 //@@@
	if (5.0f > dotSize) dotDirection = true;		 //@@@
	else if (15.0f < dotSize) dotDirection = false;	 //@@@
	glPointSize(dotSize);							 //@@@
	//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@//@@@
	//
	//				������ Ȯ�ο�
	//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@//@@@
	DWORD curTime = GetCurrentTime(); // gettick64 ����ϴ°��� �� ������ 49.71�ϵڿ� �����÷ο�߻�
	static DWORD lastTime = curTime;					  //@@@
	DWORD intervalTime = curTime - lastTime;			  //@@@
	lastTime = curTime;									  //@@@
	CString cst_tmp;									  //@@@
	if (intervalTime)									  //@@@
		cst_tmp.Format(_T("FPS : %.3lf"), 1000.0f / intervalTime);
														  //@@@
	m_textCurStat.SetWindowTextW(cst_tmp);				  //@@@
	//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@//@@@
	//
	//				����Ʈ 2�� ����
	//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@//@@@
	static boolean onoffState = true;				 //@@@
													 //@@@
	if (onoffState) onoffState = false;				 //@@@
	else onoffState = true;							 //@@@
													 //@@@
	GLuint shaderProgram3;							 //@@@
													 //@@@
	if (onoffState) myDefineVAO(vao, shaderProgram3);//@@@
	else defineVAO(vao, shaderProgram3);			 //@@@
													 //@@@
	glUseProgram(shaderProgram3);					 //@@@
	glBindVertexArray(vao);							 //@@@
	//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@//@@@
	//
	//				ī�޶� �̵�
	//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@//@@@












	//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@//@@@




	glDrawArrays(GL_POINTS, 0, (iWidth*iHeight));
	
	//antialiasing
	//glEnable(GL_POINT_SMOOTH); 
	
	//ȭ�� ������Ʈ
	SwapBuffers(m_pDC->GetSafeHdc());
}

//��ó ��Ʈ�ѿ� ������ ���� �κ� (���� ���� ����)
BOOL COpenGLwithMFCDlg::GetRenderingContext()
{
	//��ó ��Ʈ�ѿ��� �׸����� DC ����
	//���� https://goo.gl/CK36zE
	CWnd* pImage = GetDlgItem(IDC_PICTURE);
	CRect rc;
	pImage->GetWindowRect(rc);
	m_pDC = pImage->GetDC();


	if (NULL == m_pDC)
	{
		AfxMessageBox(CString("Unable to get a DC"));
		return FALSE;
	}


	if (!GetOldStyleRenderingContext())
	{
		return TRUE;
	}


	//Get access to modern OpenGL functionality from this old style context.
	glewExperimental = GL_TRUE;
	if (GLEW_OK != glewInit())
	{
		AfxMessageBox(CString("GLEW could not be initialized!"));
		return FALSE;
	}


	//Get a new style pixel format
	if (!SetupPixelFormat())
	{
		return FALSE;
	}


	//���� http://gamedev.stackexchange.com/a/30443
	GLint attribs[] =
	{
		//OpenGL 3.3 ���
		WGL_CONTEXT_MAJOR_VERSION_ARB, 3,
		WGL_CONTEXT_MINOR_VERSION_ARB, 3,
		// Uncomment this for forward compatibility mode
		//WGL_CONTEXT_FLAGS_ARB, WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB,
		// Uncomment this for Compatibility profile
		//WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_COMPATIBILITY_PROFILE_BIT_ARB,
		// We are using Core profile here
		WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
		0
	};


	HGLRC CompHRC = wglCreateContextAttribsARB(m_pDC->GetSafeHdc(), 0, attribs);
	if (CompHRC && wglMakeCurrent(m_pDC->GetSafeHdc(), CompHRC))
		m_hRC = CompHRC;

	return TRUE;
}


void COpenGLwithMFCDlg::defineVAO(GLuint &vao, GLuint &shaderProgram)
{
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);



	//====================try.old=======================
	
	pPosition = new float[iWidth*iHeight * 3];
	pColor = new float[iWidth*iHeight *3];

	for (int i = 0; i < (iWidth*iHeight); i++) {

		float kkk = (float)i / (iWidth*iHeight); //tmp		
		pPosition[i * 3 + 0] = -0.95f + 1.9f * kkk; // x ��ǥ
		pPosition[i * 3 + 1] = -0.95f + 1.9f * kkk; // y ��ǥ
		pPosition[i * 3 + 2] = 0.0f; // z ��ǥ

	}
	
	for (int i = 0; i < (iWidth*iHeight); i++) {
		float kkk = (float)i / (iWidth*iHeight); //tmp		
		pColor[i * 3 + 0] = 1.0f; // R
		pColor[i * 3 + 1] = kkk; // G
		pColor[i * 3 + 2] = 0.0f; // B
	}

	GLuint position_vbo, color_vbo;

	glGenBuffers(1, &position_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, position_vbo);
	glBufferData(GL_ARRAY_BUFFER, _msize(pPosition), pPosition, GL_STATIC_DRAW);

	glGenBuffers(1, &color_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, color_vbo);
	glBufferData(GL_ARRAY_BUFFER, _msize(pColor), pColor, GL_STATIC_DRAW);


	shaderProgram = create_program();

	GLint position_attribute = glGetAttribLocation(shaderProgram, "position");
	glBindBuffer(GL_ARRAY_BUFFER, position_vbo);
	glVertexAttribPointer(position_attribute, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(position_attribute);

	GLint color_attribute = glGetAttribLocation(shaderProgram, "color");
	glBindBuffer(GL_ARRAY_BUFFER, color_vbo);
	glVertexAttribPointer(color_attribute, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(color_attribute);

	glBindVertexArray(0);
}

// ���̴� ����
GLuint COpenGLwithMFCDlg::create_program() {

	//vertexShader = ��ġ! 3D(��) -> 2D(�����)
	const GLchar* vertexShaderSource =
		"#version 330 core\n"
		"in vec3 position;"
		"in vec3 color;"
		"out vec3 color_from_vshader;"
		"void main()"
		"{"
		"gl_Position = vec4(position, 1.0);"
		"color_from_vshader = color;"
		"}";

	//fragmentShader = ����, ������ color_from_vshader�޾Ƽ� ����ϴµ�
	const GLchar* fragmentShaderSource =
		"#version 330 core\n"
		"in vec3 color_from_vshader;"
		"out vec4 out_color;"
		"void main()"
		"{"
		"out_color = vec4(color_from_vshader, 1.0);"
		"}";


	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	GLint success;
	GLchar infoLog[512];

	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		TRACE(CString("ERROR: vertex shader ������ ���� ") + CString(infoLog) + CString("\n"));
	}

	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		TRACE(CString("ERROR: fragment shader ������ ���� ") + CString(infoLog) + CString("\n"));
	}


	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	glLinkProgram(shaderProgram);


	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);

		TRACE(CString("ERROR: shader program ���� ���� ") + CString(infoLog) + CString("\n"));
	}

	return shaderProgram;
}

// �� �ϴ��� ��
BOOL COpenGLwithMFCDlg::GetOldStyleRenderingContext()
{
	//A generic pixel format descriptor. This will be replaced with a more
	//specific and modern one later, so don't worry about it too much.
	static PIXELFORMATDESCRIPTOR pfd =
	{
		sizeof(PIXELFORMATDESCRIPTOR),
		1,
		PFD_DRAW_TO_WINDOW |            // support window
		PFD_SUPPORT_OPENGL |            // support OpenGL
		PFD_DOUBLEBUFFER,               // double buffered
		PFD_TYPE_RGBA,                  // RGBA type
		32,                             // 32-bit color depth
		0, 0, 0, 0, 0, 0,               // color bits ignored
		0,                              // no alpha buffer
		0,                              // shift bit ignored
		0,                              // no accumulation buffer
		0, 0, 0, 0,                     // accum bits ignored
		24,								// 24-bit z-buffer
		0,                              // no stencil buffer
		0,                              // no auxiliary buffer
		PFD_MAIN_PLANE,                 // main layer
		0,                              // reserved
		0, 0, 0                         // layer masks ignored
	};

	// Get the id number for the best match supported by the hardware device context
	// to what is described in pfd
	int pixelFormat = ChoosePixelFormat(m_pDC->GetSafeHdc(), &pfd);

	//If there's no match, report an error
	if (0 == pixelFormat)
	{
		AfxMessageBox(CString("ChoosePixelFormat failed"));
		return FALSE;
	}

	//If there is an acceptable match, set it as the current 
	if (FALSE == SetPixelFormat(m_pDC->GetSafeHdc(), pixelFormat, &pfd))
	{
		AfxMessageBox(CString("SetPixelFormat failed"));
		return FALSE;
	}

	//Create a context with this pixel format
	if (0 == (m_hRC = wglCreateContext(m_pDC->GetSafeHdc())))
	{
		AfxMessageBox(CString("wglCreateContext failed"));
		return FALSE;
	}

	//Make it current. 
	if (FALSE == wglMakeCurrent(m_pDC->GetSafeHdc(), m_hRC))
	{
		AfxMessageBox(CString("wglMakeCurrent failed"));
		return FALSE;
	}
	return TRUE;
}

// �� 2
BOOL COpenGLwithMFCDlg::SetupPixelFormat()
{
	//This is a modern pixel format attribute list.
	//It has an extensible structure. Just add in more argument pairs 
	//befroe the null to request more features.
	const int attribList[] =
	{
		WGL_DRAW_TO_WINDOW_ARB, GL_TRUE,
		WGL_SUPPORT_OPENGL_ARB, GL_TRUE,
		WGL_ACCELERATION_ARB,   WGL_FULL_ACCELERATION_ARB,
		WGL_DOUBLE_BUFFER_ARB,  GL_TRUE,
		WGL_PIXEL_TYPE_ARB,     WGL_TYPE_RGBA_ARB,
		WGL_COLOR_BITS_ARB,     32,
		WGL_DEPTH_BITS_ARB,     24,
		WGL_STENCIL_BITS_ARB,   8,
		0, 0  //End
	};


	unsigned int numFormats;
	int pixelFormat;
	//PIXELFORMATDESCRIPTOR pfd; //�� �ּ����� ����ϴµ� ��� ���ؼ� �ּ�ó��

	//Select a pixel format number
	wglChoosePixelFormatARB(m_pDC->GetSafeHdc(), attribList, NULL, 1, &pixelFormat, &numFormats);

	//Optional: Get the pixel format's description. We must provide a 
	//description to SetPixelFormat(), but its contents mean little.
	//According to MSDN: 
	//  The system's metafile component uses this structure to record the logical
	//  pixel format specification. The structure has no other effect upon the
	//  behavior of the SetPixelFormat function.
	//DescribePixelFormat(m_pDC->GetSafeHdc(), pixelFormat, sizeof(PIXELFORMATDESCRIPTOR), &pfd);

	//Set it as the current 

	//SetPixelFormat�� �����쿡 �ѹ��� �����ؾ� ��
	//���� �����Ϸ��� �����츦 ���� ����
	//if (FALSE == SetPixelFormat(m_pDC->GetSafeHdc(), pixelFormat, &pfd))
	//{
	//	AfxMessageBox(CString("SelectPixelFormat failed"));
	//	return FALSE;
	//}

	return TRUE;
}

// ��� ���� ī�޶� ��ȯ �׽�Ʈ
void COpenGLwithMFCDlg::OnBnClickedButton2()
{
	CDC* pDCrightPic = m_picRight1.GetDC();
	//int ikkk = EBW8Image1Test.GetWidth(); //1000
	//int ikjk = EBW8Image1Test.GetHeight(); //707 �� �޴µ�...
	//EBW8Image1Test.Draw((HDC)pDCrightPic, 1.0f, 1.0f); // �̹����� �ȳ���. -> ���� ���̼��� �̻���

	//WWWWWWWWWWWWWWWWWWWWWWWWWWeVision -> CImage class ������.. @@@@@@@@@@@@@@@@@@@@@@@@@@@@

	//imageT1.Load(_T("C:/Users/LG/Documents/Visual Studio 2015/Projects/OpenGL with MFC/OpenGL with MFC/GrayTestSmall.bmp"));
	//int kk = imageT1.GetWidth();

	//iWidth -= 1;

	//TRACE("kk = %d", kk);


	//TODO: defineVAO �����Ͽ� ī�޶� �̵��̳� ����Ʈ �߰� ���� ����..?

	GLuint shaderProgram2;
	myDefineVAO(vao, shaderProgram2);

	glUseProgram(shaderProgram2);
	glBindVertexArray(vao);
}

//���⿡ ī�޶� ��ȯ ����
BOOL COpenGLwithMFCDlg::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_KEYDOWN)
	{
		switch (pMsg->wParam)
		{
		case VK_DOWN:
			m_textCurStat.SetWindowTextW(_T("down"));
			break;
		case VK_UP:
			m_textCurStat.SetWindowTextW(_T("up"));
			break;
		case VK_RIGHT:
			m_textCurStat.SetWindowTextW(_T("right"));
			break;
		case VK_LEFT:
			m_textCurStat.SetWindowTextW(_T("left"));
			break;
		default:
			m_textCurStat.SetWindowTextW(_T("unknown")); 
			break;
		}
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}

void COpenGLwithMFCDlg::myDefineVAO(GLuint &vao, GLuint &shaderProgram)
{
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);



	//====================try.old=======================

	pPosition = new float[iWidth*iHeight * 3];
	pColor = new float[iWidth*iHeight * 3];

	for (int i = 0; i < (iWidth*iHeight); i++) {

		float kkk = (float)i / (iWidth*iHeight); //tmp		
		pPosition[i * 3 + 0] = 0.95f - 1.9f * kkk; // x ��ǥ
		pPosition[i * 3 + 1] = -0.95f +1.9f * kkk; // y ��ǥ
		pPosition[i * 3 + 2] = 0.0f; // z ��ǥ

	}

	for (int i = 0; i < (iWidth*iHeight); i++) {
		float kkk = (float)i / (iWidth*iHeight); //tmp		
		pColor[i * 3 + 0] = kkk; // R
		pColor[i * 3 + 1] = 1.0f; // G
		pColor[i * 3 + 2] = 0.0f; // B
	}

	GLuint position_vbo, color_vbo;

	glGenBuffers(1, &position_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, position_vbo);
	glBufferData(GL_ARRAY_BUFFER, _msize(pPosition), pPosition, GL_STATIC_DRAW);

	glGenBuffers(1, &color_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, color_vbo);
	glBufferData(GL_ARRAY_BUFFER, _msize(pColor), pColor, GL_STATIC_DRAW);


	shaderProgram = create_program();

	GLint position_attribute = glGetAttribLocation(shaderProgram, "position");
	glBindBuffer(GL_ARRAY_BUFFER, position_vbo);
	glVertexAttribPointer(position_attribute, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(position_attribute);

	GLint color_attribute = glGetAttribLocation(shaderProgram, "color");
	glBindBuffer(GL_ARRAY_BUFFER, color_vbo);
	glVertexAttribPointer(color_attribute, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(color_attribute);

	glBindVertexArray(0);
}

void COpenGLwithMFCDlg::myCamRotate(GLuint &vao, GLuint &shaderProgram)
{
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	
	pPosition = new float[iWidth*iHeight * 3];
	pColor = new float[iWidth*iHeight * 3];

	for (int i = 0; i < (iWidth*iHeight); i++) {

		float kkk = (float)i / (iWidth*iHeight); //tmp		
		pPosition[i * 3 + 0] = 0.95f - 1.9f * kkk; // x ��ǥ
		pPosition[i * 3 + 1] = -0.95f + 1.9f * kkk; // y ��ǥ
		pPosition[i * 3 + 2] = 0.0f; // z ��ǥ

	}

	for (int i = 0; i < (iWidth*iHeight); i++) {
		float kkk = (float)i / (iWidth*iHeight); //tmp		
		pColor[i * 3 + 0] = kkk; // R
		pColor[i * 3 + 1] = 1.0f; // G
		pColor[i * 3 + 2] = 0.0f; // B
	}

	GLuint position_vbo, color_vbo;

	static float faCameraPos[3] = { -5.0f,-5.0f,-5.0f }; //1ȸ�� ���ǵǴ� ī�޶� ��ġ ����










	glGenBuffers(1, &position_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, position_vbo);
	glBufferData(GL_ARRAY_BUFFER, _msize(pPosition), pPosition, GL_STATIC_DRAW);

	glGenBuffers(1, &color_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, color_vbo);
	glBufferData(GL_ARRAY_BUFFER, _msize(pColor), pColor, GL_STATIC_DRAW);


	shaderProgram = create_program();

	GLint position_attribute = glGetAttribLocation(shaderProgram, "position");
	glBindBuffer(GL_ARRAY_BUFFER, position_vbo);
	glVertexAttribPointer(position_attribute, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(position_attribute);

	GLint color_attribute = glGetAttribLocation(shaderProgram, "color");
	glBindBuffer(GL_ARRAY_BUFFER, color_vbo);
	glVertexAttribPointer(color_attribute, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(color_attribute);

	glBindVertexArray(0);
}