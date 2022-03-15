#include <stdio.h>
#include "encode.h"

int main() {
    Encoder en = {"test.txt"};
    encode(&en);
    deleteEncoder(&en);
    return 0;
}
