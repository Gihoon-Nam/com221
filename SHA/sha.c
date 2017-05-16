#include "sha.h"
#include <time.h>

int sha256(Word32* out, Word32* M, int blockNum)
{
	Word32 a, b, c, d, e, f, g, h;
	Word32 T1, T2;
	Word32 W[64];
	Word32 H[8] = { H0_32[0], H0_32[1], H0_32[2], H0_32[3], H0_32[4], H0_32[5], H0_32[6], H0_32[7]};
	int i, j;

	/*
	printf("MESSAGE : \n");
	for (i = 0; i < blockNum; i++)
	{
		for (j = 0; j < 16; j++)
		{
			printf("%08X ", M[(16 * i) + j]);
			if ((j + 1) % 8 == 0)
			{
				printf("\n");
			}
		}
		printf("\n");
	}
	printf("BLOCK NUM : %d\n", blockNum);
	*/

	for (i = 1; i <= blockNum; i++)
	{
		a = H[0];
		b = H[1];
		c = H[2];
		d = H[3];
		e = H[4];
		f = H[5];
		g = H[6];
		h = H[7];

		for (j = 0; j < 16; j++)
		{
			W[j] = M[(16 * (i - 1)) + j];
		}

		for (j = 16; j < 64; j++)
		{
			W[j] = SIG3_32(W[j - 2]) + W[j - 7] + SIG2_32(W[j - 15]) + W[j - 16];
		}

		for (j = 0; j < 64; j++)
		{
			T1 = h + SIG1_32(e) + CH(e, f, g) + K_32[j] + W[j];
			T2 = SIG0_32(a) + MAJ(a, b, c);
			h = g;
			g = f;
			f = e;
			e = d + T1;
			d = c;
			c = b;
			b = a;
			a = T1 + T2;
			// printf("%2d : %08X %08X %08X %08X %08X %08X %08X %08X\n", j, a, b, c, d, e, f, g, h);
		}

		H[0] += a;
		H[1] += b;
		H[2] += c;
		H[3] += d;
		H[4] += e;
		H[5] += f;
		H[6] += g;
		H[7] += h;
	}

	// printf("%08X %08X %08X %08X %08X %08X %08X %08X\n", H[0], H[1], H[2], H[3], H[4], H[5], H[6], H[7]);
	for (i = 0; i < 8; i++)
	{
		*(out + i) = H[i];
	}
	return 0;
}

int sha512(Word64* out, Word64* M, int blockNum)
{
	Word64 a, b, c, d, e, f, g, h;
	Word64 T1, T2;
	Word64 W[64];
	Word64 H[8] = { H0_64[0], H0_64[1], H0_64[2], H0_64[3], H0_64[4], H0_64[5], H0_64[6], H0_64[7]};
	int i, j;

	/*
	printf("MESSAGE : \n");
	for (i = 0; i < blockNum; i++)
	{
		for (j = 0; j < 16; j++)
		{
			printf("%016llX ", M[(16 * i) + j]);
			if ((j + 1) % 4 == 0)
			{
				printf("\n");
			}
		}
		printf("\n");
	}
	printf("BLOCK NUM : %d\n", blockNum);
	*/

	for (i = 1; i <= blockNum; i++)
	{
		a = H[0];
		b = H[1];
		c = H[2];
		d = H[3];
		e = H[4];
		f = H[5];
		g = H[6];
		h = H[7];

		for (j = 0; j < 16; j++)
		{
			W[j] = M[(16 * (i - 1)) + j];
		}

		for (j = 16; j < 80; j++)
		{
			W[j] = SIG3_64(W[j - 2]) + W[j - 7] + SIG2_64(W[j - 15]) + W[j - 16];
		}

		for (j = 0; j < 80; j++)
		{
			T1 = h + SIG1_64(e) + CH(e, f, g) + K_64[j] + W[j];
			T2 = SIG0_64(a) + MAJ(a, b, c);
			h = g;
			g = f;
			f = e;
			e = d + T1;
			d = c;
			c = b;
			b = a;
			a = T1 + T2;
			// printf("%2d : %08X %08X %08X %08X %08X %08X %08X %08X\n", j, a, b, c, d, e, f, g, h);
		}

		H[0] += a;
		H[1] += b;
		H[2] += c;
		H[3] += d;
		H[4] += e;
		H[5] += f;
		H[6] += g;
		H[7] += h;
		return 0;
	}

	// printf("%016llX %016llX %016llX %016llX %016llX %016llX %016llX %016llX\n", H[0], H[1], H[2], H[3], H[4], H[5], H[6], H[7]);

	/*
	for (i = 0; i < 8; i++)
	{
		*(out + i) = H[i];
	}
	*/
}

int sha(void* out, Byte* input, const int mod)
{
	int inputByteSize = strlen(input) + 1;
	int blockNum;
	int i;
	Word32* M32 = NULL;
	Word32* out256;
	Word64* M64 = NULL;
	Word64* out512;

	if (mod == 256)
	{
		(inputByteSize % 32) ? (blockNum = (inputByteSize / 32) + 1) : (blockNum = (inputByteSize / 32));
		M32 = malloc(sizeof(Word32) * 16 * blockNum);

		for (i = 0; i < 16 * blockNum; i++)
		{
			M32[i] = 0;
		}

		for (i = 0; i < inputByteSize - 1; i++)
		{
			M32[i / 4] += (((Word32)*(input + i)) << ( 24 - ((i % 4) * 8) ) );
		}
		M32[(inputByteSize - 1) / 4] += 0x80 << (32 - (8 * (inputByteSize)));
		M32[16 * blockNum - 1] = 8 * (inputByteSize - 1);

		out256 = (Word32*)out;
		sha256(out256, M32, blockNum);
		free(M32);
	}
	else if (mod == 512)
	{
		(inputByteSize % 64) ? (blockNum = (inputByteSize / 64) + 1) : (blockNum = (inputByteSize / 64));
		M64 = malloc(sizeof(Word64) * 16 * blockNum);

		for (i = 0; i < 16 * blockNum; i++)
		{
			M64[i] = 0;
		}

		for (i = 0; i < inputByteSize - 1; i++)
		{
			M64[i / 8] += (((Word64)*(input + i)) << ( 56 - ((i % 8) * 8) ) );
		}
		M64[(inputByteSize - 1) / 8] += 0x80 << (64 - (8 * (inputByteSize)));
		M64[16 * blockNum - 1] = 8 * (inputByteSize - 1);

		out512 = (Word64*)out;
		sha512(out512, M64, blockNum);
		free(M64);
	}
	else 
	{
		printf("INVALID SHA MOD!\n");
		return 0;
	}
	return 0;
}

int sha_test()
{
	Byte* testVector1 = "abc";
	Byte* testVector2 = "abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq";
	Byte* testVector3 = "abcdefghbcdefghicdefghijdefghijkefghijklfghijklmghijklmnhijklmnoijklmnopjklmnopqklmnopqrlmnopqrsmnopqrstnopqrstu";

	/*
	Word32 idleResult1[8] = {
		0xba7816bf, 0x8f01cfea, 0x414140de, 0x5dae2223, 0xb00361a3, 0x96177a9c, 0xb410ff61, 0xf20015ad
	};
	Word32 idleResult2[8] = {
		0x248d6a61, 0xd20638b8, 0xe5c02693, 0x0c3e6039, 0xa33ce459, 0x64ff2167, 0xf6ecedd4, 0x19db06c1
	};
	*/

	Word32 digest1[8];
	Word32 digest2[8];
	Word64 digest3[8];
	Word64 digest4[8];
	void* p;

	// code start

	/*
	printf("TEST CASE 1 - 256 \n");
	p = digest1;
	sha(p, testVector1, 256);
	printf("\n\n\n");
	
	printf("TEST CASE 2 - 256\n");
	p = digest2;
	sha(p, testVector2, 256);
	printf("\n\n\n");
	*/

	printf("TEST CASE 1 - 512 \n");
	p = digest3;
	sha(p, testVector1, 512);
	printf("\n\n\n");
	
	/*
	printf("TEST CASE 2 - 512\n");
	p = digest4;
	sha(p, testVector3, 512);
	printf("\n\n\n");
	*/
	
	

	// code end	

	return 1;
}

int sha256_time_test()
{
	int i;
	int times = 100000;
	struct timespec start;
	struct timespec end;
 	float diff_time;
	Byte *pt = "abc";
	void* p;
	//Byte *pt = "abcdefghbcdefghicdefghijdefghijkefghijklfghijklmghijklmnhijklmnoijklmnopjklmnopqklmnopqrlmnopqrsmnopqrstnopqrstu";
	// Byte *pt = "what do ya want for nothing?";
	// Byte *key = "Jefe";

	clock_gettime(CLOCK_REALTIME, &start);
	for (i = 0; i < times; i++)
	{
		sha(p, pt, 256);
	}

	clock_gettime(CLOCK_REALTIME, &end);

	diff_time = (end.tv_sec - start.tv_sec) + ((end.tv_nsec - start.tv_nsec));

	printf("Gong's SHA-256 source code!!\n");
	printf("Number of times = %d\n", times);
  	printf("time : %lf seconds(s) \n", (float)(end.tv_sec - start.tv_sec) + ((end.tv_nsec)-(start.tv_nsec))/(float)1000000000 );
  	return 0;
}

int sha512_time_test()
{
	int i;
	int times = 100000;
	struct timespec start;
	struct timespec end;
 	float diff_time;
	Byte *pt = "abc";
	void* p;
	//Byte *pt = "abcdefghbcdefghicdefghijdefghijkefghijklfghijklmghijklmnhijklmnoijklmnopjklmnopqklmnopqrlmnopqrsmnopqrstnopqrstu";
	// Byte *pt = "what do ya want for nothing?";
	// Byte *key = "Jefe";

	clock_gettime(CLOCK_REALTIME, &start);
	for (i = 0; i < times; i++)
	{
		sha(p, pt, 512);
	}

	clock_gettime(CLOCK_REALTIME, &end);

	diff_time = (end.tv_sec - start.tv_sec) + ((end.tv_nsec - start.tv_nsec));

	printf("Gong's SHA-512 source code!!\n");
	printf("Number of times = %d\n", times);
  	printf("time : %lf seconds(s) \n", (float)(end.tv_sec - start.tv_sec) + ((end.tv_nsec)-(start.tv_nsec))/(float)1000000000 );
  	return 0;
}