#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef unsigned char Byte;
typedef unsigned int Word;
#define MAX 40000
#define AAA(V) 0x ## 00 ## V ## V ## V
#define BBB(V) 0x ## V ## 00 ## V ## V
#define CCC(V) 0x ## V ## V ## 00 ## V
#define DDD(V) 0x ## V ## V ## V ## 00
#define XX(NNN,x0,x1,x2,x3,x4,x5,x6,x7,x8,x9,xa,xb,xc,xd,xe,xf)		\
	NNN(x0), NNN(x1), NNN(x2), NNN(x3), NNN(x4), NNN(x5), NNN(x6), NNN(x7), \
	NNN(x8), NNN(x9), NNN(xa), NNN(xb), NNN(xc), NNN(xd), NNN(xe), NNN(xf)
#define RS(T,R) ((Byte)((T)>>(R)))
#define B_XOR(A, B)  A[0] ^= B[0]; A[1] ^= B[1]; A[2] ^= B[2]; A[3] ^= B[3]; 
#define B_COPY(A, B) A[0]  = B[0]; A[1]  = B[1]; A[2]  = B[2]; A[3]  = B[3];
Word CK1[4] = { 0x517cc1b7, 0x27220a94, 0xfe13abe8, 0xfa9a6ee0 };
Word CK2[4] = { 0x6db14acc, 0x9e21c820, 0xff28b1d5, 0xef5de2b0 };
Word CK3[4] = { 0xdb92371d, 0x2126e970, 0x03249775, 0x04e8c90e };

const Word T0[256] = {
	XX(AAA, 63, 7c, 77, 7b, f2, 6b, 6f, c5, 30, 01, 67, 2b, fe, d7, ab, 76),
	XX(AAA, ca, 82, c9, 7d, fa, 59, 47, f0, ad, d4, a2, af, 9c, a4, 72, c0),
	XX(AAA, b7, fd, 93, 26, 36, 3f, f7, cc, 34, a5, e5, f1, 71, d8, 31, 15),
	XX(AAA, 04, c7, 23, c3, 18, 96, 05, 9a, 07, 12, 80, e2, eb, 27, b2, 75),
	XX(AAA, 09, 83, 2c, 1a, 1b, 6e, 5a, a0, 52, 3b, d6, b3, 29, e3, 2f, 84),
	XX(AAA, 53, d1, 00, ed, 20, fc, b1, 5b, 6a, cb, be, 39, 4a, 4c, 58, cf),
	XX(AAA, d0, ef, aa, fb, 43, 4d, 33, 85, 45, f9, 02, 7f, 50, 3c, 9f, a8),
	XX(AAA, 51, a3, 40, 8f, 92, 9d, 38, f5, bc, b6, da, 21, 10, ff, f3, d2),
	XX(AAA, cd, 0c, 13, ec, 5f, 97, 44, 17, c4, a7, 7e, 3d, 64, 5d, 19, 73),
	XX(AAA, 60, 81, 4f, dc, 22, 2a, 90, 88, 46, ee, b8, 14, de, 5e, 0b, db),
	XX(AAA, e0, 32, 3a, 0a, 49, 06, 24, 5c, c2, d3, ac, 62, 91, 95, e4, 79),
	XX(AAA, e7, c8, 37, 6d, 8d, d5, 4e, a9, 6c, 56, f4, ea, 65, 7a, ae, 08),
	XX(AAA, ba, 78, 25, 2e, 1c, a6, b4, c6, e8, dd, 74, 1f, 4b, bd, 8b, 8a),
	XX(AAA, 70, 3e, b5, 66, 48, 03, f6, 0e, 61, 35, 57, b9, 86, c1, 1d, 9e),
	XX(AAA, e1, f8, 98, 11, 69, d9, 8e, 94, 9b, 1e, 87, e9, ce, 55, 28, df),
	XX(AAA, 8c, a1, 89, 0d, bf, e6, 42, 68, 41, 99, 2d, 0f, b0, 54, bb, 16)
};

const Word T1[256] = {
	XX(BBB, e2, 4e, 54, fc, 94, c2, 4a, cc, 62, 0d, 6a, 46, 3c, 4d, 8b, d1),
	XX(BBB, 5e, fa, 64, cb, b4, 97, be, 2b, bc, 77, 2e, 03, d3, 19, 59, c1),
	XX(BBB, 1d, 06, 41, 6b, 55, f0, 99, 69, ea, 9c, 18, ae, 63, df, e7, bb),
	XX(BBB, 00, 73, 66, fb, 96, 4c, 85, e4, 3a, 09, 45, aa, 0f, ee, 10, eb),
	XX(BBB, 2d, 7f, f4, 29, ac, cf, ad, 91, 8d, 78, c8, 95, f9, 2f, ce, cd),
	XX(BBB, 08, 7a, 88, 38, 5c, 83, 2a, 28, 47, db, b8, c7, 93, a4, 12, 53),
	XX(BBB, ff, 87, 0e, 31, 36, 21, 58, 48, 01, 8e, 37, 74, 32, ca, e9, b1),
	XX(BBB, b7, ab, 0c, d7, c4, 56, 42, 26, 07, 98, 60, d9, b6, b9, 11, 40),
	XX(BBB, ec, 20, 8c, bd, a0, c9, 84, 04, 49, 23, f1, 4f, 50, 1f, 13, dc),
	XX(BBB, d8, c0, 9e, 57, e3, c3, 7b, 65, 3b, 02, 8f, 3e, e8, 25, 92, e5),
	XX(BBB, 15, dd, fd, 17, a9, bf, d4, 9a, 7e, c5, 39, 67, fe, 76, 9d, 43),
	XX(BBB, a7, e1, d0, f5, 68, f2, 1b, 34, 70, 05, a3, 8a, d5, 79, 86, a8),
	XX(BBB, 30, c6, 51, 4b, 1e, a6, 27, f6, 35, d2, 6e, 24, 16, 82, 5f, da),
	XX(BBB, e6, 75, a2, ef, 2c, b2, 1c, 9f, 5d, 6f, 80, 0a, 72, 44, 9b, 6c),
	XX(BBB, 90, 0b, 5b, 33, 7d, 5a, 52, f3, 61, a1, f7, b0, d6, 3f, 7c, 6d),
	XX(BBB, ed, 14, e0, a5, 3d, 22, b3, f8, 89, de, 71, 1a, af, ba, b5, 81)
};

const Word T2[256] = {
	XX(CCC, 52, 09, 6a, d5, 30, 36, a5, 38, bf, 40, a3, 9e, 81, f3, d7, fb),
	XX(CCC, 7c, e3, 39, 82, 9b, 2f, ff, 87, 34, 8e, 43, 44, c4, de, e9, cb),
	XX(CCC, 54, 7b, 94, 32, a6, c2, 23, 3d, ee, 4c, 95, 0b, 42, fa, c3, 4e),
	XX(CCC, 08, 2e, a1, 66, 28, d9, 24, b2, 76, 5b, a2, 49, 6d, 8b, d1, 25),
	XX(CCC, 72, f8, f6, 64, 86, 68, 98, 16, d4, a4, 5c, cc, 5d, 65, b6, 92),
	XX(CCC, 6c, 70, 48, 50, fd, ed, b9, da, 5e, 15, 46, 57, a7, 8d, 9d, 84),
	XX(CCC, 90, d8, ab, 00, 8c, bc, d3, 0a, f7, e4, 58, 05, b8, b3, 45, 06),
	XX(CCC, d0, 2c, 1e, 8f, ca, 3f, 0f, 02, c1, af, bd, 03, 01, 13, 8a, 6b),
	XX(CCC, 3a, 91, 11, 41, 4f, 67, dc, ea, 97, f2, cf, ce, f0, b4, e6, 73),
	XX(CCC, 96, ac, 74, 22, e7, ad, 35, 85, e2, f9, 37, e8, 1c, 75, df, 6e),
	XX(CCC, 47, f1, 1a, 71, 1d, 29, c5, 89, 6f, b7, 62, 0e, aa, 18, be, 1b),
	XX(CCC, fc, 56, 3e, 4b, c6, d2, 79, 20, 9a, db, c0, fe, 78, cd, 5a, f4),
	XX(CCC, 1f, dd, a8, 33, 88, 07, c7, 31, b1, 12, 10, 59, 27, 80, ec, 5f),
	XX(CCC, 60, 51, 7f, a9, 19, b5, 4a, 0d, 2d, e5, 7a, 9f, 93, c9, 9c, ef),
	XX(CCC, a0, e0, 3b, 4d, ae, 2a, f5, b0, c8, eb, bb, 3c, 83, 53, 99, 61),
	XX(CCC, 17, 2b, 04, 7e, ba, 77, d6, 26, e1, 69, 14, 63, 55, 21, 0c, 7d)
};

const Word T3[256] = {
	XX(DDD, 30, 68, 99, 1b, 87, b9, 21, 78, 50, 39, db, e1, 72, 09, 62, 3c),
	XX(DDD, 3e, 7e, 5e, 8e, f1, a0, cc, a3, 2a, 1d, fb, b6, d6, 20, c4, 8d),
	XX(DDD, 81, 65, f5, 89, cb, 9d, 77, c6, 57, 43, 56, 17, d4, 40, 1a, 4d),
	XX(DDD, c0, 63, 6c, e3, b7, c8, 64, 6a, 53, aa, 38, 98, 0c, f4, 9b, ed),
	XX(DDD, 7f, 22, 76, af, dd, 3a, 0b, 58, 67, 88, 06, c3, 35, 0d, 01, 8b),
	XX(DDD, 8c, c2, e6, 5f, 02, 24, 75, 93, 66, 1e, e5, e2, 54, d8, 10, ce),
	XX(DDD, 7a, e8, 08, 2c, 12, 97, 32, ab, b4, 27, 0a, 23, df, ef, ca, d9),
	XX(DDD, b8, fa, dc, 31, 6b, d1, ad, 19, 49, bd, 51, 96, ee, e4, a8, 41),
	XX(DDD, da, ff, cd, 55, 86, 36, be, 61, 52, f8, bb, 0e, 82, 48, 69, 9a),
	XX(DDD, e0, 47, 9e, 5c, 04, 4b, 34, 15, 79, 26, a7, de, 29, ae, 92, d7),
	XX(DDD, 84, e9, d2, ba, 5d, f3, c5, b0, bf, a4, 3b, 71, 44, 46, 2b, fc),
	XX(DDD, eb, 6f, d5, f6, 14, fe, 7c, 70, 5a, 7d, fd, 2f, 18, 83, 16, a5),
	XX(DDD, 91, 1f, 05, 95, 74, a9, c1, 5b, 4a, 85, 6d, 13, 07, 4f, 4e, 45),
	XX(DDD, b2, 0f, c9, 1c, a6, bc, ec, 73, 90, 7b, cf, 59, 8f, a1, f9, 2d),
	XX(DDD, f2, b1, 00, 94, 37, 9f, d0, 2e, 9c, 6e, 28, 3f, 80, f0, 3d, d3),
	XX(DDD, 25, 8a, b5, e7, 42, b3, c7, ea, f7, 4c, 11, 33, 03, a2, ac, 60)
};
void PrintBlock(const Word *w, const int n){
	int i;
	for (i = 0; i < n; i++){
		printf("%08X", w[i]);
		if (i != n){
			printf("  ");
		}
	}
	printf("\n");
}
void RightCircular(Word *w, const int n){
	//ARIA에서 right rotate에 쓰이는 n은 모두 32보다 작다.
	Word tmp = (w[3] << (32 - n));

	/*printf("Right shift 입력 : ");
	PrintBlock(w, 4);*/

	w[3] = (w[2] << (32 - n)) + (w[3] >> n);
	w[2] = (w[1] << (32 - n)) + (w[2] >> n);
	w[1] = (w[0] << (32 - n)) + (w[1] >> n);
	w[0] = tmp + (w[0] >> n);
	/*printf("Right shift 결과 : ");
	PrintBlock(w, 4);*/
}
void LeftCircular(Word *w, const int n){
	//ARIA에서 Left rotate에 쓰이는 32보다 클 수 있지만 64보다는 작다.
	int m;
	Word tmp;
	/*printf("Left shift 입력 : ");
	PrintBlock(w, 4);*/
	if (n < 32){
		tmp = w[0] >> (32 - n);
		w[0] = (w[1] >> (32 - n)) + (w[0] << n);
		w[1] = (w[2] >> (32 - n)) + (w[1] << n);
		w[2] = (w[3] >> (32 - n)) + (w[2] << n);
		w[3] = tmp + (w[3] << n);
		/*printf("Left shift 결과 : ");
		PrintBlock(w, 4);*/
	}
	else{
		m = n - 32;
		tmp = w[0];
		w[0] = w[1];
		w[1] = w[2];
		w[2] = w[3];
		w[3] = tmp;
		tmp = w[0] >> (32 - m);
		w[0] = (w[1] >> (32 - m)) + (w[0] << m);
		w[1] = (w[2] >> (32 - m)) + (w[1] << m);
		w[2] = (w[3] >> (32 - m)) + (w[2] << m);
		w[3] = tmp + (w[3] << m);
		/*printf("LEFT shift 결과 : ");
		PrintBlock(w, 4);*/
	}
}
int RoundFunc(Word *word, const int n){
	/*printf("key_add = ");
	PrintBlock(word, 4);*/
	//Sbox & M
	if (n == 1){
		word[0] = T0[RS(word[0], 24)] ^ T1[RS(word[0], 16)] ^ T2[RS(word[0], 8)] ^ T3[RS(word[0], 0)];
		word[1] = T0[RS(word[1], 24)] ^ T1[RS(word[1], 16)] ^ T2[RS(word[1], 8)] ^ T3[RS(word[1], 0)];
		word[2] = T0[RS(word[2], 24)] ^ T1[RS(word[2], 16)] ^ T2[RS(word[2], 8)] ^ T3[RS(word[2], 0)];
		word[3] = T0[RS(word[3], 24)] ^ T1[RS(word[3], 16)] ^ T2[RS(word[3], 8)] ^ T3[RS(word[3], 0)];
	}
	else if (n == 0){
		word[0] = T2[RS(word[0], 24)] ^ T3[RS(word[0], 16)] ^ T0[RS(word[0], 8)] ^ T1[RS(word[0], 0)];
		word[1] = T2[RS(word[1], 24)] ^ T3[RS(word[1], 16)] ^ T0[RS(word[1], 8)] ^ T1[RS(word[1], 0)];
		word[2] = T2[RS(word[2], 24)] ^ T3[RS(word[2], 16)] ^ T0[RS(word[2], 8)] ^ T1[RS(word[2], 0)];
		word[3] = T2[RS(word[3], 24)] ^ T3[RS(word[3], 16)] ^ T0[RS(word[3], 8)] ^ T1[RS(word[3], 0)];
	}
	else
	{
		printf("Round Flag ERROR!");
		return 1;
	}
	//M1
	
	word[1] ^= word[2];
	word[2] ^= word[3];
	word[0] ^= word[1];
	word[3] ^= word[1];
	word[2] ^= word[0];
	word[1] ^= word[2];
	
	//P
	if (n == 1){
		word[1] = ((word[1] << 8) & 0xFF00FF00) ^ ((word[1] >> 8) & 0x00FF00FF);
		word[2] = ((word[2] << 16) & 0xFFFF0000) ^ ((word[2] >> 16) & 0x0000FFFF);
		word[3] = ((word[3] << 24) & 0xFF000000) ^ ((word[3] << 8) & 0x00FF0000) ^ ((word[3] >> 8) & 0x0000FF00) ^ ((word[3] >> 24) & 0x000000FF);
	}
	else if (n == 0){
		word[3] = ((word[3] << 8) & 0xFF00FF00) ^ ((word[3] >> 8) & 0x00FF00FF);
		word[0] = ((word[0] << 16) & 0xFFFF0000) ^ ((word[0] >> 16) & 0x0000FFFF);
		word[1] = ((word[1] << 24) & 0xFF000000) ^ ((word[1] << 8) & 0x00FF0000) ^ ((word[1] >> 8) & 0x0000FF00) ^ ((word[1] >> 24) & 0x000000FF);
	}
	
	
	//M1
	
	word[1] ^= word[2];
	word[2] ^= word[3];
	word[0] ^= word[1];
	word[3] ^= word[1];
	word[2] ^= word[0];
	word[1] ^= word[2];

	/*printf("diff_layer = ");
	PrintBlock(word, 4);*/
	return 0;
};
void KeyExpansion(Word *W0, Word *W1, Word *W2, Word *W3, const Word key[]){
	// W0
	B_COPY(W0, key);

	// W1
	B_COPY(W1, W0);
	B_XOR(W1, CK1);
	RoundFunc(W1, 1);

	// W2 
	B_COPY(W2, W1);
	B_XOR(W2, CK2);
	RoundFunc(W2, 0);
	B_XOR(W2, W0);

	// W3
	B_COPY(W3, W2);
	B_XOR(W3, CK3);
	RoundFunc(W3, 1);
	B_XOR(W3, W1);
}
void Crypt(Word *pt, const Word key[]){
	Word W0[4], W1[4], W2[4], W3[4], tmp[4];

	// Key Expansion
	// B_COPY(ct, pt);
	KeyExpansion(W0, W1, W2, W3, key);

	// round 1 
	B_COPY(tmp, W1);
	RightCircular(tmp, 19);
	B_XOR(tmp, W0);
	B_XOR(pt, tmp);
	RoundFunc(pt, 1);

	// round 2
	B_COPY(tmp, W2);
	RightCircular(tmp, 19);
	B_XOR(tmp, W1);
	B_XOR(pt, tmp);
	RoundFunc(pt, 0);

	// round 3
	B_COPY(tmp, W3);
	RightCircular(tmp, 19);
	B_XOR(tmp, W2);
	B_XOR(pt, tmp);
	RoundFunc(pt, 1);

	// round 4
	B_COPY(tmp, W0);
	RightCircular(tmp, 19);
	B_XOR(tmp, W3);
	B_XOR(pt, tmp);
	RoundFunc(pt, 0);

	// round 5
	B_COPY(tmp, W1);
	RightCircular(tmp, 31);
	B_XOR(tmp, W0);
	B_XOR(pt, tmp);
	RoundFunc(pt, 1);

	// round 6
	B_COPY(tmp, W2);
	RightCircular(tmp, 31);
	B_XOR(tmp, W1);
	B_XOR(pt, tmp);
	RoundFunc(pt, 0);

	// round 7 
	B_COPY(tmp, W3);
	RightCircular(tmp, 31);
	B_XOR(tmp, W2);
	B_XOR(pt, tmp);
	RoundFunc(pt, 1);

	// round 8
	B_COPY(tmp, W0);
	RightCircular(tmp, 31);
	B_XOR(tmp, W3);
	B_XOR(pt, tmp);
	RoundFunc(pt, 0);

	// round 9
	B_COPY(tmp, W1);
	LeftCircular(tmp, 61);
	B_XOR(tmp, W0);
	B_XOR(pt, tmp);
	RoundFunc(pt, 1);

	// round 10 
	B_COPY(tmp, W2);
	LeftCircular(tmp, 61);
	B_XOR(tmp, W1);
	B_XOR(pt, tmp);
	RoundFunc(pt, 0);

	// round 11
	B_COPY(tmp, W3);
	LeftCircular(tmp, 61);
	B_XOR(tmp, W2);
	B_XOR(pt, tmp);
	RoundFunc(pt, 1);

	// round 12 
	B_COPY(tmp, W0);
	LeftCircular(tmp, 61);
	B_XOR(tmp, W3);
	B_XOR(pt, tmp);

	pt[0] = (T2[RS(pt[0], 24)] & 0xFF000000) ^ (T3[RS(pt[0], 16)] & 0x00FF0000) ^ (T0[RS(pt[0], 8)] & 0x0000FF00) ^ (T1[RS(pt[0], 0)] & 0x000000FF);
	pt[1] = (T2[RS(pt[1], 24)] & 0xFF000000) ^ (T3[RS(pt[1], 16)] & 0x00FF0000) ^ (T0[RS(pt[1], 8)] & 0x0000FF00) ^ (T1[RS(pt[1], 0)] & 0x000000FF);
	pt[2] = (T2[RS(pt[2], 24)] & 0xFF000000) ^ (T3[RS(pt[2], 16)] & 0x00FF0000) ^ (T0[RS(pt[2], 8)] & 0x0000FF00) ^ (T1[RS(pt[2], 0)] & 0x000000FF);
	pt[3] = (T2[RS(pt[3], 24)] & 0xFF000000) ^ (T3[RS(pt[3], 16)] & 0x00FF0000) ^ (T0[RS(pt[3], 8)] & 0x0000FF00) ^ (T1[RS(pt[3], 0)] & 0x000000FF);


	B_COPY(tmp, W1);
	LeftCircular(tmp, 31);
	B_XOR(tmp, W0);
	B_XOR(pt, tmp);
}
int ARIA_ECB(Word *pt, const Word key[], const int n){
	int i, j;
	Word tmp_pt[4];
	for (i = 0; i < n; i++){
		for (j = 0; j < 4; j++){
			tmp_pt[j] = pt[(4 * i) + j];
		}
		Crypt(tmp_pt, key);
		for (j = 0; j < 4; j++){
			pt[(4 * i) + j] = tmp_pt[j];
		}
	}
	return 0;
}
int ARIA_CBC(Word *pt, Word iv[], const Word key[], const int n){
	int i, j;
	Word tmp_pt[4];
	Word tmp_iv[4];
	B_COPY(tmp_iv, iv);
	for (i = 0; i < n; i++){
		for (j = 0; j < 4; j++){
			tmp_pt[j] = pt[(4 * i) + j];
		}
		B_XOR(tmp_pt, tmp_iv);
		Crypt(tmp_pt, key);
		for (j = 0; j < 4; j++){
			pt[(4 * i) + j] = tmp_pt[j];
		}
		B_COPY(tmp_iv, tmp_pt);
	}
	return 0;
}
int ARIA_CTR(Word *pt, Word *iv, const Word key[], const int n){
	int i, j, k;
	Word tmp_pt[4];
	Word tmp_ctr[4];
	B_COPY(tmp_ctr, iv);
	for (i = 0; i < n; i++){
		for (j = 0; j < 4; j++){
			tmp_pt[j] = pt[(4 * i) + j];
		}
		Crypt(iv, key);
		B_XOR(tmp_pt, iv);
		for (j = 0; j < 4; j++){
			pt[(4 * i) + j] = tmp_pt[j];
		}
		for (k = 3; k >= 0; k--){
			if (tmp_ctr[k] < 0xffffffff){
				tmp_ctr[k]++;
				break;
			}
			else if (tmp_ctr[k] == 0xffffffff){
				tmp_ctr[k] = 0;
			}
		}
		B_COPY(iv, tmp_ctr);
	}
	return 0;
}
int KatMmt(char *mode, char *KorM){
	int i, j, n;
	FILE *fin = NULL;
	FILE *fout = NULL;
	int state1, state2;
	Byte type[5];
	Byte eq[2];
	Byte m[400];
	Byte tmp[10];
	Word pt[40], key[4], iv[4], ct[40];
	if (!strcmp(KorM, "KAT")){
		if (!strcmp(mode, "ECB")){
			fin = fopen("C:\\Users\\ByoungJinSeok\\Desktop\\ARIA MOVS Test Vector\\ECB\\ARIA128(ECB)KAT.txt", "rt");
			fout = fopen("C:\\Users\\ByoungJinSeok\\Desktop\\KnownAnswerTest\\ARIA128(ECB)KAT_fax.txt", "w+");
		}
		else if (!strcmp(mode, "CBC")){
			fin = fopen("C:\\Users\\ByoungJinSeok\\Desktop\\ARIA MOVS Test Vector\\CBC\\ARIA128(CBC)KAT.txt", "rt");
			fout = fopen("C:\\Users\\ByoungJinSeok\\Desktop\\KnownAnswerTest\\ARIA128(CBC)KAT_fax.txt", "w+");
		}
		else if (!strcmp(mode, "CTR")){
			fin = fopen("C:\\Users\\ByoungJinSeok\\Desktop\\ARIA MOVS Test Vector\\CTR\\ARIA128(CTR)KAT.txt", "rt");
			fout = fopen("C:\\Users\\ByoungJinSeok\\Desktop\\KnownAnswerTest\\ARIA128(CTR)KAT_fax.txt", "w+");
		}
	}
	else if (!strcmp(KorM, "MMT"))
	{
		if (!strcmp(mode, "ECB")){
			fin = fopen("C:\\Users\\ByoungJinSeok\\Desktop\\ARIA MOVS Test Vector\\ECB\\ARIA128(ECB)MMT.txt", "rt");
			fout = fopen("C:\\Users\\ByoungJinSeok\\Desktop\\KnownAnswerTest\\ARIA128(ECB)MMT_fax.txt", "w+");
		}
		else if (!strcmp(mode, "CBC")){
			fin = fopen("C:\\Users\\ByoungJinSeok\\Desktop\\ARIA MOVS Test Vector\\CBC\\ARIA128(CBC)MMT.txt", "rt");
			fout = fopen("C:\\Users\\ByoungJinSeok\\Desktop\\KnownAnswerTest\\ARIA128(CBC)MMT_fax.txt", "w+");
		}
		else if (!strcmp(mode, "CTR")){
			fin = fopen("C:\\Users\\ByoungJinSeok\\Desktop\\ARIA MOVS Test Vector\\CTR\\ARIA128(CTR)MMT.txt", "rt");
			fout = fopen("C:\\Users\\ByoungJinSeok\\Desktop\\KnownAnswerTest\\ARIA128(CTR)MMT_fax.txt", "w+");
		}
	}
	if (fin == NULL) {
		printf("FILE LOAD FAIL - EXIT\n");
		return 1;
	}
	else
	{
		printf("%s mode %s TEST", mode, KorM);
	}
	while (1)
	{
		
		fscanf(fin, "%s %s %s", &type, &eq, &m);
		n = strlen(m) / 8;
		if (feof(fin)) break;
		if (!strcmp(type, "PT")){
			fprintf(fout, "PT = ");
			for (i = 0; i < n; i++){
				for (j = 0; j < 8; j++){
					tmp[j] = m[(8 * i) + j];
				}
				pt[i] = strtoul(tmp, NULL, 16);
				fprintf(fout, "%08X", pt[i]);
			}
			fprintf(fout, "\n");
		}
		else if (!strcmp(type, "IV")){
			fprintf(fout, "IV = ");
			for (i = 0; i < n; i++){
				for (j = 0; j < 8; j++){
					tmp[j] = m[(8 * i) + j];
				}
				iv[i] = strtoul(tmp, NULL, 16);
				fprintf(fout, "%08X", iv[i]);
			}
			fprintf(fout, "\n");
		}
		else if (!strcmp(type, "KEY")){
			fprintf(fout, "KEY = ");
			for (i = 0; i < n; i++){
				for (j = 0; j < 8; j++){
					tmp[j] = m[(8 * i) + j];
				}
				key[i] = strtoul(tmp, NULL, 16);
				fprintf(fout, "%08X", key[i]);
			}
			fprintf(fout, "\n");
		}
		else if (!strcmp(type, "CT")){
			for (i = 0; i < n; i++){
				for (j = 0; j < 8; j++){
					tmp[j] = m[(8 * i) + j];
				}
				ct[i] = strtoul(tmp, NULL, 16);
			}
			if (!strcmp(mode, "CBC")){
				ARIA_CBC(pt, iv, key, n / 4);
			}
			else if (!strcmp(mode, "ECB"))
			{
				ARIA_ECB(pt, key, n / 4);
			}
			else if (!strcmp(mode, "CTR"))
			{
				ARIA_CTR(pt, iv, key, n / 4);
			}
			
			fprintf(fout, "CT = ");
			for (i = 0; i < n; i++){
				fprintf(fout, "%08X", pt[i]);
			}
			fprintf(fout, "\n\n");
		}
	}
	fclose(fin);
	fclose(fout);
	//comparing of fin and fout
	
	if (!strcmp(KorM, "KAT")){
		if (!strcmp(mode, "ECB")){
			fin = fopen("C:\\Users\\ByoungJinSeok\\Desktop\\ARIA MOVS Test Vector\\ECB\\ARIA128(ECB)KAT.txt", "rt");
			fout = fopen("C:\\Users\\ByoungJinSeok\\Desktop\\KnownAnswerTest\\ARIA128(ECB)KAT_fax.txt", "rt");
		}
		else if (!strcmp(mode, "CBC")){
			fin = fopen("C:\\Users\\ByoungJinSeok\\Desktop\\ARIA MOVS Test Vector\\CBC\\ARIA128(CBC)KAT.txt", "rt");
			fout = fopen("C:\\Users\\ByoungJinSeok\\Desktop\\KnownAnswerTest\\ARIA128(CBC)KAT_fax.txt", "rt");
		}
		else if (!strcmp(mode, "CTR")){
			fin = fopen("C:\\Users\\ByoungJinSeok\\Desktop\\ARIA MOVS Test Vector\\CTR\\ARIA128(CTR)KAT.txt", "rt");
			fout = fopen("C:\\Users\\ByoungJinSeok\\Desktop\\KnownAnswerTest\\ARIA128(CTR)KAT_fax.txt", "rt");
		}
	}
	else if (!strcmp(KorM, "MMT"))
	{
		if (!strcmp(mode, "ECB")){
			fin = fopen("C:\\Users\\ByoungJinSeok\\Desktop\\ARIA MOVS Test Vector\\ECB\\ARIA128(ECB)MMT.txt", "rt");
			fout = fopen("C:\\Users\\ByoungJinSeok\\Desktop\\KnownAnswerTest\\ARIA128(ECB)MMT_fax.txt", "rt");
		}
		else if (!strcmp(mode, "CBC")){
			fin = fopen("C:\\Users\\ByoungJinSeok\\Desktop\\ARIA MOVS Test Vector\\CBC\\ARIA128(CBC)MMT.txt", "rt");
			fout = fopen("C:\\Users\\ByoungJinSeok\\Desktop\\KnownAnswerTest\\ARIA128(CBC)MMT_fax.txt", "rt");
		}
		else if (!strcmp(mode, "CTR")){
			fin = fopen("C:\\Users\\ByoungJinSeok\\Desktop\\ARIA MOVS Test Vector\\CTR\\ARIA128(CTR)MMT.txt", "rt");
			fout = fopen("C:\\Users\\ByoungJinSeok\\Desktop\\KnownAnswerTest\\ARIA128(CTR)MMT_fax.txt", "rt");
		}
	}
	while (1)
	{
		if (feof(fin) == 0 && feof(fout) == 0){
			eq[0] = fgetc(fin);
			eq[1] = fgetc(fout);
			if (eq[0] != eq[1]){
				printf(" - FAIL\n");
				break;
			}
		}
		else if ((feof(fin) != 0 && feof(fout) == 0) || (feof(fin) == 0 && feof(fout) != 0))
		{
			printf(" - FAIL\n");
			break;
		}
		else
		{
			printf(" - PASS\n");
			break;
		}
	}
	state1 = fclose(fin);
	state2 = fclose(fout);
	if (state1 != 0 || state2 != 0)
	{
		printf("Error in stream elimination");
		return 1;
	}

	return 0;
}
int Mct(char *mode){
	int i, j, n;
	FILE *fin = NULL;
	FILE *fout = NULL;
	int state1, state2;
	int count;
	Byte type[6];
	Byte eq[2];
	Byte m[400];
	Byte tmp[10];
	Word pt[4], key[4], iv[4], ct[4], wtmp[4];
	if (!strcmp(mode, "ECB")){
		fin = fopen("C:\\Users\\ByoungJinSeok\\Desktop\\ARIA MOVS Test Vector\\ECB\\ARIA128(ECB)MCT.txt", "rt");
		fout = fopen("C:\\Users\\ByoungJinSeok\\Desktop\\KnownAnswerTest\\ARIA128(ECB)MCT_fax.txt", "w+");
		if (fin == NULL) {
			printf("FILE LOAD FAIL - EXIT\n");
			return 1;
		}
		else
		{
			printf("%s mode MCT TEST", mode);
		}
		fscanf(fin, "%s %s %s", &type, &eq, &m);
		n = strlen(m) / 8;
		if (!strcmp(type, "COUNT")){
			count = strtol(m, NULL, 10);
		}
		fscanf(fin, "%s %s %s", &type, &eq, &m);
		n = strlen(m) / 8;
		if (!strcmp(type, "KEY")){
			for (i = 0; i < n; i++){
				for (j = 0; j < 8; j++){
					tmp[j] = m[(8 * i) + j];
				}
				key[i] = strtoul(tmp, NULL, 16);
			}
		}
		fscanf(fin, "%s %s %s", &type, &eq, &m);
		n = strlen(m) / 8;
		if (!strcmp(type, "PT")){
			for (i = 0; i < n; i++){
				for (j = 0; j < 8; j++){
					tmp[j] = m[(8 * i) + j];
				}
				pt[i] = strtoul(tmp, NULL, 16);
			}
		}
		fscanf(fin, "%s %s %s", &type, &eq, &m);
		n = strlen(m) / 8;
		if (!strcmp(type, "CT")){
			for (i = 0; i < n; i++){
				for (j = 0; j < 8; j++){
					tmp[j] = m[(8 * i) + j];
				}
				ct[i] = strtoul(tmp, NULL, 16);
			}
			for (i = 0; i < 100; i++){
				fprintf(fout, "COUNT = %d\n", count);
				fprintf(fout, "KEY = ");
				for (j = 0; j < 4; j++){
					fprintf(fout, "%08X", key[j]);
				}
				fprintf(fout, "\n");
				fprintf(fout, "PT = ");
				for (j = 0; j < 4; j++){
					fprintf(fout, "%08X", pt[j]);
				}
				fprintf(fout, "\n");
				//ECB Encryption
				for (j = 0; j < 1000; j++){
					ARIA_ECB(pt, key, n / 4);
				}
				fprintf(fout, "CT = ");
				for (j = 0; j < n; j++){
					fprintf(fout, "%08X", pt[j]);
				}
				fprintf(fout, "\n\n");
				//changing of count, key
				count++;
				B_XOR(key, pt);
			}
		}
	}
	else if (!strcmp(mode, "CBC")){
		fin = fopen("C:\\Users\\ByoungJinSeok\\Desktop\\ARIA MOVS Test Vector\\CBC\\ARIA128(CBC)MCT.txt", "rt");
		fout = fopen("C:\\Users\\ByoungJinSeok\\Desktop\\KnownAnswerTest\\ARIA128(CBC)MCT_fax.txt", "w+");
		if (fin == NULL) {
			printf("FILE LOAD FAIL - EXIT\n");
			return 1;
		}
		else
		{
			printf("%s mode MCT TEST", mode);
		}
		fscanf(fin, "%s %s %s", &type, &eq, &m);
		n = strlen(m) / 8;
		if (!strcmp(type, "COUNT")){
			count = strtol(m, NULL, 10);
		}
		fscanf(fin, "%s %s %s", &type, &eq, &m);
		n = strlen(m) / 8;
		if (!strcmp(type, "KEY")){
			for (i = 0; i < n; i++){
				for (j = 0; j < 8; j++){
					tmp[j] = m[(8 * i) + j];
				}
				key[i] = strtoul(tmp, NULL, 16);
			}
		}
		fscanf(fin, "%s %s %s", &type, &eq, &m);
		n = strlen(m) / 8;
		if (!strcmp(type, "IV")){
			for (i = 0; i < n; i++){
				for (j = 0; j < 8; j++){
					tmp[j] = m[(8 * i) + j];
				}
				iv[i] = strtoul(tmp, NULL, 16);
			}
		}
		fscanf(fin, "%s %s %s", &type, &eq, &m);
		n = strlen(m) / 8;
		if (!strcmp(type, "PT")){
			for (i = 0; i < n; i++){
				for (j = 0; j < 8; j++){
					tmp[j] = m[(8 * i) + j];
				}
				pt[i] = strtoul(tmp, NULL, 16);
			}
		}
		fscanf(fin, "%s %s %s", &type, &eq, &m);
		n = strlen(m) / 8;
		if (!strcmp(type, "CT")){
			for (i = 0; i < n; i++){
				for (j = 0; j < 8; j++){
					tmp[j] = m[(8 * i) + j];
				}
				ct[i] = strtoul(tmp, NULL, 16);
			}
			for (i = 0; i < 100; i++){
				fprintf(fout, "COUNT = %d\n", count);
				fprintf(fout, "KEY = ");
				for (j = 0; j < 4; j++){
					fprintf(fout, "%08X", key[j]);
				}
				fprintf(fout, "\n");
				fprintf(fout, "IV = ");
				for (j = 0; j < 4; j++){
					fprintf(fout, "%08X", iv[j]);
				}
				fprintf(fout, "\n");
				fprintf(fout, "PT = ");
				for (j = 0; j < 4; j++){
					fprintf(fout, "%08X", pt[j]);
				}
				fprintf(fout, "\n");
				//CBC Encryption
				
				for (j = 0; j < 1000; j++){
						ARIA_CBC(pt, iv, key, n / 4);
						B_COPY(wtmp, iv);
						B_COPY(iv, pt);
						B_COPY(pt, wtmp);
				}
				//Changing of count, key, iv
				fprintf(fout, "CT = ");
				for (j = 0; j < n; j++){
					fprintf(fout, "%08X", iv[j]);
				}
				fprintf(fout, "\n\n");

				count++;
				B_XOR(key, iv);
			}
		}
	}
	else if (!strcmp(mode, "CTR")){
		fin = fopen("C:\\Users\\ByoungJinSeok\\Desktop\\ARIA MOVS Test Vector\\CTR\\ARIA128(CTR)MCT.txt", "rt");
		fout = fopen("C:\\Users\\ByoungJinSeok\\Desktop\\KnownAnswerTest\\ARIA128(CTR)MCT_fax.txt", "w+");
		if (fin == NULL) {
			printf("FILE LOAD FAIL - EXIT\n");
			return 1;
		}
		else
		{
			printf("%s mode MCT TEST", mode);
		}
		fscanf(fin, "%s %s %s", &type, &eq, &m);
		n = strlen(m) / 8;
		if (!strcmp(type, "COUNT")){
			count = strtol(m, NULL, 10);
		}
		fscanf(fin, "%s %s %s", &type, &eq, &m);
		n = strlen(m) / 8;
		if (!strcmp(type, "KEY")){
			for (i = 0; i < n; i++){
				for (j = 0; j < 8; j++){
					tmp[j] = m[(8 * i) + j];
				}
				key[i] = strtoul(tmp, NULL, 16);
			}
		}
		fscanf(fin, "%s %s %s", &type, &eq, &m);
		n = strlen(m) / 8;
		if (!strcmp(type, "CTR")){
			for (i = 0; i < n; i++){
				for (j = 0; j < 8; j++){
					tmp[j] = m[(8 * i) + j];
				}
				iv[i] = strtoul(tmp, NULL, 16);
			}
		}
		fscanf(fin, "%s %s %s", &type, &eq, &m);
		n = strlen(m) / 8;
		if (!strcmp(type, "PT")){
			for (i = 0; i < n; i++){
				for (j = 0; j < 8; j++){
					tmp[j] = m[(8 * i) + j];
				}
				pt[i] = strtoul(tmp, NULL, 16);
			}
		}
		fscanf(fin, "%s %s %s", &type, &eq, &m);
		n = strlen(m) / 8;
		if (!strcmp(type, "CT")){
			for (i = 0; i < n; i++){
				for (j = 0; j < 8; j++){
					tmp[j] = m[(8 * i) + j];
				}
				ct[i] = strtoul(tmp, NULL, 16);
			}
			for (i = 0; i < 100; i++){
				fprintf(fout, "COUNT = %d\n", count);
				fprintf(fout, "KEY = ");
				for (j = 0; j < 4; j++){
					fprintf(fout, "%08X", key[j]);
				}
				fprintf(fout, "\n");
				fprintf(fout, "CTR = ");
				for (j = 0; j < 4; j++){
					fprintf(fout, "%08x", iv[j]);
				}
				fprintf(fout, "\n");
				fprintf(fout, "PT = ");
				for (j = 0; j < 4; j++){
					fprintf(fout, "%08X", pt[j]);
				}
				fprintf(fout, "\n");
				//CTR Encryption
				for (j = 0; j < 1000; j++){
					ARIA_CTR(pt, iv, key, n / 4);
				}
				//Changing of count, key
				fprintf(fout, "CT = ");
				for (j = 0; j < n; j++){
					fprintf(fout, "%08X", pt[j]);
				}
				fprintf(fout, "\n\n");

				count++;
				B_XOR(key, pt);
			}
		}
	}
	fclose(fin);
	fclose(fout);
	//comparing of fin and fout
	if (!strcmp(mode, "ECB")){
		fin = fopen("C:\\Users\\ByoungJinSeok\\Desktop\\ARIA MOVS Test Vector\\ECB\\ARIA128(ECB)MCT.txt", "rt");
		fout = fopen("C:\\Users\\ByoungJinSeok\\Desktop\\KnownAnswerTest\\ARIA128(ECB)MCT_fax.txt", "rt");
	}
	else if (!strcmp(mode, "CBC")){
		fin = fopen("C:\\Users\\ByoungJinSeok\\Desktop\\ARIA MOVS Test Vector\\CBC\\ARIA128(CBC)MCT.txt", "rt");
		fout = fopen("C:\\Users\\ByoungJinSeok\\Desktop\\KnownAnswerTest\\ARIA128(CBC)MCT_fax.txt", "rt");
	}
	else if (!strcmp(mode, "CTR")){
		fin = fopen("C:\\Users\\ByoungJinSeok\\Desktop\\ARIA MOVS Test Vector\\CTR\\ARIA128(CTR)MCT.txt", "rt");
		fout = fopen("C:\\Users\\ByoungJinSeok\\Desktop\\KnownAnswerTest\\ARIA128(CTR)MCT_fax.txt", "rt");
	}
	while (1)
	{
		if (feof(fin) == 0 && feof(fout) == 0){
			eq[0] = fgetc(fin);
			eq[1] = fgetc(fout);
			if (eq[0] != eq[1]){
				printf(" - FAIL\n");
				break;
			}
		}
		else if ((feof(fin) != 0 && feof(fout) == 0) || (feof(fin) == 0 && feof(fout) != 0))
		{
			printf(" - FAIL\n");
			break;
		}
		else
		{
			printf(" - PASS\n");
			break;
		}
	}
	state1 = fclose(fin);
	state2 = fclose(fout);
	if (state1 != 0 || state2 != 0)
	{
		printf("Error in stream elimination");
		return 1;
	}

	return 0;
}
int KnownAnswerTEST(){
	//KAT(Known Anser Test)
	//ARIA MOVS Test Vector의 KAT Test Vector 사용
	KatMmt("CBC", "KAT");
	KatMmt("ECB", "KAT");
	KatMmt("CTR", "KAT");
	
	return 0;
}
int Pad(Byte *pt, int *length){
	//It's boz padding
	int p, q, i;
	if (*length > 80000){
		printf("The message is too long!");
		return 1;
	}
	p = *length / 32;
	q = (*length % 32) / 2;
	if (q == 0){
		strcat(pt, "80000000000000000000000000000000");
	}
	else if(q != 0){
		strcat(pt, "80");
		q = 16 - q - 1;
		for (i = 0; i < q; i++){
			strcat(pt, "00");
		}
	}
	*length = strlen(pt);
	return 0;
}
void CtoH(Word *a_pt, Byte *b_pt, int *length){
	int i,j;
	Byte tmp[8];
	*length /= 8;
	for (i = 0; i < *length; i++){
		for (j = 0; j < 8; j++){
			tmp[j] = b_pt[(8 * i) + j];
		}
		a_pt[i] = strtoul(tmp, NULL, 16);
	}
	return 0;
}
int main(){
	Byte b_pt[80000] = "11111111aaaaaaaa11111111bbbbbbbb11111111cccccccc11111111dddddddd22222222aaaaaaaa22222222bbbbbbbb22222222cccccccc22222222dddddddd11";
	Word a_pt[10000] = { NULL, };
	int length;
	Word key[4] = { 0x00112233, 0x44556677, 0x8899aabb, 0xccddeeff };
	Word iv[4] = { 0x0f1e2d3c, 0x4b5a6978, 0x8796a5b4, 0xc3d2e1f0 };
	
	length = strlen(b_pt);
	Pad(b_pt, &length);
	printf("length = %d\n", length);
	CtoH(a_pt, b_pt, &length);
	printf("pt = \n");
	PrintBlock(a_pt, length);
	ARIA_ECB(a_pt, key, length / 4);
	printf("ecb ct = \n");
	PrintBlock(a_pt, length);
	ARIA_CBC(a_pt, iv, key, length/4);
	printf("cbc ct = \n");
	PrintBlock(a_pt, length);
	ARIA_CTR(a_pt, iv, key, length/4);
	printf("ctr ct = \n");
	PrintBlock(a_pt, length);

	////조건부 테스트
	//KnownAnswerTEST();
	//KatMmt("ECB", "MMT");
	//KatMmt("CBC", "MMT");
	//KatMmt("CTR", "MMT");
	//Mct("ECB");
	//Mct("CBC");
	//Mct("CTR");
	return 0;
}