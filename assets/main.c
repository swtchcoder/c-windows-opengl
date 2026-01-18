#include <stdio.h>
#include <stdlib.h>
#include "config.h"

void textual_process(void);

static FILE *bin;
static FILE *header;
static const long textual_count = sizeof(textuals) / sizeof(source_t);
source_t textual;
static FILE *current;
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
		textual = textuals[i];
		textual_process();
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
	current = fopen(textual.filename, "r");
	if (!current) {
		perror(textual.filename);
		exit(1);
	}
	fseek(current, 0, SEEK_END);
	size = ftell(current);
	rewind(current);
	buffer = malloc(size);
	if (!buffer) {
		perror(textual.filename);
		exit(1);
	}
	sizep = fread(buffer, 1, size, current);
	if (sizep != size) {
		if (ferror(current)) {
			perror(textual.filename);
			exit(1);
		}
		size = sizep;
		buffer = realloc(buffer, size);
		if (!buffer) {
			perror(textual.filename);
			exit(1);
		}
	}
	sizep = fwrite(buffer, 1, size, bin);
	if (sizep != size) {
		perror(textual.filename);
		exit(1);
	}
	fprintf(header, "long %s_index = %ld;\nlong %s_size = %ld;\n\n", textual.name, index, textual.name, index + size);
	index += size;
	fclose(current);
}