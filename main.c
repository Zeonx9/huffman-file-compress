#include <stdio.h>
#include "encode.h"
#include "decode.h"

int main() {
    Encoder en = {"kisa.bmp", "output.aahf"};
    encode(&en);
    deleteEncoder(&en);
    Decoder dec = {"output.aahf", "out_kisa.bmp"};
    decode(&dec);
    deleteDecoder(&dec);
    return 0;
}
