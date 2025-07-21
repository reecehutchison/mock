#include "repl.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define REPL_RUNNING true
#define BUFFER_SIZE 2048 
#define CURRENT_COMMAND true
#define COMMAND_TERMINATOR ';'
#define EXIT_REPL_CMD ".exit"
#define GET_LINE_ERROR -1

/** 
 *                 .
 *                ":"
 *              ___:____     |"\/"|
 *            ,'        `.    \  /
 *            |  O        \___/  |
 * ~^~^~^~^~^~^~^~^~^~^~^~^~^~^~^~^~^~^~^~^~^~^~^~^~^~^~^~^~^~
 * "Whale hello there!""
 */
void say_hi(void) {
    printf("hello there!\n");
}

/**
 * Start the repl loop. This loop will build commands, until terminator is
 * reached. 
 */
void start_repl(void) {
    while (REPL_RUNNING) {
        char* command_buffer = calloc(BUFFER_SIZE, sizeof(char));
        if (!command_buffer) {
            printf("Error: failed to allocate memory for command buffer.");
            exit(EXIT_FAILURE);
        }

        bool buffer_limit_exceeded = false; 
        bool first_loop_run = true; 

        printf("cmd  > "); 
        
        while (CURRENT_COMMAND) {
            if (!first_loop_run) {
                printf("     > "); 
            } 

            char* input_buffer = read_repl_input();
            if (!input_buffer) {
                break;
            }

            if (first_loop_run) {
                if (strcmp(input_buffer, EXIT_REPL_CMD) == 0) {
                    concatStrAndFree(command_buffer, input_buffer);
                    break;
                }
            }

            first_loop_run = false;

            concatStrAndFree(command_buffer, input_buffer);

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
 * Read user input into memory.
 * @return char* that points to the input buffer. Returns Null on an error. 
 */
char* read_repl_input(void) {
    size_t len = 0;
    char* buffer = NULL;

    int byte_count = getline(&buffer, &len, stdin);

    if (byte_count == GET_LINE_ERROR) {
        free(buffer);
        return NULL;
    }

    int buffer_len = strlen(buffer); 
    if (buffer_len > 0 && buffer[buffer_len - 1] == '\n') {
        buffer[buffer_len - 1] = '\0';
    }

    return buffer;
}

/**
 * Determines whether the current command is done being built.
 * @param char* command_buffer points to the command buffer. 
 * @return bool whether the command is completed or not. 
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
 * @param char* command_buffer points to the command buffer. 
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

/**
 * Concatenate 2 char* and then free the second one.
 * @param char* dest is the char* that will contain the new string.
 * @param char* source will be concatenated to dest, then freed from memory. 
 * @return void
 */
void concatStrAndFree(char* dest, char* source) {
    strcat(dest, source);
    free(source);
}
