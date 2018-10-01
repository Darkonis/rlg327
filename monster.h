#ifndef MONSTER_H
#define MONSTER_H
#include <stdio.h>
#include "dungeon_maker.h"
typedef struct monster monster_t;
void init_Monster(monster_t *m;int val,int speed,int posX,int posY);
void move(monster_t *m,dungeon_t *d);
void randMove(monster_t *m,dungeon_t *d);
void dumbMove(monster_t *m,dungeon_t *d);
void smartMove(monster_t *m,dungeon_t *d);


#endif
