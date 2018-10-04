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
//typedef int16_t pair_t[2];
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
//typedef struct dungeon {
struct dungeon{
  uint32_t num_rooms;
  room_t *rooms;
  terrain_type_t map[DUNGEON_Y][DUNGEON_X];

  /* Since hardness is usually not used, it would be expensive to pull it *                                                                                                                                 
   * into cache every time we need a map cell, so we store it in a        *                                                                                                                                 
   * parallel array, rather than using a structure to represent the       *                                                                                                                                 
   * cells.  We may want a cell structure later, but from a performanace  *                                                                                                                                 
   * perspective, it would be a bad idea to ever have the map be part of  *                                                                                                                                 
   * that structure.  Pathfinding will require efficient use of the map,  *                                                                                                                                 
   * and pulling in unnecessary data with each map cell would add a lot   *                                                                                                                                 
   * of overhead to the memory system.                                    */
 uint8_t hardness[DUNGEON_Y][DUNGEON_X];
  distance_path_t *completePath[DUNGEON_Y][DUNGEON_X];
  distance_path_t *partialPath[DUNGEON_Y][DUNGEON_X];
  uint32_t num_Monsters;
  uint32_t cur_turn;
  uint32_t pc_speed;
  uint32_t pc_nturn;
  pair_t pc;
  monster_t *mon;
  uint8_t hasLost;
  //  pair_t pc;                                                                                                                                                                                            
} ;


int roll_call(dungeon_t *d,int y,int x);
monster_t *roll_call2(dungeon_t *d,int y,int x);
typedef enum dim {
  dim_x,
  dim_y,
  num_dims
} dim_t;

static uint32_t in_room(dungeon_t *d, int16_t y, int16_t x)
{
  int i;

  for (i = 0; i < d->num_rooms; i++) {
    if ((x >= d->rooms[i].position[dim_x]) &&
        (x < (d->rooms[i].position[dim_x] + d->rooms[i].size[dim_x])) &&
        (y >= d->rooms[i].position[dim_y]) &&
        (y < (d->rooms[i].position[dim_y] + d->rooms[i].size[dim_y]))) {
      return 1;
    }
  }

  return 0;
}


#include "monster.h"

#endif
