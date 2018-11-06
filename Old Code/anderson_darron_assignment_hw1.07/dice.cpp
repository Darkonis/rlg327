#include "dice.h"
#include <iostream>
dice::dice()
{

}
dice::dice(unsigned int sides,unsigned int dice,unsigned int base)
{
  this->sides=sides;
  num_dice=dice;
  this->base=base;
}
dice::dice(unsigned int sides)
{
  this->sides=sides;
  }
dice::dice(std::string s)
{
  std::size_t found = s.find("d");
  if(found==std::string::npos)
    {
      std::cout<<s<<"\n";
      std::cout<<"error parsing"<<"\n";
      // return -1;
    }
  else
    {
      base = std::stoi(s.substr(0,s.find("+")));
      num_dice = std::stoi(s.substr(s.find("+")+1,s.find("d")));
      sides=std::stoi(s.substr(s.find("d")+1));
      // std::cout<<base<<"+"<<num_dice<<"d"<<sides<<"\n";
    }

}

//remove later if needed

int dice::roll()
{
  if(num_dice!=-1)
    {
      return-1;//error handling
    }
  int i=0;
  int sum=0;
  for(i=0;i<num_dice;i++)
    {
      sum+=rand()%sides+1;
    }
  return sum;
}
int dice::roll(unsigned num)
{
  unsigned int i;
  int sum=0;
  for(i=0;i<num;i++)
    {
      sum+=rand()%sides+1;
    }
  return sum;
}
int roll(unsigned num,unsigned sides)
{
  unsigned int i;
  int sum=0;
  for(i=0;i<num;i++)
    {
      sum+=rand()%sides+1;
    }
  return sum;
}
std::string dice::toString()
{
  std::string out = std::to_string( base);// + " + "+ num_dice+'d'+sides;
  out+="+";
  out+= std::to_string(num_dice);
  out+= "d";
  out+=std::to_string(sides);
  out+= " Expected: ";
    out+=std::to_string(base+num_dice*(.5*(sides+1)));
  //std::cout<<base<<" + "<<num_dice<<" d "<<sides<<"\n"; 
  //std::cout<<out<<"out\n";
  return out;
}
