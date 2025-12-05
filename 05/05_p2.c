#include <stdio.h>
#include <stdlib.h>

#define MAX(x, y) (((x) > (y)) ? (x) : (y))

typedef struct {
  long long start;
  long long end;
} rango;

int cmpRango(const void *a, const void *b) {
  rango *r1 = (rango *)a;
  rango *r2 = (rango *)b;
  if (r1->start < r2->start)
    return -1;
  if (r1->start > r2->start)
    return 1;
  return 0;
}

int main() {
  FILE *file;
  char filename[] = "05_input.dat";
  rango *ranges = NULL;
  int count = 0;
  int capacity = 100;

  file = fopen(filename, "r");
  if (file == NULL) {
    perror("Error al abrir el archivo 05_input.dat");
    return 1;
  }

  ranges = (rango *)malloc(capacity * sizeof(rango));
  if (ranges == NULL) {
    perror("Error de memoria");
    fclose(file);
    return 1;
  }

  long long r_start, r_end;
  while (fscanf(file, "%lld-%lld", &r_start, &r_end) == 2) {
    if (count >= capacity) {
      capacity *= 2;
      ranges = (rango *)realloc(ranges, capacity * sizeof(rango));
      if (ranges == NULL) {
        perror("Error al redimensionar memoria");
        fclose(file);
        return 1;
      }
    }
    ranges[count].start = r_start;
    ranges[count].end = r_end;
    count++;
  }
  fclose(file);

  if (count == 0) {
    perror("count");
    free(ranges);
    return 0;
  }

  qsort(ranges, count, sizeof(rango), cmpRango);

  long long total_numbers = 0;

  long long start = ranges[0].start;
  long long end = ranges[0].end;

  for (int i = 1; i < count; i++) {
    if (ranges[i].start <= end + 1) {
      end = MAX(end, ranges[i].end);
    } else {
      total_numbers += (end - start + 1);

      start = ranges[i].start;
      end = ranges[i].end;
    }
  }

  total_numbers += (end - start + 1);

  printf("Total: %lld\n", total_numbers);

  free(ranges);
  return 0;
}
