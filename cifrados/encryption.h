#ifndef ENCRYPTION_H
#define ENCRYPTION_H

#include "common.h"
#include <bcrypt.h>

typedef struct
{
	unsigned int i;
	unsigned int j;
	unsigned char s[256];

} Rc4Context;

VOID XorByInputKey(IN PBYTE pShellcode, IN SIZE_T sShellcodeSize, IN PBYTE bKey, IN SIZE_T sKeySize);
void rc4Cipher(Rc4Context* context, const unsigned char* input, unsigned char* output, size_t length);

#endif