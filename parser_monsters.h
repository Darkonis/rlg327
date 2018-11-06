#ifndef PARSER_MONSTERS_H
#define PARSER_MONSTERS_H
#include <iostream>
#include "dungeon.h"
#include "character.h"
#include "dice.h"
#include "monster_template.h"
const std::string start="BEGIN MONSTER";
const std::string stop = "END";
const std::string keywords[]={"NAME","DESC","COLOR","SPEED","ABIL","HP","DAM","SYMB","RRTY"};
const std::string abilitys[]={"SMART","TELE","ERRATIC","TUNNEL","PASS","PICKUP","DESTROY","UNIQ","BOSS"};
const std::string metaline="RLG327 MONSTER DESCRIPTION 1";
const std::string colors[]={"RED","GREEN", "BLUE", "CYAN", "YELLOW", "MAGENTA", "WHITE", "BLACK"};//todo
int parse(dungeon *d);
void print(dungeon *d);
int isKeyword(std::string in);
bool isAbility(std::string in);
bool isColor(std::string in);


#endif
