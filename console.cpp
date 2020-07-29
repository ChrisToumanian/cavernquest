#include "console.h"

Console::Console()
{
  // Initialize ncurses
  initscr();
  noecho();
  curs_set(FALSE);

  // Set colors
  start_color();
  init_pair(1, COLOR_WHITE, COLOR_BLACK); // default
  init_pair(2, 15, 233); // dark grey cave dirt
  init_pair(3, COLOR_BLACK, 239); // light grey rock
  init_pair(4, 15, 160); // red lava
}

void Console::update()
{
  refresh();
}

void Console::clear()
{
  erase();
}

void Console::printChar(int x, int y, char character)
{
  mvaddch(y, x, character);
}

void Console::printCharColor(int x, int y, char character, unsigned char forecolor, unsigned char backcolor)
{
  attron(COLOR_PAIR(forecolor));
  mvaddch(y, x, character);
  attron(COLOR_PAIR(1));
}

void Console::printCharOffset(int x, int y, int offsetX, int offsetY, char character)
{
  mvaddch(y + offsetY, x + offsetX, character);
}

void Console::printCharColorOffset(int x, int y, int offsetX, int offsetY, char character, unsigned char color)
{
  attron(COLOR_PAIR(color));
  mvaddch(y + offsetY, x + offsetX, character);
  attron(COLOR_PAIR(1));
}

void Console::printString(int x, int y, string message)
{
  mvprintw(y, x, message.c_str());
}

char Console::getChar()
{
  return getchar();
}

string Console::getString()
{
  string input;
  echo();
  nocbreak();

  std::string result;
  while(true)
  {
    int c = getch();
    if (c == ERR || c == '\n')
    {
      noecho();
      cbreak();
      return result;
    }
    else result += c; 
  }

  noecho();
  cbreak();
  return "";
}

void Console::exitGame()
{
  // Exit ncurses window
  endwin();

  // Exit program
  exit(0);
}
