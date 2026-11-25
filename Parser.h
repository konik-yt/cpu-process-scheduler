#pragma once

#include <string>

#include "Process.h"

const int MAX_PROCESSES = 100;

// Loads processes from a text file into out[]. Each line holds four numbers
// separated by spaces: pid arrival burst priority
// Returns the number of processes loaded, or -1 if the file has a problem.
int loadProcessesFromFile(const std::string& path, Process out[], int maxCount);
