/*******************/
/* System includes */
/*******************/
#include <windows.h>		// Header File For Windows
#include <gl\gl.h>			// Header File For The OpenGL32 Library
#include <gl\glu.h>			// Header File For The GLu32 Library
#include "stdio.h"
//#include "mio.c"

/****************/
/* Self include */
/****************/
#include "mioglgraph.h"

/******************/
/* Other includes */
/******************/
#include "mio.h"
#include "mdio.h"

#include "mioerr.h"

// Test to make certain we're not accidentally including <windows.h> which
// might allow for windows contamination of platform independent code.
#ifdef _INC_WINDOWS
// disabled because SDL is platform independent but it includes windows.h on windows
//xxx
#endif

/**********/
/* Macros */
/**********/

#define CAP8(x) ((GLubyte)(((x) < 255 && (x) >= 0) ? (x) : 255))
#define GET_X_LPARAM(lp)                        ((int)(short)LOWORD(lp))
#define GET_Y_LPARAM(lp)                        ((int)(short)HIWORD(lp))

/*************/
/* Constants */
/*************/
#define MIO_SDL_WINDOW_TITLE "Turing SDL Window"

/********************/
/* Global variables */
/********************/

static int stGLWinOpen;
static int stSDLLightingOn;
static BOOL stGLWinClosed;

static int myWidth,myHeight;

// windows specific
HDC			hDC=NULL;		// Private GDI Device Context
HGLRC		hRC=NULL;		// Permanent Rendering Context
HWND		hWnd=NULL;		// Holds Our Window Handle
HINSTANCE	hInstance;		// Holds The Instance Of The Application

/*********/
/* Types */
/*********/

/**********************/
/* External variables */
/**********************/

/********************/
/* Static constants */
/********************/

/********************/
/* Static variables */
/********************/

static struct WM_MOUSE {
	int X;
	int Y;
	short buttonmask;
	BOOL pressed;
} Cursor;

/******************************/
/* Static callback procedures */
/******************************/

/*********************/
/* Static procedures */
/*********************/
void MySetupOpenGL() {
		GLfloat LightAmbient[]= { 0.5f, 0.5f, 0.5f, 1.0f };
		GLfloat LightDiffuse[]= { 1.0f, 1.0f, 1.0f, 1.0f };
		GLfloat LightPosition[]= { 0.0f, 0.0f, 2.0f, 1.0f }; 
		
		// better lines		
		glEnable(GL_LINE_SMOOTH);
		glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
		glLineWidth(1.5f);

		glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
		glClearColor(0.0f, 0.0f, 0.0f, 0.5f);				// Black Background
		glClearDepth(1.0f);									// Depth Buffer Setup
		glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
		glDepthFunc(GL_LEQUAL);								// The Type Of Depth Testing To Do
		glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations

		//lighting
		glShadeModel(GL_SMOOTH);
		glLightfv(GL_LIGHT1, GL_AMBIENT, LightAmbient);

		glLightfv(GL_LIGHT1, GL_DIFFUSE, LightDiffuse);             // Setup The Diffuse Light
		glLightfv(GL_LIGHT1, GL_POSITION,LightPosition);            // Position The Light
		glEnable(GL_LIGHT1);

		glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
		glLoadIdentity();	
}
LRESULT	CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);	// Declaration For WndProc

/***********************/
/* External procedures */
/***********************/
extern void	Language_Execute_EventQueueInsert(int pmStream,
	struct EventDescriptor *pmEvent);

extern void	MIOGLGraph_InitRun () {
	stGLWinOpen = FALSE;
	stSDLLightingOn = FALSE;
	stGLWinClosed = FALSE;
}
extern void	MIOGLGraph_CloseWin ()
{
	if(stGLWinOpen){
		if (hRC)											// Do We Have A Rendering Context?
		{
			if (!wglMakeCurrent(NULL,NULL))					// Are We Able To Release The DC And RC Contexts?
			{
				MessageBox(NULL,"Release Of DC And RC Failed.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
			}

			if (!wglDeleteContext(hRC))						// Are We Able To Delete The RC?
			{
				MessageBox(NULL,"Release Rendering Context Failed.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
			}
			hRC=NULL;										// Set RC To NULL
		}

		if (hDC && !ReleaseDC(hWnd,hDC))					// Are We Able To Release The DC
		{
			//MessageBox(NULL,"Release Device Context Failed.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
			hDC=NULL;										// Set DC To NULL
		}

		if (hWnd && !DestroyWindow(hWnd))					// Are We Able To Destroy The Window?
		{
			//MessageBox(NULL,"Could Not Release hWnd.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
			hWnd=NULL;										// Set hWnd To NULL
		}

		if (!UnregisterClass("OpenGL",hInstance))			// Are We Able To Unregister Class
		{
			MessageBox(NULL,"Could Not Unregister OpenGL Window Class.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
			hInstance=NULL;									// Set hInstance To NULL
		}
		stGLWinOpen = FALSE;
	}
}
extern BOOL	MIOGLGraph_NewWin (OOTint width,OOTint height)
{
	GLuint		PixelFormat;			// Holds The Results After Searching For A Match
	WNDCLASS	wc;						// Windows Class Structure
	DWORD		dwExStyle;				// Window Extended Style
	DWORD		dwStyle;				// Window Style
	RECT		WindowRect;				// Grabs Rectangle Upper Left / Lower Right Values
	static PIXELFORMATDESCRIPTOR pfd = {				// pfd Tells Windows How We Want Things To Be
			sizeof(PIXELFORMATDESCRIPTOR),				// Size Of This Pixel Format Descriptor
			1,											// Version Number
			PFD_DRAW_TO_WINDOW |						// Format Must Support Window
			PFD_SUPPORT_OPENGL |						// Format Must Support OpenGL
			PFD_DOUBLEBUFFER,							// Must Support Double Buffering
			PFD_TYPE_RGBA,								// Request An RGBA Format
			24,										// Select Our Color Depth
			0, 0, 0, 0, 0, 0,							// Color Bits Ignored
			0,											// No Alpha Buffer
			0,											// Shift Bit Ignored
			0,											// No Accumulation Buffer
			0, 0, 0, 0,									// Accumulation Bits Ignored
			16,											// 16Bit Z-Buffer (Depth Buffer)  
			0,											// No Stencil Buffer
			0,											// No Auxiliary Buffer
			PFD_MAIN_PLANE,								// Main Drawing Layer
			0,											// Reserved
			0, 0, 0										// Layer Masks Ignored
		};
	if(!stGLWinOpen){
		WindowRect.left=(long)0;			// Set Left Value To 0
		WindowRect.right=(long)width;		// Set Right Value To Requested Width
		WindowRect.top=(long)0;				// Set Top Value To 0
		WindowRect.bottom=(long)height;		// Set Bottom Value To Requested Height

		hInstance			= GetModuleHandle(NULL);				// Grab An Instance For Our Window
		wc.style			= CS_HREDRAW | CS_VREDRAW | CS_OWNDC;	// Redraw On Size, And Own DC For Window.
		wc.lpfnWndProc		= (WNDPROC) WndProc;					// WndProc Handles Messages
		wc.cbClsExtra		= 0;									// No Extra Window Data
		wc.cbWndExtra		= 0;									// No Extra Window Data
		wc.hInstance		= hInstance;							// Set The Instance
		wc.hIcon			= LoadIcon(NULL, IDI_WINLOGO);			// Load The Default Icon
		wc.hCursor			= LoadCursor(NULL, IDC_ARROW);			// Load The Arrow Pointer
		wc.hbrBackground	= NULL;									// No Background Required For GL
		wc.lpszMenuName		= NULL;									// We Don't Want A Menu
		wc.lpszClassName	= "OpenGL";								// Set The Class Name

		if (!RegisterClass(&wc))									// Attempt To Register The Window Class
		{
			MessageBox(NULL,"Failed To Register The Window Class.","ERROR",MB_OK|MB_ICONEXCLAMATION);
			return FALSE;											// Return FALSE
		}

		dwExStyle=WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;			// Window Extended Style
		dwStyle=WS_OVERLAPPEDWINDOW;							// Windows Style
		AdjustWindowRectEx(&WindowRect, dwStyle, FALSE, dwExStyle);		// Adjust Window To True Requested Size

		// Create The Window
		if (!(hWnd=CreateWindowEx(	dwExStyle,							// Extended Style For The Window
									"OpenGL",							// Class Name
									"Turing OpenGL Window",								// Window Title
									dwStyle |							// Defined Window Style
									WS_CLIPSIBLINGS |					// Required Window Style
									WS_CLIPCHILDREN,					// Required Window Style
									0, 0,								// Window Position
									WindowRect.right-WindowRect.left,	// Calculate Window Width
									WindowRect.bottom-WindowRect.top,	// Calculate Window Height
									NULL,								// No Parent Window
									NULL,								// No Menu
									hInstance,							// Instance
									NULL)))								// Dont Pass Anything To WM_CREATE
		{
			MIOGLGraph_CloseWin();								// Reset The Display
			MessageBox(NULL,"OpenGL Window Creation Error.","ERROR",MB_OK|MB_ICONEXCLAMATION);
			return FALSE;								// Return FALSE
		}
	
		if (!(hDC=GetDC(hWnd)))							// Did We Get A Device Context?
		{
			MIOGLGraph_CloseWin();								// Reset The Display
			MessageBox(NULL,"Can't Create A GL Device Context.","ERROR",MB_OK|MB_ICONEXCLAMATION);
			return FALSE;								// Return FALSE
		}

		if (!(PixelFormat=ChoosePixelFormat(hDC,&pfd)))	// Did Windows Find A Matching Pixel Format?
		{
			MIOGLGraph_CloseWin();								// Reset The Display
			MessageBox(NULL,"Can't Find A Suitable PixelFormat.","ERROR",MB_OK|MB_ICONEXCLAMATION);
			return FALSE;								// Return FALSE
		}

		if(!SetPixelFormat(hDC,PixelFormat,&pfd))		// Are We Able To Set The Pixel Format?
		{
			MIOGLGraph_CloseWin();								// Reset The Display
			MessageBox(NULL,"Can't Set The PixelFormat.","ERROR",MB_OK|MB_ICONEXCLAMATION);
			return FALSE;								// Return FALSE
		}

		if (!(hRC=wglCreateContext(hDC)))				// Are We Able To Get A Rendering Context?
		{
			MIOGLGraph_CloseWin();								// Reset The Display
			MessageBox(NULL,"Can't Create A GL Rendering Context.","ERROR",MB_OK|MB_ICONEXCLAMATION);
			return FALSE;								// Return FALSE
		}

		if(!wglMakeCurrent(hDC,hRC))					// Try To Activate The Rendering Context
		{
			MIOGLGraph_CloseWin();								// Reset The Display
			MessageBox(NULL,"Can't Activate The GL Rendering Context.","ERROR",MB_OK|MB_ICONEXCLAMATION);
			return FALSE;								// Return FALSE
		}
		Cursor.X = 0;
		Cursor.Y = 0;
		Cursor.buttonmask = 0;
		Cursor.pressed = FALSE;
		ShowWindow(hWnd,SW_SHOW);						// Show The Window
		SetForegroundWindow(hWnd);						// Slightly Higher Priority
		SetFocus(hWnd);									// Sets Keyboard Focus To The Window

		//ogl stuff
		MySetupOpenGL();

		stGLWinOpen = TRUE;
		return TRUE;
	}
	return FALSE;
}

LRESULT CALLBACK WndProc(	HWND	hWnd,			// Handle For This Window
							UINT	uMsg,			// Message For This Window
							WPARAM	wParam,			// Additional Message Information
							LPARAM	lParam)			// Additional Message Information
{
	switch (uMsg) {
	case (WM_LBUTTONDOWN): // | WM_LBUTTONUP | WM_RBUTTONUP):
		Cursor.X = GET_X_LPARAM(lParam);
		Cursor.Y = GET_Y_LPARAM(lParam);
		Cursor.buttonmask = wParam;
		Cursor.pressed = TRUE;
		return 0;
	case WM_MOUSEMOVE:
		Cursor.X = GET_X_LPARAM(lParam);
		Cursor.Y = GET_Y_LPARAM(lParam);		
		return 0;
	case WM_CLOSE:
		MIOGLGraph_CloseWin();
		stGLWinClosed = TRUE;
		return 0;
	}
	// Pass All Unhandled Messages To DefWindowProc
	return DefWindowProc(hWnd,uMsg,wParam,lParam);
}

extern void MIOGLGraph_MouseWhere(OOTint *pmX, OOTint *pmY)
{
	*pmX = Cursor.X;
	*pmY = Cursor.Y;
	/*char buffer[256];
	snprintf(buffer, sizeof(buffer), "%s%d%s%d", "X: ", xPos, " Y: ", yPos);
	MIOFILE	pmMIOFILE;
	memset(&pmMIOFILE, 0, sizeof(MIOFILE));
	pmMIOFILE.windowType = 77;
	pmMIOFILE.windowPtr = (void *)MIO_selectedRunWindow;*/
	/*MIOWin_OutputText(MIO_selectedRunWindow, buffer);*/
}

extern BOOL MIOGLGraph_ButtonWait(OOTint *pmX, OOTint *pmY, OOTint *btn)
{
	*pmX = Cursor.X;
	*pmY = Cursor.Y;
	*btn = Cursor.buttonmask;
	if (Cursor.pressed == TRUE) {
		Cursor.pressed = FALSE;
		return TRUE;
	}
	return Cursor.pressed;
}

extern BOOL MIOGLGraph_Status()
{
	return !stGLWinClosed;
}

extern void	MIOGLGraph_Update ()
{
	if(stGLWinOpen){
		//SDL_Flip(stSDLScreen);
		//SDL_UpdateRect(stSDLScreen, 0, 0, 0, 0);
		SwapBuffers(hDC);
	}
	if(stGLWinClosed){ // check here because doing it in the windows event loop causes problems
		stGLWinClosed = FALSE;
		ABORT_WITH_ERRMSG (E_FONT_BAD_FONT_SELECT_STR, "OpenGl Window Closed By User");
	}
}

extern void	MIOGLGraph_Cls ()
{
	if(stGLWinOpen){
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clear Screen And Depth Buffer
	}
}
//light
extern void	MIOGLGraph_SetLight (OOTint lighting)
{
	if(stGLWinOpen){
		if(lighting) {
			glEnable(GL_LIGHTING);
			stSDLLightingOn = TRUE;
		} else {
			glDisable(GL_LIGHTING);
			stSDLLightingOn = FALSE;
		}
	}
}

// matrix stack
extern void	MIOGLGraph_ClearMatrix ()
{
	if(stGLWinOpen){
		glLoadIdentity();
	}
}

extern void	MIOGLGraph_PushMatrix ()
{
	if(stGLWinOpen){
		glPushMatrix();
	}
}

extern void	MIOGLGraph_PopMatrix ()
{
	if(stGLWinOpen){
		glPopMatrix();
	}
}
// matrix manipulation
extern void	MIOGLGraph_Translate (OOTreal x,OOTreal y,OOTreal z)
{
	if(stGLWinOpen){
		glTranslatef((GLfloat)x,(GLfloat)y,(GLfloat)z);
	}
}
extern void	MIOGLGraph_Rotate (OOTreal angle,OOTreal x,OOTreal y,OOTreal z)
{
	if(stGLWinOpen){
		glRotatef((GLfloat)angle,(GLfloat)x,(GLfloat)y,(GLfloat)z);
	}
}
extern void	MIOGLGraph_Scale (OOTreal x,OOTreal y,OOTreal z)
{
	if(stGLWinOpen){
		glScalef((GLfloat)x,(GLfloat)y,(GLfloat)z);
	}
}
// drawing
extern void	MIOGLGraph_Line (
								OOTreal x1,OOTreal y1,OOTreal z1, 
								OOTreal x2,OOTreal y2,OOTreal z2,
								OOTint r, OOTint g, OOTint b)
{
	if(stGLWinOpen){
		if(stSDLLightingOn) { // because winding is weird. Hafta light both sides
			float color[] = { r/255.0f, g/255.0f, b/255.0f, 1.0f };
			glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, color);
		}

		//glColor3f(r/255.0f,g/255.0f,b/255.0f);
		glColor3ub(CAP8(r), CAP8(g), CAP8(b));

		glBegin(GL_LINES);
		glVertex3f((GLfloat)x1, (GLfloat)y1, (GLfloat)z1); 
		glVertex3f((GLfloat)x2, (GLfloat)y2, (GLfloat)z2);
		glEnd();

		if(stSDLLightingOn) { // because winding is weird. Hafta light both sides

		}
	}
}

extern void	MIOGLGraph_FillTriangle (
								OOTreal x1,OOTreal y1,OOTreal z1, 
								OOTreal x2,OOTreal y2,OOTreal z2,
								OOTreal x3,OOTreal y3,OOTreal z3,
								OOTint r, OOTint g, OOTint b)
{
	if(stGLWinOpen){
		if(stSDLLightingOn) { // because winding is weird. Hafta light both sides
			float color[] = { r/255.0f, g/255.0f, b/255.0f, 1.0f };
			glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, color);
		}

		glColor3ub(CAP8(r), CAP8(g), CAP8(b));
		
		glBegin(GL_TRIANGLES);
		glVertex3f((GLfloat)x1, (GLfloat)y1, (GLfloat)z1);
		glVertex3f((GLfloat)x2, (GLfloat)y2, (GLfloat)z2);
		glVertex3f((GLfloat)x3, (GLfloat)y3, (GLfloat)z3);
		glEnd();
	}
}

extern void	MIOGLGraph_Triangle (
								OOTreal x1,OOTreal y1,OOTreal z1, 
								OOTreal x2,OOTreal y2,OOTreal z2,
								OOTreal x3,OOTreal y3,OOTreal z3,
								OOTint r, OOTint g, OOTint b)
{
	if(stGLWinOpen){		
		if(stSDLLightingOn) { // because winding is weird. Hafta light both sides
			float color[] = { r/255.0f, g/255.0f, b/255.0f, 1.0f };
			glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, color);
		}
		glColor3ub(CAP8(r), CAP8(g), CAP8(b));
		
		glBegin(GL_LINE_LOOP); // draw rect with quads
		glVertex3f((GLfloat)x1, (GLfloat)y1, (GLfloat)z1);
		glVertex3f((GLfloat)x2, (GLfloat)y2, (GLfloat)z2);
		glVertex3f((GLfloat)x3, (GLfloat)y3, (GLfloat)z3);
		glEnd();
	}
}