#include "monster_template.h"
#include "dice.h"
monster_template::monster_template()
{
  /*  symbol=' ';
  speed=100;
  color="";
  health=dice(10,0,1);
  description="ERROR";
    attack = dice("0+0d0");
  health=dice(1,1,1);
  abilitys=NULL;
  name="shit";
  */
}
void monster_template::set_symbol(char in)
{
  symbol =in;
}
void monster_template::set_speed(dice in)
{
  speed=in;
}
void monster_template::set_color(std::vector<std::string> in)
{
  color=in;
}
void monster_template::set_health(dice in)
{
  health =in;
}
void monster_template::set_description(std::string in)
{
  description = in;
}
void monster_template::set_attack(dice in)
{
  attack=in;
}
void monster_template::set_rarity(int in)
{
  rarity=in;
}
void monster_template::set_abilitys(std::vector<std::string>in,int i)
{
  abilitys=in;
  num_abilitys=i;
}
void monster_template::set_name(std::string in)
{
  name=in;
}
character monster_template::generate_char()
{
  return character(symbol,speed.roll(),color,health.roll(),description,attack.roll(),rarity,abilitys,name);
}
void monster_template::print_template()
{
  std::cout<<"Name: "<< name<<"\n";
  //std::cout<<"Symbol: "<<symbol<<"\n";
  std::cout<<"Description: "<<description<<"\n";
  std::cout<<"Color: ";
  unsigned k;
  for(k=0;k<color.size();k++)
    {
      std::cout<<color[k]<<" ";
    }
  std::cout<<"\n";
  
  std::cout<<"Speed: "<<speed.toString()<<"\n";
   std::cout<<"Abilitys: ";
   int i;
   for(i=0;i<num_abilitys;i++)
    {
      std::cout<<abilitys[i]<<" ";
    }
  std::cout<<"\n";
  std::cout<<"Health: "<<health.toString()<<"\n";
  //std::cout<<"Description: "<<description<<"\n";
  std::cout<<"DMG: "<< attack.toString()<<"\n";
  std::cout<<"Symbol: "<<symbol<<"\n";
  std::cout<<"Rarity: "<<rarity<<"\n";
  /*std::cout<<"Abilitys: ";
  int i;
  for(i=0;i<num_abilitys;i++)
    {
      std::cout<<abilitys[i];
    }
  std::cout<<"\n";
  */
  // std::cout<<"name: "<< name<<"\n";
  abilitys.clear();
  color.clear();
  color.resize(0);
}
