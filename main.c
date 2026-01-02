#include <windows.h>
#include <GL/gl.h>
#include "window.h"

static const LPCSTR class_name = TEXT("HelloWorldWindowClass");
static const LPCSTR window_name = TEXT("Hello world!");
static const DWORD style = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX;
static const int width = 800;
static const int height = 600;

int
main()
{
	window_create(class_name, window_name, style, width, height);
	glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
	while (window_update()) {
		glClear(GL_COLOR_BUFFER_BIT);
	}
	window_destroy();
	return 0;
}