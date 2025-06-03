#include "std_lib.h"

int div(int a, int b) {
  int res = 0, sign = 1;
  if (a < 0) { a = -a; sign *= -1; }
  if (b < 0) { b = -b; sign *= -1; }
  while (a >= b) { a -= b; res++; }
  return sign * res;
}

int mod(int a, int b) {
  int sign = a < 0 ? -1 : 1;
  a = a < 0 ? -a : a;
  b = b < 0 ? -b : b;
  while (a >= b) a -= b;
  return a * sign;
}

bool strcmp(char *a, char *b) {
  while (*a && *b && *a == *b) a++, b++;
  return *a == '\0' && *b == '\0';
}

void strcpy(char *dst, char *src) {
  while (*src) *dst++ = *src++;
  *dst = '\0';
}

void strcat(char *dst, const char *src) {
  while (*dst) dst++;
  while (*src) *dst++ = *src++;
  *dst = '\0';
}

void clear(byte *buf, unsigned int size) {
  for (unsigned int i = 0; i < size; i++) buf[i] = 0;
}

void atoi(char *str, int *num) {
  int i = 0, res = 0, sign = 1;
  if (str[0] == '-') { sign = -1; i++; }
  while (str[i] >= '0' && str[i] <= '9') res = res * 10 + (str[i++] - '0');
  *num = res * sign;
}

void itoa(int num, char *str) {
  int i = 0, sign = num < 0 ? -1 : 1;
  if (sign == -1) num = -num;
  do {
    str[i++] = (num % 10) + '0';
    num /= 10;
  } while (num);
  if (sign == -1) str[i++] = '-';
  str[i] = '\0';
  for (int j = 0; j < i / 2; j++) {
    char t = str[j];
    str[j] = str[i - j - 1];
    str[i - j - 1] = t;
  }
}
