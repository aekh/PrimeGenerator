#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Waring atm this might eat memory.

typedef struct vector {
  unsigned long long prime;
  unsigned int *arr;
  unsigned long long pos;
  unsigned long long size;
  unsigned long long offset;
} vec;

vec *vec_init(unsigned long long prime) {
  unsigned long long pos = 0, offset = prime;
  unsigned long long size = prime;
  unsigned int *arr = calloc(prime*prime, sizeof(unsigned long));
  if (NULL == arr) {printf("Memory error!"); exit(0);}

  for (unsigned long long i = 0; i < size; ++i) {
    arr[i] = 1;
  } arr[size - 1] = 2;

  vec *vect = calloc(1, sizeof(vec));
  if (NULL == vect) {printf("Memory error!"); exit(0);}
  vect->prime = prime;
  vect->pos = pos;
  vect->size = size;
  vect->arr = arr;
  vect->offset = offset;

  return vect;
} // [0,1,0,2,0,1,0,3]
  // [0,1,2,3,4,5,6,7]
  // [1,2,1,3]

int vec_repeat(vec *vect) {
  // Init new values
  unsigned long long newSize = vect->prime * vect->size;
  unsigned int *newArr = calloc(newSize, sizeof(unsigned long));
  if (NULL == newArr) {printf("Memory error!"); exit(0);}
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

unsigned int vec_getNextExp(vec *vect) {
  unsigned int exponent = 0llu;
  if (vect->prime == vect->offset) {
    exponent = vect->arr[vect->pos];
    if (vect->pos == vect->size - 1) {
	vec_repeat(vect);
    } else {
      vect->pos += 1;
    }
    vect->offset = 1;
  } else {
    vect->offset += 1;
  } return exponent;
}

unsigned long long powll(unsigned long long base, unsigned int exp) {
  unsigned long long result = 1llu;
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
  if (NULL == arr) {printf("Memory error!"); exit(0);}
  unsigned int pos = 1;
  arr[0] = vec_init(2llu);
  unsigned long long prevnum = 0llu, num = 1llu;

  //printf("%u, %u \n", pos, primes);
  
  printf("2, ");
  // Algorithm
  while (pos < primes) {
    prevnum = num;
    num = 1llu;
    for (int p = 0; arr[p] != NULL; ++p) {
      unsigned int exp = vec_getNextExp(arr[p]);
      num *= powll(arr[p]->prime, exp);
      //printf(" ..:: %llu^%u, thus num = %llu.\n", arr[p]->prime, exp, num);
    }
    if (1 == num) {
      // We found a new prime with value prevnum+1
      unsigned long long newPrime = prevnum + 1;
      //printf("this is what we have, prevnum:%llu . num:%llu . newPrime:%llu and %llu\n", prevnum, num, prevnum+1, newPrime);
      num = newPrime;
      arr[pos] = vec_init(newPrime);
      (void) vec_getNextExp(arr[pos]);
      ++pos;
      // Print new prime
      printf("%llu, ", newPrime);
    } //printf("prevnum: %llu, num; %llu - - \n", prevnum, num);
  }
  puts("End");
  // Fin
  for (unsigned long i = 0; i < primes; ++i) {
    free(arr[i]->arr);
    free(arr[i]);
  }
  free(arr);
  return 0;
}

int main() {//int argc, char* argv[]) {
  //if (2 != argc) {puts("one argument with number of primes to find.");}
  //unsigned int primes = strtoul(argv[0], NULL, 10);
  (void) primelister(3631);
  return 0;
}
