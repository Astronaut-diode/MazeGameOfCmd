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

// 设置初始大小
void Maze::set_size(int &height, int &width) {
    if ((height & 1) == 0) {
        std::cout << "高度为偶数，自动加1" << std::endl;
        height += 1;
    }
    if ((width & 1) == 0) {
        std::cout << "宽度为偶数，自动加1" << std::endl;
        width += 1;
    }
    if (height < min_height || height > max_height) {
        std::cout << "不在合理高度范围内，自定义为" << const_height << std::endl;
        height = const_height;
    }
    if (width < min_width || width > max_width) {
        std::cout << "不在合理宽度范围内，自定义为" << const_width << std::endl;
        width = const_width;
    }
    this->height = height;
    this->width = width;
}

// 使用随机prim算法生成迷宫
void Maze::random_prim() {
    // 全部设置为墙
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            this->maze[i][j] = obstacle_character;
        }
    }
    // 设置宽高为整数，方便后面映射计算。
    this->width = (this->width - 1) >> 1;
    this->height = (this->height - 1) >> 1;
    // 构建初始点
    birth = std::make_pair(rand() % this->height, rand() % this->width);
    this->maze[(birth.first << 1) + 1][(birth.second << 1) + 1] = birth_character;
    // 设定玩家当前的位置。
    this->hor_pos = (birth.first << 1) + 1;
    this->ver_pos = (birth.second << 1) + 1;
    // 开始删除墙壁
    std::vector<std::pair<int, int>> checklist{birth};
    while (!checklist.empty()) {
        int choice = rand() % checklist.size();
        if (!checkAdjPos(checklist[choice].first, checklist[choice].second, checklist)) {
            checklist.erase(checklist.begin() + choice);
            // 每个点都可以拿来当作终点，但是每一个后续节点都会覆盖当前的节点。
            dest = std::make_pair((checklist[choice].first << 1) + 1, (checklist[choice].second << 1) + 1);
        }
    }
    // 设置终点的标志
    this->maze[dest.first][dest.second] = dest_character;
    // 复原原始的宽高
    this->width = (this->width << 1) + 1;
    this->height = (this->height << 1) + 1;
}

// 判断这个点的上下左右的墙壁，随机删除谁。
bool Maze::checkAdjPos(int x, int y, std::vector<std::pair<int, int>> &checklist) {
    std::vector<int> directions;
    // 分别判断上下左右的墙壁是否存在在
    if (x > 0) {
        if (this->maze[((x - 1) << 1) + 1][(y << 1) + 1] == obstacle_character) {
            directions.emplace_back(0);
        }
    }
    if (x < height - 1) {
        if (this->maze[((x + 1) << 1) + 1][(y << 1) + 1] == obstacle_character) {
            directions.emplace_back(1);
        }
    }
    if (y > 0) {
        if (this->maze[(x << 1) + 1][((y - 1) << 1) + 1] == obstacle_character) {
            directions.emplace_back(2);
        }
    }
    if (y < width - 1) {
        if (this->maze[(x << 1) + 1][((y + 1) << 1) + 1] == obstacle_character) {
            directions.emplace_back(3);
        }
    }
    if (directions.size()) {
        int direction = directions[rand() % directions.size()];
        switch (direction) {
            case 0:
                // 向上的时候
                this->maze[((x - 1) << 1) + 1][(y << 1) + 1] = road_character;
                // 这里是(x, y)和(x - 1, y)映射以后中间的夹缝，设定为路
                this->maze[(((x - 1) << 1) + 1) + 1][(y << 1) + 1] = road_character;
                checklist.emplace_back(std::make_pair(x - 1, y));
                break;
            case 1:
                // 向下的时候
                this->maze[((x + 1) << 1) + 1][(y << 1) + 1] = road_character;
                // 这里是(x, y)和(x + 1, y)映射以后中间的夹缝，设定为路
                this->maze[(((x + 1) << 1) + 1) - 1][(y << 1) + 1] = road_character;
                checklist.emplace_back(std::make_pair(x + 1, y));
                break;
            case 2:
                // 向左的时候
                this->maze[(x << 1) + 1][((y - 1) << 1) + 1] = road_character;
                // 这里是(x, y)和(x, y - 1)映射以后中间的夹缝，设定为路
                this->maze[(x << 1) + 1][(((y - 1) << 1) + 1) + 1] = road_character;
                checklist.emplace_back(std::make_pair(x, y - 1));
                break;
            case 3:
                // 向右的时候
                this->maze[(x << 1) + 1][((y + 1) << 1) + 1] = road_character;
                // 这里是(x, y)和(x, y + 1)映射以后中间的夹缝，设定为路
                this->maze[(x << 1) + 1][(((y + 1) << 1) + 1) - 1] = road_character;
                checklist.emplace_back(std::make_pair(x, y + 1));
                break;
        }
        return true;
    } else {
        return false;
    }
}

// 判断是否可以移动，同时判断以下在当前位置，应该显示的字符是什么。
void Maze::update(int x, int y) {
    if (0 <= x && x < this->height - 1 && 0 <= y && y <= this->width - 1 && this->maze[x][y] != obstacle_character) {
        this->maze[hor_pos][ver_pos] = road_character;
        // 如果重合了，应该显示A。
        this->maze[(birth.first << 1) + 1][(birth.second << 1) + 1] = birth_character;
        this->maze[x][y] = now_character;
        hor_pos = x;
        ver_pos = y;
    }
}

// 构造函数
Maze::Maze(int height, int width) {
    srand((unsigned) time(NULL));
    set_size(height, width);
    maze = new char *[height];
    for (int i = 0; i < height; ++i) {
        this->maze[i] = new char[width];
    }
    // 随机prim算法生成迷宫。
    random_prim();
}

//析构函数
Maze::~Maze() {
    for (int i = 0; i < this->height; ++i) {
        delete[] this->maze[i];
    }
    delete[] this->maze;
}

// 显示地图
void Maze::display() {
    Sleep(flush_interval);
    system("cls");
    for (int i = 0; i < this->height; ++i) {
        for (int j = 0; j < this->width; ++j) {
            if(this->maze[i][j] == obstacle_character) {
                std::cout << "\033[31m " << this->maze[i][j] << "\033[0m";
            } else {
                std::cout << "\033[0m " << this->maze[i][j] << "\033[0m";
            }
        }
        std::cout << std::endl;
    }
    std::cout << std::endl << std::endl << std::endl << std::endl;
    std::cout << "WASD移动，从*点移动到@点。" << std::endl;
}

// 移动角色
bool Maze::move() {
    // 判断是否已经获胜，如果获胜，直接返回true用来退出循环。
    if (hor_pos == dest.first && ver_pos == dest.second) {
        std::cout << "你已经获取比赛的胜利" << std::endl;
        return true;
    }
    int forward = getch(), x = hor_pos, y = ver_pos;
    switch (forward) {
        case 'A':
        case 'a':
            update(x, y - 1);
            break;
        case 'd':
        case 'D':
            update(x, y + 1);
            break;
        case 'w':
        case 'W':
            update(x - 1, y);
            break;
        case 's':
        case 'S':
            update(x + 1, y);
            break;
    }
    return false;
}