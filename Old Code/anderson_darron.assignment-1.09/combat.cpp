#include <unistd.h>
#include <stdlib.h>
#include <assert.h>

#include "dungeon.h"
#include "heap.h"
#include "move.h"
#include "npc.h"
#include "pc.h"
#include "character.h"
#include "utils.h"
#include "path.h"
#include "io.h"
#include "npc.h"
#include "combat.h"
#include "dice.h"
uint32_t player_attack(dungeon *);
void do_combat(dungeon *d, character *atk, character *def)
{
int can_see_atk, can_see_def;
  const char *organs[] = {
    "liver",                   /*  0 */
    "pancreas",                /*  1 */
    "heart",                   /*  2 */
    "eye",                     /*  3 */
    "arm",                     /*  4 */
    "leg",                     /*  5 */
    "intestines",              /*  6 */
    "gall bladder",            /*  7 */
    "lungs",                   /*  8 */
    "hand",                    /*  9 */
    "foot",                    /* 10 */
    "spinal cord",             /* 11 */
    "pituitary gland",         /* 12 */
    "thyroid",                 /* 13 */
    "tongue",                  /* 14 */
    "bladder",                 /* 15 */
    "diaphram",                /* 16 */
    "stomach",                 /* 17 */
    "pharynx",                 /* 18 */
    "esophagus",               /* 19 */
    "trachea",                 /* 20 */
    "urethra",                 /* 21 */
    "spleen",                  /* 22 */
    "ganglia",                 /* 23 */
    "ear",                     /* 24 */
    "subcutaneous tissue"      /* 25 */
    "cerebellum",              /* 26 */ /* Brain parts begin here */
    "hippocampus",             /* 27 */
    "frontal lobe",            /* 28 */
    "brain",                   /* 29 */
  };
  int part;
  int killed=0;
  if (def->alive) {
    //def->alive = 0;
    //charpair(def->position) = NULL;
    int32_t dmg=0;
    if(def!=d->PC)
      {
	dmg =player_attack(d);
	
      }
    else
      {
	dmg =atk->damage->roll(); 
      }
   
    if(dmg>=(int)def->hp)
      {
	killed=1;
	if(has_characteristic(def,BOSS))
	  {
	    d->PC->has_won=1;
	  }
	  
      }
    else
      {
       
	def->hp-=dmg;
	 
      }
    if(atk==d->PC)
      {
	io_queue_message("You deal %d damage to %s",dmg,def->name);
      }
    if(killed) 
      {
	def->alive = 0;                                                          
    charpair(def->position) = NULL;
	if (def != d->PC) {
	  d->num_monsters--;
	}
	else
	  {
	    if ((part = rand() % (sizeof (organs) / sizeof (organs[0]))) < 26)
	      {
		io_queue_message("As %s%s eats your %s,", is_unique(atk) ? "" : "the ",
				 atk->name, organs[rand() % (sizeof (organs) /
							     sizeof (organs[0]))]);
		io_queue_message("   ...you wonder if there is an afterlife.");
		/* Queue an empty message, otherwise the game will not pause for *
         * player to see above.                                          */
	       io_queue_message("");}
	   else {
        io_queue_message("Your last thoughts fade away as "
                         "%s%s eats your %s...",
                         is_unique(atk) ? "" : "the ",
                         atk->name, organs[part]);
        io_queue_message("");
      }
      /* Queue an empty message, otherwise the game will not pause for *
       * player to see above.                                          */
    io_queue_message("");
      }
    atk->kills[kill_direct]++;
    atk->kills[kill_avenged] += (def->kills[kill_direct] +
                                  def->kills[kill_avenged]);
  

  if (atk == d->PC) {
    io_queue_message("You smite %s%s!", is_unique(def) ? "" : "the ", def->name);
  }

  can_see_atk = can_see(d, character_get_pos(d->PC),
                        character_get_pos(atk), 1, 0);
  can_see_def = can_see(d, character_get_pos(d->PC),
                        character_get_pos(def), 1, 0);

  if (atk != d->PC && def != d->PC) {
    if (can_see_atk && !can_see_def) {
      io_queue_message("%s%s callously murders some poor, "
                       "defenseless creature.",
                       is_unique(atk) ? "" : "The ", atk->name);
    }
    if (can_see_def && !can_see_atk) {
      io_queue_message("Something kills %s%s.",
                       is_unique(def) ? "" : "the helpless ", def->name);
    }
    if (can_see_atk && can_see_def) {
      io_queue_message("You watch in abject horror as %s%s "
                       "gruesomely murders %s%s!",
                       is_unique(atk) ? "" : "the ", atk->name,
                       is_unique(def) ? "" : "the ", def->name);
    }
  }
  }
}
}  
 uint32_t player_attack(dungeon* d)
  {
    int dmg=0;
    int i=0;
    if(!d->PC->equip[0]&&!d->PC->equip[0])
      {
	dice* d=new dice(0,1,4);
	dmg+=d->roll();
	delete d;
      }
    for(i=0;i<12;i++)
      {
	if(d->PC->equip[i])
	  {
	    dmg+=d->PC->equip[i]->roll_dice();
	  }
      }
    return dmg;
  }
