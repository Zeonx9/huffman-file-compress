#ifndef HUFFMAN_FILES_PROGRESS_BAR_H

typedef struct progress_bar_ {
    char msg[100];
    int length;
    unsigned long ful;
    unsigned long cur;
    double progress;
} ProgressBar;

void createBar();

void updateBar(unsigned long cur);

extern ProgressBar bar;

#define HUFFMAN_FILES_PROGRESS_BAR_H

#endif //HUFFMAN_FILES_PROGRESS_BAR_H
