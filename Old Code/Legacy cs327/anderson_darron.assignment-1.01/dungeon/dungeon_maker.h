int main();
void sweep();
void mkBounds();
void printDungeon();
void makeRooms();
typedef struct _room
{
  int x,y;
  int width,height;
}room;
void makeCorridors(int numRooms, room rooms[]);
