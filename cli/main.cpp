#include <iostream>

char *readFile(const char *path) {
    FILE *file = fopen(path, "rb");
    if (file == nullptr) {
        fprintf(stderr, "Could not open file \"%s\".\n", path);
        exit(74);
    }

    fseek(file, 0L, SEEK_END);
    size_t fileSize = ftell(file);
    rewind(file);

    char *buffer = (char *) malloc(fileSize + 1);
    if (buffer == nullptr) {
        fprintf(stderr, "Not enough memory to read \"%s\".\n", path);
        exit(74);
    }

    size_t bytesRead = fread(buffer, sizeof(char), fileSize, file);
    if (bytesRead < fileSize) {
        fprintf(stderr, "Could not read file \"%s\".\n", path);
        exit(74);
    }

    buffer[bytesRead] = '\0';

    fclose(file);
    return buffer;
}

int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
