#ifndef MONSTER_H
#define MONSTER_H
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <endian.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <limits.h>
#include <sys/time.h>
#include <errno.h>
//#include "dungeon_maker.h"
typedef int16_t pair_t[2];

typedef struct monster
{
  uint8_t val;
  pair_t pos;
  uint8_t isErr;
  uint8_t isSmart;
  uint8_t isTele;
  uint8_t isTun;
  uint8_t speed;
  uint8_t isSeen;//is the player currently seen                 
  long long nextTurn;
  uint8_t isLive;
} monster_t;
typedef struct dungeon dungeon_t;

#include "dungeon_maker.h"
#include "heap.h"
#define ERRATIC 0x1
#define SMART 0x2
#define TELE 0x4
#define TUNNEL 0x8

//typedef struct monster monster_t;
//typedef struct dungeon dungeon_t;

void init_Monster(monster_t *m,int val,int speed,int posX,int posY);
void move(monster_t *m,dungeon_t *d);
void randMove(monster_t *m,dungeon_t *d);
void dumbMove(monster_t *m,dungeon_t *d);
void smartMove(monster_t *m,dungeon_t *d);
void preformMove(monster_t *m,dungeon_t *d,int tarX,int tarY);

#endif
