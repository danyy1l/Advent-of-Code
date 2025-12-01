#include <stdio.h>
#include <stdlib.h>

int main() {
  FILE *input_f, *output_f;
  char buf[8];
  int rot, num, count = 0;
  int dial = 50;

  input_f = fopen("01_input.dat", "r");
  if (input_f == NULL)
    return EXIT_FAILURE;

  output_f = fopen("01_output.dat", "w");
  if (output_f == NULL)
    return EXIT_FAILURE;

  while (fscanf(input_f, "%s", buf) == 1) {
    /* Dato leido */
    num = atoi(buf + 1);

    /* Tipo de rotacion */
    if (buf[0] == 'L') {
      dial = (dial - num + 100) % 100;
    } else if (buf[0] == 'R') {
      dial = (dial + num) % 100;
    } else
      return EXIT_FAILURE;

    fprintf(output_f, "Dial after \"%s\": %d\n", buf, dial);

    if (dial == 0)
      count++;
  }

  fprintf(stdout, "The result is: %d\n", count);

  fclose(input_f);
  fclose(output_f);

  return EXIT_SUCCESS;
}
