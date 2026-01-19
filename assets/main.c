#include <stdio.h>
#include <stdlib.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"
#include "config.h"

void textual_process(void);
void image_process(void);

static FILE *bin;
static FILE *header;
static const long textual_count = sizeof(textuals) / sizeof(source_t);
source_t source;
static FILE *f;
static const long image_count = sizeof(images) / sizeof(source_t);
static long size;
static long index = 0;

int
main(void)
{
	long i;
	bin = fopen("assets.bin", "wb");
	if (!bin) {
		perror("assets.bin");
		return 1;
	}
	header = fopen("assets.h", "w");
	if (!header) {
		perror("assets.h");
		return 1;
	}
	for (i = 0; i < textual_count; i++) {
		source = textuals[i];
		textual_process();
	}
	for (i = 0; i < image_count; i++) {
		source = images[i];
		image_process();
	}
	fclose(bin);
	fclose(header);
	return 0;
}

void
textual_process(void)
{
	char *buffer;
	long sizep;
	f = fopen(source.filename, "r");
	if (!f) {
		perror(source.filename);
		exit(1);
	}
	fseek(f, 0, SEEK_END);
	size = ftell(f);
	rewind(f);
	buffer = malloc(size);
	if (!buffer) {
		perror(source.filename);
		exit(1);
	}
	sizep = fread(buffer, 1, size, f);
	if (sizep != size) {
		if (ferror(f)) {
			perror(source.filename);
			exit(1);
		}
		size = sizep;
		buffer = realloc(buffer, size);
		if (!buffer) {
			perror(source.filename);
			exit(1);
		}
	}
	sizep = fwrite(buffer, 1, size, bin);
	if (sizep != size) {
		perror(source.filename);
		exit(1);
	}
	free(buffer);
	fprintf(header, "long %s_index = %ld;\nlong %s_size = %ld;\n\n", source.name, index, source.name, index + size);
	index += size;
	fclose(f);
}

void
image_process(void)
{
	int width, height, channels;
	long sizep;
	unsigned char *buffer = stbi_load(source.filename, &width, &height, &channels, 0);
	if (!buffer) {
		fprintf(stderr, "%s: Error loading image\n", source.filename);
		exit(1);
	}
	size = width * height;
	sizep = fwrite(buffer, 1, size, bin);
	if (sizep != size) {
		perror(source.filename);
		exit(1);
	}
	fprintf(header, "long %s_index = %ld;\nlong %s_size = %ld;\nint %s_width = %d;\nint %s_height = %d;\nint %s_channels = %d;\n\n", source.name, index, source.name, index + size, source.name, width, source.name, height, source.name, channels);
	index += size;
	stbi_image_free(buffer);
}