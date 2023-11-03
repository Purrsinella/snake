//#include "snake_help.h"
//#include <iostream>
//#include <string>
//#include <random>
//void pole(Coords point, std::string s, char f, Coords &eda, std::vector<Coords> &vec)
//{
//    int height = 20;
//    int width = 40;
//
//    for (int i = 0; i < width + 2; i++)
//        std::cout << "-";
//    std::cout << std::endl;
//    for(int i = 0; i < height; ++i)
//    {
//        int j;
//        for(j = 0; j <= width; ++j)
//        {
//            if (j == 0 || j == width)
//                std::cout << "|";
//            else if(point.x == i && point.y == j)
//                std::cout << s;
//            else if(i == eda.x && j == eda.y)
//                std::cout << f;
//            else
//                std::cout << " ";
//        }
//        std::cout << std::endl;
//    }
//    for (int i = 0; i < width + 2; i++)
//        std::cout << "-";
//    std::cout << std::endl;
//}
//
//DIRECTION ret_dir(char n)
//{
//    DIRECTION dir;
//    switch (n) {
//        case 'A':
//        case 'a':
//            dir = LEFT;
//            break;
//        case 'W':
//        case 'w':
//            dir = UP;
//            break;
//        case 'D':
//        case 'd':
//            dir = RIGHT;
//            break;
//        case 's':
//        case 'S':
//            dir = DOWN;
//            break;
//        default:
//            dir = RIGHT;
//            break;
//
//    }
//    return dir;
//}
//
//void snake_update(Coords &point, DIRECTION d, Coords &eda, std::string &s, bool &game, std::vector<Coords> &vec)
//{
//    if(d == UP)
//        --point.x;
//    else if(d == LEFT)
//        --point.y;
//    else if(d == RIGHT)
//        ++point.y;
//    else if(d == DOWN)
//
//        if((vec[0].x == eda.x) && (vec[0].y == eda.y))
//        {
//            s.insert(s.end()-1,1, 'x');
//            food_gen(eda);
////            adjust_body(vec, point);
//        }
////    change_body(vec, point);
//    if(point.x == 0 || point.y == 0 || point.y == 20 || point.x == 20)
//        game = false;
//}
//
//void food_gen(Coords &eda)
//{
//    std::random_device dev;
//    std::mt19937 rng(dev());
//    std::uniform_int_distribution<std::mt19937::result_type> dist (0,20);
//
//    eda.x = dist(rng);
//    eda.y = dist(rng);
//}
////bool coordinates_check(std::vector<Coords> &vec, int a, int b)
////{
////    for(int k = 0; k < vec.size(); ++k)
////    {
////        if (vec[k].x == a && vec[k].y == b)
////            return true;
////        else return false;
////    }
////}
////
////int coordinates_return(std::vector<Coords> &vec, int a, int b)
////{
////    for (int k = 0; k < vec.size(); ++k) {
////        if (vec[k].x == a && vec[k].y == b)
////            return k;
////    }
////}
////
////void change_body(std::vector<Coords> &vec, Coords &point)
////{
////    std::vector<Coords> temp;
////    temp = vec;
////    vec[0] = point;
////    for(int k = 1; k < vec.size(); ++k)
////    {
////        vec[k] = temp[k - 1];
////    }
////}
////
////void adjust_body(std::vector<Coords> &vec, Coords &point)
////{
////    vec.insert(vec.begin(),point);
////}