#include <stdio.h>
#include "dungeon_maker.h"
#include <stdlib.h>
#include <time.h>
int width=80;
int height=21;
char dungeon[21][80];

int main(int argc, char **argv)
{
  //int i;
  int seed;

  seed = time(NULL);

  printf("argv[0] is %s\n", argv[0]);

  if (argc == 2) {
    seed = atoi(argv[1]);
  }
  printf("Seed is %d\n", seed);

  srand(seed);
  sweep();
  mkBounds();
  makeRooms();
  printDungeon();
  return 0;
}


void sweep()
{
  for(int i=0;i<height;i++)
    {
      for(int k=0;k<width;k++)
        {
          dungeon[i][k]=' ';//clears and initalizes all dungeon squares    
        }
    }
}
void mkBounds()
{
  
  for(int i=0;i<width;i++)
    {
      dungeon[0][i]='-'; //define the upper bounds                    
    }
  for(int i=0;i<width;i++)
    {
      dungeon[height-1][i]='-'; //define the lower bounds                          
    }
  for(int i=1; i<height-1;i++)
    {
      dungeon[i][0]='|';//define left bounds                           
    }
  for(int i=1; i<height-1;i++)
    {
      dungeon[i][width-1]='|';//define right bounds
    }
}
void printDungeon()
{
  for(int i=0;i<height;i++)
    {
      for(int k=0;k<width;k++)
	{
	  printf("%c",dungeon[i][k]);
	}
      printf("\n");
    }
}

void makeRooms()
{
  int numRooms =rand()%5+5;//howmany random rooms will be genrated between 5-10
  printf("NumRooms= %d\n",numRooms);
  room rooms[numRooms];
  
  for(int i=0;i<numRooms;i++)
    {
      //int loopCounter=0;
      int isSafe=0;
      while(!isSafe)
	{
	  // loopCounter++;
	  // if(loopCounter==30)//locks at 30 tries // this might need to be changed
	  room* temp = malloc(sizeof(room));
	  temp->width = rand()%5+4;
	  temp->x=rand()%(80-temp->width);
	  temp->height=rand()%5+4;
	  temp->y=rand()%(21-temp->height);
	  if(temp->y==0)
	    {
	      temp->y=1;
	    }
	  if(temp->x==0)
	    {
	      temp->x=1;
	    }
	  isSafe=1;
	  for(int k=0;k<i;k++)//yes this is horrendous for big o time
	    {
	      if((rooms[k].x<(temp->x+temp->width+1)&&(temp->x<rooms[k].x+rooms[k].width+1)))//if the new room is with in the bounds of the x values
		{
		  if((rooms[k].y<(temp->y+temp->height+1))&&(temp->y<rooms[k].y+rooms[k].height+1)) //if the new room is in the y bounds of the y values
		    {
		      isSafe=0;
		    }
		}    
  	    }
	   if(isSafe==1)
                {
		  // printf("%d,%d,%d,%d\n",temp->x,temp->y,temp->width,temp->height);
	          rooms[i]=*temp;
                }

	}
    }
  
  for (int i =0;i<numRooms;i++)
    {
      for(int k=rooms[i].y;k<(rooms[i].y+rooms[i].height);k++)
	{
	   for(int j=rooms[i].x;j<(rooms[i].x+rooms[i].width);j++)
	     {
	       dungeon[k][j]='.';
	       if(j==rooms[i].x||k==rooms[i].y||k==(rooms[i].y+rooms[i].height-1)||j==(rooms[i].x+rooms[i].width-1))
		 {
		   dungeon[k][j]='.';
		 }
	     }
	}
    }
  printf("numRooms = %d\n",numRooms);
  makeCorridors(numRooms,rooms);
}
void swap(room *r1, room *r2)
{
  room tmp= *r1;
  *r1=*r2;
  *r2=tmp;
}


void makeCorridors(int numRooms,room rooms[])
{
  int min_idx;
  for(int i=0;i<numRooms-1;i++)
    {
      min_idx=i;
      for(int k=i+1;k<numRooms;k++)
	{
	  if(rooms[k].x<rooms[min_idx].x)
	    {
	      min_idx=k;
	    }
	 
	}
     swap(&rooms[min_idx],&rooms[i]);

    }  
  for(int i=0;i<numRooms-1;i++)
    {
      if(rooms[i].x+rooms[i].width<rooms[i+1].x)
	{
	 int  posX=rooms[i].x+rooms[i].width;
	 int  posY=rooms[i].y+rooms[i].height/2;
	 while(((dungeon[posY][posX]!='.'))&&dungeon[posY][posX]!='*')
	    {
	      if(posX<rooms[i+1].x)
		{
		  dungeon[posY][posX]='*';
		  posX++;
		}
	      else if(posY > rooms[i+1].y)
		{
		   dungeon[posY][posX]='*';
                  posY--;
		}
	      else if(posY < rooms[i+1].y)
                {
                   dungeon[posY][posX]='*';
                  posY++;
                }
	     
	    }
	  

	}
    
      // else if(rooms[i].x<rooms[i+1].x&&rooms[i].x+rooms[i].width>rooms[i+1].x)
      //	{
      else  if(rooms[i].y<rooms[i+1].y)
	{
	  int posX=rooms[i].x+rooms[i].width/2;
	  int posY=rooms[i].y+rooms[i].height;
	  while(posY!=21&&(!(dungeon[posY][posX]=='.')&&dungeon[posY][posX]!='*'))
	    {
	      if(posY!=rooms[i+1].y)
		{
		  dungeon[posY][posX]='*';
		  posY++;
		}
	      else if(posX<rooms[i+1].x)
		{
		  dungeon[posY][posX]='*';
		  posX++;
		  
		}
	      else if(posX>rooms[i+1].x+rooms[i+1].width)
		{
		  dungeon[posY][posX]='*';
		  posX--;
		  
		}
	      
	    }
	}
      //}
	  else if(rooms[i].y>rooms[i+1].y)
            {
              int posX=rooms[i].x+rooms[i].width/2;
              int posY=rooms[i].y-1;
	      //nt test=0;
	      do
                 {
		   //  printf("Testing");
		   //scanf("%d",&test);
		   if(posY!=rooms[i+1].y+rooms[i+1].height-1)
		     {
		       dungeon[posY][posX]='*';
		       posY--;
		     }
		   else if(posX<rooms[i+1].x)
		     {
		       dungeon[posY][posX]='*';
		       posX++;
		       
		     }
		   else //(posX>rooms[i+1].x+rooms[i+1].width)
                     {
		       dungeon[posY][posX]='*';
		       posX--;
		       
                     }

		 }while((dungeon[posY][posX]!='.')&&dungeon[posY][posX]!='*');
            }

    }
}

