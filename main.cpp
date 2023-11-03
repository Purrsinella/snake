#include <iostream>
#include <string>
#include <random>
#include <vector>
#include <ncurses.h>

struct Coords {
    int x;
    int y;
};

int height = 20;
int width = 40;
int start_y = 1;
int start_x = 1;

enum DIRECTION {
    LEFT, UP, RIGHT, DOWN
};

void title();
void food_gen(Coords &eda, std::vector<Coords> &vec);
void create_snake(std::vector<Coords> &s);
void pole(WINDOW *w, Coords &eda, std::vector<Coords> &vec);
DIRECTION ret_dir(char n);
void snake_update(WINDOW *w, DIRECTION d, Coords &eda, bool &game, std::vector<Coords> &vec);

int main() {
    initscr();
    title();
    curs_set(0); // делает курсор невидимым
    WINDOW *win = newwin(height, width, start_y, start_x);
    box(win, 0, 0);
    refresh();
    wrefresh(win);
    bool GameOn = true;
    DIRECTION dir;
    char d, td;
    std::vector<Coords> snake_body;
    create_snake(snake_body);
    Coords food_coords{};
    food_gen(food_coords, snake_body);
    pole(win, food_coords, snake_body);
    keypad(win, true);
    while(GameOn)
    {
        noecho();
        halfdelay(5);
        d = static_cast<char>(wgetch(win));
        if(d == 'a' || d == 'd' || d == 's' || d == 'w')
        {
            td = d;
            dir = ret_dir(d);
        } else
            dir = ret_dir(td);

        snake_update(win, dir, food_coords, GameOn, snake_body);
        pole(win,food_coords, snake_body);
        refresh();
    }

    clear();
    printw("Game over!\n");
    wrefresh(win);
    getch();
    endwin();
    return 0;
}

void title()
{
    printw("Snake game\n");
    printw("Press enter to start\n");
    char c = getch();
    while(c != '\n')
    {
        printw("\nEnter\n");
        c = getch();
    }

    clear();
    return;
}
//используется только в самом начале для создания змейки
void create_snake(std::vector<Coords> &s) {
    Coords snake_head{10, 10};
    Coords snake_tail{10, 11};
    s.push_back(snake_head);
    s.push_back(snake_tail);
}

void food_gen(Coords &eda, std::vector<Coords> &vec) {
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist(1, 38);
    std::uniform_int_distribution<std::mt19937::result_type> dist2(1, 18);
    eda.x = dist(rng);
    eda.y = dist2(rng);
    for(int i = 0; i < vec.size(); ++i) {
        if (eda.x == vec[i].x && eda.y == vec[i].y)
            food_gen(eda, vec);
    }
}

void pole(WINDOW *w, Coords &eda, std::vector<Coords> &vec)
{
    werase(w);
    box(w, 0, 0);

    mvwprintw(w, eda.y, eda.x, "F");

    mvwprintw(w, vec[0].y, vec[0].x, "X");

    for(int i = 1; i < vec.size()-1; ++i)
    {
        mvwprintw(w, vec[i].y, vec[i].x, "x");
    }


    mvwprintw(w, vec[vec.size()-1].y, vec[vec.size()-1].x, "i");

    wrefresh(w);
}

DIRECTION ret_dir(char n)
{
    n = static_cast<char>(tolower(n));
    DIRECTION dir;
    switch (n) {
        case 'a':
            //case KEY_LEFT:
            dir = LEFT;
            break;
        case 'w':
            //case KEY_UP:
            dir = UP;
            break;
            //case KEY_RIGHT:
        case 'd':
            dir = RIGHT;
            break;
        case 's':
            //case KEY_DOWN:
            dir = DOWN;
            break;
        default:
            dir = RIGHT;
            break;

    }
    return dir;
}

void snake_update(WINDOW *w, DIRECTION d, Coords &eda, bool &game, std::vector<Coords> &vec)
{
    Coords temp = vec[0];

    if(d == UP)
        --temp.y;
    else if(d == LEFT)
        --temp.x;
    else if(d == RIGHT)
        ++temp.x;
    else if(d == DOWN)
        ++temp.y;

    if((eda.x == temp.x) && (eda.y == temp.y))
    {
        food_gen(eda, vec);
        vec.insert(vec.begin(), temp);
    }
    else
    {
        std::vector <Coords>temp_vec;
        temp_vec = vec;
        vec[0] = temp;
        for(int i = 1; i < vec.size(); ++i)
            vec[i] = temp_vec[i-1];
        temp_vec.erase(temp_vec.begin(), temp_vec.end());
    }

    if(temp.x == 0 || temp.y == 0 || temp.x == width-1 || temp.y == height)
        game = false;

    for(int k = 1; k < vec.size(); ++k)
    {
        if(vec[0].x == vec[k].x && vec[0].y == vec[k].y)
            game = false;
    }
}