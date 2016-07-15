CC = g++
CFLAGS = -Wall -g
OBJECTS =  $(patsubst %.o, obj/%.o, Main.o State.o GameManager.o Util.o)
OBJDIR = obj
TARGET = threepile

nim : $(OBJECTS)
	@[ -d bin ] || mkdir bin
	@$(CC) $(CFLAGS) $(OBJECTS) -o ./bin/$(TARGET)
	@echo "Complete!"
	@echo "Binary located at /bin/threepile."

$(OBJDIR)/Main.o : src/main.cpp
	@[ -d obj ] || mkdir obj
	@$(CC) $(CFLAGS) -c src/main.cpp -o obj/Main.o

$(OBJDIR)/State.o : src/Game/State.cpp src/Game/State.h
	@[ -d obj ] || mkdir obj
	@$(CC) $(CFLAGS) -c src/Game/State.cpp -o obj/State.o

$(OBJDIR)/GameManager.o : src/GameManager/GameManager.cpp src/GameManager/GameManager.h
	@[ -d obj ] || mkdir obj
	@$(CC) $(CFLAGS) -c src/GameManager/GameManager.cpp -o obj/GameManager.o

$(OBJDIR)/Util.o : src/Util/Util.cpp src/Util/Util.h
	@[ -d obj ] || mkdir obj
	@$(CC) $(CFLAGS) -c src/Util/Util.cpp -o obj/Util.o

clean:
	@rm ./bin/$(TARGET) ./obj/*
	@echo "Clean finished."
