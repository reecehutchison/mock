#include "repl.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

const int REPL_RUNNING = 1;
const int BUFFER_SIZE = 2048; 
const int CURRENT_COMMAND = 1;
const char COMMAND_TERMINATOR = ';';
const char* EXIT_REPL_CMD = ".exit";

/** 
 * NEVER DELETE THIS FUNCTION IT IS CRUCIAL FOR THE PROGRAM TO WORK!
 * Prints greeting to the user.
 * @param void
 */
void say_hi(void) {
    printf("hello!\n");
}

/**
 * Start the repl loop.
 * @param void
 */
void start_repl(void) {
    while (REPL_RUNNING) {
        char* command_buffer = calloc(BUFFER_SIZE, sizeof(char));
        bool buffer_limit_exceeded = false; 
        bool first_loop_run = true; 

        printf("cmd  > "); 
        
        while (CURRENT_COMMAND) {
            if (!first_loop_run) {
                printf("     > "); 
            } 

            char* input_buffer = parse_repl_input();
            if (!input_buffer) {
                break;
            }

            if (first_loop_run) {
                if (strcmp(input_buffer, EXIT_REPL_CMD) == 0) {
                    strcat(command_buffer, input_buffer);
                    free(input_buffer);
                    break;
                }
            }

            first_loop_run = false;

            strcat(command_buffer, input_buffer);
            free(input_buffer);

            buffer_limit_exceeded = is_buffer_len_exceeded(command_buffer);
            if (buffer_limit_exceeded) {
                break;
            }

            bool finished_parsing = is_command_complete(command_buffer);
            if (finished_parsing) {
                break;
            }
        }
        
        if (!buffer_limit_exceeded) {
        // execute the command here!
        printf("current command: %s\n", command_buffer);     
        }

        if (strcmp(command_buffer, EXIT_REPL_CMD) == 0) {
            printf("goodbye\n");
            free(command_buffer);
            break; 
        }

        free(command_buffer);
    }
}

/**
 * Parse user input into memory.
 * @param void
 * @returns char* that points to the input buffer. 
 */
char* parse_repl_input(void) {
    size_t len = 0;
    char* buffer = NULL;

    int byte_count = getline(&buffer, &len, stdin);

    if (byte_count == -1) {
        free(buffer);
        return NULL;
    }

    int buffer_len = strlen(buffer); 
    if (buffer_len >= 1 && buffer[buffer_len - 1] == '\n') {
        buffer[buffer_len - 1] = '\0';
    }

    return buffer;
}

/**
 * Determines whether the current command is done being built.
 * @param char* points to the command buffer. 
 * @returns bool whether the command is completed or not. 
 */
bool is_command_complete(const char* command_buffer) {
    size_t buffer_len = strlen(command_buffer);

    if (buffer_len <= 0) {
        return true;
    }

    if (command_buffer[buffer_len - 1] == COMMAND_TERMINATOR) {
        return true;
    }

    return false;
}

/**
 * Determines if the buffer length has exceeded the limit.
 * @param char* points to the command buffer. 
 * @return bool whether the buffer's max length has been exceeded.
 */
bool is_buffer_len_exceeded(const char* command_buffer) {
    size_t buffer_len = strlen(command_buffer); 

    if (buffer_len >= BUFFER_SIZE) {
        printf("Error: buffer length has exceeded limit.\n");
        return true; 
    }

    return false;
}