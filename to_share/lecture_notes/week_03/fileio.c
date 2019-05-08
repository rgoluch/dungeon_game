#include <stdio.h>
#include <stdlib.h>

typedef enum action {
  read_binary,
  write_binary,
  read_text,
  write_text
} action_t;

int main(int argc, char *argv[])
{
  FILE *f;

  struct {
    int i;
    int j;
  } s = { 1, 2 };

  if (!(f = fopen("binary_file", "w"))) {
    fprintf(stderr, "Failed to open file");

    return -1;
  }

  if (fwrite(&s, sizeof (s), 1, f) != 1) {
    // Error
  }

  s.i = 0;
  s.j = 0;

  fclose(f);
  f = fopen("binary_file", "r");

  fread(&s, sizeof (s), 1, f);

  fclose(f);

  printf("Read the values %d and %d\n", s.i, s.j);

  return 0;
}
