#ifndef MAZE_MAP_H
#define MAZE_MAP_H

class Maze {
private:
    // 地图
    char **maze;
    // 地图的宽高
    int width, height;
    // 默认的宽高以及最高和最小的宽高
    static const int min_width = 11;
    static const int max_width = 101;
    static const int min_height = 11;
    static const int max_height = 65;
    static const int const_width = 31;
    static const int const_height = 21;
    // 当前点所占的位置
    int hor_pos, ver_pos;
    // 当前位置的符号
    static const char now_character = 'A';
    // 出生点的位置
    std::pair<int, int> birth;
    // 出生点的符号
    static const char birth_character = '*';
    // 终点的位置
    std::pair<int, int> dest;
    // 终点的符号
    static const char dest_character = '@';
    // 障碍物的符号，直接写成静态常量，反正也不会发生改变
    static const char obstacle_character = '#';
    // 刷新时间
    static const int flush_interval = 300;
    static const char road_character = ' ';

    // 设置初始的尺寸
    void set_size(int &width, int &height);

    // 使用随机prim生成地图
    void random_prim();

    // 判断这个点的上下左右的墙壁，随机删除谁。
    bool checkAdjPos(int x, int y, std::vector<std::pair<int, int>> &checklist);

    // 更新画面
    void update(int x, int y);
public:
    // 构造函数
    Maze(int width = const_width, int height = const_height);

    // 析构函数
    ~Maze();

    // 显示地图
    void display();

    // 移动角色,同时判断是否已经达到终点。
    bool move();
};

#endif
