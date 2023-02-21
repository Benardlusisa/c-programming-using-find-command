# c-programming-using-find-command
To compile: Type "make" in the command line while in the same directory as the source code files and Makefile.
To run: Type "./search" in the command line followed by any desired command line options and arguments.
*/

/*
This program allows the user to traverse a file hierarchy and perform various functions on each file in the hierarchy. The user can specify the starting directory for the file traversal, and can also use command line options to filter the output of the program based on file size, file name pattern, and file type.

Functions:
- main(): parses command line options and calls the appropriate functions to traverse the file hierarchy and display the file information.

Files:
- search.c: contains the main() function and the option parsing code.
- search.h: contains function prototypes for the functions in search.c and any necessary constant definitions.


Compilation instructions:
- Ensure that all source code files and the Makefile are in the same directory.
- Open a terminal window and navigate to the directory containing the source code files and the Makefile.
- Type "make" in the terminal window to compile the program.
- If compilation is successful, the program binary will be named "search" and will be located in the same directory as the source code files.

Execution instructions:
- Open a terminal window and navigate to the directory containing the "search" binary.
- Type "./search" in the terminal window followed by any desired command line options and arguments.

Example command line usage:
- Traverse the file hierarchy starting from the current directory and print file information to standard output:
    ./search
- Traverse the file hierarchy starting from the directory "/home/user/documents" and print file information to standard output:
    ./search /home/user/documents
- Traverse the file hierarchy starting from the current directory and print file information to standard output, with file sizes and permissions:
    ./search -S
- Traverse the file hierarchy starting from the current directory and print file information to standard output, with only files less than or equal to 1024 bytes in size:
    ./search -s 1024
- Traverse the file hierarchy starting from the current directory and print file information to standard output, with only files containing the string "jpg" and with a depth less than or equal to 1:
    ./search -f jpg 1
- Traverse the file hierarchy starting from the current directory and print file information to standard output, with file sizes and permissions, and only files containing the string "jpg" and with a depth less than or equal to 2:
    ./search -S -f jpg 2
*/

/* 
Note: The program assumes that the user has appropriate read permissions to access all files and directories in the specified file hierarchy. If the user does not have sufficient permissions, the program may not be able to traverse the entire file hierarchy or may produce unexpected results.
*/


