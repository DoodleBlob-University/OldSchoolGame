# OldSchoolGame

## Getting Started

### Requirements
#### sqlite3
`sudo apt-get install sqlite3 libsqlite3-dev`
#### ncurses
`sudo apt-get install libncurses5-dev libncursesw5-dev`
#### g++ version 5+
`sudo apt-get install g++-5`

### Cloning the directory
Navigate to where you want this repository to clone, then type:
`git clone https://github.com/doodleblob/OldSchoolGame`

### Compiling and Running
#### Navigate to the game file
`cd OldSchoolGame/Game`
#### Compile
`g++-5 -std=c++14 game.cpp maptile.cpp terminalfunc.cpp map.cpp window.cpp combatsystem.cpp login.cpp -o game -lncursesw -lsqlite3`
#### Run
`./game`

## References

#### Ncurses
https://invisible-island.net/ncurses/
#### Credit to rubdos for the libsqlitepp C++ library.
https://github.com/glycos/libsqlitepp
