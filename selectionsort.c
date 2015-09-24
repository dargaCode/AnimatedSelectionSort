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
#define MAX_DELAY_DUR 1000
#define MAX_ELEMENT_FACTOR 5

static int delay_duration = 0;

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
        printf("Usage: selectionsort <size 1-%i> ", MAX_ARRAY_LEN);
        printf("(delay in ms 1-%i) \n", MAX_DELAY_DUR);
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
    if (arg_count < 2 || arg_count > 3)
    {
        return false;
    }

    int len = atoi(args[1]);
    if (len < 1 || len > MAX_ARRAY_LEN)
    {
        return false;
    }

    if (arg_count == 3)
    {
        int delay = atoi(args[2]);

        if (delay < 1 || delay > 1000)
        {
            return false;
        }
        else
        {
            printf("%i \n", delay);
            // assign to global variable
            delay_duration = delay;
        }
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
    // include one extra loop to draw ] on final element
    for (int i = 0; i <= len; i++)
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
        // print the actual element, but leave off the extra
        if (i < len)
        {
            printf("%i", data[i]);
        }
        printf(COLOR_RESET);
    }
    printf("\n");
    delay_ms(delay_duration);
 }

 /*
  * Sort the array
  */
void sort_array(int data[], int len)
{
    // outer loops
    for (int i = 0; i < len; i++)
    {
        int done = i;

        // show starting state for this loop
        render_array(data, len, done, -10, -10);

        // last item will always be sorted by default
        if (done == len - 1)
        {
            break;
        }

        // preset smallest
        int lowest = done;

        // inner loop
        for (int j = done; j < len; j++)
        {
            // new lowest
            if (data[j] < data[lowest])
            {
                lowest = j;
            }
            render_array(data, len, done, lowest, j);
        }
        // swap the first unsorted element with lowest
        int temp = data[done];
        data[done] = data[lowest];
        data[lowest] = temp;
    }
    // show one last render of all done
    render_array(data, len, len, -10, -10);
}

