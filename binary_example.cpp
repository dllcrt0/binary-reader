#include "binary_reader.h"

void main() {
    unsigned char raw[21] = {
        0x39, 0x05, 0x00, 0x00, 0x76, 0x65, 0x72, 0x79, 0x20, 0x6E, 0x69, 0x63,
        0x65, 0x45, 0x00, 0x00, 0x00, 0x00, 0x00, 0xD2, 0x43
    };

    io::binary_reader reader(raw, sizeof(raw));
    printf("%i\n", reader.read_uint32());
    printf("%s\n", reader.read_string(8));
    printf("%i\n", reader.read_uint32());
    printf("%.0f\n", reader.read_float());
    reader.release();
}