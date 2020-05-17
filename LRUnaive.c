#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
void printmas(int *mas, int n) {
  int i = 0;
  printf("\n");
  for (i = 0; i < n; i++) {
    printf(" %d ", mas[i]);
  }
  printf("\n");
  return;
}

void movemas(int *cache, int j, int m) {
  long long int k = 0;
  long long int tmp;
  if (j == 0)
    return;
  assert(j < m);
  tmp = cache[j];
  for (k = j; k > 0; k--) {
    cache[k] = cache[k - 1];
    // printf("\nmovemas: k = %d; ", k);
    // printmas(cache, m);
  }
  cache[0] = tmp;
  return;
}

void movemas2(int *cache, int num, int m) {
  long long int k = 0;
  for (k = m - 1; k > 0; k--) {
    cache[k] = cache[k - 1];
    // printf("\nmovemas2: k = %d; ", k);
    // printmas(cache, m);
  }
  cache[0] = num;
  return;
}

int cachecheck(FILE *f, int *cache, int m, int n) {
  long long int res = 0, i, j, curfull = 0, isequal = 0, num;
  for (i = 0; i < n; i++) {
    fscanf(f, "%lli", &num);
    if (curfull == m) {
      for (j = 0; j < m; j++) {
        if (cache[j] == num) {
          isequal = 1;
          res++;
          movemas(cache, j, m);    // puts cache[j] to cache[0] and moves other cache elements
          j = m - 1; 
        }
      }
      if (isequal == 0) {
        movemas2(cache, num, m);
      }
      isequal = 0;
    }
    if (curfull < m) {
      for (j = 0; j < m; j++) {
        if ((cache[j] == num) && (j < curfull)) {
          res++;
          isequal = 1;
          movemas(cache, j, m);
        }
      }
      if (isequal == 0) {
        movemas2(cache, num, m);
        curfull++;
      }
      isequal = 0;
    }
  }
  return res;
}


int main() {
  FILE *f;
  long long int m, n, res = -1;
  int *cache;
  fscanf(stdin, "%lli %lli", &m, &n);
  cache = (int *)calloc(m, sizeof(int));
  res = cachecheck(f, cache, m, n);
  printf("number of hits = %lli", res);
  return 0;
}
