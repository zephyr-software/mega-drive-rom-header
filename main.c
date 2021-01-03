#include <stdio.h>

void readFile(char fileName[])
{
    printf("read file: %s\n", fileName);

    FILE *file;
    file = fopen(fileName, "rb");
    if (file == NULL)
    {
        printf("file is not found - error!\n");
        return;
    }

    printf("offset 0x100 - rom header\n");
    fseek(file, 0x100, SEEK_SET);

    char systemType[16];
    fread(&systemType, 16, 1, file);
    systemType[16] = '\0';

    printf("system type: %s\n", systemType);

    fclose(file);
}

int main(int argc, char **argv)
{
    printf("mega drive rom header\n");

    int i;
    for(i = 0; i < argc; i++) {
        printf("argv[%d]: %s\n", i, argv[i]);
    }

    readFile(argv[1]);

    return 0;
}
