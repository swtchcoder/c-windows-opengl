#include <stdio.h>
#include <stdlib.h>
#include "assets_import.h"

static FILE *f;

void
assets_open(void)
{
	f = fopen("assets.bin", "rb");
	if (!f) {
		perror("assets.bin");
		exit(EXIT_FAILURE);
	}
}

void *
assets_load(const size_t offset, const size_t size) {
	void *buffer;
	fseek(f, offset, SEEK_SET);
	if (fread(buffer, 1, size, f) != size) {
		perror("assets.bin");
		exit(EXIT_FAILURE); 
	}
	return buffer;
}

void
assets_close(void)
{
	fclose(f);
}