#include <stdio.h>

#include <stdlib.h>
#include "chessboard.h"

int isACircle=0;
int *path;
int **chessboard;
int recLevel=0;
int counter=0;
void chessboardDefine(int x,int y)
{
  chessboard= (int**)malloc(x*sizeof(int*));
    for(int i=0;i<y;i++)
      {
       chessboard[i]=(int*)malloc(y*sizeof(int));
      }
    path=malloc((x*y+1)*sizeof(int));
  
  for(int i=0;i<x;i++)
    {
      for(int k=0;k<y;k++)
	{
	  chessboard[i][k]=0;//initilizes the chessboard
	}
    }
  for(int z=0;z<x;z++)
    {
      for(int w=0;w<y;w++)
	{
	  makeAMove(z,w,x,y);
	}
    }
  // makeAMove(0,0,x,y);//begin recursion
  
  printf("%d\n",counter);
}

void makeAMove(int xPos,int yPos,int xMax,int yMax)
  {
    int done =1;
    visit(xPos,yPos);//mark this point as visited and increment the recursion level
    for(int t=0;t<xMax;t++)
    {
      
      for(int i =0;i<yMax;i++)
	{
	  if(chessboard[t][i]==0)
	    {
	      done=0;
	    }
	}
    }
    if(done==1)
      {
	 for(int i =0;i<xMax*yMax-1;i++)
        {
          printf("%d, ",path[i]);
        }
      printf("\n");
      counter++;

      }
  
  if(xPos+2<xMax) // condition 2 right 1 up
    {
      if(yPos-1>=0)
	{
	  if(chessboard[xPos+2][yPos-1]==0)
	    {
	      makeAMove(xPos+2,yPos-1,xMax,yMax);
	    }
	}
    }
  if(xPos+2<xMax) //condition three right 1 one down
    {
      if(yPos+1<yMax)
        {
          if(chessboard[xPos+2][yPos+1]==0)
            {
              makeAMove(xPos+2,yPos+1,xMax,yMax);
            }
        }
    }
  if(xPos-2>=0)//condition 2 left 1 up
    {
      if(yPos-1>=0)
        {
          if(chessboard[xPos-2][yPos-1]==0)
            {
              makeAMove(xPos-2,yPos-1,xMax,yMax);
            }
        }
    }
    if(xPos-2>=0)//condition 2 left 1 down
    {
      if(yPos+1<yMax)
        {
          if(chessboard[xPos-2][yPos+1]==0)
            {
              makeAMove(xPos-2,yPos+1,xMax,yMax);
            }
	}
    } 
 if(xPos+1<xMax) // condition 1 right 2 up                                   
    {
      if(yPos-2>=0)
        {

          if(chessboard[xPos+1][yPos-2]==0)
            {
	      
              makeAMove(xPos+1,yPos-2,xMax,yMax);

            }
        }
    }
  if(xPos+1<xMax) //condition 1 right 2 down                              
    {
      if(yPos+2<yMax)
        {
          if(chessboard[xPos+1][yPos+2]==0)
            {
             makeAMove(xPos+1,yPos+2,xMax,yMax);
            }
	}
    }
  
  if(xPos-1>=0)//condition 1 left 2 up                                         
    {
      if(yPos-2>=0)
        {
          if(chessboard[xPos-1][yPos-2]==0)
            {
              makeAMove(xPos-1,yPos-2,xMax,yMax);
            }
	}
    }
    if(xPos-1>=0)//condition 1 left 2 down                                     
    {
      if(yPos+2<yMax)
        {
          if(chessboard[xPos-1][yPos+2]==0)
            {
              makeAMove(xPos-1,yPos+2,xMax,yMax);
            }
	}
    }
    unvisit(xPos,yPos);
}
void visit(int xPos,int yPos)
{
  path[recLevel]=(xPos+1)+(yPos*5);
  chessboard[xPos][yPos]=1;

  recLevel++;
}
void unvisit(int xPos, int yPos)
{
  
  chessboard[xPos][yPos]=0;
  recLevel--;
}
