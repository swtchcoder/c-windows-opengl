#ifndef _WINDOW_H
#define _WINDOW_H

void window_create(const char *name, const int resizable, const int width, const int height);
int window_update(void);
void window_destroy(void);

#endif