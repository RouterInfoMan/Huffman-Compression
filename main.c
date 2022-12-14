#include <stdio.h>
#include <string.h>

void HuffmannCompress(const char *fileName) {

};
void HuffmannDecompress(const char *fileName) {

};

int main(int argc, char **argv) {
    if (argc != 3) {
        printf("Wrong number of arguments: %d\n", argc);
        
        return -1;
    }
    if (strcmp(argv[1], "-d") == 0) {
        HuffmannDecompress(argv[2]);
        return 0;
    }
    if (strcmp(argv[1], "-c") == 0) {
        HuffmannCompress(argv[2]);
        return 0;
    }
    printf("Unknown argument: \"%s\"\n", argv[1]);
    return 0;
}