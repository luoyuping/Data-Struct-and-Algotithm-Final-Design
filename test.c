
int add_disertence(queue *head,int end,float (*matrix)[m])
{
    int father,son;

    int sum=0;

    queue *temp;
    temp=head->next;
    while(temp->next)
    {
       father=temp->father;
       son=temp->next->father;
       sum+=matrix[father][son];
       printf("%.1f\n", matrix[father][son]);

       temp=temp->next;
   }
   father=temp->father;
   son=end;
   sum+=matrix[father][son];
   printf("%.1f\n", matrix[father][son]);
   return sum;
}




void  shortest(graph *g,queue *head,int start,int end,float(*matrix)[m])
{ 
    head=init_queue();
    int in_stack[m];
    int father=start;
    int son;
    int count=0;


    int sum=infinity;

    for (int i = 0; i < m; ++i)                in_stack[i]=0; 

           
    if(g->point[start].head->next)
    {
            
        son=g->point[start].head->next->vexnode;
        push(head,father,son);
       // printf("(f,s):%d,%d has push into the queue\n", father,son);
        in_stack[start]=1;
        if(g->point[start].head->next->vexnode==end)      
        {
            if(sum <(add_disertence(head,end,matrix)))
            {    
                sum=add_disertence(head,end,matrix);
                printf("the sum:%d\n",sum);
                print_rout(head,end);
            }

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
                    // printf("(f,s):%d,%d has push into the queue\n", father,son);
                     in_stack[father]=1;
                     father=son;
                     son=-1;
                }
                else
                {
                    push(head,father,son);
                    in_stack[father]=1;
                    if(sum <(add_disertence(head,end,matrix)))
                    {    
                        sum=add_disertence(head,end,matrix);
                        printf("the sum:%d\n",sum);
                        print_rout(head,end);
                    }
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
          //  printf("(f,s):%d,%d has get out of the queue\n", father,son);
        }
    }
    //printf("out of the while\n");
    printf("in total:%d way(s)\n",count);
} 



void test_shortest(graph *g,queue *head,float (*matrix)[m])
{
    int start=-1,end=-1;
    creat_graph(g,matrix);

    test(g,matrix);
    
    while((start!=0) || (end!=0))
    {
       printf("input the start point and end_point:\n");
       scanf("%d%d",&start,&end);
       shortest(g,head,start,end,matrix);
    }
    


}