#include <stdio.h>
#include <stdarg.h>
#include <math.h>

/*
  foo("sdfc", string, int, float, character);
 */
void foo(const char *format, ...)
{
  va_list ap;
  char *s;
  int d;
  float f;
  char c;

  va_start(ap, format);

  while (*format) {
    switch (*format++) {
    case 's':
      s = va_arg(ap, char *);
      printf("string: %s\n", s);
      break;
    case 'd':
      d = va_arg(ap, int);
      printf("int: %d\n", d);
      break;
    case 'f':
      f = va_arg(ap, double);   /* floats get promoted to double when passed */
      printf("float: %f\n", f); /* through a variable argument list.         */
      break;
    case 'c':
      c = va_arg(ap, int);      /* chars get promoted to int when passed */
      printf("char: %c\n", c);  /* through a variable argument list.     */
      break;
    }
  }

  va_end(ap);
}

#define FOO(...) printf(__VA_ARGS__)

int main(int argc, char *argv[])
{
  foo("sfdc", "Hello World!", M_PI, 42, 'q');

  return 0;
}
