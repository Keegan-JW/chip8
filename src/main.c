#include <stdio.h>
#include "raylib.h"
#include "chip8.h"

void drawVideoBuffer(Chip8 *chip8) {
  for (int row = 0; row < VIDEO_W; row++) {
    for (int col = 0; col < VIDEO_H; col++) {
      if (chip8->video[row][col]) {
        DrawRectangle(row * 20, col * 20, 20, 20, WHITE);
      }
    }
  }
}

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
    BeginDrawing();
    SetTargetFPS(30);
    ClearBackground(BLACK);
    fetchDecode(chip8);
    drawVideoBuffer(chip8);
    EndDrawing();
  }
  CloseWindow();
  return 0;
}
