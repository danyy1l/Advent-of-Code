#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int vecinos(char **matriz, int filas, int columnas, int i, int j) {
  int count = 0;
  int x, y, ni, nj;

  for (x = -1; x <= 1; x++) {
    for (y = -1; y <= 1; y++) {
      if (x == 0 && y == 0)
        continue;
      ni = i + x;
      nj = j + y;

      if (ni >= 0 && ni < filas && nj >= 0 && nj < columnas) {
        if (matriz[ni][nj] == '@')
          count++;
      }
    }
  }
  return count;
}

int main() {
  FILE *pf = NULL;
  char buf[2048];
  int i, j;
  long cuenta = 0;

  if ((pf = fopen("04_input.dat", "r")) == NULL) {
    perror("fopen");
    return EXIT_FAILURE;
  }

  int filas = 0, columnas = 0;
  while (fgets(buf, sizeof(buf), pf)) {
    int len = strlen(buf);
    if (buf[len - 1] == '\n')
      len--;
    if (columnas == 0)
      columnas = len;
    filas++;
  }

  rewind(pf);

  char **matriz = (char **)malloc(filas * sizeof(char *));
  for (i = 0; i < filas; i++) {
    matriz[i] = (char *)malloc(columnas * sizeof(char));
    if (matriz[i] == NULL) {
      for (j = 0; j < i; j++) {
        free(matriz[j]);
      }
      free(matriz);
      perror("malloc");
      fclose(pf);
      return EXIT_FAILURE;
    }
  }

  for (i = 0; i < filas; i++) {
    fgets(buf, sizeof(buf), pf);
    for (j = 0; j < columnas; j++)
      matriz[i][j] = (buf[j] != '\n' && buf[j] != '\0') ? buf[j] : ' ';
  }

  for (i = 0; i < filas; i++) {
    for (j = 0; j < columnas; j++) {
      if (matriz[i][j] == '@' && vecinos(matriz, filas, columnas, i, j) < 4) {
        cuenta++;
      }
    }
  }

  printf("%ld\n", cuenta);

  fclose(pf);
  for (i = 0; i < filas; i++) {
    free(matriz[i]);
  }
  free(matriz);
  return EXIT_SUCCESS;
}
