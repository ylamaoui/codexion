#ifndef CODEXION_H
# define CODEXION_H

# include <unistd.h>
# include <stdlib.h>
# include <stddef.h>
# include <limits.h>
# include <stdio.h>
#include <string.h>


typedef struct rule
{
    int     coders;
    int     burnout;
    int     compile;
    int     debug;
    int     refactor;
    int     c_required;
    int     cooldown;
    int     time;
    int     done;
    char    *scheduler;
}       t_rule;

#endif