#include "GPSR.h"
int main(int argc,char *argv[])
{
    MainInterface ui;
    ui.time = 1;
    while(ui.achive){
        ui.MainPicture();
        sleep(ui.time);
    }
    endwin();
    /* 显示转发路径 */
    ui.Path_Display(ui.path);
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
        /* 设置通信半径与名称代数 */
        Node[i].radius = 3;
        Node[i].namenum = i;
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
        move(Node[i].pos_y,Node[i].pos_x);
        if(strcmp(Node[i].name,"源节点") == 0)
        addstr("S");
        else if(strcmp(Node[i].name,"目的节点") == 0)
        addstr("D");
        else
        {
            addstr("*");
        }
        refresh();
    }
    UpdatePosition();
}
void MainInterface::UpdatePosition()
{
  /* 贪婪转发策略 */
    if(strcmp(Node[num-2].name,"源节点"))
        GreedyMethod();
    else
        achive = false;

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
     /* 存取节点路径 */
    path.push_back(Node[src].name);
    /* 赋初值，为了选取距离最短的点 */
    double distance = Node[src].Distance(Node[src].pos_x,Node[src].pos_y,Node[dest].pos_x,Node[dest].pos_y);
    /* 选取节点 */
    int sel_node = -1;
    for(int i = 0;i < Node[src].Neighber_Node.size();++i){
        if(Node[dest].Distance(Node[src].Neighber_Node[i].pos_x,Node[src].Neighber_Node[i].pos_y,Node[dest].pos_x,Node[dest].pos_y) <= distance){
            distance = Node[dest].Distance(Node[src].Neighber_Node[i].pos_x,Node[src].Neighber_Node[i].pos_y,Node[dest].pos_x,Node[dest].pos_y);
            sel_node = i;
        }
    }

    
    /* 右手转发策略 */
    if(sel_node == -1){
        RightHandMethod(sel_node,src,dest);
        printf("右手转发策略\n");
        if(sel_node == -1){
            perror("无法到达目的地\n");
            exit(0);
        }
    }
    else
    {
        /* 防止路由环 */
        Node[src].Neighber_Node[sel_node].flags = false;
        printf("贪婪转发策略\n");
    }
    if(strcmp(Node[src].Neighber_Node[sel_node].name,"目的节点"))
        strcpy(Node[src].name,Node[src].Neighber_Node[sel_node].name);
    else
       strcpy(Node[src].name,"*");
    strcpy(Node[Node[src].Neighber_Node[sel_node].namenum].name,"源节点");
}
void MainInterface::RightHandMethod(int &sel_node,int src,int dest)
{
    /* 赋初值，为了选取距离最短的点 */
    double distance =Node[src].Distance(Node[src].pos_x,Node[src].pos_y,Node[dest].pos_x,Node[dest].pos_y);
     for(int i = 0;i < Node[src].Neighber_Node.size();++i){
        if(Node[src].Distance(Node[src].pos_x,Node[src].pos_y,Node[src].Neighber_Node[i].pos_x,Node[src].Neighber_Node[i].pos_y) <= distance  && Node[src].Neighber_Node[i].flags){
            distance = Node[src].Distance(Node[src].pos_x,Node[src].pos_y,Node[src].Neighber_Node[i].pos_x,Node[src].Neighber_Node[i].pos_y);
            sel_node = i;
        }
    }
}
void MainInterface::Path_Display(std::vector<char*> p)
{
    for(int i = 0;i < p.size();++i)
        if(i != p.size()-1)
            std::cout<<p[i]<<"-->";
        else
        {
            std::cout<<"目的节点"<<std::endl;
        }
        
}

void node::NeighberTable(MainInterface* ui)
{
    double distance;
     for(int i = 0;i < ui->num;++i){
        if(strcmp(ui->Node[i].name,this->name)){    
            distance = this->Distance(ui->Node[i].pos_x,ui->Node[i].pos_y,pos_x,pos_y);
            if(distance <= this->radius){
                Neighber_Node.push_back(ui->Node[i]);
            }
        }
    }
}
double node::Distance(double x1,double y1,double x2,double y2)
{
    return sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
}
