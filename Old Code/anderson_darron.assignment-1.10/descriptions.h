#ifndef DESCRIPTIONS_H
# define DESCRIPTIONS_H

# include <cstdint>
# include <vector>
# include <string>

//#include "character.h"
# include "dice.h"
# include "npc.h"
//# include "spell.h"
uint32_t parse_descriptions(dungeon *d);
uint32_t print_descriptions(dungeon *d);
uint32_t destroy_descriptions(dungeon *d);
//class spell;
typedef enum object_type {
  objtype_no_type,
  objtype_WEAPON,
  objtype_OFFHAND,
  objtype_RANGED,
  objtype_LIGHT,
  objtype_ARMOR,
  objtype_HELMET,
  objtype_CLOAK,
  objtype_GLOVES,
  objtype_BOOTS,
  objtype_AMULET,
  objtype_RING,
  objtype_SCROLL,
  objtype_BOOK,
  objtype_FLASK,
  objtype_GOLD,
  objtype_AMMUNITION,
  objtype_FOOD,
  objtype_WAND,
  objtype_CONTAINER
} object_type_t;
typedef enum spell_school{ // this isn't used use it as a guide 
   destruction,//dmg
   restoration, //healing
   alteration, //stat change
   divination, //looking around
  } spell_school_t;
extern const char object_symbol[];
class npc;

class monster_description {
 private:
  std::string name, description;
  char symbol;
  std::vector<uint32_t> color;
  uint32_t abilities;
  dice speed, hitpoints, damage;
  uint32_t rarity;
  uint32_t num_alive, num_killed;
  inline bool can_be_generated()
  {
    return (((abilities & NPC_UNIQ) && !num_alive && !num_killed) ||
            !(abilities & NPC_UNIQ));
  }
  inline bool pass_rarity_roll()
  {
    return rarity > (unsigned) (rand() % 100);
  }

 public:
  monster_description() : name(),       description(), symbol(0),   color(0),
                          abilities(0), speed(),       hitpoints(), damage(),
                          rarity(0), num_alive(0), num_killed(0)
  {
  }
  void set(const std::string &name,
           const std::string &description,
           const char symbol,
           const std::vector<uint32_t> &color,
           const dice &speed,
           const uint32_t abilities,
           const dice &hitpoints,
           const dice &damage,
           const uint32_t rarity);
  std::ostream &print(std::ostream &o);
  char get_symbol() { return symbol; }
  static npc *generate_monster(dungeon *d);
  inline void birth()
  {
    num_alive++;
  }
  inline void die()
  {
    num_killed++;
    num_alive--;
  }
  inline void destroy()
  {
    num_alive--;
  }
  friend npc;
  friend bool boss_is_alive(dungeon *d);
};

class object_description {
 private:
  std::string name, description;
  object_type_t type;
  uint32_t color;
  dice hit, damage, dodge, defence, weight, speed, attribute, value;
  bool artifact;
  uint32_t rarity;
  uint32_t num_generated;
  uint32_t num_found;
 public:
  object_description() : name(),    description(), type(objtype_no_type),
                         color(0),  hit(),         damage(),
                         dodge(),   defence(),     weight(),
                         speed(),   attribute(),   value(),
                         artifact(false), rarity(0), num_generated(0),
                         num_found(0)
  {
  }
  inline bool can_be_generated()
  {
    return !artifact || (artifact && !num_generated && !num_found);
  }
  inline bool pass_rarity_roll()
  {
    return rarity > (unsigned) (rand() % 100);
  }
  void set(const std::string &name,
           const std::string &description,
           const object_type_t type,
           const uint32_t color,
           const dice &hit,
           const dice &damage,
           const dice &dodge,
           const dice &defence,
           const dice &weight,
           const dice &speed,
           const dice &attrubute,
           const dice &value,
           const bool artifact,
           const uint32_t rarity);
  void set(const std::string &name,
           const std::string &description,
           const object_type_t type,
           const uint32_t color,
            dice &hit,
            dice &damage,
            dice &dodge,
            dice &defence,
            dice &weight,
            dice &speed,
            dice &attrubute,
            dice &value,
           const bool artifact,
           const uint32_t rarity);

  std::ostream &print(std::ostream &o);
  /* Need all these accessors because otherwise there is a *
   * circular dependancy that is difficult to get around.  */
  inline const std::string &get_name() const { return name; }
  inline const std::string &get_description() const { return description; }
  inline const object_type_t get_type() const { return type; }
  inline const uint32_t get_color() const { return color; }
  inline const dice &get_hit() const { return hit; }
  inline const dice &get_damage() const { return damage; }
  inline const dice &get_dodge() const { return dodge; }
  inline const dice &get_defence() const { return defence; }
  inline const dice &get_weight() const { return weight; }
  inline const dice &get_speed() const { return speed; }
  inline const dice &get_attribute() const { return attribute; }
  inline const dice &get_value() const { return value; }
  inline void generate() { num_generated++; }
  inline void destroy() { num_generated--; }
  inline void find() { num_found++; }
};
class spell_description
{
private:
  std::string name, description;
  int type=1; //this is meant to define spell types eg healing destruction
  bool special;//unique spells if nessasary
  dice effect;//not strictly dmg could be healing
  uint32_t cost;//how much mana does this spell cost to use
  uint32_t range;
  uint32_t aoe; //how much area does this spell affect in a grid
  uint32_t rarity;
  uint32_t num_generated=0;
public:
  spell* generate();
   bool pass_rarity_roll()
  {
    return rarity >(unsigned) (rand() % 100);
  }
  std::string get_name(){return name;}
  std::string get_description(){return description ;}
  uint32_t get_type(){return type;}
  bool get_special() {return special;}
  uint32_t get_effects() {return effect.roll();}
  uint32_t get_cost() {return cost;}
  uint32_t get_range(){return range;}
  uint32_t get_aoe(){return aoe;}
  uint32_t get_rarity() {return rarity;}
   std::ostream &print(std::ostream &o);
  void set(std::string name,std::string description,int type,bool special,dice effect,uint32_t cost,uint32_t range,uint32_t aoe,uint32_t rarity);
};
std::ostream &operator<<(std::ostream &o, monster_description &m);
std::ostream &operator<<(std::ostream &o, object_description &od);
std::ostream &operator<<(std::ostream &o, spell_description &s);
#endif
