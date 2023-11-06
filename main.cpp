#include <iostream>
#include <string>
#include <random>
#include <vector>
#include <ncurses.h>

struct Player{
    int score = 0;
    int food_amount = 0;
};
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

int title();
void food_gen(Coords &eda, std::vector<Coords> &vec);
void create_snake(std::vector<Coords> &s);
void pole(WINDOW *w, Coords &eda, std::vector<Coords> &vec, Player &p);
DIRECTION ret_dir(char n);
void snake_update(WINDOW *w, DIRECTION d,  Player &p, Coords &eda, bool &game, std::vector<Coords> &vec, int &dif);
void direction_check(char &direct, char &temp_direct);
void difficulty_increase(Player &p, int &d);

int main() {
    initscr();
    int difficulty = title();
    curs_set(0); // делает курсор невидимым
    WINDOW *win = newwin(height, width, start_y, start_x);
    box(win, 0, 0);
    refresh();
    wrefresh(win);
    Player player;
    bool GameOn = true;
    DIRECTION dir;
    char d, td;
    std::vector<Coords> snake_body;
    create_snake(snake_body);
    Coords food_coords{};
    food_gen(food_coords, snake_body);
    pole(win, food_coords, snake_body, player);
    keypad(win, true);
    while(GameOn)
    {
        noecho();
        halfdelay(difficulty);
        d = static_cast<char>(wgetch(win));
        if(d == 'a' || d == 'd' || d == 's' || d == 'w')
        {
            direction_check(d, td);
            td = d;
            dir = ret_dir(d);
        } else
            dir = ret_dir(td);

        snake_update(win, dir, player,food_coords, GameOn, snake_body, difficulty);
        pole(win,food_coords, snake_body, player);
        refresh();
    }

    char c;
    while((c = getch()) != 'q')
    {
        clear();
        printw("Game over!\n");
        printw("Your score is %d!\n", player.score);
        printw("You've eaten %d apples.\n", player.food_amount);
        printw("Press q to quit.\n");
        wrefresh(win);
    }

    getch();
    endwin();
    return 0;
}

int title()
{
    int dif;
    printw("Snake game\n");
    printw("Choose difficulty mode:\na. Easy\nb. Medium.\nc. Hard\n");
    dif = getch();
    switch (dif) {
        case 'a':
            dif = 10;
            break;
        case 'b':
            dif = 6;
            break;
        case 'c':
            dif = 4;
            break;
        default:
            printw("Medium difficulty.\n");
            dif = 6;
            break;
    }
    printw("\nPress enter to start\n");
    char c = getch();
    while(c != '\n')
    {
        printw("\nEnter\n");
        c = getch();
    }

    clear();
    return dif;
}
//используется только в самом начале для создания змейки
void create_snake(std::vector<Coords> &s) {
    Coords snake_head{10, 10};
    Coords snake_tail{10, 11};
    s.push_back(snake_head);
    s.push_back(snake_tail);
}

//не дает змейке врезаться в себя, если направление меняется на противоположное
void direction_check(char &direct, char &temp_direct)
{
    if((temp_direct== 'a' && direct == 'd') || (temp_direct == 'd' && direct == 'a') || (temp_direct == 'w' && direct == 's') || (temp_direct== 's' && direct == 'w'))
        direct = temp_direct;
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

void pole(WINDOW *w, Coords &eda, std::vector<Coords> &vec, Player &p)
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

    mvprintw(21, 1, "You've eaten %d apples.\n", p.food_amount);
    mvprintw(21, 30, "Your score is %d.\n", p.score);
}

DIRECTION ret_dir(char n)
{
    n = static_cast<char>(tolower(n));
    DIRECTION dir;
    switch (n) {
        case 'a':
            dir = LEFT;
            break;
        case 'w':
            dir = UP;
            break;
        case 'd':
            dir = RIGHT;
            break;
        case 's':
            dir = DOWN;
            break;
        default:
            dir = RIGHT;
            break;

    }
    return dir;
}

void snake_update(WINDOW *w, DIRECTION d, Player &p, Coords &eda, bool &game, std::vector<Coords> &vec, int &dif)
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
        ++p.food_amount;
        difficulty_increase(p, dif);
        if(eda.x > 35 || eda.x < 4 || eda.y < 4 || eda.y > 15)
            p.score += 150;
        else
            p.score += 100;
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

void difficulty_increase(Player &p, int &d)
{
    if(p.food_amount > 0 && d > 1 && p.food_amount % 5 == 0)
        --d;
}