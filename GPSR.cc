#include "GPSR.h"
int main(int argc,char *argv[])
{
   MainInterface ui;
   ui.time = 1;
   ui.MainPicture();
   sleep(ui.time);
   ui.MainPicture();
  
    return 0;
}
void MainInterface::GetData(node* &Node)
{
    /*节点个数*/
    FILE *fp = fopen("node_num","r");
    fscanf(fp,"%d",&num);
    fclose(fp);
    Node = new node[num];
    FILE* fq = fopen("config.store1","r");
    for(int i = 0;i < num;++i){
        fscanf(fq,"%s%d%d",Node[i].name,&(Node[i].pos_x),&(Node[i].pos_y));
        /* 设置通信半径 */
        Node[i].radius = 3;
    }
    fclose(fq);
    /* 获取邻居节点 */
    for(int i = 0;i < num;++i){
         Node[i].NeighberTable(this);
    }
}
void MainInterface::MainPicture()
{
     /* 获取数据 */
    if(flags){
         GetData(Node);
         this->flags = false;
    }
    initscr();
    clear();
    for(int i = 0;i < this->num;++i){
        move(Node[i].pos_x,Node[i].pos_y);
        if(i%2 == 1)
            standout();
        if(strcmp(Node[i].name,"源节点") == 0)
        addstr("S");
        else if(strcmp(Node[i].name,"目的节点") == 0)
        addstr("D");
        else
        {
            addstr("*");
        }
        if(i%2 == 1)
        standend();
        refresh();
    }
    getch();
    endwin();
}
void MainInterface::UpdatePosition()
{
  /* 贪婪转发策略 */

  /* 右手准则 */


}
void MainInterface::GreedyMethod()
{
    /* 源节点 */
    int src;
    /* 目的节点 */
    int dest;
    for(int i = 0;i < num;++i){
        if(strcmp(Node[i].name,"源节点") == 0){
            src = i;
        }
        if(strcmp(Node[i].name,"目的节点") == 0){
            dest = i;
        }
    }
    /* 赋初值，为了选取距离最短的点 */
    double distance = Node[src].Distance(Node[src].pos_x,Node[src].pos_y,Node[dest].pos_x,Node[dest].pos_y);
    for(int i = 0;i < Node[src].Neighber_Node.size();++i){

    }
}
void node::NeighberTable(MainInterface* ui)
{
    double distance;
     for(int i = 0;i < ui->num;++i){
        if(strcmp(ui->Node[i].name,this->name)){    
            distance = this->Distance(ui->Node[i].pos_x,ui->Node[i].pos_y,pos_x,pos_y);
            if(distance < this->radius){
                Neighber_Node.push_back(ui->Node[i]);
            }
        }
    }
}
double node::Distance(double x1,double y1,double x2,double y2)
{
    return sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
}