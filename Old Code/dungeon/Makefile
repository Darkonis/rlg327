main: dungeon_maker.o
	gcc dungeon_maker.o -o main 
dungeon_maker.o: dungeon_maker.c
	gcc -c dungeon_maker.c -Wall -Werror -ggdb -o dungeon_maker.o
#f2c.o: f2c.c cf.h
 #       gcc -c f2c.c -Wall -Werror -ggdb -o f2c.o

clean:
	rm -f dungeon main *~ 
