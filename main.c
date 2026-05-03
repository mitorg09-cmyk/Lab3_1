#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

int main()
{
    char str[256] =  "01010111111010101001010101010";
    char str1[256] = "00011110";
    size_t len = 0;
    size_t len1 = 0;
    unsigned char* vec = strToLongBV(str, &len);
    unsigned char* vec1 = strToLongBV(str1, &len1);
    printf("%d %d \n", len, len1);

    // printf("%d %d \n", vec[0], vec1[0]);

    char* nStr = NULL;
    nStr = LongBVtoStr(vec, len);
    // char* nStr1 = LongBVtoStr(vec, len);

    // printf("%s \n", nStr);
    PrintBV(vec, len);

    free(vec1);
    vec1 = NULL;
    free(vec);
    vec = NULL;
    free(nStr);
    nStr = NULL;
}

unsigned char* strToLongBV(char* str1, size_t* len)
{
  if(!str1 || !len)
  {
    return NULL;
  }

  int ix = 0;
  int i = 0;
  size_t cells = 0;
  unsigned char mask = 1;
  *len = strlen(str1);
  cells = ((*len - 1) / 8) + 1;

  unsigned char* vec = (unsigned char*)calloc(cells, sizeof(unsigned char));
  if(!vec) return NULL;

  for(i = 0; i < cells; i++)
  {
    mask = 1;
    for(int j = 0; j < 8 && ix < *len; j++)
    {
      if(str1[ix] != '0')
      {
        vec[i] = vec[i] | mask;
      }
      mask = mask << 1;
      ix++;
    }
  }
  return vec;
}

char* LongBVtoStr(unsigned char* vec, size_t len)
{
  if(!vec) return NULL;

  int ix = 0;
  int i = 0;
  size_t cells = 0;
  unsigned char mask = 1;
  cells = ((len - 1) / 8) + 1;

  char* str = (char*)calloc(len + 1, sizeof(char));
  if(!str) return NULL;


  for(i = 0; i < cells; i++)
  {
    mask = 1;
    for(int j = 0; j < 8 && ix < len; j++)
    {
      if(vec[i] & mask)
        str[ix] = '1';
      else
        str[ix] = '0';

      mask = mask << 1;
      ix++;
    }
  }
  str[len] = '\0';
  return str;
}

void PrintBV(unsigned char* vec, size_t bits)
{
  if(!vec) return;

  size_t cells = ((bits - 1) / 8) + 1;
  size_t ix = 0;
  unsigned char mask = 1;

  for(size_t i = 0; i < cells; i++)
  {
    mask = 1;
    for(size_t j = 0; j < 8 && ix < bits; j++)
    {
      if(vec[i] & mask)
        printf("1");
      else
        printf("0");
      mask = mask << 1;
      ix++;
    }
  }
  printf("\n");
}

unsigned char* logMul(unsigned char *vecA, size_t bitsA, unsigned char *vecB, size_t bitsB)
{
  if(!vecA || !vecB) return NULL;
  if(bitsA != bitsB) return NULL;

  size_t cells = ((bitsA - 1) / 8) + 1;

  unsigned char* vec = (unsigned char*)calloc(cells, sizeof(unsigned char));
  if(!vec) return NULL;

  for(size_t i = 0; i < cells; i++)
  {
    vec[i] = (vecA[i]) & (vecB[i]);
  }

  return vec;
}

unsigned char* logSum(unsigned char *vecA, size_t bitsA, unsigned char *vecB, size_t bitsB)
{
  if(!vecA || !vecB) return NULL;
  if(bitsA != bitsB) return NULL;

  size_t cells = ((bitsA - 1) / 8) + 1;

  unsigned char* vec = (unsigned char*)calloc(cells, sizeof(unsigned char));
  if(!vec) return NULL;

  for(size_t i = 0; i < cells; i++)
  {
    vec[i] = (vecA[i]) | (vecB[i]);
  }

  return vec;
}

unsigned char * sumMod2(unsigned char *vecA, size_t bitsA, unsigned char *vecB, size_t bitsB)
{
  if(!vecA || !vecB) return NULL;
  if(bitsA != bitsB) return NULL;

  size_t cells = ((bitsA - 1) / 8) + 1;

  unsigned char* vec = (unsigned char*)calloc(cells, sizeof(unsigned char));
  if(!vec) return NULL;

  for(size_t i = 0; i < cells; i++)
  {
    vec[i] = (vecA[i]) ^ (vecB[i]);
  }

  return vec;
}

void shiftRight(unsigned char *vec, size_t bits, size_t k)
{
  if(!vec) return;

  size_t cells = ((bits - 1) / 8) + 1;
  size_t indxToCopy = k / 8;
  size_t shift = k % 8;
  size_t tailLen = cells * 8 - bits;

  for(int i = cells - 1; i >= 0; i--)
  {
    if(i - indxToCopy >= 0)
    {
      vec[i] = vec[i - indxToCopy];
    }
    else
    {
      vec[i] = 0;
    }

    if(i - indxToCopy - 1 >= 0)
      vec[i] = (vec[i] << shift) | (vec[i - indxToCopy - 1] >> (8 - shift));
    else
      vec[i] = vec[i] << shift;
  }

  if(tailLen > 0)
  {
    unsigned char mask = 255; // ~0 == cell full of ones
    mask = mask >> tailLen;
    vec[cells - 1] = vec[cells - 1] & mask;
  }
}

void shiftLeft(unsigned char *vec, size_t bits, size_t k)
{
  if(!vec) return;

  size_t cells = ((bits - 1) / 8) + 1;
  size_t indxToCopy = k / 8;
  size_t shift = k % 8;

  for(int i = 0; i < cells; i++)
  {
    if(i + indxToCopy < cells)
    {
      vec[i] = vec[i + indxToCopy];
    }
    else
    {
      vec[i] = 0;
    }

    if(i + indxToCopy + 1 < cells)
      vec[i] = (vec[i] >> shift) | (vec[i + indxToCopy + 1] << (8 - shift));
    else
      vec[i] = vec[i] >> shift;
  }
}

void inversion(unsigned char *vec, size_t bits)
{
  if(!vec) return;

  size_t cells = ((bits - 1) / 8) + 1;
  size_t tailLen = cells * 8 - bits;

  for(int i = 0; i < cells; i++)
  {
    vec[i] = ~vec[i];
  }

  if(tailLen > 0)
  {
    unsigned char mask = 255; // ~0 == cell full of ones
    mask = mask >> tailLen;
    vec[cells - 1] = vec[cells - 1] & mask;
  }
}

void set1(unsigned char *vec, size_t bits, size_t bit)
{
  if(!vec) return;
  if(bits - 1 < bit) return;

  size_t byte = bit / 8;
  size_t shiftForMask = bit % 8;

  unsigned char mask = 1;
  mask = mask << shiftForMask;
  vec[byte] = vec[byte] | mask;
}

void set0(unsigned char *vec, size_t bits, size_t bit)
{
  if(!vec) return;
  if(bits - 1 < bit) return;

  size_t byte = bit / 8;
  size_t shiftForMask = bit % 8;

  unsigned char mask = 1;
  mask = mask << shiftForMask;
  vec[byte] = (vec[byte] | mask) ^ mask;
}
