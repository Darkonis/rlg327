//#ifndef MONSTER_C
//#define MONSTER_C
#include <stdio.h>
#include "monster.h"
#include "dungeon_maker.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
//#include "dungeon_maker.c"

#define ERRATIC 0x1
#define SMART 0x2
#define TELE 0x4
#define TUNNEL 0x8
//#endif


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
  m->nextTurn=0;
  m->isSeen=1;
  m->isLive=1;
}

void move(monster_t *m,dungeon_t *d)
{
  m->nextTurn+=1000/(m->speed);
  //int xPos = m->pos[0];
  //int yPos =m->pos[1];
  if(m->isErr&&rand()%2)
    {
      randMove(m,d);
    }
  if(m->isTele&&m->isSmart)
    {
      smartMove(m,d);
      return;
    }
   in_room(d,1,1);
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
  tarX=m->pos[0];
  tarY=m->pos[1];

  if(m->isTun)
    {
      if(d->completePath[m->pos[1]][m->pos[0]]->cost!=0)
	{
	  tarX=d->completePath[m->pos[1]][m->pos[0]]->from[0];
	  tarY=d->completePath[m->pos[1]][m->pos[0]]->from[1];
	}
    }
  else
    {
      
      //  printf("\n%d %d:%d %d\n",m->val,m->speed,m->pos[0],m->pos[1]);
      if(d->partialPath[m->pos[1]][m->pos[0]]->cost!=0)
        {
	  tarX=d->partialPath[m->pos[1]][m->pos[0]]->from[0];
	  tarY=d->partialPath[m->pos[1]][m->pos[0]]->from[1];
	}
    }
  preformMove(m,d,tarX,tarY);
  // printf("\n%d, %d:%d %d\n",m->val,m->speed,m->pos[0],m->pos[1]);

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
	   m->pos[0]=tarX;
	   m->pos[1]=tarY;
	}
    }
  else if(d->map[tarY][tarX]==ter_floor_room||d->map[tarY][tarX]==ter_floor_hall)
    {
      if(roll_call2(d,tarY,tarX))
	{
	  monster_t *tmp=roll_call2(d,tarY,tarX);
	  if(tmp==m)
	    {
	      return;
	    }
	  roll_call2(d,tarY,tarX)->isLive=0;
	  roll_call2(d,tarY,tarX)->nextTurn=INT_MAX;
	  // monster_t *tmp=roll_call2(d,tarY,tarX);
	  tmp->isLive=0;
	}
      m->pos[0]=tarX;
      m->pos[1]=tarY;
      if(tarX==d->pc[0]&&tarY==d->pc[1])
	{
	  d->hasLost=1;
	}
      
    }
  
  
}

