/*!
  * \file Options.hpp
  * \brief This file contain headers functions for options and usage program.
  * \author Jeremy ZYRA
  * \version 1.0
*/
#ifndef OPTIONS_H
#define OPTIONS_H

#include <iostream>
#include <cstring>
#include <cstdlib>

using namespace std;

bool get_options(const int argc, const char* argv[], bool &round);
void print_help(const char *name);

#endif
