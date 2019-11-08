// Modify this file for your assignment

#include <stdio.h>
#include <stdlib.h>
#include <signal.h> // This is new!
#include <unistd.h>
#include <ctype.h>
#include <string.h>
#include <limits.h>

const int BUFFER_SIZE = 80;

/*
  Function: populateBuiltinCommands
  Parameters: none
  Usage: populates an array with the names of shell builtins.
*/
char** populateBuiltinCommands() {
  char *command1 = (char*)malloc(sizeof(char) * 8);
  char *command2 = (char*)malloc(sizeof(char) * 8);
  char *command3 = (char*)malloc(sizeof(char) * 8);
  char *command4 = (char*)malloc(sizeof(char) * 8);

  strcpy(command1, "./cd");
  strcpy(command2, "./help");
  strcpy(command3, "./exit");
  strcpy(command4, "./tft");

  char **commandPaths = (char**)malloc(sizeof(char*) * 4);

  commandPaths[0] = command1;
  commandPaths[1] = command2;
  commandPaths[2] = command3;
  commandPaths[3] = command4;
  return commandPaths;
}

/*
  Function: stringTrim
  Parameters: a pointer to a char array (i.e. a C string)
  Usage: trims the whitespace around a string.
  Returns: a whitespace-trimmed string.
*/
char *stringTrim(char *str) {
  char *end;

  // Trim leading space
  while(isspace(*str)) {
    str++;
  }

  if(*str == 0)  // string must've been all spaces and now
    return str;  // has reached terminator

  end = str + strlen(str) - 1;
  while(end > str && isspace(*end)) {
    end--;
  }

  // Write null terminator at end of string
  end[1] = '\0';

  return str;
}

/* Create a signal handler

  Function: sigint_handler
  Parameters: an int representing a keystroke -> this is a bit of POSIX magic
  Usage: if the user presses ctrl+c, this function will terminate the current
          session of the shell.
*/
void sigint_handler(int sig){
  // ensuring that this function only runs for ctrl+c
  if (sig == SIGINT) {
  	write(1, "mini-shell terminated\n", 22);
  	exit(0);
  }
}


int main() {

  pid_t pid1, pid2;
  int pipefd[2];

	// Install our signal handler
	signal(SIGINT, sigint_handler);

  char homeDir[PATH_MAX];

  if (pid1 != 0) {
    printf("================Running Chris's mini-shell!======================\n");
  	printf("You can only terminate by pressing Ctrl+C\n");
  }

	while(1) {

		sleep(1);

    if (pid1 != 0) {
      write(1, "mini-shell> ", 12);
    }

    char in[BUFFER_SIZE];

    fgets(in, BUFFER_SIZE, stdin);

    if (strlen(in) <= 1) {
      continue;
    }

    char* argv[16];
    char** commandPaths = populateBuiltinCommands();
    char* temp = strtok(in, " ");
    // iterates through input separating strings by "|"
    int i = 0;
    char command[strlen(temp) + 1];
    char arg1[10];
    char arg2[10];
    argv[0] = command;
    argv[1] = arg1;
    argv[2] = arg2;

    while (temp != NULL) {
      temp = stringTrim(temp);

      // this is a command ex: ls -a
      strcpy(argv[i], temp);
      temp = strtok(NULL, " ");
      i++;

    }

        if (strcmp(argv[0], "exit") == 0) {
            exit(1);
        }


        if (strcmp(argv[0], "tft") == 0) {
          char *homeDir = getenv("HOME");
          argv[i] = getenv("HOME");
          argv[i + 1] = NULL;
        }
        else {
          argv[i] = NULL;
        }


        // by this point we have an arg vector to pass to program

        pid1 = fork();

        // the parent process will wait for the child to finish executing.
        if (pid1 != 0) {
          int* childStatus = 0;
          waitpid(pid1, childStatus, 0);
        }

        // check to see if command is any of the built-ins
      else {

        int i;
        char commandName[6];
        strcpy(commandName, argv[0]);

        char programWithPath[BUFFER_SIZE] = "/bin/";
        strncat(programWithPath, commandName, strlen(commandName));
        if (execve(programWithPath, argv, NULL) == -1) {

          strcpy(programWithPath, "./");
          strncat(programWithPath, commandName, strlen(commandName));

          argv[0] = programWithPath;
          for (i = 0; i < 4; i++) {
            if (strcmp(programWithPath, commandPaths[i]) == 0) {
                execve(programWithPath, argv, NULL);
                exit(1);
            }
          }
          // write(1, programWithPath, 150);
          write(1, "Command not found--Did you mean something else?\n", 48);
          exit(0);
        }
        else {
          exit(0);
        }
      }
    }
	return 0;
}
