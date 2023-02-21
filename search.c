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

// Main function
int main(int argc, char** argv) {
    char* dir_path;
    int opt;

    // Parse command-line options
    while ((opt = getopt(argc, argv, "s:Sf:")) != -1) {
        switch (opt) {
            case 's':
                option_s = true;
                option_s_val = atoi(optarg);
                break;
            case 'S':
                option_S = true;
                break;
            case 'f':
                option_f = true;
                option_f_val = optarg;
                option_f_depth = atoi(argv[optind]);
                break;
            default:
                printf("Invalid option: %c\n", opt);
                exit(EXIT_FAILURE);
        }
    }

    // Get directory path from command-line argument or use current directory
    if (optind < argc) {
        dir_path = argv[optind];
    } else {
        dir_path = ".";
    }

    // Call traverse_directory function with appropriate process_file function based on options
    if (option_S && !option_s && !option_f) {
        traverse_directory(dir_path, 0, print_file_info_size);
    } else if (option_f && !option_S && !option_s) {
        traverse_directory(dir_path, 0, print_file_info_search);
    } else if (option_S && option_s && !option_f) {
        traverse_directory(dir_path, 0, print_file_info_size);
    } else if (option_S && !option_s && option_f) {
        traverse_directory(dir_path, 0, print_file_info_search);
    } else if (option_s && option_f && !option_S) {
        traverse_directory(dir_path, 0, print_file_info_search);
    } else if (option_S && option_s && option_f) {
        traverse_directory(dir_path, 0, print_file_info_search);
    } else {
        traverse_directory(dir_path, 0, print_file_info);
    }

    return 0;
}

// Helper function to print file information without options
void print_file_info(const char* file_path, const struct stat* file_stat, const int depth) {
    for (int i = 0; i < depth; i++) {
        printf("\t");
    }

    if (S_ISLNK(file_stat->st_mode)) {
        char link_dest[1024];
        ssize_t len = readlink(file_path, link_dest, sizeof(link_dest) - 1);
        if (len != -1) {
            link_dest[len] = '\0';
           printf("%s (%s)", file_path, link_dest);

            }
        }
    }
      // Helper function to print file information with option -s
    void print_file_info_size(const char* file_path, const struct stat* file_stat, const int depth) {
    if (S_ISREG(file_stat->st_mode)) {
    if (file_stat->st_size >= option_s_val) {
    for (int i = 0; i < depth; i++) {
    printf("\t");
    }
    printf("%s\n", file_path);
    }
    }
    }

    // Helper function to print file information with option -f
    void print_file_info_search(const char* file_path, const struct stat* file_stat, const int depth) {
    if (depth <= option_f_depth) {
    if (S_ISREG(file_stat->st_mode)) {
    char* file_name = strrchr(file_path, '/');
    if (file_name != NULL) {
    file_name++;
    } else {
    file_name = (char*) file_path;
    }
    if (strcmp(file_name, option_f_val) == 0) {
    for (int i = 0; i < depth; i++) {
    printf("\t");
    }
    printf("%s\n", file_path);
    }
    }
    }
    }

    // Helper function to traverse a directory recursively and call the given process_file function on each file
    void traverse_directory(const char* dir_path, const int depth, process_file_func process_file) {
    DIR* dir = opendir(dir_path);
    if (dir == NULL) {
    printf("Cannot open directory: %s\n", dir_path);
    exit(EXIT_FAILURE);
    }
    struct dirent* dir_entry;
while ((dir_entry = readdir(dir)) != NULL) {
    char file_path[1024];
    snprintf(file_path, sizeof(file_path), "%s/%s", dir_path, dir_entry->d_name);

    struct stat file_stat;
    if (lstat(file_path, &file_stat) == -1) {
        printf("Cannot get file information: %s\n", file_path);
        continue;
    }

    if (S_ISDIR(file_stat.st_mode)) {
        if (strcmp(dir_entry->d_name, ".") != 0 && strcmp(dir_entry->d_name, "..") != 0) {
            traverse_directory(file_path, depth + 1, process_file);
        }
    } else {
        process_file(file_path, &file_stat, depth);
    }
}

closedir(dir);
}

