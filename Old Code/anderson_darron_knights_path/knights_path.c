//this program was developed by Darron Anderson
#include <stdio.h>
#include <stdlib.h>
#include "chessboard.h"
#include "chessboard.c"
int main()
{
  int x=0;
  int y=0;
  printf("please enter a length value\n");
  scanf("%d",&x);//get the width of the chess board
  printf("please enter a height value\n");
  scanf("%d",&y);//get the height of the chess board
  chessboardDefine(x,y);
  return 0;	
}

