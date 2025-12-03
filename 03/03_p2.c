#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
  FILE *pf = NULL;

  pf = fopen("03_input.dat", "r");
  if (pf == NULL) {
    perror("fopen");
    return EXIT_FAILURE;
  }

  char *line = NULL;
  char *lineFromMax = NULL;
  size_t len = 0;
  long result = 0;
  int maxIsLast = 0;

  while (1) {
    ssize_t read = getline(&line, &len, pf);
    if (read == -1) {
      break;
    }

    int max = -1;
    int maxPos = -1;
    int i = 0;

    /* Valor maximo */
    while (line[i] != '\0' && line[i] != '\n') {
      if (line[i] - '0' > max) {
        max = (line[i] - '0');
        maxPos = i;
      }
      i++;
    }

    /* Segundo maximo */
    int secMax = -1;
    i = maxPos + 1;
    while (line[i] != '\0' && line[i] != '\n') {
      if (line[i] - '0' > secMax)
        secMax = (line[i] - '0');

      i++;
    }

    /* Caso maximo es ultimo */
    if (secMax == -1) {
      maxIsLast = 1;
      i = 0;
      while (i < maxPos) {
        int v = line[i] - '0';
        if (v > secMax)
          secMax = v;
        i++;
      }
      result += secMax * 10 + max;
    } else {
      result += max * 10 + secMax;
    }

    /* AHORA DEBERIA COGER LOS MAS GRANDES COMPRENDIDOS ENTRE LOS MAXIMOS,
     * REVISAR CASOS ESPECIALES
     */
  }

  printf("%ld\n", result);
  free(line);
  fclose(pf);

  return EXIT_SUCCESS;
}
