# 3단계
## 3단계 개발설계
현재 한단계만 실행 가능한 구조를 개선하기 위해 자료가 저장된 구조를 변경하고, 각 단계를 이터레이터로 돌릴수 있게끔 수정한다. 모든 GOAL 구역이 BOX로 채워지면 다음 단계로 넘어가는 로직을 추가한다. 현재 상태를 표시하는 WINDOW인 info_win을 만든다. info_win에는 현재 스테이지 번호, 현재 스테이지에서 움직인 횟수, 현재 스테이지에서 박스를 민 횟수를 표시한다. Q를 눌렀을때 터미널이 바로 종료되는 것이 아닌, 종료 한다는 메시지를 띄우고 종료하도록 수정한다.

### 1차 수정
- info_win 구현

        #include <ncurses.h>
        #include <clocale>
        #include <memory.h>
        #include "stages.h"

        enum Direction {LEFT, RIGHT, UP, DOWN};
        enum Tile {DEFAULT, WALL, BOX, GOAL, OUTSIDE, CURR};
        enum Pair {P_DEFAULT = 1, P_WALL, P_BOX, P_GOAL, P_OUTSIDE, P_CURR};
        // Enum starts with 1 because We can't assign 0 to COLOR_PAIR palette.
        struct Pos { int y; int x; Direction heading; };

        Pos chk_pos(Direction dir, Pos curr);
        void refr_game(WINDOW* w, Pos curr);
        void refr_info(WINDOW* w);

        int heights[STAGEN] = {7, 9, 6, 7, 8};
        int widths[STAGEN] = {6, 7, 8, 7, 10};

        int arr1_height = 9;
        int arr1_width = 7;

        int curr_arr[9][7];

        int step = 0;
        int push = 0;
        int level = 1;
        bool cleared = false;
        int main() {
            memcpy(curr_arr, stage2, sizeof(stage2));

            setlocale(LC_ALL, ""); // to use unicode

            Pos curr = {2, 2, LEFT}; // y, x, Dir
            WINDOW *game_win;
            WINDOW *info_win;

            initscr();
            keypad(stdscr, TRUE);
            curs_set(0);
            noecho();
            resize_term(40, 40);

            start_color();
            init_pair(P_DEFAULT, COLOR_WHITE, COLOR_WHITE);
            init_pair(P_WALL, COLOR_RED, COLOR_RED);
            init_pair(P_BOX, COLOR_MAGENTA, COLOR_MAGENTA);
            init_pair(P_GOAL, COLOR_YELLOW, COLOR_YELLOW);
            init_pair(P_OUTSIDE, COLOR_BLACK, COLOR_BLACK);
            init_pair(P_CURR, COLOR_WHITE, COLOR_GREEN);

            mvprintw(0, 0, "★PushBox Game☆"); // length = 14
            mvprintw(0, 26, "Press :"); // length = 7
            mvprintw(1, 26, "Q to Exit"); // length = 9
            refresh();

            game_win = newwin(arr1_height, arr1_width*2, 3, 3);
            wbkgd(game_win, COLOR_PAIR(DEFAULT));
            refr_game(game_win, curr);

            info_win = newwin(20, 15, 6, 26);
            wbkgd(game_win, COLOR_PAIR(DEFAULT));
            mvwprintw(info_win, 0, 0, "STEP : ");
            mvwprintw(info_win, 1, 0, "PUSH : ");
            mvwprintw(info_win, 2, 0, "LEVEL");
            refr_info(info_win);

            refresh();

            int chr = 0;
            Pos chk = curr;
            while (chr != 'q' && chr != 'Q') {
                chr = getch();

                if (chr == KEY_LEFT) chk = chk_pos(LEFT, curr);
                else if (chr == KEY_RIGHT) chk = chk_pos(RIGHT, curr);
                else if (chr == KEY_UP) chk = chk_pos(UP, curr);
                else if (chr == KEY_DOWN) chk = chk_pos(DOWN, curr);
                else continue;

                int chk_num = curr_arr[chk.y][chk.x];

                if (chk_num == WALL) continue; // heading to wall
                else if (chk_num == DEFAULT || chk_num == GOAL) {
                    curr.y = chk.y;
                    curr.x = chk.x;
                    refr_game(game_win, curr);
                    step += 1;
                    refr_info(info_win);
                }
                else if (chk_num == BOX) {
                    Pos alt_chk = chk_pos(chk.heading, chk);
                    int alt_chk_num = curr_arr[alt_chk.y][alt_chk.x];

                    if (alt_chk_num == WALL || alt_chk_num == BOX) continue;
                    else if (alt_chk_num == DEFAULT || alt_chk_num == GOAL) {
                        curr_arr[alt_chk.y][alt_chk.x] = BOX;
                        curr_arr[chk.y][chk.x] = DEFAULT;
                        curr.y = chk.y;
                        curr.x = chk.x;
                        refr_game(game_win, curr);
                        step += 1;
                        refr_info(info_win);
                    }
                }
            }

            mvprintw(1, 0, cleared? "You win!" : "Quit game");
            mvprintw(2, 0, "Press any key to quit game");

            getch();
            delwin(game_win);
            endwin();

            return 0;
        }

        Pos chk_pos(Direction dir, Pos curr) {
            Pos chk = {0, 0, LEFT};
            switch (dir) {
                case LEFT:
                    chk.heading = LEFT;
                    chk.y = curr.y;
                    chk.x = curr.x-1;
                    break;
                case RIGHT:
                    chk.heading = RIGHT;
                    chk.y = curr.y;
                    chk.x = curr.x+1;
                    break;
                case UP:
                    chk.heading = UP;
                    chk.y = curr.y-1;
                    chk.x = curr.x;
                    break;
                case DOWN:
                    chk.heading = DOWN;
                    chk.y = curr.y+1;
                    chk.x = curr.x;
                    break;
            }

            return chk;
        }

        void refr_game(WINDOW *w, Pos curr) {
            for(int y=0; y < arr1_height; y++) {
                for(int x=0; x < arr1_width*2; x++) {
                    int n = curr_arr[y][x];
                    wattron(w, COLOR_PAIR(n+1));
                    char *c = new char;
                    sprintf(c, "%d", n);
                    mvwprintw(w, y, (x*2), c);
                    mvwprintw(w, y, (x*2)+1, c);
                    wattroff(w, COLOR_PAIR(n+1));
                    delete c;
                }
            }

            wattron(w, COLOR_PAIR(CURR));
            mvwprintw(w, curr.y, (curr.x*2), "C");
            mvwprintw(w, curr.y, (curr.x*2)+1, "C");
            wattron(w, COLOR_PAIR(CURR));

            wrefresh(w);
            refresh();
        }

        void refr_info(WINDOW *w) {
            char *c = new char;
            sprintf(c, "%d", step);
            mvwprintw(w, 0, 7, c);
            sprintf(c, "%d", push);
            mvwprintw(w, 1, 7, c);
            sprintf(c, "%d", level);
            mvwprintw(w, 2, 6, c);
            delete c;
            wrefresh(w);
        }

- WINDOW* info_win을 만들어 기초적인 설정 후, step, push 변수를 적절한 상황에서만 증가시킨다.

### 2차 수정
- 현재 상태 (curr_status)를 std::vector< std::vector<int> >, 즉 2차원 int형 벡터형으로 바꿨다. 이 변경을 통해 다양한 크기의 stage를 현재 상태로써 만들수 있다.
- 1차 수정 이후로 바뀐 부분만 작성했다.

        #include <vector> // vector 사용을 위해 추가
        
        void refr_game(WINDOW* w, Pos curr, std::vector< std::vector<int> > curr_status);
        // 현재 상태 변수를 main()의 지역 변수로 만들기 위해 함수에 인자 추가

        std::vector< std::vector<int> > curr_status;
        for (int i = 0; i < arr1_height; i++) {
            curr_status.push_back(std::vector<int>());
            for (int j = 0; j < arr1_width; j++)
                curr_status[i].push_back(stage1[i][j]);
        } // memcpy 대신, for문으로 직접 복사. (std::copy를 쓰려 했으나, 사용하지 못했다)

        // 이하 단순 변수 이름 변경

### 최종 수정
- 스테이지를 정수형 배열로 각각 선언했더니, 스테이지를 넘어가는 것을 구현하기 힘들었다. 일단은, 각 배열의 메모리 주소를 배열로 가지고 있는 int* 형 배열 stagep를 만들었다. 각 배열을 (int*)를 통해 명시적 형변환하여 넣었다. 이 때문에 main 코드에서 2차원적으로 값을 찾던 방식을 사용하지 못하고, [y * width + x] 로 index를 찾는 방식을 변경했다.

#### in stages.h
        int* stagep[STAGEN] = {(int*)stage1, (int*)stage2, (int*)stage3, (int*)stage4, (int*)stage5};
#### in main.cpp
        curr_status[i].push_back(stagep[level][i * widths[level]+j]);
        // 등 모든 배열 참조 형식 변경


- 각 색상이 어떤 타일을 뜻하는지 알려주는 정보창을 추가했다.

        attron(COLOR_PAIR(P_BOX));
        mvprintw(4, 26, "  ");
        attroff(COLOR_PAIR(P_BOX));
        mvprintw(4, 28, " is BOX");
        attron(COLOR_PAIR(P_WALL));
        mvprintw(5, 26, "  ");
        attroff(COLOR_PAIR(P_WALL));
        mvprintw(5, 28, " is WALL");
        attron(COLOR_PAIR(P_GOAL));
        mvprintw(6, 26, "  ");
        attroff(COLOR_PAIR(P_GOAL));
        mvprintw(6, 28, " is GOAL");
        attron(COLOR_PAIR(P_CURR));
        mvprintw(7, 26, "  ");
        attroff(COLOR_PAIR(P_CURR));
        mvprintw(7, 28, " is Character");

- 현재 GOAL에 들어오지 못한 상자의 개수를 나타내는 정수형 변수를 만들어, 이 변수가 0일 때 다음 스테이지로 넘어가는 로직을 추가했다.

        if (not_goaled_box <= 0) { // when stage clear
            curr_status.clear();

            wattron(game_win, COLOR_PAIR(P_OUTSIDE));
            for(int y=0; y < heights[level]+1; y++) {
                for (int x = 0; x < widths[level]+1; x++)
                    mvprintw(y + 2, (x * 2) + 2, "    ");
            }
            wattroff(game_win, COLOR_PAIR(P_OUTSIDE));
            refresh();

            level += 1;
            if (level >= STAGEN) {
                cleared = true;
                break;
            }
            step = 0;
            push = 0;

            game_win = newwin(heights[level], widths[level]*2, 3, 3);

            for (int i = 0; i < heights[level]; i++) {
                curr_status.push_back(std::vector<int>());
                for (int j = 0; j < widths[level]; j++)
                    curr_status[i].push_back(stagep[level][i * widths[level]+j]);
            }

            not_goaled_box = boxn[level];
            curr.y = init_curr[level][0];
            curr.x = init_curr[level][1];
            curr.heading = LEFT; // y, x, Dir
            refr_game(game_win, curr, curr_status);
            refr_info(info_win);
        }

- R을 누르면, 현재 스테이지가 0으로 초기화되는 기능을 넣었다.

        else if (chr == 'r' || chr == 'R') {
            step = 0;
            push = 0;
            not_goaled_box = boxn[level];

            curr_status.clear();
            for (int i = 0; i < heights[level]; i++) {
                curr_status.push_back(std::vector<int>());
                for (int j = 0; j < widths[level]; j++)
                    curr_status[i].push_back(stagep[level][i * widths[level]+j]);
            }

            curr.y = init_curr[level][0];
            curr.x = init_curr[level][1];
            curr.heading = LEFT; // y, x, Dir
            refr_game(game_win, curr, curr_status);
            refr_info(info_win);
            continue;
        }

- 상자가 지나가면 GOAL이 DEFAULT로 변경되는 오류를 수정했다.
        curr_status[chk.y][chk.x] = (stagep[level][chk.y*widths[level]+chk.x] == GOAL) ?
            stagep[level][chk.y*widths[level]+chk.x]
            : DEFAULT;


- COLOR_GREEN이 적용되지 않는 것은 단순히 변수를 잘못 넣어 있던 오류였고, 수정했다.
        wattron(w, COLOR_PAIR(P_CURR));
