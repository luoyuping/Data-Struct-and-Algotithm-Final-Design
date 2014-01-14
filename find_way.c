#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define   m   15

#define   n   50
#define   infinity       99999



typedef struct node
{
   float distence;
   int  vexnode;
   struct node *next;

}Arcnode;



typedef struct vertexnode
{
	char name[30];
	char information[100];
	Arcnode* head;
} Line;



typedef struct  adjlist
{
	Line point[m];
	int  arcnum;
	int  vexnum;
} graph;



typedef struct queue
{
     int father;
     int son;
     struct queue *next;    
}queue;



typedef struct  mst_point
{
    int father;
    int son;
    struct mst_point *next;
}mst_point;



//========================================================================
//creat the graph and test it


void   init_matrix(float (*matrix) [m])
{
    for (int i = 0; i < m; ++i)
        for (int j = 0; j <m ; ++j)
             matrix[i][j]=infinity;
}



void  init_graph(graph *g)
{
    for (int i = 0; i < m; ++i)
    {
        memset(g->point[i].name,0,30*sizeof(char));
        memset(g->point[i].information,0,100*sizeof(char));
    }

    for (int i = 0; i < m; ++i)
    {
        g->point[i].name[29]='\n';
        g->point[i].information[29]='\n';
    }

    
}

void  creat_graph(graph* g,float (*matrix)[m],FILE *fp)
{
     Arcnode *temp;
     int vexnum;
     int  w;
     int vexnode;
     float distence;
     //int length;

     
     
         
     init_graph(g);

     printf("how many points in total?\n");
     scanf("%d",&vexnum);
     getchar();

     fprintf(fp, "%d\n",vexnum );

     g->vexnum=vexnum;

     for (int i = 0; i < vexnum; ++i)
     {
     	g->point[i].head=(Arcnode*)malloc(sizeof(Arcnode));
     	g->point[i].head->next=NULL;
     	printf("the %dth line:\n",i);
     	printf("input the %dth point's name:", i);
     	
        //scanf("%[^\n]",g->point[i].name);
        //getchar();
        gets(g->point[i].name);
        //printf("%s\n",g->point[i].name );

        fwrite(g->point[i].name,30,1,fp);

     	printf("input the basic information of %s\n", g->point[i].name);
     	//scanf("%[^\n]",g->point[i].information);
        //getchar();
        gets(g->point[i].information);
        //printf("%s\n",g->point[i].information );
        fwrite(g->point[i].information,100,1,fp);

     	printf("\nhow many points connect to the %d:",i);//g->point[i].name);
     	scanf("%d",&w);
        getchar();
        fprintf(fp, "%d\n", w);
     	printf("which one connected to the %d,and the distence?\n",i);//g->point[i].name);
     	for (int j = 0; j <w; ++j)
     	{
     		temp=(Arcnode *)malloc(sizeof(Arcnode));
     		scanf("%d%f",&vexnode,&distence);
            getchar();
            fprintf(fp, "%d %f\n",vexnode,distence );


            temp->vexnode=vexnode;
            temp->distence=distence;

            temp->next=g->point[i].head->next;
            g->point[i].head->next=temp;

            matrix[i][vexnode]=distence;
     	}

     }
     //printf("creat over!\n");
}




void test(graph *g,float (*matrix)[m])
{

	Arcnode *temp;
	

    
    printf("the matrix is as follows:\n");
    printf("%d\n",g->vexnum );

    //sleep(5);
    
    for (int i = 0; i < g->vexnum; ++i)
    {
        for (int j = 0; j < g->vexnum; ++j)
        {
            printf("%6.1f  ", matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    printf("%d\n", g->vexnum);
    for (int i = 0; i < g->vexnum; ++i)
    {

        temp=g->point[i].head->next;
        printf("point connected to '%s':",g->point[i].name);
        while(temp)
        {
            printf(" (%s,distence:%.1f) ", g->point[temp->vexnode].name,temp->distence);
            temp=temp->next;
        }
        printf("\n");
        printf("information:%s", g->point[i].information);
        printf("\n\n\n");
    }

    

}

//============================================================================



//============================================================================
//creat queue and all related function


queue * init_queue()
{
    queue* head=(queue *)malloc(sizeof(queue));
    head->next=NULL;
    return head;

}




int  empty(queue *head)
{
    if(head->next)     return 0;            //not empty
    else               return -1;           //empty
}




void push(queue *head,int i,int j)   // i:father point   j:son point
{

     queue *temp=(queue *)malloc(sizeof(queue));
     if(temp)
     {
         temp->father=i;
         temp->son=j;
         temp->next=head->next;
         head->next=temp;
     }
}




void pop(queue *head,int* i,int* j)
{
    queue * temp;
    if(!empty(head))
    {
        temp=head->next;
        (*i)=temp->father;
        (*j)=temp->son;

        head->next=temp->next;
        free(temp);
    }
}




void print_queue(queue *head)
{
    queue *temp;
    temp=head->next;
    printf("the queue :\n");
    while(temp)
    {
        printf("father:%d ,son:%d ", temp->father,temp->son);
        temp=temp->next;
    } 
}



/*
void test_queue(queue *head)
{

    head=init_queue();
    int order=-2;

    printf("test push:input the order:\n");
    while(order != -1)
    {              
         scanf("%d",&order);
         push(head,order);
    }
    printf("\n");

    printf("test pop :\n");
    while(!empty(head))
    {    
        pop(head,&order);
        printf("%d ",order);
    }

    printf("\n");

    printf("test push:input the order:\n");
    while(order !=-1)
    {
         scanf("%d",&order);
         push(head,order);
    }

    printf("\n");
    printf("test pop :\n");
    while(!empty(head))
    {    
        pop(head,&order);
        printf("%d ",order);
    }

    print_queue(head);

}

*/ 




//==============================================================
//find all way between two points


void  print_rout(graph *g,queue *head,int end)
{
    queue *temp=head->next;
    printf("the rout:\n");
    printf("%s <- ",g->point[end].name);
    while(temp) 
    {
        printf("%s <- ",g->point[temp->father].name);
        temp=temp->next;
    }
    printf("\n");
}





int get_next(graph* g,int* father,int* son)
{
    Arcnode *temp=g->point[*father].head->next;
    if((*son)==-1)
    {
        if(temp)
        {
           (*son)=temp->vexnode;
            return 1;
        }
        else 
            return 0;
    }
    else
    {

        while(temp->vexnode !=(*son))
           temp=temp->next;
        if(temp->next)
        {
           (*son)=temp->next->vexnode;
           return 1;
        }
        else
            return 0;
    }
}


int contin_find(graph*g,int father,int son,int start)
{

    Arcnode *temp=g->point[father].head->next;
    while(temp->vexnode !=son)
        temp=temp->next;
    if( temp->next!=NULL)
        return 1;
    else 
        return 0;
}
void  allways_bttps(graph *g,queue *head,int start,int end)
{ 
    head=init_queue();
    int in_stack[m];
    int father=start;
    int son;
    int count=0;

    for (int i = 0; i < m; ++i)                in_stack[i]=0; 

           
    if(g->point[start].head->next)
    {
            
        son=g->point[start].head->next->vexnode;
        push(head,father,son);
        //printf("(f,s):%d,%d has push into the queue\n", father,son);
        in_stack[start]=1;
        if(g->point[start].head->next->vexnode==end)      
        {
            print_rout(g,head,end);
            count ++;
            in_stack[father]=0;
            //get_next(g,head,&start,&end);
        }
        else
        {
             father=son;
             son=-1;
        }
    }

    else   
    {
            printf("there is no way between the two points \n");
            return;
    }


    while((empty(head)==0)||(contin_find(g,father,son,start)))
    {
        //printf("enter while\n");

        if(get_next(g,&father,&son))
        {
            if(in_stack[father]==0)
            {
                if(son!=end)  
                {
                     push(head,father,son);
                     //printf("(f,s):%d,%d has push into the queue\n", father,son);
                     in_stack[father]=1;
                     father=son;
                     son=-1;
                }
                else
                {
                    push(head,father,son);
                    in_stack[father]=1;
                    print_rout(g,head,son);
                    count ++;

                }
            }
            /*
            else
            {
                pop(head,&father,&son);
                printf("(f,s):%d,%d has  get out of the queue\n", father,son);
                in_stack[father]=0;
            }
            */


        }
        else
        {
            //in_stack[father]=0;
            pop(head,&father,&son);
            in_stack[father]=0;
            //printf("(f,s):%d,%d has get out of the queue\n", father,son);
        }
    }
    //printf("out of the while\n");
    printf("in total:%d way(s)\n",count);
} 






/*
void test_dfs(graph *g,queue *head,float (*matrix)[m])
{
    int start=-1,end=-1;
    creat_graph(g,matrix);

    test(g,matrix);
    
    while((start!=0) || (end!=0))
    {
       printf("input the start point and end_point:\n");
       scanf("%d%d",&start,&end);
       allways_bttps(g,head,start,end);
    }
    


}
*/



//=================================================================================






//==================================================================================
//find the shortest way between two points

   


   
void dijkstra(graph *g,float (*matrix)[m],int start,int end,int dist[m],int path[m][m+1])
{
     int mindist;
     int t,k;
     t=1;


     for (int i = 0; i < g->vexnum; ++i)
         path[i][0]=0;
     for (int i = 0; i <g->vexnum ; ++i)
     {
         for (int j = 1; j < m+1; ++j)
         {
             path[i][j]=-1;
         }
     }

     for (int i = 0; i < g->vexnum; ++i)
     {
         dist[i]=matrix[start][i];
         if(matrix[start][i]!=infinity)
            path[i][1]=start;
     }
     

     path[start][0]=1;
     for (int i = 1; i < g->vexnum; ++i)     //?
     {
         mindist=infinity;
         for (int j = 0; j < g->vexnum; ++j)
         {
               if(!path[j][0]  && dist[j]<mindist)
               {
                   k=j;
                   mindist=dist[j];
               }
         }

         if(mindist==infinity)
         {
            printf("this point has no out way \n" );    
            return ;      
         }
         path[k][0]=1;
         

         for (int j = 1; j < m; ++j)
         {
             if(!path[j][0] && matrix[k][j]<infinity  && (dist[k]+matrix[k][j]<dist[j]))
             {
                dist[j]=dist[k]+matrix[k][j];
                t=1;
                while(path[k][t]!=-1)
                {
                    path[j][t]=path[k][t];
                    t++;
                }
                path[j][t]=k;
                //path[j][t+1]=0;
             }
         }
     }

     

     printf("the shortest way between the %s and %s is\n",g->point[start].name,g->point[end].name);
     t=1;
     while((k=path[end][t])!=-1)
     {
        printf("%s  ", g->point[k].name);
        t++;
     }

     printf("%s\n",g->point[end].name );

     printf("\nin length:%d\n", dist[end]);


}



void test_dijs(int *dist,int path[][m+1])
{
    printf("the distence array:\n");
    for (int i = 0; i < m; ++i)
    {
        printf("%d ", dist[i]);
    }
    printf("\n");

    printf("the path array:\n");

    for (int i = 0; i < m; ++i)
    {
        for (int j = 0; j <m+1 ; ++j)
        {
            printf("%d  ", path[i][j]);
        }
        printf("\n");
    }

    printf("\n");

}

//===============================================================================
//algorithm prim   to get MST tree




mst_point * prim(graph* g,float(*matrix)[m],int start)
{
     mst_point *head=(mst_point *)malloc(sizeof(mst_point));
     mst_point* temp;
     struct
     {
        int adjvex;
        int lowcost;
     } closedge[m];

     int k ,s,min;

     head->next=NULL;

     closedge[start].lowcost=0;

     for (int i = 0; i < g->vexnum; ++i)
         if (i!=start)
         {
             closedge[i].adjvex=start;
             closedge[i].lowcost=matrix[start][i];
     
         }


     for (int i = 0; i < g->vexnum-1; ++i)
     {
         min=infinity;
         for (int j = 0; j < g->vexnum; ++j)
         {
             if(closedge[j].lowcost !=0 && closedge[j].lowcost<min)
                 {
                    s=j;   
                    min=closedge[j].lowcost;
                 }
         }

        
        temp=(mst_point*)malloc(sizeof(mst_point));
        temp->father=closedge[s].adjvex;
        temp->son=s;

        temp->next=head->next;
        head->next=temp;





        closedge[s].lowcost=0;

        for (int j = 0; j < g->vexnum; ++j)
            if(j!=s && matrix[s][j] <closedge[j].lowcost)
            {
                closedge[j].lowcost=matrix[s][j];
                closedge[j].adjvex=s;

            }
     }
     return head;
}


void test_mst(mst_point *head)
{
    mst_point* temp;
    temp=head->next;
    printf("the MST tree is:\n");
    while(temp)
    {
        printf("(%d,%d)  ", temp->father,temp->son);
        temp=temp->next;
    }
    printf("\n");

}

//=================================================================================
void  read(graph* g,float (*matrix)[m],FILE *fp)
{
     Arcnode *temp;
     int vexnum;
     int  w;
     int vexnode;
     float distence;


     //printf("how many points in total?\n");
     //scanf("%d",&vexnum);
    // printf("enter read\n");

     fscanf(fp, "%d\n",&vexnum );
     //printf("line 682\n");
     //printf("%d\n", vexnum);


     g->vexnum=vexnum;
     for (int i = 0; i < vexnum; ++i)
     {
        g->point[i].head=(Arcnode*)malloc(sizeof(Arcnode));
        g->point[i].head->next=NULL;
       // printf("the %dth line:\n",i+1);
        //printf("input the %dth point's name:", i+1);
        //scanf("%s",g->point[i].name);

        fread(g->point[i].name,30,1,fp);

        //printf("input the basic information of %s\n", g->point[i].name);
        //scanf("%s",g->point[i].information);

        fread(g->point[i].information,100,1,fp);

        //printf("\nhow many points connect to the %d:",i);//g->point[i].name);
        //scanf("%d",&w);
        fscanf(fp, "%d\n", &w);
        //printf("which one connected to the %d,and the distence?\n",i);//g->point[i].name);
        for (int j = 0; j <w; ++j)
        {
            temp=(Arcnode *)malloc(sizeof(Arcnode));
            //scanf("%d%f",&vexnode,&distence);
            fscanf(fp, "%d %f\n",&vexnode,&distence );


            temp->vexnode=vexnode;
            temp->distence=distence;

            temp->next=g->point[i].head->next;
            g->point[i].head->next=temp;

            matrix[i][vexnode]=distence;
        }

     }
     //printf("creat over!\n");
     test(g,matrix);
}



void display(graph *g)
{

    int choice;
    printf("\n    places intrduction    \n");
    for (int i = 0; i < g->vexnum; ++i)
    {
        printf("%d : %s\n",i,g->point[i].name);
        
    }
    scanf("%d",&choice);
    getchar();
    printf("%s\n\n",g->point[choice].information);

}



void Select(graph *g)
{
    int point;
    for (int i = 0; i < g->vexnum; ++i)
    {
        printf("%d:%s\n",i,g->point[i].name);
        
    }
}



//==================================================================================

void display_mst(graph* g,mst_point *head)
{
     test_mst(head);
     mst_point* temp;
     temp=head->next;
     printf("visit way as:\n");
     while(temp)
     {
        printf("%s to %s\n", g->point[temp->father].name,g->point[temp->son].name);
        temp=temp->next;
     }
}


void add(graph *g,float(*matrix)[m],int start,int end,float distence)
{
     Arcnode *temp=(Arcnode *)malloc(sizeof(Arcnode));
     temp->vexnode=end;
     temp->distence=distence;
     temp->next=g->point[start].head->next;
     g->point[start].head->next=temp;

     matrix[start][end]=distence;
}



void cut(graph *g,float(*matrix)[m],int start,int end)
{
    Arcnode *temp=g->point[start].head;
    Arcnode *p;

    while(temp->next->vexnode !=end)
        temp=temp->next;
    p=temp->next;
    temp->next=temp->next->next;
    free(p);
    matrix[start][end]=infinity;

}



void add_point(graph *g,float (*matrix)[m])
{
    int w1,w2;
    int vexnode;
    float distence;
    int vexnum;
    Arcnode *temp;

    (g->vexnum) ++;

    vexnum=g->vexnum;
    printf("%d\n", vexnum);
    printf("input the point's name:");
    getchar();
    scanf("%[^\n]",g->point[m].name);
    getchar();
    printf("how many points connected from this point?\n");
    scanf("%d",&w1);
    printf("%d\n", w1);
    printf("input the point and distence\n");
    g->point[vexnum].head=(Arcnode*)malloc(sizeof(Arcnode));

    g->point[vexnum].head->next=NULL;

    for (int j = 0; j < w1; ++j)
        {

            temp=(Arcnode *)malloc(sizeof(Arcnode));
            scanf("%d%f",&vexnode,&distence);
            getchar();
            temp->vexnode=vexnode;
            temp->distence=distence;

            temp->next=g->point[vexnum].head->next;
            g->point[vexnum].head->next=temp;

            matrix[vexnum][vexnode]=distence;
        }

    printf("how many points connected to this point?\n");
    scanf("%d",&w2);
    printf("input the point and distence\n");
  
    for (int i = 0; i < w2; ++i)
    {
        temp=(Arcnode *)malloc(sizeof(Arcnode));
        scanf("%d%f",&vexnode,&distence);
        getchar();

        temp->vexnode=m;
        temp->distence=distence;

        temp->next=g->point[vexnode].head->next;
        g->point[vexnode].head->next=temp;

        matrix[vexnode][g->vexnum]=distence;

    }

    test(g,matrix);
}
/*
void del_point(graph *g,float (*matrix)[m])
{
    int choice;
    printf("\n    places intrduction    \n");
    for (int i = 0; i < g->vexnum; ++i)
    {
        printf("%d : %s\n",i,g->point[i].name);
    }

    printf("input the point you want to del:");
    scanf("%d",&choice);
    getchar();



     
}
*/

int main(int argc, char const *argv[])
{
    
	graph g;
    queue *head;
    float matrix[m][m];
    int path[m][m+1];
    int start,end;
    int dist[m];

    mst_point *Head;

    init_matrix(matrix);

    int point;
    


	//creat_graph(&g,matrix);
	//test(&g,matrix);

    //test_queue(head);
    //test_dfs(&g,head,matrix);
    //printf("input the start point and end_point\n");
    //scanf("%d%d",&start,&end);

    //dijkstra(matrix,start,end,dist,path);
    //test_dijs(dist,path);
    //test_shortest(&g,head,matrix);
    //scanf("%d",&start);
    //Head=prim(matrix,start);
    //test_mst(Head);

    int choice;
    FILE *fp;
    float distence;

    
    while(1)
{

    system("clear");

    printf("                       西 安 市 区 域 查 询 系 统 demo                \n\n ");
    printf("                                   功能页面                            \n");
    printf("      0.地图的基本信息.                                                \n");
    printf("      1.可供查询的地点及其基本信息介绍                                  \n");
    printf("      2.查询任意两点间所有的路径                                       \n");
    printf("      3.查询两点间最短路径                                            \n");
    printf("      4.查询从某点出发的最短连通路径                                  \n");
    printf("      5.路径的扩充                                                  \n");
    printf("      6.路径的撤销                                                  \n");
    printf("      7.新建整张地图                                                 \n");
    printf("      8.add point                                                  \n");
    printf("      9.delete   point                                             \n");
    printf("      10.退出该系统                                                  \n");
    printf("\n\n  根据序号输入你的选择：   ");
    
    scanf("%d",&choice);
    if(choice==10)
        break;
    else
    {
        switch(choice)
        {
            case 0:
            {
                  fp=fopen("graph.txt","rt");
                  read(&g,matrix,fp);
                  fclose(fp);
                  getchar();
                  getchar();
                  break;

           

            }
            case 1:
            { 
                fp=fopen("graph.txt","rt");
                read(&g,matrix,fp);
                fclose(fp);
                display(&g);
                getchar();
                getchar();
                break;


            }
            case 2:
            {
                fp=fopen("graph.txt","rt");
                read(&g,matrix,fp);
                fclose(fp);
                Select(&g);
                printf("input the start point and target point:");
                scanf("%d%d",&start,&end);
                getchar();
                allways_bttps(&g,head,start,end);
                getchar();
                getchar();
                break;
            }
            case 3:
            {
                 fp=fopen("graph.txt","rt");
                 read(&g,matrix,fp);
                 fclose(fp);
                 Select(&g);
                 printf("input the start point and target point:");
                 scanf("%d%d",&start,&end);
                 getchar();
                 dijkstra(&g,matrix,start,end,dist,path);
                 getchar();
                 getchar();
                 break;
            }
            case 4:
            {
                fp=fopen("graph.txt","rt");
                read(&g,matrix,fp);
                fclose(fp);
                Select(&g);
                printf("input the start point:\n");
                scanf("%d",&start);
                getchar();
                Head=prim(&g,matrix,start);
                display_mst(&g,Head);
                getchar();
                getchar();
                break;
  

            }
            case 5:
            {
                 fp=fopen("graph.txt","rt");
                 read(&g,matrix,fp);
                 Select(&g);
                 fclose(fp);
                 printf("input the rout needed to be expend\n");
                 printf("start:");  scanf("%d",&start);
                 printf("end:");  scanf("%d",&end);
                 printf("distence:");   scanf("%f",&distence);
                 printf("\n");
                 getchar();
                 add(&g,matrix,start,end,distence);
                 printf("now,the graph should be:\n");
                 test(&g,matrix);
                 getchar();
                 getchar();
                 break;


            }
            case 6:
            {
                 fp=fopen("graph.txt","rt");
                 read(&g,matrix,fp);
                 Select(&g);
                 fclose(fp);
                 printf("input the rout needed to be cut\n");
                 printf("start:");  scanf("%d",&start);
                 printf("end:");  scanf("%d",&end);
                 //printf("distence:");   scanf("%f",&distence);
                 printf("\n");
                 getchar();
                 cut(&g,matrix,start,end);
                 printf("now,the graph should be:\n");
                 test(&g,matrix);
                 getchar();
                 getchar();
                 break;
            }
            case 7:
            {
                  fp=fopen("graph.txt","wt");
                  creat_graph(&g,matrix,fp);
                  fclose(fp);
                  test(&g,matrix);
                  getchar();
                  break;

            }
            case 8:
            {
                  fp=fopen("graph.txt","rt");

                  read(&g,matrix,fp);
                  Select(&g);

                  fclose(fp);
                  add_point(&g,matrix);
                  test(&g,matrix);

                  getchar();
                  getchar();
                  break;
            }
            case 9:
            {
                  fp=fopen("graph.txt","rt");
                  read(&g,matrix,fp);
                  Select(&g);
                  fclose(fp);
                  //del_point(&g,matrix);
                  test(&g,matrix);
                  
                  getchar();
                  getchar();
                  break;
            }
        }
    }
       

}

	return 0;
}
