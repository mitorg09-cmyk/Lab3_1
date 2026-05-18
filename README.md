# Lab3_1
Contanes functions for working with long Boolean vectors and tests for all.

func list:

unsigned char* strToLongBV(char* str1, size_t* len);
char* LongBVtoStr(unsigned char* vec, size_t len);
void PrintBV(unsigned char* vec, size_t bits);
unsigned char * logMul(unsigned char *vecA, size_t bitsA, unsigned char *vecB, size_t bitsB);
unsigned char * logSum(unsigned char *vecA, size_t bitsA, unsigned char *vecB, size_t bitsB);
unsigned char * sumMod2(unsigned char *vecA, size_t bitsA, unsigned char *vecB, size_t bitsB);
void shiftRight(unsigned char *vec, size_t bits, size_t k);
void shiftLeft(unsigned char *vec, size_t bits, size_t k);
void inversion(unsigned char *vec, size_t bits);
void set1(unsigned char *vec, size_t bits, size_t bit);
void set0(unsigned char *vec, size_t bits, size_t bit);