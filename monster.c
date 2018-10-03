#include <stdio.h>
#include "monster.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>


#define ERRATIC 0x1
#define SMART 0x2
#define TELE 0x4
#define TUNNEL 0x8

/*

set up the monster
 */


void init_Monster(monster_t *m,int val,int speed,int posX,int posY)
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
  if(m->isErr&&rand()%2)
    {
      randMove(m,d);
    }
  if(m->isTele&&m->isSmart)
    {
      smartMove(m,d);
      return;
    }
  if(m->isSmart&&m->isSeen)//yes I could combine with the above but that would make the intent less clear in my opinion
    {
      smartMove(m,d);
      return;
    }
  if(m->isTele||m->isSeen)
    {
      dumbMove(m,d);
      return;
    }
  else
    {
      randMove(m,d);
    }

}
void randMove(monster_t *m,dungeon_t *d)
{
  int tarX=0;
  int tarY=0;
  tarX= m->pos[0]+ rand()%2-1;
  tarY=m->pos[1]+rand()%2-1;
  if(d->map[tarY][tarX]==ter_wall&&!(m->isTun))
    {
      randMove(m,d);//if the monster would go into a wall but isnt tunneling retry
    }
  else
    {
      preformMove(m,d,tarX,tarY);
    }
  
}
void dumbMove(monster_t *m,dungeon_t *d)
{
 int  tarX=m->pos[0];
 int tarY=m->pos[1];
  if(d->pc[0]<m->pos[0])
    {
      tarX=m->pos[0]-1;
    }
  if(d->pc[0]>m->pos[0])
    {
      tarX=m->pos[0]+1;
    }
  if(d->pc[1]<m->pos[1])
    {
      tarY=m->pos[1]-1;
    }
  if(d->pc[1]>m->pos[1])
    {
      tarY=m->pos[1]+1;
    }
  preformMove(m,d,tarX,tarY);



}
void smartMove(monster_t *m,dungeon_t *d)
{
  int tarX;
  int tarY;
  if(m->isTun)
    {
      tarX=d->completePath[m->pos[0]][m->pos[1]]->pos[0];
      tarY=d->completePath[m->pos[0]][m->pos[1]]->pos[1];
    }
  else
    {
      tarX=d->partialPath[m->pos[0]][m->pos[1]]->pos[0];
      tarY=d->partialPath[m->pos[0]][m->pos[1]]->pos[1];
    }
}
void preformMove(monster_t *m,dungeon_t *d,int tarX,int tarY)
{
if(d->map[tarY][tarX]==ter_wall&&(m->isTun))
    {
      if(d->hardness[tarY][tarX]>=85)
        {
          d->hardness[tarY][tarX]-=85;
	}
      else
        {
           d->hardness[tarY][tarX]=0;
           d->map[tarY][tarX]=ter_floor_hall;
	}
    }
  else if(d->map[tarY][tarX]==ter_floor_room||d->map[tarY][tarX]==ter_floor_hall)
    {
      m->pos[0]=tarX;
      m->pos[1]=tarY;
    }


}

