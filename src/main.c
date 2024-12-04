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

  // Init graphics - 20x scale
  InitWindow(1280, 640, "Chip8");

  // Init chip8
  Chip8 *chip8 = init_chip8(chip8);

  // Put ROM in memory at an offset of 0x200
  fread(&chip8->memory[0x200], 1, MEMORY_SIZE - 0x200, rom);
  fclose(rom);
  printf("ROM loaded and closed\n");

  while (!WindowShouldClose()) {
    // chip8 cycle
    uint16_t opcode = (chip8->memory[chip8->pc] << 8) | chip8->memory[chip8->pc + 1];
    printf("0x%04X\n", opcode);
    chip8->pc += 2;

    BeginDrawing();
    // Draw screen
    
    ClearBackground(RAYWHITE);

    EndDrawing();
  }
  CloseWindow();
  return 0;
}
