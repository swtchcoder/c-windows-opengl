#include <windows.h>
#include <GL/gl.h>

static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

static const LPCSTR class_name = TEXT("HelloWorldWindowClass");
static const LPCSTR window_name = TEXT("Hello world!");
static const DWORD style = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX;
static const int width = 800;
static const int height = 600;
static const PIXELFORMATDESCRIPTOR pfd = {
	sizeof(PIXELFORMATDESCRIPTOR),
	1,
	PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
	PFD_TYPE_RGBA,
	32,
	0, 0,
	0,0,
	0,0, 
	0, 0,
	0,
	0, 0, 0, 0,
	24,
	8,
	0,
	PFD_MAIN_PLANE, 
	0, 
	0, 0, 0
};

int
main()
{
	WNDCLASS wc = {0};
	MSG msg;
	HWND hwnd;
	HDC hdc;
	HGLRC ctx;
	int pixel_format;
	int loop;
	wc.lpfnWndProc = WndProc;
	wc.hInstance = GetModuleHandle(NULL);
	wc.lpszClassName = class_name;
	if (!RegisterClass(&wc)) {
		MessageBox(NULL, TEXT("Could not register window class"), NULL, MB_ICONERROR);
		return 1;
	}
	hwnd = CreateWindowA(
		class_name, 
		window_name,
		style,
		CW_USEDEFAULT, 
		CW_USEDEFAULT, 
		width, 
		height, 
		NULL, 
		NULL,
		wc.hInstance, 
		NULL
	);
	if (!hwnd) {
		MessageBox(NULL, TEXT("Could not create window"), NULL, MB_ICONERROR);
		return 1;
	}
	hdc = GetDC(hwnd);
	pixel_format = ChoosePixelFormat(hdc, &pfd);
	SetPixelFormat(hdc, pixel_format, &pfd);
	ctx = wglCreateContext(hdc);
	if (!ctx) {
		MessageBox(NULL, TEXT("Could not create OpenGL context"), NULL, MB_ICONERROR);
		return 1;
	}
	if (!wglMakeCurrent(hdc, ctx)) {
		MessageBox(NULL, TEXT("Could not make OpenGL context current"), NULL, MB_ICONERROR);
		return 1;
	}
	ShowWindow(hwnd, SW_SHOW);
	UpdateWindow(hwnd);
	loop = 1;
	glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
	while (loop) {
		if (PeekMessageA(&msg, NULL, 0, 0, PM_REMOVE)) {
			if (msg.message == WM_QUIT) {
				loop = 0;
			}
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		glClear(GL_COLOR_BUFFER_BIT);
		SwapBuffers(hdc);
	}
	wglMakeCurrent(NULL, NULL);
	wglDeleteContext(ctx);
	ReleaseDC(hwnd, hdc);
	DestroyWindow(hwnd);
	return 0;
}

static LRESULT CALLBACK
WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg) {
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hwnd, msg, wParam, lParam);
}