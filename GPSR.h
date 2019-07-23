#ifndef _GPSR_
#define _GPSR_
#include <iostream>
#include <curses.h>
#include <unistd.h>
#include <string.h>
#include <math.h>
#include <vector>
class MainInterface;
class node;
class node
{
    public:
    /* 用于标记是否是经过的节点 */
    bool flags;
    /* 节点名称与名称代数 */
    char name[50];
    char namenum;
    /* 当前节点位置 */
    int pos_x;
    int pos_y;
    /* 通信半径 */
    int radius;
    /* 对消息进行处理 */
    void handleMessage(void* message);
    /* 邻居表 */
    void NeighberTable(MainInterface* ui);
    std::vector<node> Neighber_Node;
    /* 计算距离 */
    double Distance(double x1,double y1,double x2,double y2);
};
class MainInterface
{
    public:
    /* 判断是否是第一次获取数据 */
    bool flags;
    /* 判断是否到达目的节点 */
    bool achive;
    /* 节点数 */
    int num;
    node* Node;
    /* 获取数据 */
    void GetData(node* &Node);
    /* 界面更新时间 */
    int time;
    /* 主界面 */
    void MainPicture();
    /* 更新位置 */
    node *position;
    void UpdatePosition();
    /* 贪婪转发策略与右手转发策略 */
    void GreedyMethod();
    void RightHandMethod(int& sel_node,int src,int dest);
    /* 存取路径 */
    std::vector<char*> path;
    void Path_Display(std::vector<char*>);

};
#endif