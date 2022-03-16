#include <stdio.h>
#include "encode.h"
#include "decode.h"


int main() {
    Encoder en = {"text.txt", "output.ahf"};
    encode(&en);
    deleteEncoder(&en);
    Decoder dec = {"output.ahf"};
    rebuildCounter(&dec);
    return 0;
}
