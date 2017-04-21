#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <time.h>
#include <string.h>

typedef unsigned long long Word;
typedef unsigned char Byte;
#define W_RS(A, n) ((A) >> (n)) ^ ((A) << (64-n))
#define LSIG_0(a) (W_RS(a, 28) ^ W_RS(a, 34) ^ W_RS(a, 39))
#define LSIG_1(e) (W_RS(e, 14) ^ W_RS(e, 18) ^ W_RS(e, 41))
#define SSIG_0(x) (W_RS(x, 1) ^ W_RS(x, 8) ^ (x >> 7))
#define SSIG_1(x) (W_RS(x, 19) ^ W_RS(x, 61) ^ (x >> 6))
#define COM(x) ((x) ^ (0xffffffffffffffff))
#define Ch(e, f, g) (((e) & (f)) ^ (COM(e) & (g)))
#define Maj(a, b, c) (((a) & (b)) ^ ((a) & (c)) ^ ((b) & (c)))
#define NW(i) (Word)(W[i-16] + SSIG_0(W[i-15]) + W[i-7] + SSIG_1(W[i-2]))

Word a, b, c, d, e, f, g, h;
Word W[80];
Word H[8];
const Word K[80] = {
	0x428a2f98d728ae22, 0x7137449123ef65cd, 0xb5c0fbcfec4d3b2f, 0xe9b5dba58189dbbc,
	0x3956c25bf348b538, 0x59f111f1b605d019, 0x923f82a4af194f9b, 0xab1c5ed5da6d8118,
	0xd807aa98a3030242, 0x12835b0145706fbe, 0x243185be4ee4b28c, 0x550c7dc3d5ffb4e2,
	0x72be5d74f27b896f, 0x80deb1fe3b1696b1, 0x9bdc06a725c71235, 0xc19bf174cf692694,
	0xe49b69c19ef14ad2, 0xefbe4786384f25e3, 0x0fc19dc68b8cd5b5, 0x240ca1cc77ac9c65,
	0x2de92c6f592b0275, 0x4a7484aa6ea6e483, 0x5cb0a9dcbd41fbd4, 0x76f988da831153b5,
	0x983e5152ee66dfab, 0xa831c66d2db43210, 0xb00327c898fb213f, 0xbf597fc7beef0ee4,
	0xc6e00bf33da88fc2, 0xd5a79147930aa725, 0x06ca6351e003826f, 0x142929670a0e6e70,
	0x27b70a8546d22ffc, 0x2e1b21385c26c926, 0x4d2c6dfc5ac42aed, 0x53380d139d95b3df,
	0x650a73548baf63de, 0x766a0abb3c77b2a8, 0x81c2c92e47edaee6, 0x92722c851482353b,
	0xa2bfe8a14cf10364, 0xa81a664bbc423001, 0xc24b8b70d0f89791, 0xc76c51a30654be30,
	0xd192e819d6ef5218, 0xd69906245565a910, 0xf40e35855771202a, 0x106aa07032bbd1b8,
	0x19a4c116b8d2d0c8, 0x1e376c085141ab53, 0x2748774cdf8eeb99, 0x34b0bcb5e19b48a8,
	0x391c0cb3c5c95a63, 0x4ed8aa4ae3418acb, 0x5b9cca4f7763e373, 0x682e6ff3d6b2b8a3,
	0x748f82ee5defb2fc, 0x78a5636f43172f60, 0x84c87814a1f0ab72, 0x8cc702081a6439ec,
	0x90befffa23631e28, 0xa4506cebde82bde9, 0xbef9a3f7b2c67915, 0xc67178f2e372532b,
	0xca273eceea26619c, 0xd186b8c721c0c207, 0xeada7dd6cde0eb1e, 0xf57d4f7fee6ed178,
	0x06f067aa72176fba, 0x0a637dc5a2c898a6, 0x113f9804bef90dae, 0x1b710b35131c471b,
	0x28db77f523047d84, 0x32caab7b40c72493, 0x3c9ebe0a15c9bebc, 0x431d67c49c100d4c,
	0x4cc5d4becb3e42b6, 0x597f299cfc657e2a, 0x5fcb6fab3ad6faec, 0x6c44198c4a475817
};
void PrintBlock(const Word *p, const int n){
	int i;
	for (i = 0; i < n; i++){
		printf("%016llx", p[i]);
		if (i != n - 1)
			printf("  ");
	}
	printf("\n");
}
void B_Init(){
	a = 0x6a09e667f3bcc908;
	b = 0xbb67ae8584caa73b;
	c = 0x3c6ef372fe94f82b;
	d = 0xa54ff53a5f1d36f1;
	e = 0x510e527fade682d1;
	f = 0x9b05688c2b3e6c1f;
	g = 0x1f83d9abfb41bd6b;
	h = 0x5be0cd19137e2179;
}
void M_scheduler(const Word *M){
	int i;
	for (i = 0; i < 80; i++){
		if (i < 16){
			W[i] = M[i];
		}
		else if (i >= 16){
			W[i] = NW(i);
		}
	}
}
void RoundFunction(const int t){
	Word T1, T2;
	T1 = (Word)(h + Ch(e, f, g) + LSIG_1(e) + W[t] + K[t]);
	//printf("h = %016llx, Ch(efg) = %016llx, LSIG_1(e) = %016llx, W[t] = %016llx, K[t] = %016llx\n", h, Ch(e, f, g), LSIG_1(e), W[t], K[t]);
	//printf("T1 = %016llx\n", T1);
	T2 = (Word)(LSIG_0(a) + Maj(a, b, c));
	//printf("T2 = %016llx\n", T2);
	h = g;
	//printf("h = %016llx\n", h);
	g = f;
	//printf("g = %016llx\n", g);
	f = e;
	//printf("f = %016llx\n", f);
	e = (Word)(d + T1);
	//printf("e = %016llx\n", e);
	d = c;
	//printf("d = %016llx\n", d);
	c = b;
	//printf("c = %016llx\n", c);
	b = a;
	//printf("b = %016llx\n", b);
	a = (Word)(T1 + T2);
	//printf("a = %016llx\n", a);
}
void Compress(){
	

	int t = 0;
	//Initialization of buffer.
	H[0] = a;
	H[1] = b;
	H[2] = c;
	H[3] = d;
	H[4] = e;
	H[5] = f;
	H[6] = g;
	H[7] = h;
	
	// 80 Round
	for (t = 0; t < 80; t++){
		//printf("round %d\n", t);
		RoundFunction(t);
	}

	//MD
	H[0] += a;
	H[1] += b;
	H[2] += c;
	H[3] += d;
	H[4] += e;
	H[5] += f;
	H[6] += g;
	H[7] += h;
	
	//printf("MD = ");
	//PrintBlock(H, 8);
}
int Pad(Word *a_pt, Byte *pt, int *length){
	//It's boz padding
	int i=0,j=0, n = 0;
	if (*length > 40000){
		printf("The message is too long!");
		return 1;
	}
	n = *length % 128;
	if (n > 111)
		n = (*length / 128) + 2;
	else
		n = (*length / 128) + 1;

	for (i = 0; i < *length; i++){
		*(a_pt + j) += (Word)(*(pt + i)) << (64 - (((i%8)+1)*8));
		if (((i % 8) + 1) == 8)
			j++;
	}

	*(a_pt + j) += (Word)(0x80) << (64 - (((i % 8) + 1) * 8));
	*(a_pt + 16 * n - 1) = (Word)((*length) * 8);
	//for (i = 0; i < n * 16; i++){
	//	printf("a_pt[%d] = %016llx\n", i, *(a_pt + i));
	//}
	*length = n * 16;

	return 0;
}
void Process(Byte *b_pt, int *length){
	int n; //The number of block
	int i, j;
	Word a_pt[5000] = { 0, };
	Word tmp[16];

	Pad(a_pt, b_pt, length);

	//printf("Padded PT = ");
	//PrintBlock(a_pt, *length);
	//printf("length = %d\n", *length);
	n = *length / 16;
	for (i = 0; i < n; i++){
		for (j = 0; j < 16; j++){
			*(tmp + j) = *(a_pt + (16 * i) + j);
		}
		M_scheduler(tmp);
		if (i == 0){
			B_Init();
		}
		else if (i != 0)
		{
			a = H[0];
			b = H[1];
			c = H[2];
			d = H[3]; 
			e = H[4];
			f = H[5];
			g = H[6];
			h = H[7];
		}
		Compress();
	}
	*length = strlen(b_pt);
	//printf("RESULT = ");
	//PrintBlock(H, 8);
}
int main(){
	//Byte *pt = "abc";
	Byte *pt = "abcdefghbcdefghicdefghijdefghijkefghijklfghijklmghijklmnhijklmnoijklmnopjklmnopqklmnopqrlmnopqrsmnopqrstnopqrstu";
	int i;
	int times = 100000;
	clock_t start, end;

	int length = strlen(pt);

	start = clock();
	for (i = 0; i < times; i++)
		Process(pt, &length);
	end = clock();
	printf("Seok's SHA-512, %d times\n", times);
	printf("time : %.3lf\n", ((double)end - start) / CLOCKS_PER_SEC);
	printf("RESULT = ");
	PrintBlock(H, 8);
	
	
	return 0;
}
