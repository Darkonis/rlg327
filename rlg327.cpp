//#include <stdio.h>
#include <string>
#include <sys/time.h>
#include <unistd.h>
#include <ncurses.h>
/* Very slow seed: 686846853 */

#include "dungeon.h"
#include "pc.h"
#include "npc.h"
#include "move.h"
#include <stdbool.h>

const char *victory =
  "\n                                       o\n"
  "                                      $\"\"$o\n"
  "                                     $\"  $$\n"
  "                                      $$$$\n"
  "                                      o \"$o\n"
  "                                     o\"  \"$\n"
  "                oo\"$$$\"  oo$\"$ooo   o$    \"$    ooo\"$oo  $$$\"o\n"
  "   o o o o    oo\"  o\"      \"o    $$o$\"     o o$\"\"  o$      \"$  "
  "\"oo   o o o o\n"
  "   \"$o   \"\"$$$\"   $$         $      \"   o   \"\"    o\"         $"
  "   \"o$$\"    o$$\n"
  "     \"\"o       o  $          $\"       $$$$$       o          $  ooo"
  "     o\"\"\n"
  "        \"o   $$$$o $o       o$        $$$$$\"       $o        \" $$$$"
  "   o\"\n"
  "         \"\"o $$$$o  oo o  o$\"         $$$$$\"        \"o o o o\"  "
  "\"$$$  $\n"
  "           \"\" \"$\"     \"\"\"\"\"            \"\"$\"            \""
  "\"\"      \"\"\" \"\n"
  "            \"oooooooooooooooooooooooooooooooooooooooooooooooooooooo$\n"
  "             \"$$$$\"$$$$\" $$$$$$$\"$$$$$$ \" \"$$$$$\"$$$$$$\"  $$$\""
  "\"$$$$\n"
  "              $$$oo$$$$   $$$$$$o$$$$$$o\" $$$$$$$$$$$$$$ o$$$$o$$$\"\n"
  "              $\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\""
  "\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"$\n"
  "              $\"                                                 \"$\n"
  "              $\"$\"$\"$\"$\"$\"$\"$\"$\"$\"$\"$\"$\"$\"$\"$\"$\"$\"$\""
  "$\"$\"$\"$\"$\"$\"$\"$\n"
  "                                   You win!\n\n";

const char *tombstone =
  "\n\n\n\n                /\"\"\"\"\"/\"\"\"\"\"\"\".\n"
  "               /     /         \\             __\n"
  "              /     /           \\            ||\n"
  "             /____ /   Rest in   \\           ||\n"
  "            |     |    Pieces     |          ||\n"
  "            |     |               |          ||\n"
  "            |     |   A. Luser    |          ||\n"
  "            |     |               |          ||\n"
  "            |     |     * *   * * |         _||_\n"
  "            |     |     *\\/* *\\/* |        | TT |\n"
  "            |     |     *_\\_  /   ...\"\"\"\"\"\"| |"
  "| |.\"\"....\"\"\"\"\"\"\"\".\"\"\n"
  "            |     |         \\/..\"\"\"\"\"...\"\"\""
  "\\ || /.\"\"\".......\"\"\"\"...\n"
  "            |     |....\"\"\"\"\"\"\"........\"\"\"\"\""
  "\"^^^^\".......\"\"\"\"\"\"\"\"..\"\n"
  "            |......\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"......"
  "..\"\"\"\"\"....\"\"\"\"\"..\"\"...\"\"\".\n\n"
  "            You're dead.  Better luck in the next life.\n\n\n";
 void to_init_terminal(void)
    {
      initscr();
      raw();
      noecho();
      curs_set(0);
      keypad(stdscr, TRUE);
    }
void usage(char *name)
{
  fprintf(stderr,
          "Usage: %s [-r|--rand <seed>] [-l|--load [<file>]]\n"
          "          [-s|--save [<file>]] [-i|--image <pgm file>]\n"
          "          [-n|--nummon <count>]",
          name);

  exit(-1);
}
void render_menu(dungeon_t *d,int curMenu)
{
  // erase();//clean the screen from input
  // refresh();
  int lineNum=1;
  int m_count=0;
  int x;
  int y;
  for(y=0;y<DUNGEON_Y;y++)
    {
       for (x = 0; x < DUNGEON_X; x++)
	 {
	   
	   if(d->character[y][x]!=NULL&&d->character[y][x]->known&&d->character[y][x]->alive)//if there is a monster at this location
	     {
	       if(m_count>=21*curMenu&&m_count<21*(curMenu+1))
		 {
		   int xdif=d->pc.position[0]-x;
		   int ydif= d->pc.position[1]-y;
		   if(!xdif&&!ydif)
		     {
		       continue;
		     }
		   mvprintw(lineNum,0,"Monster num:%d, Monster symbol %c is ",m_count,d->character[y][x]->symbol);
		   if(xdif>0)
		     {
		       printw("%d spaces west ",xdif);//35
		     }
		   else if(xdif<0)
		     {
		       printw("%d spaces east ",-xdif);
		     }
		   if(xdif&&ydif)
		     {
		       printw("and ");
		     }
		   if(ydif<0)
		     {
		       printw("%d spaces south",-ydif);
		     }
		   else if(ydif>0)
		     {
		       printw("%d spaces north",ydif);
		     }
		   lineNum++;
		   m_count++;
		 }
	       else
		 {
		   m_count++;
		 }
	     }
	 }
       
    }
  refresh();
}
bool isFow=true;
void teleMove(dungeon_t *d,int in,int *tarX,int *tarY);
char process_input(dungeon_t *d)
{
  if(isFow)
    {
  see(d);
  render_seen(d);
    }
  else
    {
      render_dungeon(d);
    }
  int in;
      in = getch();
      if(in=='f')
	{
	  isFow=!isFow;
	  return in;
	}
      if(in=='g')
	{
	  in='a';//make sure it doesn;t enter the loop
	  int tarX=d->pc.position[0];
	  int tarY=d->pc.position[1];
	  d->character[d->pc.position[dim_y]][d->pc.position[dim_x]] = NULL;
	  render_dungeon(d);
	  mvaddch(tarY,tarX,'&');
	  refresh();
	  while(in!='g'&&in!='r'&&in!='Q')
	    {
	      render_dungeon(d);
	       mvaddch(tarY,tarX,'&');
	       refresh();
	      in=getch();
	      if(in=='r')
		{
		 tarY=rand()%19+1;
		 tarX=rand()%78+1;
		  pair_t next;
                 next[1]=tarY;
                 next[0]=tarX;
                 if(charpair(next))
                   {
                     //charpair(next)->alive=0;
                     move_character(d,&(d->pc),next);
                   }
                 d->pc.position[1]=tarY;
	             d->pc.position[0]=tarX;

		  continue;
		}
	      else if(in=='g')
		{
		  //d->pc.position[1]=tarY;
		  //d->pc.position[0]=tarX;
		 pair_t next;
		 next[1]=tarY;
		 next[0]=tarX;
		 if(charpair(next))
		   {
		     //charpair(next)->alive=0;
		     move_character(d,&(d->pc),next);
		   }
		 d->pc.position[1]=tarY;
                     d->pc.position[0]=tarX;

		 
		}
	      else
		{
		  teleMove(d,in,&tarX,&tarY);
		}
	      refresh();
	    }
	  if(isFow)
	    {
	      see(d);
	      render_seen(d);
	    }
	  else
	    {
	      render_dungeon(d);
	    }
	}
      if(in=='m')
	{
	  clear();
	  int curMenu=0;
	  while(in!=27&&in!='Q')
	    {
	      if(in == KEY_DOWN&&curMenu!=d->num_monsters/21)
		{
		  curMenu++;
		}
	      else if(in==KEY_UP&&curMenu!=0)
		{
		  curMenu--;
		}
	      //erase();
	      mvprintw(22,0,"input is:%d and curMenu is %d", in,curMenu);
	       render_menu(d,curMenu);
	      in=getch();
	    }
	}
      
      switch(in)
	{
	case 48:
	case 49:
	case 50:
	case 51:
	case 52:
	case 53:
	case 54:
	case 55:
	case 56:
	case 57:
	case 121://y
	case 107 ://k
	case 117://u
	case 108://l
	case 110://n
	case 106://j
	case 98://b
	case 104://h
	case 60://<
	case 62 ://>
	case (char )' ':
	  mvprintw(22,0,"input is:%c ", in);
	  char l = (char) in;
	  do_moves(d,&l);
	   mvprintw(2,0,"input is:%c ", in);
	   refresh();
	   break;
	}
      see(d);
      render_seen(d);
      return in;

}
void teleMove(dungeon_t *d,int in,int *tarX,int *tarY)
{
  switch(in)
    {
    case 54:
    case 108:
      (*tarX)++;
      break;
    case 52:
    case 104:
      (*tarX)--;
      break;
    case 'k':
    case 56:
      (*tarY)--;
      break;
    case 'j':
    case 50:
      (*tarY)++;
      break;
    case 'b':
    case 49:
      (*tarX)--;
      (*tarY)++;
      break;
    case'n':
    case 51:
      (*tarX)++;
      (*tarY)++;
      break;
    case 'u':
    case 57:
      (*tarX)++;
      (*tarY)--;
	break;
    case 'y':
    case 55:
      (*tarX)--;
      (*tarY)--;
      break;
    }
  if(!tarX)
    {
      (*tarX)++;
    }
  if((*tarX)==79)
    {
      (*tarX)--;
    }
  if(!tarY)
    {
      (*tarY)++;
    }
  if((*tarY)==20)
    {
      (*tarY)--;
    }

}
int main(int argc, char *argv[])
{
  dungeon_t d;
  time_t seed;
  struct timeval tv;
  uint32_t i;
  uint32_t do_load, do_save, do_seed, do_image, do_save_seed, do_save_image;
  uint32_t long_arg;
  char *save_file;
  char *load_file;
  char *pgm_file;
  to_init_terminal();
  /* Quiet a false positive from valgrind. */
  memset(&d, 0, sizeof (d));
  
  /* Default behavior: Seed with the time, generate a new dungeon, *
   * and don't write to disk.                                      */
  do_load = do_save = do_image = do_save_seed = do_save_image = 0;
  do_seed = 1;
  save_file = load_file = NULL;
  d.max_monsters = MAX_MONSTERS;

  /* The project spec requires '--load' and '--save'.  It's common  *
   * to have short and long forms of most switches (assuming you    *
   * don't run out of letters).  For now, we've got plenty.  Long   *
   * forms use whole words and take two dashes.  Short forms use an *
    * abbreviation after a single dash.  We'll add '--rand' (to     *
   * specify a random seed), which will take an argument of it's    *
   * own, and we'll add short forms for all three commands, '-l',   *
   * '-s', and '-r', respectively.  We're also going to allow an    *
   * optional argument to load to allow us to load non-default save *
   * files.  No means to save to non-default locations, however.    *
   * And the final switch, '--image', allows me to create a dungeon *
   * from a PGM image, so that I was able to create those more      *
   * interesting test dungeons for you.                             */
 
 if (argc > 1) {
   for (i = 1, long_arg = 0; i <(unsigned)argc; i++, long_arg = 0) {
      if (argv[i][0] == '-') { /* All switches start with a dash */
        if (argv[i][1] == '-') {
          argv[i]++;    /* Make the argument have a single dash so we can */
          long_arg = 1; /* handle long and short args at the same place.  */
        }
        switch (argv[i][1]) {
        case 'n':
          if ((!long_arg && (unsigned)argv[i][2]) ||
              (long_arg && strcmp(argv[i], "-nummon")) ||
              (unsigned)argc < ++i + 1 /* No more arguments */ ||
              !sscanf(argv[i], "%hu", &d.max_monsters)) {
            usage(argv[0]);
          }
          break;
        case 'r':
          if ((!long_arg && argv[i][2]) ||
              (long_arg && strcmp(argv[i], "-rand")) ||
              (unsigned)argc < ++i + 1 /* No more arguments */ ||
              !sscanf(argv[i], "%lu", &seed) /* Argument is not an integer */) {
            usage(argv[0]);
          }
          do_seed = 0;
          break;
        case 'l':
          if ((!long_arg && argv[i][2]) ||
              (long_arg && strcmp(argv[i], "-load"))) {
            usage(argv[0]);
          }
          do_load = 1;
          if (((unsigned)argc > i + 1) && argv[i + 1][0] != '-') {
            /* There is another argument, and it's not a switch, so *
             * we'll treat it as a save file and try to load it.    */
            load_file = argv[++i];
          }
          break;
        case 's':
          if ((!long_arg && argv[i][2]) ||
              (long_arg && strcmp(argv[i], "-save"))) {
            usage(argv[0]);
          }
          do_save = 1;
          if (((unsigned)argc > i + 1) && argv[i + 1][0] != '-') {
            /* There is another argument, and it's not a switch, so *
             * we'll save to it.  If it is "seed", we'll save to    *
	     * <the current seed>.rlg327.  If it is "image", we'll  *
	     * save to <the current image>.rlg327.                  */
	    if (!strcmp(argv[++i], "seed")) {
	      do_save_seed = 1;
	      do_save_image = 0;
	    } else if (!strcmp(argv[i], "image")) {
	      do_save_image = 1;
	      do_save_seed = 0;
	    } else {
	      save_file = argv[i];
	    }
          }
          break;
        case 'i':
          if ((!long_arg && argv[i][2]) ||
              (long_arg && strcmp(argv[i], "-image"))) {
            usage(argv[0]);
          }
          do_image = 1;
          if (((unsigned)argc > i + 1) && argv[i + 1][0] != '-') {
            /* There is another argument, and it's not a switch, so *
             * we'll treat it as a save file and try to load it.    */
            pgm_file = argv[++i];
          }
          break;
        default:
          usage(argv[0]);
        }
      } else { /* No dash */
        usage(argv[0]);
      }
    }
  }

  if (do_seed) {
    /* Allows me to generate more than one dungeon *
     * per second, as opposed to time().           */
    gettimeofday(&tv, NULL);
    seed = (tv.tv_usec ^ (tv.tv_sec << 20)) & 0xffffffff;
  }

  if (!do_load && !do_image) {
    printf("Seed is %ld.\n", seed);
  }
  srand(seed);

  init_dungeon(&d);

  if (do_load) {
    read_dungeon(&d, load_file);
  } else if (do_image) {
    read_pgm(&d, pgm_file);
  } else {
    gen_dungeon(&d);
    int t=0;
    while(t==0)
      {
	int i = rand()%21;
	int k=rand()%80;
	if(d.map[i][k]==ter_floor_room)
	  {
	    t=1;
	    d.map[i][k]=ter_stair_up;
 	  }
      }
    t=0;
    while(t==0)
      {
        int i = rand()%21;
	int k=rand()%80;
        if(d.map[i][k]==ter_floor_room)
          {
            t= 1;
            d.map[i][k]=ter_stair_down;
          }
      }

    
  }

  /* Ignoring PC position in saved dungeons.  Not a bug. */
  config_pc(&d);
  gen_monsters(&d);
  
  // int isMenu=0;
  // int curMenu=0;
  while (pc_is_alive(&d) && dungeon_has_npcs(&d)) {
    
   char t= process_input(&d);
   if (t=='Q')
     {
       break;
     }
  }
  if (do_save) {
    if (do_save_seed) {
       /* 10 bytes for number, please dot, extention and null terminator. */
      save_file = (char*)malloc(18);
      sprintf(save_file, "%ld.rlg327", seed);
    }
    if (do_save_image) {
      if (!pgm_file) {
	fprintf(stderr, "No image file was loaded.  Using default.\n");
	do_save_image = 0;
      } else {
	/* Extension of 3 characters longer than image extension + null. */
	save_file = (char*)malloc(strlen(pgm_file) + 4);
	strcpy(save_file, pgm_file);
	strcpy(strchr(save_file, '.') + 1, "rlg327");
      }
    }
    write_dungeon(&d, save_file);

    if (do_save_seed || do_save_image) {
      free(save_file);
    }
  }
  if(endwin()!=0)
    {
      printf("error deinitilizing ncurses");
    }
  clear();
  printf("%s", pc_is_alive(&d) ? victory : tombstone);
  printf("You defended your life in the face of %u deadly beasts.\n"
         "You avenged the cruel and untimely murders of %u "
         "peaceful dungeon residents.\n",
         d.pc.kills[kill_direct], d.pc.kills[kill_avenged]);

  pc_delete(d.pc.pc);
  /*  if(endwin()!=0)
    {
      printf("error deinitilizing ncurses");
    }
  */
  delete_dungeon(&d);
  //  _nc_free_and_exit();
  //ExitProgram();
  return 0;
}
