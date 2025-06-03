#include "shell.h"
#include "kernel.h"
#include "std_lib.h"
#include <string.h>


char username[16] = "user";
char suffix[16] = "";
int color = 0x07;

const char *yogurtQuotes[] = {
  "yo",
  "ts unami gng </3",
  "sygau"
};

void printPrompt() {
  char prompt[64];
  strcpy(prompt, username);
  if (suffix[0] != '\0') {
    strcat(prompt, "@");
    strcat(prompt, suffix);
  }
  strcat(prompt, "> ");
  printString(prompt);
}

void shell() {
  char buf[128];
  char cmd[64];
  char arg[2][64];
  int yogurtCounter = 0;

  printString("Welcome to EorzeOS!\n");
  while (true) {
    printPrompt();
    readString(buf);
    parseCommand(buf, cmd, arg);

    if (strcmp(cmd, "user")) {
      if (arg[0][0] == '\0') {
        strcpy(username, "user");
        printString("Username changed to user\n");
      } else {
        strcpy(username, arg[0]);
        printString("Username changed to ");
        printString(username);
        printString("\n");
      }
    } else if (strcmp(cmd, "grandcompany")) {
      if (strcmp(arg[0], "maelstrom")) {
        color = 0x04; // merah
        strcpy(suffix, "Storm");
        clearScreen();
      } else if (strcmp(arg[0], "twinadder")) {
        color = 0x0E; // kuning
        strcpy(suffix, "Serpent");
        clearScreen();
      } else if (strcmp(arg[0], "immortalflames")) {
        color = 0x01; // biru
        strcpy(suffix, "Flame");
        clearScreen();
      } else {
        printString("Unknown Grand Company!\n");
      }
    } else if (strcmp(cmd, "clear")) {
      color = 0x07;
      suffix[0] = '\0';
      clearScreen();
    } else if (strcmp(cmd, "add")) {
      int x, y;
      atoi(arg[0], &x);
      atoi(arg[1], &y);
      char res[16];
      itoa(x + y, res);
      printString(res);
      printString("\n");
    } else if (strcmp(cmd, "sub")) {
      int x, y;
      atoi(arg[0], &x);
      atoi(arg[1], &y);
      char res[16];
      itoa(x - y, res);
      printString(res);
      printString("\n");
    } else if (strcmp(cmd, "mul")) {
      int x, y;
      atoi(arg[0], &x);
      atoi(arg[1], &y);
      char res[16];
      itoa(x * y, res);
      printString(res);
      printString("\n");
    } else if (strcmp(cmd, "div")) {
      int x, y;
      atoi(arg[0], &x);
      atoi(arg[1], &y);
      if (y == 0) printString("Error: div by 0\n");
      else {
        char res[16];
        itoa(div(x, y), res);
        printString(res);
        printString("\n");
      }
    } else if (strcmp(cmd, "yogurt")) {
      printString("gurt> ");
      printString((char *)yogurtQuotes[yogurtCounter]);
      printString("\n");
      yogurtCounter = (yogurtCounter + 1) % 3;
    } else {
      printString(cmd);
      if (arg[0][0] != '\0') {
        printString(" ");
        printString(arg[0]);
      }
      if (arg[1][0] != '\0') {
        printString(" ");
        printString(arg[1]);
      }
      printString("\n");
    }
  }
}

void parseCommand(char *buf, char *cmd, char arg[2][64]) {
  int i = 0, j = 0, k = 0;
  while (buf[i] != ' ' && buf[i] != '\0') cmd[j++] = buf[i++];
  cmd[j] = '\0';
  for (int m = 0; m < 2; m++) arg[m][0] = '\0';
  for (int m = 0; m < 2 && buf[i] == ' '; m++) {
    i++;
    k = 0;
    while (buf[i] != ' ' && buf[i] != '\0') {
      arg[m][k++] = buf[i++];
    }
    arg[m][k] = '\0';
  }
}
