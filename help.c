#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>


int main(int argc, char const *argv[]) {
  char helpString[] = "Hello! This is Chris's mini-shell, an adaptaion of the "
                      "fan-favorite Linux shell! There are a handful of commands"
                      " available with this shell that you may find useful:\n\n"
                      "cd - changes the directory you're currently working in.\n"
                      "help - provides helpful information for this shell.\n"
                      "exit - terminates the mini-shell.\n";

  write(1, helpString, strlen(helpString));
  return 0;
}
