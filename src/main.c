#include <stdio.h>
#include "raylib.h"
#include "chip8.h"

int main(int argc, char *argv[]) {
  if (argc != 2) {
    fprintf(stderr, "Error: No ROM file given\n");
    return 1;
  }
  char *filename = argv[1];

  FILE *rom = fopen(filename, "rb");
  if (!rom) {
    perror("Error");
    return 1;
  }

  // Init graphics

  // Init chip8
  Chip8 *chip8 = init_chip8(chip8);

  // Put ROM in memory at an offset of 0x200
  fread(&chip8->memory[0x200], 1, MEMORY_SIZE - 0x200, rom);
  fclose(rom);
  printf("ROM loaded and closed\n");

  // chip8 cycle
  
  return 0;
}
