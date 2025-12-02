#ifndef PARSER_H
#define PARSER_H

#include "process.h"

process_t* parse_config(const char *filename, int *num_processes);

#endif
