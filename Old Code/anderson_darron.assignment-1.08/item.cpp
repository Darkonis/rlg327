#include "item.h"
#include "dungeon.h"
#include "utils.h"
#include <ncurses.h>
void gen_items(dungeon *d)
{
  uint32_t i;
  item *m;
  uint32_t room;
  pair_t p;
  //const static char symbol[] = "0123456789abcdef";                                                                                                                                                        
  //uint32_t num_cells;
  d->num_objects=12;
  m=new item;
  
  //num_cells = max_monster_cells(d);
  //d->num_monsters = d->max_monsters < num_cells ? d->max_monsters : num_cells;

  for (i = 0; i < d->num_objects; i++) {
    int flag=0;
    //mvprintw(21,0,m->description.c_str());
    // getchar();
    while(!flag)
      {
        //std::cout<<d->monster_descriptions.size()<<'\n';                                                                                                                                                  
        // getchar();
	//std::cout<<m<<'\n';
	
	//	mvaddch(21,0,d->object_descriptions.size()+48);
	//refresh();
	//getchar();


        int item_tar=rand()%d->object_descriptions.size();
        if(d->object_descriptions[item_tar].get_rarity()<(unsigned)rand()%100&&(!d->object_descriptions[item_tar].get_artifact() ||!d->object_descriptions[item_tar].get_exists()))
          {
	    d->object_descriptions[item_tar].set_exists(1);
            flag=1;
            m=d->object_descriptions[item_tar].generate_item();
	    //   std::cout<<m<<'\n';
	    //mvprintw(21,0,d->item_map[p[dim_y]][p[dim_x]]->description.c_str());
	    // getchar();

                                                                                                       
            //getchar();                                                                                                                                                                                    
            // memset(m, 0, sizeof (*m));                                                                                                                                                                   
          }
      }
    do {
      room = rand_range(1, d->num_rooms - 1);
      p[dim_y] = rand_range(d->rooms[room].position[dim_y],
                            (d->rooms[room].position[dim_y] +
                             d->rooms[room].size[dim_y] - 1));
      p[dim_x] = rand_range(d->rooms[room].position[dim_x],
                            (d->rooms[room].position[dim_x] +
                             d->rooms[room].size[dim_x] - 1));
    } while (d->item_map[p[dim_y]][p[dim_x]]);
    m->position[dim_y] = p[dim_y];
    m->position[dim_x] = p[dim_x];
    //d->item_map[p[dim_y]][p[dim_x]] = m;
    // m->speed = rand_range(5, 20);                                                                                                                                                                        
    // m->alive = 1;
    //m->sequence_number = ++d->character_sequence_number;
    //m->characteristics = rand() & 0x0000000f;                                                                                                                                                             
    /*    m->npc->characteristics = 0xf;*/
    //m->symbol = symbol[m->characteristics];                                                                                                                                                               
    // m->have_seen_pc = 0;
    //m->kills[kill_direct] = m->kills[kill_avenged] = 0;
    d->item_map[p[dim_y]][p[dim_x]] = m;
    
  }
}
