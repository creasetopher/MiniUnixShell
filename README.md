## A mini Unix Shell

### All /usr/bin command are available to this shell.

#### There is also an additional command `tft`


#### tft (short for "traverse file tree")

SYNOPSIS:
tft is a command that will search the current directory all the way up to the user's home directory for a specific file of directory. tft wii take a file or directory name and search all parent/descendant folders of the current working directory.



DESCRIPTION:

usage 1:
  In this example, there is a file named "file.txt" in the folder /Users/username/Documents.

	Run the script with command
		tft file.txt

		>> tft file.txt
		>> This file is in: /Users/username/Documents

 usage 2:
	In this example, a user is looking for a file named "grappling.c" which does
	not exist on the users machine. This command will look in the current folder and move its way
	up the file tree looking for the file until it reaches the user's home directory. If a file or directory with a name matching the passed in parameter is not found, the command will notify the user.

    >> tft "grappling.c"
    >> Unable to locate file or directory: grappling.c



tft is a command that will traverse a file tree from current directory up to the home directory searching for a specific file or directory.

Essentially, tft will take in an argument that will be the filename to search for. Then, using the dirent.h header file, opens the current directory and iterates through the list of files, parses each filename to compare to the passed-in filename, and returns the path of the directory being searched if found.
