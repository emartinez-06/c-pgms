# CSI 3336 Systems Programming

## Project 8

### Parallel Sums

 

You’re going to write a program called pSum.c. This program will use multiple processes to sum numbers found in a file.

When communicating between the parent and the child instances, we will be using a single pipe for each child.

Your program should retrieve a filename and a number from the command line. The filename represents a file that stores a list of integer values. The number represents the number of child processes that must be used in the calculation of the sum of all the numbers located in the file. You will need to evenly distribute the number of values found in the file between all the child processes.

Each child process will sum the values it is responsible for and then submit that sum to the parent process. The parent process will accumulate all values submitted by its children. Once the parent is done accumulating the values from all children, it will report the completed sum to the screen.

You can use stdio, but the file will store integers using as a binary representation as defined on our Linux servers not as a text representation. You may find it easier to restrict yourself to using system calls for all I/O with the exception of printing the final result to the screen.

When you are done, submit an electronic copy of your program (via a submission script) and turn in a pdf of your source code on Canvas.
