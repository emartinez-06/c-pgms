# easterEggs.c

This problem will give you an opportunity to practice interacting with the Linux file system and processes from within a C program. Write a C program, easterEggs.c, that processes the command-line to obtain a filename. Your program will then spawn five child processes assigning each child a unique color. Each child process will be responsible for using the filename, passed on the command-line to the parent, to search for all instances of this filename starting in the current directory and count the number of times its assigned color is found within the all instance of the file. Each child will report its count back to the parent which will display the results to the screen after all results are collected.

The following example illustrates the operation of easterEggs. The line starting with an angle bracket illustrates how one might invoke easterEggs. The following line shows the output of easterEggs.

\> easterEggs easter.egg
red:     10
green:    9
blue:   110
yellow:  23
orange:   5
All instances of the file named on the command-line, easter.egg in the example, will contain a list of integers that correspond to colors as described in the following enumerated data type. Each file instance will store an unknown number of integer values in binary format

enum color {red, green, blue, yellow, orange};
When you are done, turn in a pdf of your source code on Canvas and submit an electronic copy using submit.systems.


### Remarks
- Required to use the struct dirent
- Use system MACROS before stat()
- Read Chapter 3
- Read input unformatted





