#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int digits(const long x) {
  if (x == 0)
    return 1;

  return floor(log10(x)) + 1;
}

void separar(const long x, long *mitadSup, long *mitadInf) {
  int digitos = digits(x);
  int mitad = digitos / 2;
  long divisor = 1;

  for (int i = 0; i < mitad; i++) {
    divisor *= 10;
  }

  *mitadSup = x / divisor;
  *mitadInf = x % divisor;
}

int main() {
  FILE *pf = NULL;
  char *token;

  if ((pf = fopen("02_input.dat", "r")) == NULL) {
    perror("fopen");
    return EXIT_FAILURE;
  }

  char *line = NULL;
  size_t len = 0;

  /* Leo toda la linea del fichero */
  ssize_t read = getline(&line, &len, pf);
  if (read == -1) {
    perror("read");
    fclose(pf);
    return EXIT_FAILURE;
  }

  char *ptr = line;
  long inf, sup;
  long count = 0;

  while (*ptr) {
    /* Leo de la linea los datos */
    sscanf(ptr, "%ld-%ld", &inf, &sup);

    if (digits(inf) % 2 == 0 || digits(sup) % 2 == 0 ||
        (digits(inf) != digits(sup))) {

      long foo = inf;
      long mitadSup, mitadInf;

      while (foo <= sup) {
        separar(foo, &mitadSup, &mitadInf);
        if (mitadInf == mitadSup) {
          count += foo;
          printf("Num: %ld | mitadSup: %ld | mitadInf: %ld | count = %ld\n",
                 foo, mitadInf, mitadSup, count);
          fflush(stdout);
        }
        foo++;
      }
    }

    /* Desplazo despues de la coma */
    ptr = strchr(ptr, ',');
    /* EOF  */
    if (!ptr)
      break;
    ptr++;
  }

  fprintf(stdout, "El resultado es: %ld\n", count);
  free(line);
  fclose(pf);
  return EXIT_SUCCESS;
}
