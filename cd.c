#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <string.h>


char *pathTrim(char *str) {
  char *end;

  end = str + strlen(str) - 1;
  while(end > str && *end != '/') {
    end--;
  }
  // Write null terminator at end of string
  end[1] = '\0';

  return str;
}

/*
  Function: cd
  Parameters: a char array pointer that is the path to the new directory
  Usage: if directory exists, this function will switch to this directory as the
          pwd. If the directory does not exist, a "does not exist" message is sent
          to the user.
*/
int cd(char *path) {
   // char *args[3] = {"shell"};
   char tempPath[1000];
   strcpy(tempPath, path);
   char oldDir[1000];
   char cwd[1000];

   getcwd(oldDir, sizeof(oldDir));
   getcwd(cwd, sizeof(cwd));

   if (strcmp(tempPath, ".") == 0) {
     exit(1);
   }
   else if (strcmp(tempPath, "..") == 0) {
     pathTrim(cwd);
    
   }
   else {
     strcat(cwd, "/");
     strcat(cwd, tempPath);
   }
   char confirmationString[30];
   if (chdir(cwd) != 0) {
     strcpy(confirmationString, " does not exist!\n");
     write(1, "directory ", 10);
     write(1, tempPath, strlen(tempPath));
     write(1, confirmationString, strlen(confirmationString));
   }

   else {

       strcpy(confirmationString, "You are now in -> ");
       write(1, confirmationString, strlen(confirmationString));
       write(1, cwd, strlen(cwd));
       write(1, "\n", 1);
       strcat(oldDir, "/shell");
       execve(&oldDir, NULL, NULL);
     }

   exit(1);
   return 0;
  }

int main(int argc, char const *argv[]) {
  write(1, "got!!!", 8);

  cd(argv[1]);
  return 0;
}
