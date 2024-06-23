#include "common.h"
#include "encryption.h"
#include "obfuscation.h"
#include <stdlib.h>
#define _CRT_SECURE_NO_WARNINGS 1

// Key for encryptions
unsigned char key[] = {
	0x00, 0x01, 0x02, 0x03, 0x04, 0x05
};

// Visual Helps
void banner() {
	printf("----- HELL SHELL -----\n");
	printf("Zeropio's Custom Implementation\n\n");
}

void usage() {
	printf("[-] Usage: HellShell.exe <shellcode file> <encryption/obfuscation method>\n");
	printf("[?] Encryption options: xor, rc4\n");
	printf("[?] Obfuscation options: ipv4, ipv6, mac, uuid\n");
}

// Get file contents
unsigned char* parser(char* path, int* size) {
	FILE* file = NULL;
	errno_t err = fopen_s(&file, path, "rb"); // Open in binary mode
	if (err != 0 || file == NULL) {
		perror("Error opening file");
		exit(-1);
	}

	// Find the file size
	fseek(file, 0, SEEK_END);
	*size = ftell(file);
	fseek(file, 0, SEEK_SET);

	// Allocate memory for file contents
	unsigned char* buffer = malloc(*size);
	if (buffer == NULL) {
		perror("Memory allocation failed");
		fclose(file);
		exit(-1);
	}

	// Read file into buffer
	fread(buffer, 1, *size, file);
	fclose(file);

	return buffer;
}

// Main
int main(int argc, char** argv) {
	unsigned char *contents;
	Rc4Context rc4Context;
	int contentsSize;
	
	banner();

	// Check for user input
	if (argc < 1) return -1;

	// Check if missing parameters
	if (argc < 3) {
		usage();
		return -1;
	}

	// Get file contents
	contents = parser(argv[1], &contentsSize);
	contentsSize = sizeof(contents);

	// Execute function
	if (strcmp(argv[2], "xor") == 0) {
		XorByInputKey(contents, contentsSize, key, sizeof(key));
		for (size_t i = 0; i < contentsSize; i++) {
			printf("%02x ", contents[i]);
		}
	}

	else if (strcmp(argv[2], "rc4") == 0) {
		// Initialize RC4 context with the key
		rc4Init(&rc4Context, key, sizeof(key));

		// Allocate memory for RC4 output
		unsigned char* rc4Output = malloc(contentsSize);
		if (rc4Output == NULL) {
			perror("Memory allocation failed");
			free(contents);
			return -1;
		}

		// Perform RC4 cipher
		rc4Cipher(&rc4Context, contents, rc4Output, contentsSize);

		// Print RC4 cipher output
		for (size_t i = 0; i < contentsSize; i++) {
			printf("%02x ", rc4Output[i]);
		}
		printf("\n");

		// Free allocated memory for RC4 output
		free(rc4Output);
	}

	else if (strcmp(argv[2], "ipv4") == 0) {
		if (!GenerateIpv4Output(contents, contentsSize)) {
			// if failed, that is sizeof(rawData) isn't a multiple of 4 
			return -1;
		}
	}

	else if (strcmp(argv[2], "ipv6") == 0) {
		if (!GenerateIpv6Output(contents, contentsSize)) {
			// if failed, that is sizeof(rawData) isn't a multiple of 4 
			return -1;
		}
	}

	else if (strcmp(argv[2], "mac") == 0) {
		if (!GenerateMacOutput(contents, contentsSize)) {
			// if failed, that is sizeof(rawData) isn't a multiple of 4 
			return -1;
		}
	}

	else if (strcmp(argv[2], "uuid") == 0) {
		if (!GenerateUuidOutput(contents, contentsSize)) {
			// if failed, that is sizeof(rawData) isn't a multiple of 4 
			return -1;
		}
	}

	else {
		printf("Error: %s is not an option", argv[2]);
		usage();
		return -1;
	}

	free(contents);

	return 0;
}