#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

/* Function prototypes */
void print_prompt(void);
char *get_command(void);
void execute_command(char *command);
void wait_for_child(void);

#endif
