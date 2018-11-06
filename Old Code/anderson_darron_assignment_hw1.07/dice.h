#ifndef DICE_H
#define DICE_H
#include <iostream>
#include <string.h>
class dice
{
 private:
  int sides=-1;
  int num_dice=-1;
  int base=-1;
  //std::string mem_var;
public:
  dice(unsigned int,unsigned int,unsigned int);
  dice(unsigned int);
  //std::string mem_var;
  dice(std::string);
  dice();
  int roll();
  int roll(unsigned int);
  std::string toString();
  //  std::string mem_var;

};
/*dice::dice(unsigned int in_sides,unsigned int dice)
{
  sides=in_sides;
  num_dice=dice;
}
dice::dice(unsigned int in_sides)
{
  sides=in_sides;
}
*/
//int  dice::dice(String s);
//dice::dice(std::string);

int roll(unsigned num,unsigned sides);

#endif  
