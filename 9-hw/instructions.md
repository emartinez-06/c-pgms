# Homework 9
## Due 10/30/2026

Ensure that execution happens in *parallel*. For example any child process should not have any expectation of finishing execution before any other child process.

1. Write a program that simulates the action of bash. Your program should take a command as a command-line parameter, execute the command using one of the exec family of functions, and return the value returned by the command to the shell. Notice that you will need to fork a child process to do this problem.

2. Write a program that forks 5 child processes. The parent process should print "Waiting for children..." then wai for all the children to finish. Each child should print the current time to the screen in the format: day of the week, month/day/year hour:min:sec. The parent should print "Done" after all children have finsihed.
