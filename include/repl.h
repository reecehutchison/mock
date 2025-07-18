#ifndef REPL_H
#define REPL_H

#include <stdbool.h>


void say_hi(void);
void start_repl(void);
char* parse_repl_input(void);
bool is_command_complete(const char* command_buffer);
bool is_buffer_len_exceeded(const char* command_buffer);

#endif