#include <stdio.h>

#define ROM_HEADER_OFFSET 256L
#define ROM_HEADER_SIZE   256
#define ROM_FILE_NAME     "rom.bin"

typedef struct {
    char system_type[17];
    char copyright_and_release_date[17];
    char domestic_game_title[49];
    char overseas_game_title[49];
    char serial_number[15];
    unsigned short checksum;
    char device_support[17];
    unsigned long rom_start_address;
    unsigned long rom_end_address;
    unsigned long ram_start_address;
    unsigned long ram_end_address;
} MegaDriveRomHeader;

static MegaDriveRomHeader rom_header;

int read_rom_header(const char *file_name)
{
    FILE *file_pointer;
    size_t byte_count;
    unsigned char checksum_buffer[2];
    unsigned char address_buffer[4];

    file_pointer = fopen(file_name, "rb");
    if (file_pointer == NULL) {
        printf("error: could not open file: %s\n", file_name);

        return 1;
    }

    if (fseek(file_pointer, ROM_HEADER_OFFSET, SEEK_SET) != 0) {
        printf("error: fseek failed (offset %ld)\n", (long)ROM_HEADER_OFFSET);
        fclose(file_pointer);

        return 1;
    }

    byte_count = fread(rom_header.system_type, 1, 16, file_pointer);
    if (byte_count != 16) {
        printf("error: failed to read system type (read %lu bytes)\n",
               (unsigned long)byte_count);
        fclose(file_pointer);

        return 1;
    }
    rom_header.system_type[16] = '\0';

    byte_count =
        fread(rom_header.copyright_and_release_date, 1, 16, file_pointer);
    if (byte_count != 16) {
        printf
            ("error: failed to read copyright and release date (read %lu bytes)\n",
             (unsigned long)byte_count);
        fclose(file_pointer);

        return 1;
    }
    rom_header.copyright_and_release_date[16] = '\0';

    byte_count = fread(rom_header.domestic_game_title, 1, 48, file_pointer);
    if (byte_count != 48) {
        printf("error: failed to read domestic game title (read %lu bytes)\n",
               (unsigned long)byte_count);
        fclose(file_pointer);

        return 1;
    }
    rom_header.domestic_game_title[49] = '\0';

    byte_count = fread(rom_header.overseas_game_title, 1, 48, file_pointer);
    if (byte_count != 48) {
        printf("error: failed to read overseas game title (read %lu bytes)\n",
               (unsigned long)byte_count);
        fclose(file_pointer);

        return 1;
    }
    rom_header.overseas_game_title[49] = '\0';

    byte_count = fread(rom_header.serial_number, 1, 14, file_pointer);
    if (byte_count != 14) {
        printf("error: failed to read serial number (read %lu bytes)\n",
               (unsigned long)byte_count);
        fclose(file_pointer);

        return 1;
    }
    rom_header.serial_number[15] = '\0';

    byte_count = fread(checksum_buffer, 1, 2, file_pointer);
    if (byte_count != 2) {
        printf("error: failed to read checksum (read %lu bytes)\n",
               (unsigned long)byte_count);
        fclose(file_pointer);

        return 1;
    }
    rom_header.checksum = ((unsigned short)checksum_buffer[0] << 8)
        | (unsigned short)checksum_buffer[1];

    byte_count = fread(rom_header.device_support, 1, 16, file_pointer);
    if (byte_count != 16) {
        printf("error: failed to read device support (read %lu bytes)\n",
               (unsigned long)byte_count);
        fclose(file_pointer);

        return 1;
    }
    rom_header.device_support[17] = '\0';

    byte_count = fread(address_buffer, 1, 4, file_pointer);
    if (byte_count != 4) {
        printf("error: failed to read rom start address (read %lu bytes)\n",
               (unsigned long)byte_count);
        fclose(file_pointer);

        return 1;
    }
    rom_header.rom_start_address =
        ((unsigned long)address_buffer[0] << 24) |
        ((unsigned long)address_buffer[1] << 16) |
        ((unsigned long)address_buffer[2] << 8) |
        ((unsigned long)address_buffer[3]);

    byte_count = fread(address_buffer, 1, 4, file_pointer);
    if (byte_count != 4) {
        printf("error: failed to read rom end address (read %lu bytes)\n",
               (unsigned long)byte_count);
        fclose(file_pointer);

        return 1;
    }
    rom_header.rom_end_address =
        ((unsigned long)address_buffer[0] << 24) |
        ((unsigned long)address_buffer[1] << 16) |
        ((unsigned long)address_buffer[2] << 8) |
        ((unsigned long)address_buffer[3]);

    byte_count = fread(address_buffer, 1, 4, file_pointer);
    if (byte_count != 4) {
        printf("error: failed to read ram start address (read %lu bytes)\n",
               (unsigned long)byte_count);
        fclose(file_pointer);

        return 1;
    }
    rom_header.ram_start_address =
        ((unsigned long)address_buffer[0] << 24) |
        ((unsigned long)address_buffer[1] << 16) |
        ((unsigned long)address_buffer[2] << 8) |
        ((unsigned long)address_buffer[3]);

    byte_count = fread(address_buffer, 1, 4, file_pointer);
    if (byte_count != 4) {
        printf("error: failed to read ram end address (read %lu bytes)\n",
               (unsigned long)byte_count);
        fclose(file_pointer);

        return 1;
    }
    rom_header.ram_end_address =
        ((unsigned long)address_buffer[0] << 24) |
        ((unsigned long)address_buffer[1] << 16) |
        ((unsigned long)address_buffer[2] << 8) |
        ((unsigned long)address_buffer[3]);

    fclose(file_pointer);

    return 0;
}

void print_rom_header()
{
    printf("system type               : [%s]\n", rom_header.system_type);
    printf("copyright and release date: [%s]\n",
           rom_header.copyright_and_release_date);
    printf("domestic game title       : [%s]\n",
           rom_header.domestic_game_title);
    printf("overseas game title       : [%s]\n",
           rom_header.overseas_game_title);
    printf("serial number             : [%s]\n", rom_header.serial_number);
    printf("checksum                  : [%04X]\n", rom_header.checksum);
    printf("device support            : [%s]\n", rom_header.device_support);
    printf("rom start address         : [%08lX]\n",
           rom_header.rom_start_address);
    printf("rom end address           : [%08lX]\n", rom_header.rom_end_address);
    printf("ram start address         : [%08lX]\n",
           rom_header.ram_start_address);
    printf("ram end address           : [%08lX]\n", rom_header.ram_end_address);
}

int main(void)
{
    int result;

    printf("mega drive rom header\n");

    result = read_rom_header(ROM_FILE_NAME);
    if (result == 0) {
        print_rom_header();
    }
    else {
        printf("error: result: %d\n", result);
    }

    return result;
}
