#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

    long foo = inf;
    char haystack[2048];
    char needle[1024];

    while (foo <= sup) {
      snprintf(haystack, sizeof(haystack), "%ld%ld", foo, foo);
      snprintf(needle, sizeof(needle), "%ld", foo);
      haystack[strlen(haystack) - 1] = '\0';
      char *strip = haystack + 1;
      if (strstr(strip, needle)) {
        printf("Foo: %ld | Needle: %s | Haystack: %s | count: %ld\n", foo,
               needle, strip, count);
        count += foo;
      }

      foo++;
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
