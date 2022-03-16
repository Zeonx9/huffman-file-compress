#include <stdio.h>
#include "encode.h"
#include "decode.h"



int main() {
    Encoder en = {"test.txt", "output.ahf"};
    encode(&en);
    deleteEncoder(&en);
    Decoder dec = {"output.ahf"};
    decode(&dec);
    return 0;
}
