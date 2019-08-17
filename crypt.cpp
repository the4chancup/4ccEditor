#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>

#include "crypt.h"

//encrypter & decrypter helpers ...
uint8_t *readFile(const TCHAR *path, uint32_t *sizePtr)
{
	struct _stat file;
	uint8_t *input;
	int size;
    FILE *inStream = _tfopen(path, _T("rb"));
    if (!inStream)
        return NULL;

    if (_tstat(path, &file))
        return NULL;
    size = file.st_size;

    input = (uint8_t *)malloc(size);
    fread(input, 1, size, inStream);
    fclose(inStream);

    if (sizePtr)
        *sizePtr = size;

    return input;
}


void writeFile(const TCHAR *path, const uint8_t *data, int size)
{
    FILE *outStream = _tfopen(path, _T("wb"));
    if (!outStream)
        return;
    fwrite(data, 1, size, outStream);
    fclose(outStream);
}
