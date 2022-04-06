#include "console_interface.h"
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "encode.h"
#include "decode.h"

void runConsoleFileCompression() {
    printf("--------------------------------------------------------------------\n");
    printf("Enter a command (compress, decompress, exit) and follow instructions\n=>");
    char command[100] = "", inName[100] = "", outName[100] = "";
    scanf("%s", command);
    if (strcmp(command, "compress") == 0) {
        printf("specify path to file to compress\n=>");
        scanf("%s", inName);
        printf("specify directory and name (without extension, it (.aahf) will be added automatically) of output file\n=>");
        scanf("%s", outName);

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
               (double) dif / en.fileSize * 100, dif / 1024);
        deleteEncoder(&en);
        runConsoleFileCompression();
    }
    else if (strcmp(command, "decompress") == 0) {
        printf("specify path to compressed file (.aahf), name should not include this extension)\n=>");
        scanf("%s", inName);
        printf("specify directory and name, where you want decompressed file to be\n"
               "(also without extension, it will be recovered automatically)\n=>");
        scanf("%s", outName);

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

    else if (strcmp(command, "exit") == 0)
        return;
    else {
        printf("(!) your command can not be interpreted, only \"compress\", \"decompress\" and \"exit\" are possible!\n");
        printf("try again.\n");
        runConsoleFileCompression();
    }

}