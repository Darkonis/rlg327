#include <fstream>
#include <vector>
#include "parser_monsters.h"
#include "monster_template.h"
#include <iostream>
#include <fstream>
int parse(dungeon *d)
{
  std::string home;
  home=getenv("HOME");
  std::string local;
  local ="/.rlg327/monster_desc.txt";
  // std::cout<<home<<local<<"\n";
  std::ifstream read(home+local);
  
  //read.open(filename);
  std::string check;
  //std::cout<<read.is_open()<<"\n";
    
  getline(read,check);
  if(check.compare(metaline)!=0)
    {
      return -1; //the file dosn't have the metaline exit and tell the main program
    }
  // d->valid_mon=(monster_template*)malloc(sizeof(monster_template));
  for(std::string line;std::getline(read,line);)
    {
      if(!line.compare(start))//if its time to start a monster is about to start
	{
	  d->num_possible++;
	  
	  monster_template a= monster_template();
	  //std::cout<<sizeof(a)<<"\n";
	  //std::cout<<d->num_possible<<"\n";
	  // d->valid_mon.push_back(a);
	  //std::cout<<sizeof(*(d->valid_mon))<<"\n";

	  bool valid=true;
	  //dynamicly adjust the size of valid mon
	  while(line.compare(stop)!=0)
	    {
	      std::getline(read,line);
	      //std::string tmp;
	      std::string tmp=(line.substr(0,line.find(" ")));
	      line =line.substr(line.find(" ")+1);
	      switch(isKeyword(tmp))
		{
		case -1://if not a keyword continue
		  break;
		case 0://name
		  a.set_name(line);
		  //std::cout<<line<<"\n";
		    break;
		case 1://desc
		  { std::string des;
		     
		    while(line.compare(".")!=0)//while the description is still going
		      {
			std::getline(read,line);
			if(line.length()>=78)
                        {
			  // std::cout<<des.length()<<"des\n";
                          valid=false;
			}
			des=des+line+"\n";
		      }
		    // std::cout<<des<<"\n";
		    a.set_description(des);
		  }
		    break;
		case 2://color
		  //a.set_color(line.substr(line.find(" ")+1));
		  //int num_abilitys=-1;
                  { std::vector<std::string> colorL;
		  while(line.compare("")!=0)
                    {
                      std::string tmp2="";
                      if(line.find(" ")==std::string::npos)
                        {
                          tmp2=line.substr(0,line.size());
                        }
                      else
                        {
                          tmp2=(line.substr(0,line.find(" ")));
                        }
		      // if(isColor(tmp2))
		      if(true)
		      {
                          colorL.push_back(tmp2);
                        }
                      if(line.find(" ")==std::string::npos)
                        {
			  a.set_color(colorL);
			  // colorL.push_back(line);
                          line="";
                          break;
                        }
                      else
                        {
                           line=line.substr(line.find(" ")+1);
                        }
                      //std::cout<<line<<"2\n";                                                                                                                                                             
                      a.set_color(colorL);
                    }
                  }
		  break;
		case 3://speed
		  a.set_speed(dice(line.substr(line.find(" ")+1)));
		  // std::cout<<line.substr(line.find(" ")+1)<<" :S\n";
		  break;
		case 4://abilitys
		  {
		   int num_abilitys=-1;
		   std::vector<std::string> abilityL;
		   // abilityL=std::string*)malloc(1);
		   //line = line.substr(line.find(" ")+1);
		   while(line.compare("")!=0)
		    {
		      std::string tmp2="";
		      if(line.find(" ")==std::string::npos)
			{
			  tmp2=line.substr(0,line.size()); 
			}
		      else
			{
			  tmp2=(line.substr(0,line.find(" ")));
			}
		      if(isAbility(tmp2))
		      //if(true)
		      {
			  num_abilitys++;			  
			  abilityL.push_back(tmp2);
			}
		      if(line.find(" ")==std::string::npos)
			{
			  a.set_abilitys(abilityL,num_abilitys);
			  line="";
			  break;
			}
		      else
			{
			   line=line.substr(line.find(" ")+1);
			}
		      //std::cout<<line<<"2\n";
		      a.set_abilitys(abilityL,num_abilitys);
		    }
		  }
		  break;
		case 5://hp this is a dice
		  a.set_health(dice(line.substr(line.find(" ")+1)));
		  //std::cout<<line.substr(line.find(" ")+1)<<" :h\n";
		  break;
		case 6: //dmg
		  a.set_attack(dice(line.substr(line.find(" ")+1)));
		  //std::cout<<line.substr(line.find(" ")+1)<<" :d\n";
		    break;
		case 7:
		  a.set_symbol(line.substr(line.find(" ")+1).c_str()[0]);//check
		  break;
		case 8:
		  {
		    a.set_rarity(atoi(line.substr(line.find(" ")+1).c_str()));
		    //std::cout<<line.substr(line.find(" ")+1)<<"r\n";
		    break;

		  }
		}
	      
	    
	    }
	  if(valid)
	    {
	      d->valid_mon.push_back(a);
	    }
	  else
	    {
	      d->num_possible--;
	    }
       }


    }
  return 0;
}
void print(dungeon *d)
{
     
}
int isKeyword(std::string in)//detects if some string is a valid keyword
{
  uint32_t i;
  for(i=0;i<(sizeof(keywords)/sizeof(std::string));i++)
    {
      if(!in.compare(keywords[i]))
	{
	  return i;
	}
    }
  return -1;

}
bool isAbility(std::string in)
{
  uint32_t i;
  for(i=0;i<sizeof(abilitys)/sizeof(std::string);i++)
    {
      if(in.compare(abilitys[i])==0)
	{
	  return true;
	}
    }
  return false;
}
bool isColor(std::string in)
{
  uint32_t i;
  for(i=0;i<sizeof(abilitys)/sizeof(std::string);i++)
    {
      if(in.compare(colors[i])==0)
        {
          return true;
        }
    }
  return false;

}
