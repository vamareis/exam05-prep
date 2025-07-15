#include "bsq.h"

int main(int argc, char **argv)
{
    if (argc == 1)
        bsq(NULL);
    else
        for(int i = 1; i < argc; i++)
            bsq(argv[i]);
    return (0);
}
