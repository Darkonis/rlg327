#ifndef SPELL_H
# define SPELL_H
# include <stdint.h>
# include <vector>
# include <cstdlib>
# include <stdio.h>
#include <unistd.h>
#include <string>
#include "dims.h"
//#include "descriptions.h"
//#include "dungeon.h"
# include "dice.h"
//#include "descriptions.h"
class dungeon;
class dice;
class character;
class spell {
 private:
   std::string name, description;
  int type; //this is meant to define spell types eg healing destruction     
  bool special;//unique spells if nessasary                                    
  dice effect;//not strictly dmg could be healing                              
  uint32_t cost;//how much mana does this spell cost to use                    
  uint32_t range;
  uint32_t aoe; //how much area does this spell affect in a grid               
  uint32_t rarity;
 public:
  std::string get_name(){return name;}
  std::string get_description() {return description;}
  dice get_effect(){return effect;}
  //int dmg(){return effect.roll();}
  uint32_t get_cost(){return cost;}
  uint32_t get_range(){return range;}
  uint32_t get_aoe(){return aoe;}
  int get_type(){return type;}
  spell(std::string name,std::string description,int type,bool special,dice effect,uint32_t cost,uint32_t range,int aoe,uint32_t rarity);
  void set(std::string name,std::string description,int type,bool special,dice effect,uint32_t cost,uint32_t range,int aoe,uint32_t rarity);
  void cast(dungeon *d,pair_t tar,character* caster);


};
spell* find_spell(dungeon *d, std::string to_find);
#endif
