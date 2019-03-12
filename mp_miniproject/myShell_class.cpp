#include "myShell_class.h"

#include <dirent.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
extern char ** environ;

/*Helper function vectorToArray is used to convert a vector of string to
  a array of char *.*/
char ** vectorToArray(std::vector<std::string> v) {
  char ** array = new char *[v.size() + 1];
  size_t index = 0;
  for (std::vector<std::string>::iterator it = v.begin(); it != v.end(); ++it) {
    array[index] = new char[it->length() + 1];
    strncpy(array[index], (*it).c_str(), it->length() + 1);
    index++;
  }

  /*Set the last element of the array to NULL since the argv and envp arrays
    in the function execve must each include a null pointer pointer at the end.*/
  array[index] = NULL;

  return array;
}

/*Initialize the ECE551PATH with the value of PATH and save the initial PATH value.*/
void myShell::initEnv() {
  char * env = getenv("PATH");
  if (setenv("ECE551PATH", env, 1) != 0) {
    perror("putenv");
    exit(EXIT_FAILURE);
  }
  std::string ENV("PATH");
  std::string PATH(env);
  setVar(ENV, PATH);
}

/*Update the ECE551PATH when PATH is exported(changed).*/
void myShell::setEnv() {
  std::string value = vars["PATH"];
  if (setenv("ECE551PATH", value.c_str(), 1) != 0) {
    perror("putenv");
    exit(EXIT_FAILURE);
  }
}

/*Parse the paths from the environment variable ECE551PATH*/
void myShell::getPathVector() {
  char * env = getenv("ECE551PATH");
  std::string path = "";

  /*Check every character in the environment variable.
    If it is ':', we have get a path in variable path. Save it in the pathVector.
    If not, add the character to the path, meaning we are still getting a path.*/
  for (size_t i = 0; i < strlen(env); i++) {
    if (env[i] != ':') {
      path += env[i];
    }
    else {
      pathVector.push_back(path);
      path = "";
    }
  }

  /*The last path is not followed by a ':'. Check if it exists and save it.*/
  if (path.length() != 0) {
    pathVector.push_back(path);
  }
}

/*Check if a command without / is exists in the directories in the ECE551PATH.
  Or check if a command with / is valid.*/
bool myShell::searchCommand() {
  /*found is a sign indicating whether the command exists or not.*/
  bool found = false;

  std::string command = argvVector[0];
  std::string fullPath = "";

  /*Check if there is a / in the command.*/
  if (command.find('/') == std::string::npos) {
    /*If not, iteratively get the path in the patnVector. Combine the path with the command to generate 
      a possible full path of the command.
      Try to read the file with ifstream. If the state of the stream is good, it means this path is valid. 
      We find the command and thus change the command without / with the full path we found.*/
    for (std::vector<std::string>::iterator it = pathVector.begin(); it != pathVector.end(); ++it) {
      fullPath = *it + '/' + command;
      std::ifstream ifs(fullPath.c_str());
      if (ifs.good()) {
        found = true;
        argvVector[0] = fullPath;
        break;
      }
    }
  }

  /*If so, just check if the path with / is valid.*/
  else {
    std::ifstream ifs(command.c_str());
    if (ifs.good()) {
      found = true;
    }
  }

  return found;
}

/*Parse the input command to get the arguments.*/
void myShell::getArgvVector(std::string & commandLine) {
  std::size_t end = 0;
  /*str is used to save each argument we found.*/
  std::string str = "";
  std::string temp(commandLine);

  /*Check if there is whitespace left since we would erase the whitespace and characters
    after we deal with them.*/
  while ((end = temp.find(' ')) != std::string::npos) {
    /*If the whitespace is at the first place of remaining command line.
      If the str is empty, it is just one of the multiple sequential whiterspace as separator. 
      We can just erase it.
      If not, it is the one following the escaped whitespace "\ " and works as a separator. We
      then save the argument.*/
    if (end == 0) {
      if (str.length() == 0) {
        temp.erase(0, 1);
      }
      else {
        argvVector.push_back(str);
        str = "";
      }
    }

    /*If the character in front of the whitespace is not a \. The whitespace is a separator.
      We save the all characters before the whitespace as an argument and erase the argument 
      and the whitespace from the temporary command line.*/
    else if (temp[end - 1] != '\\') {
      for (size_t i = 0; i < end; i++) {
        str += temp[i];
      }
      argvVector.push_back(str);
      str = "";
      temp.erase(0, end + 1);
    }

    /*If the whitespcae follows a \, we meet a escaped whitespace. We save all the characters before the \
      and add a whitespace at the end. But we do not consider this string as an argument since we do not
      meet with a whiterspace as a separator.*/
    else {
      for (size_t i = 0; i < end - 1; i++) {
        str += temp[i];
      }
      str += ' ';
      temp.erase(0, end + 1);
    }

    /*This part is special for command set. If we find the first command name is set and we hava got one
      argument. We then try to find to the next non-whitespace character after the argument and save all 
      the characters starting from the non-whitespace as the variable value.*/
    if (argvVector.size() != 0) {
      if (argvVector[0] == "set" && argvVector.size() == 2) {
        size_t found = temp.find_first_not_of(' ');
        temp.erase(0, found);
        argvVector.push_back(temp);
        return;
      }
    }
  }

  /*If there are things left after we deal with the last whitespace. We need to check there is something left 
    in the str.
    If str is not empty, the last whitespace is an escaped whitespace, we then combine str and the remaining 
    of temp as an argument. If str is empty, simple save the remaining of temp as an argument.*/
  if (temp.length() != 0) {
    if (str.length() == 0) {
      argvVector.push_back(temp);
    }
    else {
      str += temp;
      argvVector.push_back(str);
    }
  }

  /*If there is nothing left in the remaining of temp, we simple save the non-empty str as an argument.*/
  else if (str.length() != 0) {
    argvVector.push_back(str);
  }
}

/*Change the current working directory.*/
void myShell::changeDir() {
  /*If the input command includes the argument of ~, change to the home directory.*/
  if (argvVector[1] == "~") {
    char * path = getenv("HOME");
    if (chdir(path) != 0) {
      std::cerr << "Cannot change the directory." << std::endl;
      exit(EXIT_FAILURE);
    }
  }

  /*Otherwise, change to the corresponding directory.*/
  else if (chdir(argvVector[1].c_str()) != 0) {
    std::cerr << "Cannot change the directory." << std::endl;
    exit(EXIT_FAILURE);
  }

  /*Set the OLDPWD to the previous curDir.*/
  if (setenv("OLDPWD", curDir.c_str(), 1) != 0) {
    perror("putenv");
    exit(EXIT_FAILURE);
  }

  /*Get the current directory and set the PWD to the current curDir.*/
  char cwd[1024];
  curDir = getcwd(cwd, sizeof(cwd));
  if (setenv("PWD", curDir.c_str(), 1) != 0) {
    perror("putenv");
    exit(EXIT_FAILURE);
  }
}

/*Check if a variable name is valid.*/
bool myShell::checkVarName(std::string & varName) {
  bool valid = true;
  for (std::string::iterator it = varName.begin(); it != varName.end(); ++it) {
    if (((*it) != '_') && (isalnum(*it) == 0)) {
      valid = false;
      break;
    }
  }
  return valid;
}

/*Initialize the variable if needed and increment it by 1.*/
void myShell::incVar(std::string & varName) {
  double num = 0;
  std::string value;
  std::stringstream ss;
  std::map<std::string, std::string>::iterator it = vars.find(varName);

  /*If the variable cannot be found in the vars. It is not set yet. Set it to "".*/
  if (it == vars.end()) {
    value = "";
  }
  else {
    value = it->second;
  }

  /*Use stringstream to convert a num string to a num and increment by 1.
    If the variable does not represent a number, set it to 1.*/
  ss << value;
  ss >> num;
  if (ss.good() == 0) {
    num = num + 1;
  }
  else {
    num = 1;
  }

  /*Convert the incremented num to string. Save or update the variable value.*/
  std::ostringstream oss;
  oss << num;
  value = oss.str();
  setVar(varName, value);
}

/*Export the variable value to the environment.*/
void myShell::exportVar(std::string & varName) {
  if (setenv(varName.c_str(), vars[varName].c_str(), 1) != 0) {
    perror("putenv");
    exit(EXIT_FAILURE);
  }
}

/*Set or update the variable value in vars.*/
void myShell::setVar(std::string & varName, std::string & value) {
  vars[varName] = value;
}

/*Evaluate a possible varibale to its value.*/
std::string myShell::evalVar(std::string & varName) {
  std::map<std::string, std::string>::iterator it;

  /*We input the longest possible variable name and search it in the vars.
    If not found, erase the last character of the variable name and search again.
    Repeat until we found it or all the possible names are not found.*/
  while (((it = vars.find(varName)) == vars.end()) && (varName.length() != 0)) {
    varName.erase(varName.end() - 1);
  }

  /*If we cannot found, evaluate this variable to empty string.
    If found, return its value.*/
  if (varName.length() == 0) {
    return "";
  }
  else {
    return it->second;
  }
}

/*Evaluate all the variables in the input command line to its value.*/
void myShell::evalCommandLine(std::string & Line) {
  std::string temp(Line);
  std::string value;
  size_t end;

  /*Find the last $ since it would not be affected by other $ evaluation.*/
  while ((end = temp.find_last_of('$')) != std::string::npos) {
    /*If $ is not followed by valid character of a variable name, we simply keep all the things.*/
    if (temp[end + 1] != '_' && isalnum(temp[end + 1]) == 0) {
      temp = temp.substr(0, end);  //keep
    }

    else {
      /*Otherwise, extract all the characters after the $.*/
      std::string lastPart(temp.substr(end + 1, temp.length() - end - 1));

      /*Find out the longest possible variable name after $.*/
      std::string varName;
      while ((lastPart[0] == '_') || (isalnum(lastPart[0]) != 0)) {
        varName += lastPart[0];
        lastPart.erase(0, 1);
      }

      /*Try to evaluate the variable to its value.*/
      std::string tempName(varName);
      value = evalVar(varName);

      /*If the varName is empty, we do not find any match in the vars. So evaluate the longest possible 
        variable to empty string.
        If not, evaluate the actual varName to its value.*/
      if (varName.empty()) {
        varName = '$' + tempName;
      }
      else {
        varName = '$' + varName;
      }

      /*Find the last occurence of the varName. It just means where we do $ evaluation just now.
        Replace the $varname with its value.*/
      std::size_t found = Line.rfind(varName);
      Line.replace(found, varName.length(), value);

      /*Re-start from the whole command line that has been evaluated to enable nest evaluation.*/
      temp = Line;
    }
  }
}

/*Execute the input command.*/
void myShell::execute(std::string & commandLine) {
  /*Evaluate all the varibles in the command line to their value. */
  evalCommandLine(commandLine);

  /*We are always using the same myShell. So we need to clear the argvVector
    and pathVector before re-use.*/
  argvVector.clear();

  /*Parse the input command line to arguments.*/
  getArgvVector(commandLine);

  /*Check if the input command line is empty.*/
  if (argvVector.empty()) {
    std::cerr << "No command input." << std::endl;
    return;
  }

  pathVector.clear();
  /*Parse the ECE551PATH to all the paths.*/
  getPathVector();

  /*If command is cd, check the number of arguments.*/
  if (argvVector[0] == "cd") {
    if (argvVector.size() != 2) {
      std::cerr << "Wrong number of arguments" << std::endl;
      return;
    }
    changeDir();
  }

  /*If command is set, check the number of arguments and the variable name.*/
  else if (argvVector[0] == "set") {
    if (argvVector.size() != 3) {
      std::cerr << "Wrong number of arguments" << std::endl;
      return;
    }
    std::string varName(argvVector[1]);
    std::string value(argvVector[2]);
    if (checkVarName(varName)) {
      setVar(varName, value);
    }
    else {
      std::cerr << "Invalid variable name." << std::endl;
      return;
    }
  }

  /*If command is export, check the number of arguments and the variabla name.
    If the variable name is PATH, then change the ECE551PATH in the environment too. */
  else if (argvVector[0] == "export") {
    if (argvVector.size() != 2) {
      std::cerr << "Wrong number of arguments" << std::endl;
      return;
    }
    if (checkVarName(argvVector[1])) {
      if (argvVector[1] != "PATH") {
        exportVar(argvVector[1]);
      }
      else {
        exportVar(argvVector[1]);
        setEnv();
      }
    }
    else {
      std::cerr << "Invalid variable name." << std::endl;
      return;
    }
  }

  /*If command is inc, check the number of arguments and the variable name.*/
  else if (argvVector[0] == "inc") {
    if (argvVector.size() != 2) {
      std::cerr << "Wrong number of arguments" << std::endl;
      return;
    }
    if (checkVarName(argvVector[1])) {
      incVar(argvVector[1]);
    }
    else {
      std::cerr << "Invalid variable name." << std::endl;
      return;
    }
  }

  /*Otherwise, the command is some binary executeable file or a script.
    We can use function execve() to execute.*/
  else {
    pid_t cpid, w;
    int wstatus;
    cpid = fork();
    if (cpid == -1) {
      perror("fork");
      exit(EXIT_FAILURE);
    }

    if (cpid == 0) {
      if (!searchCommand()) {
        std::cerr << "Command " << argvVector[0] << " not found" << std::endl;
        exit(EXIT_FAILURE);
      }

      char ** newargv = vectorToArray(argvVector);
      execve(newargv[0], newargv, environ);
      perror("execve");
      exit(EXIT_FAILURE);
    }
    else {
      do {
        w = waitpid(cpid, &wstatus, WUNTRACED | WCONTINUED);
        if (w == -1) {
          perror("waitpid");
          exit(EXIT_FAILURE);
        }
        if (WIFEXITED(wstatus)) {
          std::cout << "Program exited with status " << WEXITSTATUS(wstatus) << std::endl;
        }
        else if (WIFSIGNALED(wstatus)) {
          std::cout << "Program was killed by signal " << WTERMSIG(wstatus) << std::endl;
        }
      } while (!WIFEXITED(wstatus) && !WIFSIGNALED(wstatus));
    }
  }
}
