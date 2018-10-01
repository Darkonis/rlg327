#include <stdio.h>
#include "monster.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>


#define ERRATIC 0x1
#define SMART 0x2
#define TELE 0x4
#define TUNNEL 0x8

typedef struct monster
{
  uint8_t val=0;
  pair_t pos;
  uint8_t isErr=0;
  uint8_t isSmart=0;
  uint8_t isTele=0;
  uint8_t isTun=0;
  uint8_t speed=0;
  uint8_t player=0;//is the player currently seen
  
} monster_t;
/*

set up the monster
 */
void init_Monster(monster_t *m;int val,int speed,int posX,int posY)
{
  m->val=val;
  m->pos[0]=posX;
  m->pos[1]=posY;
  m->isErr=ERRATIC&val;
  m->isSmart=SMART&val;
  m->isTele=TELE&val;
  m->isTun=TUNNEL&val;
  m->speed=speed;
}

void move(monster_t *m,dungeon_t *d)
{
  int xPos = m->pos[0];
  int yPos =m->pos[1];
  if(m->isTele&&m->isTunnel&&m->isSmart)
    {
     

    }

}
void randMove(monster_t *m,dungeon_t *d)
{
  int tarX=0;
  int tarY=0;
  tarX= m->pos[0]+ rand_range(-1,1);
  tarY=m->pos[1]+rand_range(-1,1);
  if(dungeon->map[tarY][tarx]==ter_wall&&!(m->isTunnel))
    {
      randMove(m,d);//if the monster would go into a wall but isnt tunneling retry
    }

}
