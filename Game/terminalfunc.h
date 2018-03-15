//Charles Barry
#ifndef TERMINALFUNC_H
#define TERMINALFUNC_H

class TerminalFunctions{//Charles Barry
private:
  WINDOW* stat;
  WINDOW* term;
  int windowWidth;
public:
  int getWindowWidth(){return windowWidth;}
  void printTerminalText(std::string text);
  WINDOW* getStat(){return stat;}
  std::string getUserInput();
  bool getUserYN();
  void eraseTerminal();
  TerminalFunctions(WINDOW* _stat, WINDOW* _term, int _windowWidth);
};

#endif
