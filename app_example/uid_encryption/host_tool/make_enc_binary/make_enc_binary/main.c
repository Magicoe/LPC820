#include <stdio.h>
#include <assert.h>
#include <windows.h>
#pragma comment(lib, "advapi32.lib")

extern void encode_data(unsigned __int32 *v, int n, const unsigned __int32 key[4]);
const __int32 magic_offset = 0xC8;
unsigned __int32 mcu_uid = 0x1601D046;
const unsigned __int32 mcu_system_clk = 30000000;
const unsigned __int32 main_addr = 0x00000BA9;
extern char    *optarg;                /* argument associated with option */
int main(int argc, char *argv[])
{
	FILE *binary_fp = NULL;
	FILE *cypher_fp = NULL;
	HCRYPTPROV hProvider = 0;
	unsigned __int32 magic_word[2];
	__int8 cypher[16];
	char binary_file_name[MAX_PATH];
	char cypher_file_name[MAX_PATH];
	int c;

	strncpy(binary_file_name, "binary.bin", MAX_PATH);
	strncpy(cypher_file_name, "cypher.hex", MAX_PATH);

	while(1) {
		c = getopt(argc, argv, "b:c:u:");
		if (c == -1)
			break;

		switch (c) {
		case 'b' :
			strncpy(binary_file_name, optarg, MAX_PATH);
			break;
		case 'c':
			strncpy(cypher_file_name, optarg, MAX_PATH);
			break;
		case 'u':
			mcu_uid = atoi(optarg);
			break;
		}
	}
		

	if (!CryptAcquireContextW(&hProvider, 0, 0, PROV_RSA_FULL, CRYPT_VERIFYCONTEXT | CRYPT_SILENT))
		return 1;

	fopen_s(&binary_fp, binary_file_name, "r+b");
	assert(binary_fp != 0);

	fopen_s(&cypher_fp, cypher_file_name, "r+b");
	if (cypher_fp) {
		fread_s(cypher, 16, 1, 16, cypher_fp);
	}
	else {
		fopen_s(&cypher_fp, "cypher.hex","wb");
		printf("Generate a random cypher\r\n");
		if (!CryptGenRandom(hProvider, 16, cypher))
		{
			CryptReleaseContext(hProvider, 0);
			return 1;
		}
		fwrite(cypher, 1, 16, cypher_fp);
	}
	fclose(cypher_fp);

	magic_word[0] = mcu_uid * 739;
	magic_word[1] = (main_addr ^ mcu_system_clk) * 37;
	encode_data(magic_word, 2, cypher);

	fseek(binary_fp, magic_offset, SEEK_SET);
	fwrite(magic_word, sizeof(__int32), 2, binary_fp);
	fclose(binary_fp);

	return 0;
}