#include "spell.h"
#include "dungeon.h"
#include "descriptions.h"
#include "character.h"
#include "io.h"
spell::spell(std::string name,std::string description,int type,bool special,dice effect,uint32_t cost,uint32_t range,int aoe,uint32_t rarity)
{
  this->name=name;
  this->description=description;
  this->type=type;
  this->special=special;
  this->effect=effect;
  this->cost=cost;
  this->range=range;
  this->aoe=aoe;
  this->rarity=rarity;
}
void spell::set(std::string name,std::string description,int type,bool special,dice effect,uint32_t cost,uint32_t range,int aoe,uint32_t rarity)
{
  this->name=name;
  this->description=description;
  this->type=type;
  this->special=special;
  this->effect=effect;
  this->cost=cost;
  this->range=range;
  this->aoe=aoe;
  this->rarity=rarity;
}
void spell::cast(dungeon *d,pair_t tar,character* caster)
{
  if(caster->mana<get_cost())
    {
      io_queue_message("You don't have enough mana to cast that. :%d",caster->mana);
      return;
    }
  caster->mana-=get_cost();
  int y;
  int x;
  int minY=tar[dim_y]-get_aoe();
  int maxY=tar[dim_y]+get_aoe();
  int minX=tar[dim_x]-get_aoe();
  int maxX=tar[dim_x]+get_aoe();
  if(minY<0)
    {
      minY=1;
    }
  if(maxY>=DUNGEON_Y)
    {
      maxY=DUNGEON_Y-1;
    }
  if(minX<=0)
    {
      minX=1;
    }
  if(maxX>=DUNGEON_X)
    {
      maxX=DUNGEON_X-1;
    }
  for(y=minY;y<=maxY;y++)
    {
      for(x=minX;x<=maxX;x++)
	{
	  if(charxy(x,y)&&(charxy(x,y)!=caster||get_type()==1))
	    {
	        int eff =get_effect().roll();
		
	      //bool killed=false;
	      switch(get_type())
		{
		case 0:
		  io_queue_message("you deal %d dmg to the monster with magic",eff);
		  if(charxy(x,y)->hp<=(unsigned)eff)
		  {
		    charxy(x,y)->alive = 0;
		    charxy(x,y) = NULL;
		    if (charxy(x,y) !=(character*) d->PC) {
			 d->num_monsters--;
		       }
		    io_queue_message("It dies");
		  }
		  else
		    {
		      charxy(x,y)->hp-=eff;
		    }
		  break;
		  
		case 1:
		  if(charxy(x,y)->hp>1000)
		    {
		      io_queue_message("You can't heal any more.");
		      continue;
		    }
		  charxy(x,y)->hp+=eff;
		  io_queue_message("you are healed for %d",eff);
		  io_queue_message("your health is %d",caster->hp);
		  break;
		default:
		  break;
		}
	      
	    }
	}
    }
}
spell* find_spell(dungeon *d, std::string name)
{
  unsigned i;
  for(i=0;i<d->spell_descriptions.size();i++)
    {
      if(d->spell_descriptions[i].get_name().compare(name)==0)
	{
	  return d->spell_descriptions[i].generate();
	}
      
    }
  return NULL;
}
