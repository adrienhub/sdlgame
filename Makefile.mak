CPP    = g++
WINDRES= windres
RM     = rm -f
OBJS   = main.o \
         game.o \
         object.o \
         AppResource.res

LIBS   = -mwindows -lmingw32 -lSDL2main -lSDL2 -lSDL2_image
CFLAGS = -Iinclude

.PHONY: sldgame.exe clean clean-after

all: sldgame.exe

clean:
	$(RM) $(OBJS) sldgame.exe

clean-after:
	$(RM) $(OBJS)

sldgame.exe: $(OBJS)
	$(CPP) -Wall -s -o $@ $(OBJS) $(LIBS)

main.o: main.cpp game.h
	$(CPP) -Wall -s -c $< -o $@ $(CFLAGS)

game.o: game.cpp game.h
	$(CPP) -Wall -s -c $< -o $@ $(CFLAGS)

object.o: object.cpp object.h
	$(CPP) -Wall -s -c $< -o $@ $(CFLAGS)

AppResource.res: AppResource.rc
	$(WINDRES) -i AppResource.rc -J rc -o AppResource.res -O coff

