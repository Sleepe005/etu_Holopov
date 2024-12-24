#include <locale.h>
#include <ncurses.h>
#include "workWithData.h"
#include "workWithDate.h"
#include "menu.h"

int main(){
    // Установка языка, инициализация окна и цветов
    setlocale(LC_ALL, "");
    initscr();
    start_color();
    init_pair(1, COLOR_BLACK, COLOR_RED);
    init_pair(2, COLOR_BLACK, COLOR_MAGENTA);
    bkgd(COLOR_PAIR(2));
    attrset(COLOR_PAIR(1));

    menuFunc();

    endwin();
    return 0;
}