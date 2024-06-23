#ifndef OBFUSCATION_H
#define OBFUSCATION_H

#include "common.h"

BOOL GenerateIpv4Output(unsigned char* pShellcode, SIZE_T ShellcodeSize);
BOOL GenerateIpv6Output(unsigned char* pShellcode, SIZE_T ShellcodeSize);
BOOL GenerateMacOutput(unsigned char* pShellcode, SIZE_T ShellcodeSize);
BOOL GenerateUuidOutput(unsigned char* pShellcode, SIZE_T ShellcodeSize);

#endif