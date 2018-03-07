# OldSchoolGame

Discord: https://discord.gg/j2b8Aue
Kanban Chart: https://goo.gl/NY8UXm

## Getting Started

```
git clone https://github.coventry.ac.uk/barryc2/OldSchoolGame/
cd OldSchoolGame

sudo apt-get install sqlite3 libsqlite3-dev
sudo apt-get install libncurses5-dev libncursesw5-dev

g++ -std=c++14 *filename*.cpp -o *filename* -lncursesw -lsqlite3
./*filename*
```
Some code may need 2 files to be compiled at once.
For this, simply add more files to the terminal command as demonstrated below:
```
g++ -std=c++14 *filename*.cpp *filename2*.cpp -o *filename* -lncursesw -lsqlite3
```
