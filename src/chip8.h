#ifndef CHIP8_H
#define CHIP8_H

#include <stdint.h>

#define MEMORY_SIZE 4096
#define REGISTERS 16 
#define STACK_SIZE 16 
#define VIDEO_W 64
#define VIDEO_H 32

typedef struct {
  uint8_t memory[MEMORY_SIZE];
  uint8_t V[REGISTERS];
  uint16_t I;
  uint16_t pc;
  uint16_t stack[STACK_SIZE];
  uint8_t sp;
  uint8_t video[VIDEO_W * VIDEO_H];
} Chip8;

Chip8* init_chip8(Chip8 *chip8);

#endif
