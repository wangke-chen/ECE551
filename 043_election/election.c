#include "election.h"
//include any other headers you need here...
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

state_t parseLine(const char * line) {
  //STEP 1: write me
  int n = 0;
  int j = 0;
  char * s[3] = {NULL}; /*Store the three part of the inpue line*/
  char t[300] = "0";    /*Copy the input line for later use*/
  char * d = ":";
  state_t parse;

  /*Check if line points to NULL*/
  if (line == NULL) {
    perror("The input line cannot be NULL.\n");
    exit(EXIT_FAILURE);
  }

  /*check if the input string contains the proper three parts separated by ':'*/
  while (line[n] != '\0') {
    if (line[n] == ':') {
      j++;
    }
    n++;
  }
  if (j != 2) {
    perror("Improper format. Proper format: Name:population:electoral votes.\n");
    exit(EXIT_FAILURE);
  }

  /*Copy line into a temporary string, separate the string into three parts*/
  strncpy(t, line, n);
  s[0] = strtok(t, d);
  int i = 0;
  while (s[i] != NULL) {
    i++;
    s[i] = strtok(NULL, d);
  }

  /*Check if any of required three parts is empty*/
  for (j = 0; j < 3; j++) {
    if (s[j] == NULL) {
      perror("Either part of the input line cannot be empty\n");
      exit(EXIT_FAILURE);
    }
  }

  /*Check if the length of name is too long*/
  if (strlen(s[0]) > 63) {
    perror("The length of name cannot be longer than 63.\n");
    exit(EXIT_FAILURE);
  }

  /*Put the three parts into the corresponding fields of the strut parse*/
  strcpy(parse.name, s[0]);
  parse.population = atoi(s[1]);
  parse.electoralVotes = atoi(s[2]);

  /*check if the population and electoralVotes contain non-zero numbers*/
  if ((parse.population == 0) || (parse.electoralVotes == 0)) {
    perror("The population and electoralVotes should be non-zero numbers.\n");
    exit(EXIT_FAILURE);
  }

  return parse;
}

unsigned int countElectoralVotes(state_t * stateData, uint64_t * voteCounts, size_t nStates) {
  //STEP 2: write me
  size_t i = 0;
  unsigned int count = 0;

  /*For some candidate, check the votes percent of each state, count the total electoral votes*/
  for (i = 0; i < nStates; i++) {
    if (((double)voteCounts[i] / stateData[i].population) > 0.5) {
      count = count + stateData[i].electoralVotes;
    }
  }
  return count;
}

void printRecounts(state_t * stateData, uint64_t * voteCounts, size_t nStates) {
  //STEP 3: write me
  double p = 0; /*p represent the percentage of the vote*/

  /*Check the percentage of the vote of each state, determine the state(s) that need recounts*/
  for (size_t i = 0; i < nStates; i++) {
    p = (double)voteCounts[i] / stateData[i].population;
    if ((p >= 0.495) && (p <= 0.505)) {
      printf("%s requires a recount (Candidate A has %.2f%% of the vote)\n",
             stateData[i].name,
             100 * p);
    }
  }
  return;
}

void printLargestWin(state_t * stateData, uint64_t * voteCounts, size_t nStates) {
  //STEP 4: write me
  size_t index = 0;
  double max_p;
  double p = 0;

  /*Find out the maximum percentage of votes among all the states*/
  max_p = (double)voteCounts[0] / stateData[0].population;
  for (size_t i = 1; i < nStates; i++) {
    p = (double)voteCounts[i] / stateData[i].population;
    if (p > max_p) {
      max_p = p;
      index = i;
    }
  }
  printf("Candidate A won %s with %.2f%% of the vote\n", stateData[index].name, 100 * max_p);

  return;
}
