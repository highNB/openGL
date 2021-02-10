
// OpenGL with MFCDlg.cpp : 구현 파일
//

#include "stdafx.h"
#include "OpenGL with MFC.h"
#include "OpenGL with MFCDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
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


// COpenGLwithMFCDlg 대화 상자


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


// COpenGLwithMFCDlg 메시지 처리기

BOOL COpenGLwithMFCDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
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

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.


	iWidth = WIDTH_TEST;
	iHeight = HEIGHT_TEST;


	//OpenGL context 생성
	if (!GetRenderingContext())
	{
		AfxMessageBox(CString("OpenGL 초기화중 에러가 발생하여 프로그램을 실행할 수 없습니다."));
		return -1;
	}
	
	GLuint shaderProgram;
	defineVAO(vao, shaderProgram);

	glUseProgram(shaderProgram);
	glBindVertexArray(vao);

	SetTimer(1000, 15, NULL); //15 =: 60 FPS / 30 =: 30FPS

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
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

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void COpenGLwithMFCDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR COpenGLwithMFCDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void COpenGLwithMFCDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.

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
	//				포인트 사이즈 변경
	//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@//@@@
	//실시간인지 테스드해봄 (밑으로4줄)				 //@@@
	if (dotDirection) dotSize += 0.5f;				 //@@@
	else dotSize -= 0.5f;							 //@@@
	if (5.0f > dotSize) dotDirection = true;		 //@@@
	else if (15.0f < dotSize) dotDirection = false;	 //@@@
	glPointSize(dotSize);							 //@@@
	//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@//@@@
	//
	//				프레임 확인용
	//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@//@@@
	DWORD curTime = GetCurrentTime(); // gettick64 사용하는것이 더 안전함 49.71일뒤에 오버플로우발생
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
	//				포인트 2개 교차
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
	//				카메라 이동
	//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@//@@@












	//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@//@@@




	glDrawArrays(GL_POINTS, 0, (iWidth*iHeight));
	
	//antialiasing
	//glEnable(GL_POINT_SMOOTH); 
	
	//화면 업데이트
	SwapBuffers(m_pDC->GetSafeHdc());
}

//픽처 컨트롤에 윈도우 생성 부분 (아직 이해 못함)
BOOL COpenGLwithMFCDlg::GetRenderingContext()
{
	//픽처 컨트롤에만 그리도록 DC 생성
	//참고 https://goo.gl/CK36zE
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


	//참고 http://gamedev.stackexchange.com/a/30443
	GLint attribs[] =
	{
		//OpenGL 3.3 사용
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
		pPosition[i * 3 + 0] = -0.95f + 1.9f * kkk; // x 좌표
		pPosition[i * 3 + 1] = -0.95f + 1.9f * kkk; // y 좌표
		pPosition[i * 3 + 2] = 0.0f; // z 좌표

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

// 쉐이더 관련
GLuint COpenGLwithMFCDlg::create_program() {

	//vertexShader = 위치! 3D(모델) -> 2D(모니터)
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

	//fragmentShader = 색상, 위에서 color_from_vshader받아서 사용하는듯
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
		TRACE(CString("ERROR: vertex shader 컴파일 실패 ") + CString(infoLog) + CString("\n"));
	}

	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		TRACE(CString("ERROR: fragment shader 컴파일 실패 ") + CString(infoLog) + CString("\n"));
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

		TRACE(CString("ERROR: shader program 연결 실패 ") + CString(infoLog) + CString("\n"));
	}

	return shaderProgram;
}

// 뭐 하는지 모름
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

// 모름 2
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
	//PIXELFORMATDESCRIPTOR pfd; //밑 주석에서 사용하는데 사용 안해서 주석처리

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

	//SetPixelFormat은 윈도우에 한번만 실행해야 함
	//새로 설정하려면 윈도우를 새로 생성
	//if (FALSE == SetPixelFormat(m_pDC->GetSafeHdc(), pixelFormat, &pfd))
	//{
	//	AfxMessageBox(CString("SelectPixelFormat failed"));
	//	return FALSE;
	//}

	return TRUE;
}

// 잠시 접고 카메라 전환 테스트
void COpenGLwithMFCDlg::OnBnClickedButton2()
{
	CDC* pDCrightPic = m_picRight1.GetDC();
	//int ikkk = EBW8Image1Test.GetWidth(); //1000
	//int ikjk = EBW8Image1Test.GetHeight(); //707 잘 받는데...
	//EBW8Image1Test.Draw((HDC)pDCrightPic, 1.0f, 1.0f); // 이미지가 안나옴. -> 동글 라이센스 이상함

	//WWWWWWWWWWWWWWWWWWWWWWWWWWeVision -> CImage class 진행중.. @@@@@@@@@@@@@@@@@@@@@@@@@@@@

	//imageT1.Load(_T("C:/Users/LG/Documents/Visual Studio 2015/Projects/OpenGL with MFC/OpenGL with MFC/GrayTestSmall.bmp"));
	//int kk = imageT1.GetWidth();

	//iWidth -= 1;

	//TRACE("kk = %d", kk);


	//TODO: defineVAO 수정하여 카메라 이동이나 포인트 추가 삭제 구현..?

	GLuint shaderProgram2;
	myDefineVAO(vao, shaderProgram2);

	glUseProgram(shaderProgram2);
	glBindVertexArray(vao);
}

//여기에 카메라 전환 진행
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
		pPosition[i * 3 + 0] = 0.95f - 1.9f * kkk; // x 좌표
		pPosition[i * 3 + 1] = -0.95f +1.9f * kkk; // y 좌표
		pPosition[i * 3 + 2] = 0.0f; // z 좌표

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
		pPosition[i * 3 + 0] = 0.95f - 1.9f * kkk; // x 좌표
		pPosition[i * 3 + 1] = -0.95f + 1.9f * kkk; // y 좌표
		pPosition[i * 3 + 2] = 0.0f; // z 좌표

	}

	for (int i = 0; i < (iWidth*iHeight); i++) {
		float kkk = (float)i / (iWidth*iHeight); //tmp		
		pColor[i * 3 + 0] = kkk; // R
		pColor[i * 3 + 1] = 1.0f; // G
		pColor[i * 3 + 2] = 0.0f; // B
	}

	GLuint position_vbo, color_vbo;

	static float faCameraPos[3] = { -5.0f,-5.0f,-5.0f }; //1회만 정의되는 카메라 위치 선언










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