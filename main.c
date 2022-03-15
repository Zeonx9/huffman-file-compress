#include <stdio.h>
#include "encode.h"

int main() {
    Encoder en = {"test.txt", "output.ahf"};
    encode(&en);
    deleteEncoder(&en);
    return 0;
}
