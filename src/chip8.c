#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "chip8.h"

Chip8* init_chip8(Chip8 *chip8) {
  chip8 = malloc(sizeof(Chip8));
  // Set memory to all 0s
  memset(chip8->memory, 0, MEMORY_SIZE);
  // Set program counter to 0x200, this is where the ROM is loaded in chip8
  chip8->pc = 0x200;
}

void fetchDecode(Chip8 *chip8) {
  // Get opcode
  uint16_t opcode = (chip8->memory[chip8->pc] << 8) | chip8->memory[chip8->pc + 1];
  printf("0x%04X\n", opcode);

  // Move program counter to the next byte
  chip8->pc += 2;

  uint16_t address = 0;
  uint8_t x = 0; 
  uint16_t nn = 0;
  // Decode opcode to get the instruction
  switch (opcode & 0xF000) {
    // Check for 0x00E0: Clear screen
    case 0x0000:
      // Clear screen
      if ((opcode & 0x00FF) == 0x00E0) { memset(chip8->video, 0, 64 * 32); printf("Screen cleared\n"); }
      else {
        fprintf(stderr, "Error: 0x%04 not known\n", opcode);
      }
      break;
    
    // Jump - Set pc to NNN
    case 0x1000:
      address = opcode & 0x0FFF;
      chip8->pc = address;
      break;

    // Set - Set register V[X] to NN
    case 0x6000:
      x = (opcode & 0x0F00) >> 8;
      nn = opcode & 0x00FF;
      chip8->V[x] = nn;
      break;

    // Add - Add NN to V[X]
    case 0x7000:
      x = (opcode & 0x0F00) >> 8;
      nn = opcode & 0x00FF;
      chip8->V[x] += nn;
      break;

    // Set index - Set I to NNN
    case 0xA000:
      address = opcode & 0x0FFF;
      chip8->I = address;
      break;

    // Print sprite
    case 0xD000:
      x = (opcode & 0x0F00) >> 8;
      uint8_t y = (opcode & 0x00F0) >> 4;
      uint8_t n = opcode & 0x000F;

      uint8_t x_coord = chip8->V[x];
      uint8_t y_coord = chip8->V[y];
      uint8_t collision = 0;

      for (int row = 0; row < n; row++) {
          uint8_t sprite_byte = chip8->memory[chip8->I + row];
          for (int col = 0; col < 8; col++) {
              uint8_t sprite_pixel = (sprite_byte >> (7 - col)) & 1;
              uint8_t *screen_pixel = &chip8->video[(x_coord + col) % 64][(y_coord + row) % 32];

              if (*screen_pixel && sprite_pixel) {
                  collision = 1; 
              }
              *screen_pixel ^= sprite_pixel;
          }
      }
      chip8->V[0xF] = collision;
      break;

    default:
      fprintf(stderr, "Unknown opcode\n");
  }
}
