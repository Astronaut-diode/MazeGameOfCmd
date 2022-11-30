#ifndef MAZE_MAP_H
#define MAZE_MAP_H

class Map {
private:
    // 用来显示的地图
    char **map;
    // 代表地图的大小是m * n
    int m, n;
    // 默认的最小和最大的宽高
    static int min_m, min_n, max_m, max_n;
    // 刷新界面的时间
    static const int flush_interval = 50;
    // 生成障碍物的概率。
    static int build_obstacle;
    // 块的符号
    static const char obstacle = 'X';
    // 出生点
    std::pair<int, int> birth;
    // 出生点的符号
    static const char birth_character = 'A';
    // 终点
    std::pair<int, int> dest;
    // 目标点的符号
    static const char dest_character = 'Z';
public:
    // 构造函数
    Map(int m = min_m, int n = min_n, int build_obstacle = 10);

    // 析构函数
    ~Map();

    // 获取地图的宽高
    std::pair<int, int> get_size();

    // 构建地图
    void constructor();

    // 显示地图
    void display();

    // 创建出生点和终点
    void make_dot(std::pair<int, int> &dot);

    // 更新移动
    void move();

    // 判断当前位置是否可以走进去，如果可以走进去就更新当前位置。
    void update_birth(int x, int y);

    // 判断游戏是否已经结束了。
    bool success() {return birth == dest; };
};


// 获取用户的初始输入
std::pair<int, int> get_choose();

#endif //MAZE_MAP_H
