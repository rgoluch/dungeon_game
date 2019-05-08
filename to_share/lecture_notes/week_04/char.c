#include <stdio.h>
#include <ctype.h>

char *words[] = {
  "aardvark",
  "beaver",
  "chris",
  "doggo",
  "elephant",
  "frog",
  "giraffe",
  "hipopotamus",
  "iguana",
  "jeremy",
  "koala",
  "llama",
  "memes",
  "nerd",
  "owl",
  "pteradactyl",
  "qinoa",
  "resuscitation",
  "sico mode",
  "tsunami",
  "umbrella",
  "vape",
  "wumbo",
  "xylephone",
  "yeet",
  "zamboni",
};

int main(int argc, char *argv[])
{
  if (argc != 2) {
    fprintf(stderr, "Please supply a letter!\n");
    return -1;
  }

  printf("%s begins with %c\n", words[tolower(argv[1][0]) - 'a'], argv[1][0]);

  return 0;
}
