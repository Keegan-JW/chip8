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


  uint8_t x = 0; 
  uint16_t nn = 0;
  // Decode opcode to get the instruction
  switch (opcode & 0xF000) {
    // Check for 0x00E0: Clear screen
    case 0x0000:
      if ((opcode & 0x00FF) == 0x00E0) {
        memset(chip8->video, 0, 64 * 32);
        printf("Screen cleared\n");
      }
      else {
        fprintf(stderr, "Error: 0x%04 not known\n", opcode);
      }
      break;

    case 0x1000:
      uint16_t address = opcode & 0x0FFF;
      chip8->pc = address;
      break;

    case 0x6000:
      x = (opcode & 0x0F00) >> 8;
      nn = opcode & 0x00FF;
      chip8->V[x] = nn;
      break;

    case 0x7000:
      x = (opcode & 0x0F00) >> 8;
      nn = opcode & 0x00FF;
      chip8->V[x] += nn;
      break;
  }

}
