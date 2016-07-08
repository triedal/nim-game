# nim-game
A project for Analysis of Algorithms.

## Compiling
Run `make` in the root directory to compile. The binary will be located in the /bin folder.

## Cleaning
If you need to clean the project run `make clean`. This will delete the binary and all object files.

## Structure
This project uses two main classes, State and GameManager. You can think of State as being the three piles and GameManager as the acutal
implementation of the game functions, isWinner, bestMove, main game play, etc.

## Known Issues
* Entering the sequence *1*, *2*, *3* results in a seg fault. However, *3*, *2*, *1* functions fine.

## Debugging
Hopefully you have a favored IDE with a sweet debugger. I did not so I was stuck using [GDB](http://www.yolinux.com/TUTORIALS/GDB-Commands.html).
Running `gdb -tui ./bin/nim` will enter you into the "graphical" debugger. I have created the following functions to assist in
visualizing the data:
* `Util::pV1` - prints the contents of a vector
  * If you are in a breakpoint you can dump the contents of the vector with `call Util::pV1(nameOfVect)`
* `Util::pV2` - prints the contents of a 3x3 vector
  * If you are in a breakpoint you can dump the contents of the vector with `call Util::pV2(nameOfVect)`
* `GameManager::pMemo` - prints the value of a memoized game state
  * If you are in a breakpoint you can dump the contents of the vector with `call pMemo(amtInPile1, amtInPile2, amtInPile3)`
