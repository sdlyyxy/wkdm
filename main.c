#include "WKdm.h"
#include <stdio.h>
#include <assert.h>
#include <string.h>

int main(int argc, char* argv[])
{
	char page[4096];
	char outpage[4096];
	if (argc != 3)
		return 111;

	int bytesIn=0;
	int bytesOut=0;
	FILE* in = fopen(argv[1], "rb");
	assert(in);

	FILE* out = fopen(argv[2], "wb");
	assert(out);

	while (!feof(in)) {
		size_t bread = fread(page, 1, 4096, in);
		bytesIn+=bread;
		if (bread < 4096)
			memset(page+bread, 0, 4096-bread);
		size_t wwrite = WKdm_compress((WK_word*)page, (WK_word*)outpage, 1024);
		bytesOut+=wwrite;
		fwrite(outpage, 1, wwrite, out);
		printf("Packed %zu bytes into %zu bytes\n", bread, wwrite);
	}

	fclose(out);
	fclose(in);

	printf("Compressed size is %.2f%% of the original size.\n",(double)bytesOut/bytesIn*100);
	return 0;
}

