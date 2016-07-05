all:
	@[ -d bin ] || mkdir bin
	@g++ -o ./bin/nim ./src/**/*.cpp
	@echo "Complete!"

clean:
	@rm ./bin/nim
	@echo "Clean finished."