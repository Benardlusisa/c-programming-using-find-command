#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#define MAX_DEPTH 100

// Function pointer type for file processing function
typedef void (*process_file_func)(const char*, const struct stat*, const int);

// Global variables for command-line options
bool option_s = false;
bool option_S = false;
bool option_f = false;
int option_s_val;
char* option_f_val;
int option_f_depth;
int current_depth;

// Function prototypes
void print_file_info(const char* file_path, const struct stat* file_stat, const int depth);
void print_file_info_size(const char* file_path, const struct stat* file_stat, const int depth);
void print_file_info_search(const char* file_path, const struct stat* file_stat, const int depth);
void traverse_directory(const char* dir_path, const int depth, process_file_func process_file);

