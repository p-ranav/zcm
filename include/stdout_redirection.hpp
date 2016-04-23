/*
 * Redirect stdout to file
 * Author: Pranav Srinivas Kumar
 * Date: 2016.04.23
 */
#ifndef STDOUT_REDIRECTION
#define STDOUT_REDIRECTION
#include <stdio.h>
#include <iostream>
#include <fcntl.h>
#include "unistd.h"

const int stdoutfd(dup(fileno(stdout)));

int redirect_stdout(const char* fname){
  fflush(stdout);
  int newstdout = open(fname, O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
  dup2(newstdout, fileno(stdout));
  close(newstdout);
}

int restore_stdout(){
  fflush(stdout);
  dup2(stdoutfd, fileno(stdout));
  return stdoutfd;
}
#endif
