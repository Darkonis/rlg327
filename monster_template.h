#ifndef monster_template_h
#define monster_template_h
#include <vector>
#include "dice.h"
#include "character.h"
#include <iostream>
class monster_template
{
 private:
   char symbol;
   dice speed;
  std::vector<std::string> color;
   dice health;
   std::string description;
   dice attack;
   int rarity;
  std::vector<std::string> abilitys;//this can be made dynamic                     
   int num_abilitys=-1;
   std::string name;
 public:
    monster_template();
  void set_symbol(char);
  void set_speed(dice);
  void set_color(std::vector<std::string>);
   void set_health(dice);
   void set_description(std::string);
   void set_attack(dice);
   void set_rarity(int);
  void set_abilitys(std::vector<std::string>,int);
   void set_name(std::string);
   character generate_char();
   void print_template();
     


};





#endif
