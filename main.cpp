#include <iostream>
#include <string>
#include <random>
#include <vector>
#include <curses.h>
#include <ncurses.h>

struct Coords{
    int x;
    int y;
};

int height = 20;
int width = 40;

void food_gen(Coords &eda);
enum DIRECTION {LEFT, UP, RIGHT, DOWN};
void pole(std::string s, char f, Coords &eda, std::vector<Coords> &vec);
DIRECTION ret_dir(char n);
void snake_update(DIRECTION d, Coords &eda, std::string &s, bool &game, std::vector<Coords> &vec);
int main() {
    bool  GameOn = true;
    DIRECTION dir;
    Coords snake_head{10, 10};
    Coords snake_tail{10, 11};
    std::vector<Coords> snake_body;
    snake_body.push_back(snake_head);
    snake_body.push_back(snake_tail);
    Coords food_coords{};
    food_gen(food_coords);
    char Food = 'F';
    std::string snake = "Xi";
    pole(snake, Food, food_coords, snake_body);
    char d;
    while(GameOn)
    {
        std::cout << "Enter smth.\n";
        std::cin >> d;
        while(std::cin.get() !='\n')
            continue;
        dir = ret_dir(d);
        std::cout << std::flush;
        snake_update(dir, food_coords, snake, GameOn, snake_body);
        pole(snake, Food, food_coords, snake_body);
    }

    std::cout << "Game over!\n";
    return 0;
}

void pole(std::string s, char f, Coords &eda, std::vector<Coords> &vec)
{

    for (int i = 0; i < width + 2; i++)
        std::cout << "-";
    std::cout << std::endl;
    for(int i = 0; i < height; ++i)
    {
        int j;
        for(j = 0; j <= width; ++j)
        {
            if (j == 0 || j == width)
                std::cout << "|";
            bool prTail = false; //я не знаю, для чего оно, но без него строка с пробелами печатается
            for(int k = 0; k < vec.size(); ++k)
            {
                if(i == vec[k].x && j == vec[k].y) {
                    std::cout << s[k];
                    prTail = true;
                }
            }

            if(i == eda.x && j == eda.y)
                std::cout << f;
            else if(!prTail)
                std::cout << " ";
        }
        std::cout << std::endl;
    }
    for (int i = 0; i < width + 2; i++)
        std::cout << "-";
    std::cout << std::endl;
}

DIRECTION ret_dir(char n)
{
    DIRECTION dir;
    switch (n) {
        case 'A':
        case 'a':
            dir = LEFT;
            break;
        case 'W':
        case 'w':
            dir = UP;
            break;
        case 'D':
        case 'd':
            dir = RIGHT;
            break;
        case 's':
        case 'S':
            dir = DOWN;
            break;
        default:
            dir = RIGHT;
            break;

    }
    return dir;
}

void snake_update(DIRECTION d, Coords &eda, std::string &s, bool &game, std::vector<Coords> &vec)
{
    Coords temp = vec[0];

    if(d == UP)
        --temp.x;
    else if(d == LEFT)
        --temp.y;
    else if(d == RIGHT)
        ++temp.y;
    else if(d == DOWN)
        ++temp.x;

    if((temp.x == eda.x) && (temp.y == eda.y))
    {
        s.insert(s.end()-1,1, 'x');
        food_gen(eda);
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

    if(temp.x == 0 || temp.y == 0 || temp.x == height || temp.y == width-1)
        game = false;

    for(int k = 1; k < vec.size(); ++k)
    {
        if(vec[0].x == vec[k].x && vec[0].y == vec[k].y)
            game = false;
    }
}

void food_gen(Coords &eda)
{
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist (0,20);
    std::uniform_int_distribution<std::mt19937::result_type> dist2 (0,40);
    eda.x = dist(rng);
    eda.y = dist2(rng);
    if(eda.x == 10 && eda.y == 10)
        food_gen(eda);
}



