#include <GL/gl.h>
#include "window.h"

static const char *window_name = "Hello world!";
static const int width = 800;
static const int height = 600;

int
main()
{
	window_create(window_name, 1, width, height);
	glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
	while (window_update()) {
		glClear(GL_COLOR_BUFFER_BIT);
	}
	window_destroy();
	return 0;
}