#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <ctype.h>
#include <string.h>
#include <stdio.h>
#include <dirent.h>
#include <limits.h>

int main(int argc, char const *argv[]) {
  if (argv[2] == NULL) {
    write(1, "Please provide an filename or directory "
              "name argument with the tft command", 75);
    exit(1);
  }
  char homeDir[PATH_MAX];
  strcpy(homeDir, argv[2]);
  char currentDir[PATH_MAX];
  strcpy(currentDir, getcwd(NULL, 0));
  const char *filename = argv[1];
  DIR *dir;
  struct dirent *file;
  int i = 0;


  // if (homeDir == NULL) {
  //   strcpy(homeDir, argv[2]);
  // // }
  // printf("homeDir = %s\n", homeDir);
  // write(1, homeDir, 25);
  // scanf("\n");

  char homeDirWithSlash[strlen(homeDir) + 2];
  strcpy(homeDirWithSlash, homeDir);
  strcat(homeDirWithSlash, "/");

  while (strcmp(currentDir, homeDirWithSlash) != 0) {

    dir = opendir(currentDir);
    if (dir != NULL) {
      file = readdir(dir);
      while (file != NULL) {
        if (strcmp(filename, file->d_name) == 0) {
          write(1, "file is located in: ", 20);
          write(1, currentDir, strlen(currentDir));
          exit(1);
        }
        file = readdir(dir);
      }
      int end = strlen(currentDir) - 2;

      while (currentDir[end] != '/') {
        end--;
      }
      currentDir[end + 1] = '\0';
    }
    else {
      write(1, "error opening directory: ", 30);
      write(1, currentDir, strlen(currentDir));
      scanf("\n");
    }
  }
  write(1, "Unable to locate file or directory: ", 40);
  write(1, filename, strlen(filename));
  write(1, "\n", 2);
  exit(1);
  return 0;
}
