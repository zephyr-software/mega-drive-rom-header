#include <stdio.h>

void readFile(char fileName[])
{
    FILE *file;
    file = fopen(fileName, "rb");
    if (file == NULL)
    {
        printf("file is not found - error!\n");
        return;
    }

    fseek(file, 0x100, SEEK_SET);

    unsigned char systemType[16];
    fread(systemType, sizeof(systemType), 1, file);

    unsigned char copyrightAndReleaseDate[16];
    fread(copyrightAndReleaseDate, sizeof(copyrightAndReleaseDate), 1, file);

    unsigned char gameTitleDomestic[48];
    fread(gameTitleDomestic, sizeof(gameTitleDomestic), 1, file);

    unsigned char gameTitleOverseas[48];
    fread(gameTitleOverseas, sizeof(gameTitleOverseas), 1, file);

    unsigned char serialNumber[14];
    fread(serialNumber, sizeof(serialNumber), 1, file);

    unsigned char romChecksum[2];
    fread(romChecksum, sizeof(romChecksum), 1, file);

    unsigned char deviceSupport[16];
    fread(deviceSupport, sizeof(deviceSupport), 1, file);

    unsigned char romAddressRange[8];
    fread(romAddressRange, sizeof(romAddressRange), 1, file);

    unsigned char ramAddressRange[8];
    fread(ramAddressRange, sizeof(ramAddressRange), 1, file);

    unsigned char extraMemory[12];
    fread(extraMemory, sizeof(extraMemory), 1, file);

    unsigned char modemSupport[12];
    fread(modemSupport, sizeof(modemSupport), 1, file);

    unsigned char reservedFirst[40];
    fread(reservedFirst, sizeof(reservedFirst), 1, file);

    unsigned char regionSupport[3];
    fread(regionSupport, sizeof(regionSupport), 1, file);

    unsigned char reservedSecond[13];
    fread(reservedSecond, sizeof(reservedSecond), 1, file);

    fclose(file);

    printf("system type               : %.*s\n", (int) sizeof(systemType), systemType);
    printf("copyright and release date: %.*s\n", (int) sizeof(copyrightAndReleaseDate), copyrightAndReleaseDate);
    printf("game title (domestic)     : %.*s\n", (int) sizeof(gameTitleDomestic), gameTitleDomestic);
    printf("game title (overseas)     : %.*s\n", (int) sizeof(gameTitleOverseas), gameTitleOverseas);
    printf("serial number             : %.*s\n", (int) sizeof(serialNumber), serialNumber);
    printf("rom checksum              : %#X %#X\n", romChecksum[0], romChecksum[1]);
    printf("device support            : %.*s\n", (int) sizeof(deviceSupport), deviceSupport);
    printf("rom address range         : %.*s\n", (int) sizeof(romAddressRange), romAddressRange);
    printf("ram address range         : %.*s\n", (int) sizeof(ramAddressRange), ramAddressRange);
    printf("extra memory              : %.*s\n", (int) sizeof(extraMemory), extraMemory);
    printf("modem support             : %.*s\n", (int) sizeof(modemSupport), modemSupport);
    printf("reserved                  : %.*s\n", (int) sizeof(reservedFirst), reservedFirst);
    printf("region support            : %.*s\n", (int) sizeof(regionSupport), regionSupport);
    printf("reserved                  : %.*s\n", (int) sizeof(reservedSecond), reservedSecond);
}

int main(int argc, char **argv)
{
    printf("mega drive rom header\n\n");

    readFile(argv[1]);

    return 0;
}
