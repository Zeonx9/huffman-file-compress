#include "progress_bar.h"
#include <stdio.h>

ProgressBar bar = {};
#define BAR_LEN 35

void createBar(){
    bar.length = BAR_LEN;
    bar.cur = 0; bar.progress = 0;
    printf("%s", bar.msg);
    for(int i = 0; i < bar.length; ++i)
        printf("%c", 176);
    printf(" %4.2lf%%", bar.progress);
}

void updateBar(unsigned long cur) {
    printf("\r");
    bar.cur = cur;
    bar.progress = ((double) bar.cur / bar.ful * 100);
    for (int i = 0; i < bar.length; ++i)
        printf("%c", i < (bar.length * bar.progress / 100) ? 178 : 176);
    printf(" %4.2lf%%", bar.progress);
}