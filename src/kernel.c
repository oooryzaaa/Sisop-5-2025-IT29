#include "shell.h"
#include "kernel.h"

int main() {
  clearScreen();
  shell();
}

void printString(char *str) {
  int i = 0;
  while (str[i] != '\0') {
    interrupt(0x10, 0x0E00 + str[i], 0, 0, 0);
    i++;
  }
}

void readString(char *buf) {
  int i = 0;
  char c;
  while (1) {
    c = interrupt(0x16, 0x0000, 0, 0, 0);
    if (c == '\r') break;
    else if (c == '\b') {
      if (i > 0) {
        i--;
        printString("\b \b");
      }
    } else {
      buf[i++] = c;
      interrupt(0x10, 0x0E00 + c, 0, 0, 0);
    }
  }
  buf[i] = '\0';
  printString("\r\n");
}

void clearScreen() {
  for (int i = 0; i < 80 * 25 * 2; i += 2) {
    putInMemory(0xB000, i, ' ');
    putInMemory(0xB000, i + 1, 0x07);
  }
  interrupt(0x10, 0x0200, 0, 0, 0); // set cursor ke 0,0
}
