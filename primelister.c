#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

typedef struct vector {
  unsigned long long prime;
  unsigned long long *arr;
} vec;

vec *vec_init(unsigned long long prime) {
  unsigned long long *arr = calloc(64, sizeof(unsigned long));
  if (NULL == arr) {printf("Memory error!"); exit(0);}
  arr[0] = prime - 1;

  vec *vect = calloc(1, sizeof(vec));
  if (NULL == vect) {printf("Memory error!"); exit(0);}
  vect->prime = prime;
  vect->arr = arr;

  return vect;
}

unsigned short vec_getNextExp(vec *vect) {
  unsigned short exponent = 0llu;
  for (unsigned short i = 0; i < 64; ++i) {
    if (vect->arr[i] == vect->prime - 1) {
      vect->arr[i] = 0;
      continue;
    } else {
      vect->arr[i] += 1;
      exponent = i;
      break;
    }
  } return exponent;
}

unsigned long long powll(unsigned long long base, unsigned short exp) {
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
  puts("");
  // Fin
  for (unsigned long i = 0; i < primes; ++i) {
    free(arr[i]->arr);
    free(arr[i]);
  }
  free(arr);
  return 0;
}

int main(int argc, char **argv) {
  if (2 != argc) {puts("one argument with number of primes to find.");}
  unsigned int primes = strtoul(argv[1], NULL, 10);
  (void) primelister(primes);
  return 0;
}
