#include <cs50.h>
#include <stdio.h>
#include <time.h>

// printf ANSI colors
#define COLOR_RED     "\x1b[31m"
#define COLOR_GREEN   "\x1b[32m"
#define COLOR_YELLOW  "\x1b[33m"
#define COLOR_BLUE    "\x1b[34m"
#define COLOR_MAGENTA "\x1b[35m"
#define COLOR_CYAN    "\x1b[36m"
#define COLOR_RESET   "\x1b[0m"

// constant
#define MAX_ARRAY_LEN 200
#define MAX_ELEMENT_FACTOR 5

// prototypes
bool is_valid(int arg_count, string args[]);
void randomize_array(int data[], int len);
void render_array(int data[], int len, int done, int low, int active);
void delay_ms(int milliseconds);
void sort_array(int data[], int len);

int main(int argc, string argv[])
{
    // failure
    if (!is_valid(argc, argv))
    {
        printf(COLOR_RED);
        printf("Usage: selectionsort <array size up to %i> \n", MAX_ARRAY_LEN);
        printf(COLOR_RESET);
        return 1;
    }

    int len = atoi(argv[1]);
    int data[len];
    randomize_array(data, len);
    // remove buffer from stdout (enables printf to display
    // partial lines without flushing the buffer.
    setbuf(stdout, NULL);
 
    sort_array(data, len);

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
    if (len < 1 || len > MAX_ARRAY_LEN)
    {
        return false;
    }
    return true;
}

/*
 * Fill with randomized data
 */
 void randomize_array(int data[], int len)
 {
    // random seed
    srand(time(NULL));

    for (int i = 0; i < len; i++)
    {
        // using higher limit than len reduces duplicates
        data[i] = rand() % (len * MAX_ELEMENT_FACTOR);
    }
 }

 /*
  * Create a delay for a given number of milliseconds
  */
void delay_ms(int milliseconds)
{
    //tick vars
    clock_t start = clock();
    clock_t now = clock();

    // convert milliseconds to ticks
    long delay = milliseconds * (CLOCKS_PER_SEC / 1000);

    while (now < start + delay)
    {
        now = clock();
    }
}

 /*
  * Render the information to the screen
  */
 void render_array(int data[], int len, int done, int low, int active)
 {
    for (int i = 0; i < len; i++)
    {
        // prepend element with blank space or bracket
        if (i == active)
        {
            printf(COLOR_YELLOW);
            printf("[");
            printf(COLOR_RESET);
        }
        else if (i == active + 1)
        {
            printf(COLOR_YELLOW);
            printf("]");
            printf(COLOR_RESET);
        }
        else
        {
            printf(" ");
        }

        // establish element color
        if (i < done)
        {
            printf(COLOR_CYAN);
        }
        else if (i == low)
        {
            printf(COLOR_MAGENTA);
        }
        // print the actual element
        printf("%i", data[i]);
        printf(COLOR_RESET);
    }
    printf("\n");
    delay_ms(500);
 }

 /*
  * Sort the array
  */
void sort_array(int data[], int len)
{
    for (int i = 0; i < len; i++)
    {
        int done = i;

        // show starting state for this loop
        render_array(data, len, done, -10, -10);

        for (int j = done; j < len; j++)
        {
            render_array(data, len, done, -10, j);
        }
    }
    // show one last render of all green
    render_array(data, len, len, -10, -10);
}

