#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

#include <cstring>
#include <iostream>

#include "myShell_class.h"
extern char ** environ;

/*readIn function is used to print the prompt and read from stdin.*/
bool readIn(std::string & commandLine, myShell & shell) {
  /*Get current directory from the class myShell*/
  std::string curDir = shell.getCurDir();

  std::cout << "myShell:" << curDir << " $";
  std::getline(std::cin, commandLine);

  /*Check if EOF is encountered.*/
  return std::cin.good();
}

int main(int argc, char * argv[]) {
  std::string commandLine;
  myShell shell;

  /*Initialize the ECE551PATH environment variable with the value of PATH.
    Set PATH and save it for later use.*/
  shell.initEnv();

  /*Keep reading from stdin*/
  while (readIn(commandLine, shell)) {
    /*If "exit" be typed, exit the program.*/
    if (commandLine == "exit") {
      return EXIT_SUCCESS;
    }

    /*Otherwise, execute the program.*/
    shell.execute(commandLine);
  }
  return EXIT_SUCCESS;
}
