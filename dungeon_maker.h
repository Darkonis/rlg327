#ifndef DUNGEON_MAKER_H
#define DUNGEON_MAKER_H 
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
#include "heap.h"
#include "monster.h"
#define DUNGEON_X              80
#define DUNGEON_Y              21
typedef struct distance_path {
  heap_node_t *hn;
  uint8_t pos[2];
  uint8_t from[2];
  int32_t cost;
} distance_path_t;

typedef enum __attribute__ ((__packed__)) terrain_type {
  ter_debug,
  ter_wall,
  ter_wall_immutable,
  ter_floor,
  ter_floor_room,
  ter_floor_hall,
} terrain_type_t;
typedef int16_t pair_t[2];
typedef struct room {
  pair_t position;
  pair_t size;
} room_t;
typedef struct dungeon dungeon_t;

int roll_call(dungeon_t *d,int y,int x);

static uint32_t in_room(dungeon_t *d, int16_t y, int16_t x);
#endif
