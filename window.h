#ifndef _WINDOW_H
#define _WINDOW_H

#include <windows.h>

void window_create(const LPCSTR class_name, const LPCSTR name, const DWORD style, const int width, const int height);
int window_update(void);
void window_destroy(void);

#endif