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
#include <time.h>
#include "map.h"

int Map::min_m = 10, Map::min_n = 10, Map::max_m = 30, Map::max_n = 30, Map::build_obstacle = 10;

Map::Map(int m, int n, int build_obstacle) {
    // ����Ѷ���0-100֮��Ϳ����ã�����ֱ�Ӹ�Ϊ10.
    if (build_obstacle <= 0 || build_obstacle >= 100) {
        Map::build_obstacle = 10;
    } else {
        Map::build_obstacle = build_obstacle;
    }
    srand((unsigned) time(NULL));
    // ��֤����Ĺ�Сʱ��ʹ��min,����Ĺ���ʱʹ��max������ʹ��ԭʼ���롣
    this->m = std::max(m, min_m);
    this->n = std::max(n, min_n);
    this->m = std::min(this->m, max_m);
    this->n = std::min(this->n, max_n);
    // ����m��Ԫ�ص�charָ�����顣
    this->map = new char *[this->m];
    for (int i = 0; i < this->m; ++i) {
        this->map[i] = new char[this->n + 1];
        for (int j = 0; j < this->n; j++) {
            this->map[i][j] = ' ';
        }
        this->map[i][this->n] = '\0';
    }
    // ���ɳ�������յ㡣
    make_dot(birth);
    this->map[birth.first][birth.second] = birth_character;
    make_dot(dest);
    this->map[dest.first][dest.second] = dest_character;
}

Map::~Map() {
    // ɾ���ַ���
    for (int i = 0; i < m; ++i) {
        delete[] this->map[i];
    }
    // ɾ���ַ����顣
    delete this->map;
}

// ��ȡ��ͼ�ĳߴ�
std::pair<int, int> Map::get_size() {
    std::pair<int, int> res(this->m, this->n);
    return res;
}

// ������ͼ
void Map::constructor() {
    for (int i = 0; i < this->m; ++i) {
        for (int j = 0; j < this->n; ++j) {
            if (rand() % 100 < Map::build_obstacle && this->map[i][j] == ' ') {
                this->map[i][j] = obstacle;
            }
        }
    }
    this->display();
}

// ��ʾ��ͼ
void Map::display() {
    Sleep(flush_interval);
    system("cls");
    std::string horizon(this->n + 2, '-');
    std::cout << horizon << std::endl;
    for (int i = 0; i < this->m; ++i) {
        std::cout << "|" << this->map[i] << "|" << std::endl;
    }
    std::cout << horizon << std::endl;
    std::cout << " W " << std::endl;
    std::cout << "ASD" << std::endl;
    std::cout << "�ƶ�A��Z��ȥ" << std::endl;
}

// ������������յ�
void Map::make_dot(std::pair<int, int> &dot) {
    if (rand() % 2 == 0) {   // ѡ������
        if (rand() % 2 == 0) {   // ѡ����
            dot = std::make_pair(rand() % this->m, 0);
        } else {
            dot = std::make_pair(rand() % this->m, this->n - 1);
        }
    } else {    // ѡ������
        if (rand() % 2 == 0) {   // ѡ����
            dot = std::make_pair(0, rand() % this->n);
        } else {
            dot = std::make_pair(this->m - 1, rand() % this->n);
        }
    }
}

// �ƶ����
void Map::move() {
    int forward = getch(), x = birth.first, y = birth.second;
    switch (forward) {
        case 'A':
        case 'a':
            update_birth(x, y - 1);
            break;
        case 'd':
        case 'D':
            update_birth(x, y + 1);
            break;
        case 'w':
        case 'W':
            update_birth(x - 1, y);
            break;
        case 's':
        case 'S':
            update_birth(x + 1, y);
            break;
    }
}

// �жϵ�ǰλ���Ƿ�����߽�ȥ����������߽�ȥ�͸��µ�ǰλ�á�
void Map::update_birth(int x, int y) {
    if (0 <= x && x < this->m && 0 <= y && y < this->n && this->map[x][y] != obstacle) {
        // �ȸ�ԭԭʼ��λ�á�
        this->map[x][y] = birth_character;
        this->map[birth.first][birth.second] = ' ';
        birth = std::make_pair(x, y);
    }
}

// ��ȡ��ʼ����
std::pair<int, int> get_choose() {
    int m, n;
    std::cout << "�����Թ��ĸߺͿ�(m * n):";
    std::cin >> m >> n;
    // ��ȡ�������ֵ�ʱ����Ļس�����
    getchar();
    std::pair<int, int> res{m, n};
    return res;
}

