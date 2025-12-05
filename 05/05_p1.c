#include <stdio.h>
#include <stdlib.h>

int main() {
  FILE *pf = NULL;

  if ((pf = fopen("05_input.dat", "r")) == NULL) {
    perror("fopen");
    return EXIT_FAILURE;
  }

  long **matriz = NULL;
  char *line = NULL;
  size_t len = 0;
  ssize_t read;
  int rangos = 0;

  /* Leo toda la linea del fichero */
  while ((read = getline(&line, &len, pf)) != -1) {
    if (line[0] == '\n')
      break;

    rangos++;
  }
  rewind(pf);

  matriz = (long **)malloc(rangos * sizeof(long *));
  if (matriz == NULL) {
    perror("malloc");
    return EXIT_FAILURE;
  }
  for (long i = 0; i < rangos; i++) {
    matriz[i] = (long *)malloc(2 * sizeof(long));
    if (matriz[i] == NULL) {
      for (long j = 0; j < i; j++) {
        free(matriz[j]);
      }
      free(matriz);
      perror("malloc2");
      return EXIT_FAILURE;
    }
  }

  long i = 0;
  while ((read = getline(&line, &len, pf)) != -1) {
    if (line[0] == '\n')
      break;

    sscanf(line, "%ld-%ld", &matriz[i][0], &matriz[i][1]);
    i++;
  }

  long num = 0;
  int count = 0;
  while (fscanf(pf, "%ld", &num) == 1) {
    for (i = 0; i < rangos; i++) {
      if (num >= matriz[i][0] && num <= matriz[i][1]) {
        count++;
        break;
      }
    }
  }

  printf("%d\n", count);

  for (long j = 0; j < rangos; j++) {
    free(matriz[j]);
  }
  free(matriz);
  free(line);
  fclose(pf);
  return EXIT_SUCCESS;
}
