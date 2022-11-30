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
    std::pair<int, int> res = get_choose();
    int build_obstacle;
    std::cout << "输入难度:";
    std::cin >> build_obstacle;
    Map map(res.first, res.second, build_obstacle);
    map.constructor();
    while(true) {
        map.move();
        map.display();
        if(map.success()) {
            break;
        }
    }
    std::cout << "随意敲击键盘退出界面..." << std::endl;
    getch();
    return 0;
}
