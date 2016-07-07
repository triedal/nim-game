CC = g++
CFLAGS = -Wall -g
OBJECTS =  $(patsubst %.o, obj/%.o, Main.o State.o GameManager.o)
OBJDIR = obj

nim : $(OBJECTS)
	@[ -d bin ] || mkdir bin
	@$(CC) $(CFLAGS) $(OBJECTS) -o ./bin/nim
	@echo "Complete!"

$(OBJDIR)/Main.o : src/main.cpp
	@[ -d obj ] || mkdir obj
	@$(CC) $(CFLAGS) -c src/main.cpp -o obj/Main.o

$(OBJDIR)/State.o : src/Game/State.cpp src/Game/State.h
	@[ -d obj ] || mkdir obj
	@$(CC) $(CFLAGS) -c src/Game/State.cpp -o obj/State.o

$(OBJDIR)/GameManager.o : src/GameManager/GameManager.cpp src/GameManager/GameManager.h
	@[ -d obj ] || mkdir obj
	@$(CC) $(CFLAGS) -c src/GameManager/GameManager.cpp -o obj/GameManager.o

clean:
	@rm ./bin/nim ./obj/*
	@echo "Clean finished."