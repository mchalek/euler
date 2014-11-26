#include <stdio.h>

#define MAX_POS 8 // position of final operation
#define VALID_OPS 13

typedef enum _op { 
    open_
    plus, minus, times, divide, // all can precede an open-paren or follow a close-paren
    plus_open, minus_open, times_open, divide_open,
    concat,
    close_plus, close_minus, close_times, close_divide
} op_t;

void enumerate(int pos, int open_paren_count, int items[]) 
{
    if(pos == 8) {
        print_expr(items);
        return;
    }

    int i;
    for(i = 0; i < 
}

int main()
{
    return 0;
}
