#ifndef __MYSHELL_H__
#define __MYSHELL_H__
#include <stdlib.h>

#include <map>
#include <string>
#include <vector>
class myShell
{
 private:
  /*argvVector is used to save the arguments separated by whitespace.*/
  std::vector<std::string> argvVector;

  /*pathVector is used to save all the directories specified
    in the ECE551PATH.*/
  std::vector<std::string> pathVector;

  /*curDir saves the current directory.*/
  std::string curDir;

  /*vars saves the name and value of all variables that has been set.*/
  std::map<std::string, std::string> vars;

  /*getPathVector is used to separate and save the colon-delimited paths 
    in the ECE551PATH.*/
  void getPathVector();

  /*searchCommand is used to search each directory in the ECE551PATH,
    and check if a command without / exists.*/
  bool searchCommand();

  /*getArgvVector is used to separate and save the whitespace-delimited
    arguments in the input command and also deal with escaped whitespcae*/
  void getArgvVector(std::string & commandLine);

  /*changeDir is used to change the current directory when inputting 
    command cd*/
  void changeDir();

  /*checkVarName is used to check if the variable name is valid.*/
  bool checkVarName(std::string & varName);

  /*incVar is used to deal with the variable value and increment it
    when inputting command inc.*/
  void incVar(std::string & varName);

  /*exportVar is used to export the variable value into the environment
    when inputting command export.*/
  void exportVar(std::string & varName);

  /*setVar is used to set or update the variable value when inputting
    command set.*/
  void setVar(std::string & varName, std::string & value);

  /*evalVar is used to do $ evaluation.*/
  std::string evalVar(std::string & varName);

  /*evalCommandLine is used to evaluate the input command line to replace
    the $varname to its current value.*/
  void evalCommandLine(std::string & Line);

  /*setEnv is used to update the value of environment variable ECE551PATH 
   when the PATH was exported.*/
  void setEnv();

 public:
  /*Constructor: set the initial current directory.*/
  myShell() { curDir = getenv("PWD"); }

  /*getCurDir is used to provide current directory to main function.*/
  std::string getCurDir() { return curDir; }

  /*initEnv is used to initialize the ECE551PATH and save the initial PATH 
    value for the later recovery of ECE551PATH if needed.*/
  void initEnv();

  /*execute is used to execute the input command.*/
  void execute(std::string & commandLine);
};
#endif
