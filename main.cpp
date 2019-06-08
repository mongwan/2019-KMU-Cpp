#include <ncurses.h>
#include <clocale>

enum {P_DEFAULT = 1, P_WALL, P_BOX, P_GOAL, P_OUTSIDE};
// Enum starts with 1 because We can't assign 0 to COLOR_PAIR palette.

int main() {
    setlocale(LC_ALL, ""); // to use unicode

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

    init_pair(P_DEFAULT, COLOR_WHITE, COLOR_WHITE);
    init_pair(P_WALL, COLOR_RED, COLOR_RED);
    init_pair(P_BOX, COLOR_MAGENTA, COLOR_MAGENTA);
    init_pair(P_GOAL, COLOR_YELLOW, COLOR_YELLOW);
    init_pair(P_OUTSIDE, COLOR_BLACK, COLOR_BLACK);

    mvprintw(0, 0, "PushBox Game");
    refresh();

    game_win = newwin(arr1_height, arr1_width*2, 3, 3);
    wbkgd(game_win, COLOR_PAIR(P_DEFAULT));
    for(int y=0; y < arr1_height; y++) {
        for(int x=0; x < arr1_width*2; x++) {
            int n = arr1[y][x];
            wattron(game_win, COLOR_PAIR(n+1));
            char *c = new char;
            sprintf(c, "%d", n);
            mvwprintw(game_win, y, (x*2), c);
            mvwprintw(game_win, y, (x*2)+1, c);
            wattroff(game_win, COLOR_PAIR(n+1));
            delete c;
        }
    }
    wrefresh(game_win);
    refresh();

    getch();
    delwin(game_win);
    endwin();

    return 0;
}