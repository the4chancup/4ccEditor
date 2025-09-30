#ifndef _CRYPT_H
#define _CRYPT_H

#include <tchar.h>
#include "pstdint.h"

struct FileHeaderNew
{
    uint8_t mysteryData[64];
    uint32_t dataSize;
    uint32_t logoSize;
    uint32_t descSize;
    uint32_t serialLength;
    uint8_t hash[64];
    uint8_t fileTypeString[32];
    uint8_t gameVersionString[32];
};

struct FileHeaderOld
{
    uint8_t mysteryData[64];
    uint32_t dataSize;
    uint32_t logoSize;
    uint32_t descSize;
    uint32_t serialLength;
    uint8_t hash[64];
    uint8_t fileTypeString[32];
};

struct FileDescriptorNew
{
    uint8_t *encryptionHeader;
    struct FileHeaderNew *fileHeader;

    uint8_t *description;
    uint8_t *logo;
    uint8_t *data;
    uint8_t *serial;
};

struct FileDescriptorOld
{
    uint8_t *encryptionHeader;
    struct FileHeaderOld *fileHeader;

    uint8_t *description;
    uint8_t *logo;
    uint8_t *data;
    uint8_t *serial;
};

struct FileDescriptor15
{
    uint32_t dataSize;
    unsigned char startByte;
    uint32_t chunk0Size; //384
    uint32_t chunk1Size;
    uint32_t chunk2Size;

    uint8_t* chunk0; //Fixed length "Edit file" string
    uint8_t* chunk1lenBytes; //4 bytes that encode length of chunk 1
    uint8_t* chunk1; //PNG
    uint8_t* chunk2lenBytes; //4 bytes that encode length of chunk 2
    uint8_t* data; //Main edit data (chunk 2)
};

//struct FileDescriptor CRYPTER_EXPORT *createFileDescriptor();
typedef struct FileDescriptorOld* (__cdecl *pf_createFileDescriptorOld)();
typedef struct FileDescriptorNew* (__cdecl *pf_createFileDescriptorNew)();
typedef struct FileDescriptor15* (__cdecl* pf_createFileDescriptor15)();

//void CRYPTER_EXPORT destroyFileDescriptor(struct FileDescriptor *desc);
typedef void (__cdecl *pf_destroyFileDescriptorOld)(struct FileDescriptorOld*);
typedef void (__cdecl *pf_destroyFileDescriptorNew)(struct FileDescriptorNew*);
typedef void (__cdecl *pf_destroyFileDescriptor15)(struct FileDescriptor15*);

//void CRYPTER_EXPORT decryptWithKey(struct FileDescriptor *descriptor, const uint8_t *input, const char *masterKey);
typedef void (__cdecl *pf_decryptWithKeyOld)(struct FileDescriptorOld*, const uint8_t*, const char*);
typedef void (__cdecl *pf_decryptWithKeyNew)(struct FileDescriptorNew*, const uint8_t*, const char*);
typedef void (__cdecl *pf_decryptFile15)(struct FileDescriptor15*, const uint8_t*);

//uint8_t CRYPTER_EXPORT *encryptWithKey(const struct FileDescriptor *descriptor, int *size, const char *masterKey);
typedef uint8_t* (__cdecl *pf_encryptWithKeyOld)(const struct FileDescriptorOld*, int*, const char*);
typedef uint8_t* (__cdecl *pf_encryptWithKeyNew)(const struct FileDescriptorNew*, int*, const char*);
typedef uint8_t* (__cdecl *pf_encryptFile15)(const struct FileDescriptor15*, int*);

uint8_t *readFile(const TCHAR *path, uint32_t *sizePtr);

void writeFile(const TCHAR *path, const uint8_t *data, int size);

#endif /* _CRYPT_H */
