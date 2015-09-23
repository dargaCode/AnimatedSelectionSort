#include <cs50.h>
#include <stdio.h>

// printf ANSI colors
#define COLOR_RED     "\x1b[31m"
#define COLOR_GREEN   "\x1b[32m"
#define COLOR_YELLOW  "\x1b[33m"
#define COLOR_BLUE    "\x1b[34m"
#define COLOR_MAGENTA "\x1b[35m"
#define COLOR_CYAN    "\x1b[36m"
#define COLOR_RESET   "\x1b[0m"

// prototypes
bool is_valid(int arg_count, string args[]);

int main(int argc, string argv[])
{
    if (!is_valid(argc, argv))
    {
        printf(COLOR_RED);
        printf("Usage: selectionsort <array length> \n");
        printf(COLOR_RESET);
        return 1;
    }
    
    // success
    return 0;
}

/*
 * Must be exactly 2 args, and second must be positive int
 */
bool is_valid(int arg_count, string args[])
{
    if (arg_count != 2)
    {
        return false;
    }
    
    int len = atoi(args[1]);
    if (len < 1)
    {
        return false;
    }
    return true;
}
