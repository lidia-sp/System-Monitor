#include "ncurses_display.h"
#include "system.h"

#include "linux_parser.h"
#include "format.h"
#include <numeric>

int main() {
  System system;
    
NCursesDisplay::Display(system);
}