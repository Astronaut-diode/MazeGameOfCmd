#include <iostream>
#include <stack>
#include <queue>
#include <vector>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <cstring>
#include <string>
#include <cmath>
#include <fstream>
#include <numeric>
#include <regex>
#include <dirent.h>
#include <cctype>
#include <windows.h>
#include <conio.h>
#include "map.h"

int main() {
    int width, height;
    std::cout << "请输入迷宫的宽高，空格隔开(需要为奇数):";
    std::cin >> height >> width;
    Maze maze(height, width);
    maze.display();
    while(!maze.move()) {
        maze.display();
    }
    std::cout << "输入任意字符退出程序" << std::endl;
    getch();
    return 0;
}
