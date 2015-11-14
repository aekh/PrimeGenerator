#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// Waring atm this might eat memory.

typedef struct vector {
  unsigned long long prime;
  unsigned int *arr;
  unsigned long long pos;
  unsigned long long size;
} vec;

vec *vec_init(unsigned long long prime) {
  unsigned long long pos = prime - 1;
  unsigned long long size = prime*prime;
  unsigned int *arr = calloc(prime*prime, sizeof(unsigned long));
  for (unsigned long long i = 1; i < prime; ++i) {
    arr[i * prime - 1] = 1;
  } arr[size - 1] = 2;

  vec *vect = calloc(1, sizeof(vec));
  vect->prime = prime;
  vect->pos = pos;
  vect->size = size;
  vect->arr = arr;

  return vect;
}

int vec_repeat(vec *vect) {
  // Init new values
  unsigned long long newSize = vect->prime * vect->size;
  unsigned int *newArr = calloc(newSize, sizeof(unsigned long));
  for (unsigned long i = 0; i < vect->prime; ++i) {
    memcpy(newArr + i * vect->size, vect->arr, vect->size * sizeof(unsigned long));
  } newArr[newSize - 1] += 1;

  // Get old array
  unsigned int *oldArr = vect->arr;

  // Set the old values
  vect->pos += 1;
  vect->size = newSize;
  vect->arr = newArr;
  
  // Free old array
  free(oldArr);

  return 0;
}

unsigned long long powll(unsigned long long base, unsigned int exp) {
  unsigned long long result = 1ULL;
  while (exp) {
    if (exp & 1) {result *= base;}
    exp >>= 1;
    base *= base;
  }
  return result;
}

int primelister(unsigned int primes) {
  // Init
  //unsigned long *primeArr = calloc(primes, sizeof(unsigned long)); primeArr[0] = 2;
  vec **arr = calloc(primes, sizeof(vec *));
  unsigned int pos = 1;
  arr[0] = vec_init(2);
  unsigned long long prevnum = 0, num = 1;

  //printf("%u, %u \n", pos, primes);
  
  printf("2, ");
  // Algorithm
  while (pos < primes) {
    printf("current pos:%u, primes:%u\n", pos, primes);
    prevnum = num;
    num = 1;
    for (int p = 0; arr[p] != NULL; ++p) {
      num *= powll(arr[p]->prime, arr[p]->arr[arr[p]->pos]);
      //printf(" ..:: %llu^%u, thus num = %llu.\n", arr[p]->prime, arr[p]->arr[arr[p]->pos], num);
      if (arr[p]->pos == arr[p]->size - 1) {
	vec_repeat(arr[p]);
      } else {
	arr[p]->pos += 1;
      }
    }
    if (prevnum > num) {
      // We found a new prime with value prevnum+1
      unsigned long long newPrime = prevnum + 1;
      //printf("this is what we have, prevnum:%llu . num:%llu . newPrime:%llu and %llu\n", prevnum, num, prevnum+1, newPrime);
      num = newPrime;
      arr[pos] = vec_init(newPrime);
      arr[pos]->pos += 1;
      ++pos;
      // Print new prime
      printf("%llu, ", newPrime);
    } //printf("prevnum: %llu, num; %llu - - \n", prevnum, num);
  }
  puts("End");
  // Fin
  for (unsigned long i = 0; i < primes; ++i) {
    free(arr[i]->arr);
  }
  free(arr);
  return 0;
}

int main(){//int argc, char* argv[]) {
  //if (2 != argc) {puts("one argument with number of primes to find.");}
  //unsigned int primes = strtoul(argv[0], NULL, 10);
  (void) primelister(500);
  return 0;
}
