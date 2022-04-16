#include "console_interface.h"
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "encode.h"
#include "decode.h"

void scanNameOrSkip(char * dest) {
    do *dest = (char) getchar();
    while (*dest++ != '\n');
    dest[-1] = 0;
}

void runConsoleFileCompression() {
    printf("--------------------------------------------------------------------\n");
    printf("Enter a command (compress / -c, decompress / -d, exit / -e) and follow instructions\n=> ");
    char command[100] = "", inName[100] = "", outName[100] = "";
    scanf("%s", command);
    if (strcmp(command, "compress") == 0 || strcmp(command, "-c") == 0) {
        printf("specify path to file to compress\n=> ");
        scanf("%s", inName);
        fflush(stdin);
        printf("specify directory and name of output file\n"
               "(without extension, it (.aahf) will be added automatically)\n"
               "or press enter to give compressed file same name as input\n=> ");
        scanNameOrSkip(outName);
        if (!outName[0]) {
            strcpy(outName, inName);
            int i = (int) strlen(outName) - 1;
            while(outName[i] != '.') --i;
            outName[i] = 0;
        }
        fflush(stdin);

        Encoder en = {};
        strcpy(en.fileName, inName);
        strcpy(en.outName, outName);

        clock_t begin = clock();
            encode(&en);
        clock_t end = clock();
        printf("file has been compressed, in %.3lf sec.\n", (double) (end - begin) / CLOCKS_PER_SEC );
        signed long long dif = en.fileSize;
        dif -= en.bufPos;
        printf("total compression is about %.2lf%% (%ld Kb)\n",
               (double) dif / en.fileSize * 100, (long) dif / 1024);
        deleteEncoder(&en);
        runConsoleFileCompression();
    }
    else if (strcmp(command, "decompress") == 0 || strcmp(command, "-d") == 0) {
        printf("specify path to compressed file (.aahf), name should not include this extension)\n=> ");
        scanf("%s", inName);
        fflush(stdin);
        printf("specify directory and name, where you want decompressed file to be\n"
               "(also without extension, it will be recovered automatically)\n"
               "or skip and output file will have the same name as compressed\n=> ");
        scanNameOrSkip(outName);
        if (!outName[0]) strcpy(outName, inName);
        fflush(stdin);

        Decoder dec = {};
        strcpy(dec.fileName, inName);
        strcpy(dec.outName, outName);

        clock_t begin = clock();
            decode(&dec);
        clock_t end = clock();
        printf("File has been decompressed, in %.3lf sec.\n", (double)(end - begin) / CLOCKS_PER_SEC );
        deleteDecoder(&dec);
        runConsoleFileCompression();
    }

    else if (strcmp(command, "exit") == 0 || strcmp(command, "-e") == 0)
        return;
    else {
        printf("(!) your command can not be interpreted, only \"compress\", \"decompress\" and \"exit\" are possible!\n");
        printf("try again.\n");
        runConsoleFileCompression();
    }

}