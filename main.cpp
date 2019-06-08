#include <ncurses.h>
#include <clocale>
#include <cstring>
#include <iostream>

enum {P_DEFAULT, P_WALL, P_BOX, P_GOAL, P_OUTSIDE};

int main() {
    setlocale(LC_ALL, "");

    int arr1[9][7] = {
            {1, 1, 1, 1, 4, 4, 4},
            {1, 3, 0, 1, 1, 4, 4},
            {1, 3, 0, 0, 1, 4, 4},
            {1, 3, 0, 2, 1, 4, 4},
            {1, 1, 2, 0, 1, 1, 1},
            {4, 1, 0, 2, 0, 0, 1},
            {4, 1, 0, 0, 0, 0, 1},
            {4, 1, 0, 0, 1, 1, 1},
            {4, 1, 1, 1, 1, 4, 4}
    };
    int arr1_height = 9;
    int arr1_width = 7;

    WINDOW *game_win;

    initscr();
    resize_term(30, 25);

    start_color();
    init_color(COLOR_RED, 1000, 500, 500);
    init_color(COLOR_BLUE, 0, 0, 1000);
    init_color(COLOR_YELLOW, 500, 500, 500);
    init_pair(P_DEFAULT, COLOR_WHITE, COLOR_BLACK);
    init_pair(P_WALL, COLOR_WHITE, COLOR_RED);
    init_pair(P_BOX, COLOR_WHITE, COLOR_BLUE);
    init_pair(P_GOAL, COLOR_WHITE, COLOR_YELLOW);
    init_pair(P_OUTSIDE, COLOR_BLACK, COLOR_WHITE);

    mvprintw(0, 0, "PushBox Game");
    refresh();

    game_win = newwin(arr1_height+2, arr1_width+2, 3, 3);
    wbkgd(game_win, COLOR_PAIR(P_DEFAULT));
    wattron(game_win, COLOR_PAIR(P_OUTSIDE));
    wborder(game_win, '@', '@', '@', '@', '@', '@', '@', '@');
    for(int y=0; y < arr1_height; y++) {
        for(int x=0; x < arr1_width; x++) {
            int n = arr1[y][x];
            wattron(game_win, COLOR_PAIR(n));
            char c[1];
            sprintf(c, "%d", n);
            mvwprintw(game_win, y+1, x+1, c);
            wattroff(game_win, COLOR_PAIR(n));
        }
    }
    wrefresh(game_win);
    refresh();

    getch();
    delwin(game_win);
    endwin();

    return 0;
}