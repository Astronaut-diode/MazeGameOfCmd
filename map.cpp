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

// ���ó�ʼ��С
void Maze::set_size(int &height, int &width) {
    if ((height & 1) == 0) {
        std::cout << "�߶�Ϊż�����Զ���1" << std::endl;
        height += 1;
    }
    if ((width & 1) == 0) {
        std::cout << "���Ϊż�����Զ���1" << std::endl;
        width += 1;
    }
    if (height < min_height || height > max_height) {
        std::cout << "���ں���߶ȷ�Χ�ڣ��Զ���Ϊ" << const_height << std::endl;
        height = const_height;
    }
    if (width < min_width || width > max_width) {
        std::cout << "���ں����ȷ�Χ�ڣ��Զ���Ϊ" << const_width << std::endl;
        width = const_width;
    }
    this->height = height;
    this->width = width;
}

// ʹ�����prim�㷨�����Թ�
void Maze::random_prim() {
    // ȫ������Ϊǽ
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            this->maze[i][j] = obstacle_character;
        }
    }
    // ���ÿ��Ϊ�������������ӳ����㡣
    this->width = (this->width - 1) >> 1;
    this->height = (this->height - 1) >> 1;
    // ������ʼ��
    birth = std::make_pair(rand() % this->height, rand() % this->width);
    this->maze[(birth.first << 1) + 1][(birth.second << 1) + 1] = birth_character;
    // �趨��ҵ�ǰ��λ�á�
    this->hor_pos = (birth.first << 1) + 1;
    this->ver_pos = (birth.second << 1) + 1;
    // ��ʼɾ��ǽ��
    std::vector<std::pair<int, int>> checklist{birth};
    while (!checklist.empty()) {
        int choice = rand() % checklist.size();
        if (!checkAdjPos(checklist[choice].first, checklist[choice].second, checklist)) {
            checklist.erase(checklist.begin() + choice);
            // ÿ���㶼�������������յ㣬����ÿһ�������ڵ㶼�Ḳ�ǵ�ǰ�Ľڵ㡣
            dest = std::make_pair((checklist[choice].first << 1) + 1, (checklist[choice].second << 1) + 1);
        }
    }
    // �����յ�ı�־
    this->maze[dest.first][dest.second] = dest_character;
    // ��ԭԭʼ�Ŀ��
    this->width = (this->width << 1) + 1;
    this->height = (this->height << 1) + 1;
}

// �ж��������������ҵ�ǽ�ڣ����ɾ��˭��
bool Maze::checkAdjPos(int x, int y, std::vector<std::pair<int, int>> &checklist) {
    std::vector<int> directions;
    // �ֱ��ж��������ҵ�ǽ���Ƿ������
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
                // ���ϵ�ʱ��
                this->maze[((x - 1) << 1) + 1][(y << 1) + 1] = road_character;
                // ������(x, y)��(x - 1, y)ӳ���Ժ��м�ļз죬�趨Ϊ·
                this->maze[(((x - 1) << 1) + 1) + 1][(y << 1) + 1] = road_character;
                checklist.emplace_back(std::make_pair(x - 1, y));
                break;
            case 1:
                // ���µ�ʱ��
                this->maze[((x + 1) << 1) + 1][(y << 1) + 1] = road_character;
                // ������(x, y)��(x + 1, y)ӳ���Ժ��м�ļз죬�趨Ϊ·
                this->maze[(((x + 1) << 1) + 1) - 1][(y << 1) + 1] = road_character;
                checklist.emplace_back(std::make_pair(x + 1, y));
                break;
            case 2:
                // �����ʱ��
                this->maze[(x << 1) + 1][((y - 1) << 1) + 1] = road_character;
                // ������(x, y)��(x, y - 1)ӳ���Ժ��м�ļз죬�趨Ϊ·
                this->maze[(x << 1) + 1][(((y - 1) << 1) + 1) + 1] = road_character;
                checklist.emplace_back(std::make_pair(x, y - 1));
                break;
            case 3:
                // ���ҵ�ʱ��
                this->maze[(x << 1) + 1][((y + 1) << 1) + 1] = road_character;
                // ������(x, y)��(x, y + 1)ӳ���Ժ��м�ļз죬�趨Ϊ·
                this->maze[(x << 1) + 1][(((y + 1) << 1) + 1) - 1] = road_character;
                checklist.emplace_back(std::make_pair(x, y + 1));
                break;
        }
        return true;
    } else {
        return false;
    }
}

// �ж��Ƿ�����ƶ���ͬʱ�ж������ڵ�ǰλ�ã�Ӧ����ʾ���ַ���ʲô��
void Maze::update(int x, int y) {
    if (0 <= x && x < this->height - 1 && 0 <= y && y <= this->width - 1 && this->maze[x][y] != obstacle_character) {
        this->maze[hor_pos][ver_pos] = road_character;
        // ����غ��ˣ�Ӧ����ʾA��
        this->maze[(birth.first << 1) + 1][(birth.second << 1) + 1] = birth_character;
        this->maze[x][y] = now_character;
        hor_pos = x;
        ver_pos = y;
    }
}

// ���캯��
Maze::Maze(int height, int width) {
    srand((unsigned) time(NULL));
    set_size(height, width);
    maze = new char *[height];
    for (int i = 0; i < height; ++i) {
        this->maze[i] = new char[width];
    }
    // ���prim�㷨�����Թ���
    random_prim();
}

//��������
Maze::~Maze() {
    for (int i = 0; i < this->height; ++i) {
        delete[] this->maze[i];
    }
    delete[] this->maze;
}

// ��ʾ��ͼ
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
    std::cout << "WASD�ƶ�����*���ƶ���@�㡣" << std::endl;
}

// �ƶ���ɫ
bool Maze::move() {
    // �ж��Ƿ��Ѿ���ʤ�������ʤ��ֱ�ӷ���true�����˳�ѭ����
    if (hor_pos == dest.first && ver_pos == dest.second) {
        std::cout << "���Ѿ���ȡ������ʤ��" << std::endl;
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