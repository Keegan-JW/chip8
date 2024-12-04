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
