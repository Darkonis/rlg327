#ifndef ITEM_H
# define ITEM_H
# include <stdint.h>
# undef swap
#include <string>
#include "dice.h"
#include "descriptions.h"
//typedef enum object_type object_type_t; 
class item{
 public:
  std::string name, description;
  pair_t position;
  //object_type_t type;
   char symbol;
  uint32_t color;
  uint32_t hit, dodge, defence, weight, speed, attribute, value;
  dice damage;
  bool artifact;

};
void gen_items(dungeon *d);




#endif
