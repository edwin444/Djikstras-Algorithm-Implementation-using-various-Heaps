#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<limits.h> 
#include <sys/time.h> 

#include "fibonacci.h"
#include "binomial.h"
#include "binary.h"
#include "dijkstra.h"
#include "graph_generation.h"

extern int numberOfVertices;
int operations = 0;


int main()
{
    int V,src,i,j,lineno = 1;
    int **graph;
    


    while(1)
    {
        //we define a menu driver program to display the running times
        printf("\n\n\t\t==============MENU====================\n\n");
        printf("\t\tBinary Heap Running Time: 1\n");
        printf("\t\tBinomial Heap Running Time: 2\n");
        printf("\t\tFibonacci Heap Running Time: 3\n");
        printf("\t\tTo generate Randomn Graph: 4\n");
        printf("\t\tTo generate adjacency matrix: 5\n");
        printf("\t\tExit: 6\n\n");

        int ch;
        printf("\nEnter the choice: ");
        scanf("%d",&ch);
        if (ch==1)
        {
            
             

            struct timeval start, end; 
  
            // start timer. 
            gettimeofday(&start, NULL); 
            // Setting heap values
            struct minheap h;
            h.capacity = 100000000;
            h.heapsize = 0;
            h.harr = (struct node_binary*)malloc(h.capacity * sizeof(struct node_binary));
            dijkstra_binary(graph,V,src,&h); 

             // stop timer. 
            gettimeofday(&end, NULL); 
        
            // Calculating total time taken by the program. 
            double time_taken; 
        
            time_taken = (end.tv_sec - start.tv_sec) * 1e6; 
            time_taken = (time_taken + (end.tv_usec -  
                                    start.tv_usec)) * 1e-6;
            printf("\nTime taken: %f\n",time_taken);
            printf("\nTotal operations: %d\n",operations);
            

        }
        else if (ch==2)
        {
            
            struct timeval start, end; 
  
            // start timer. 
            gettimeofday(&start, NULL); 
            // Setting heap values
            struct node_binomial *head = NULL;
            head = dijkstra_binomial(graph,V,src,head);

             // stop timer. 
            gettimeofday(&end, NULL); 
        
            // Calculating total time taken by the program. 
            double time_taken; 
        
            time_taken = (end.tv_sec - start.tv_sec) * 1e6; 
            time_taken = (time_taken + (end.tv_usec -  
                                    start.tv_usec)) * 1e-6;
            printf("\nTime taken: %f\n",time_taken);
            printf("\nTotal operations: %d\n",operations);

           

        }
        else if(ch==3)
        {
            struct timeval start, end; 
  
            // start timer. 
            gettimeofday(&start, NULL); 
           
            // Setting heap values
            struct FibHeap *H1 = createHeap();
            H1 = dijkstra_f(graph,V,src,&H1);


             // stop timer. 
            gettimeofday(&end, NULL);
            // Calculating total time taken by the program. 
            double time_taken; 
        
            time_taken = (end.tv_sec - start.tv_sec) * 1e7; 
            time_taken = (time_taken + (end.tv_usec -  
                                    start.tv_usec)) * 1e-7;
            printf("\nTime taken: %f\n",time_taken);
            printf("\nTotal operations: %d\n",operations);
           
        }
        else if(ch==4)
        {
            gen_graph();
           
        }
        else if(ch==5)
        {
            lineno = 1;

            FILE *fp;
            fp = fopen("input1.txt", "r");
            char c;
            char str[50];
            str[0] = '\0';
            int curVer, curWgt;
            int chkWgt = 0;
            while((c = fgetc(fp)) != EOF)
            {
                if(c == ' ' || c == '\n')
                {
                    if(str[0] != '\0')
                    {
                        switch(lineno)
                        {
                            case 1: V = atoi(str);
                                    printf("V: %d\n",V);
                                    if(V < 0)
                                    {
                                        printf("\nError at line 1 in input.txt, number of vertices cannot be negative\n");
                                        return 1;
                                    }
                                    graph = (int**)malloc(V * sizeof(int*));
                                    for(i=0;i<V;i++)
                                        graph[i] = (int*)malloc(V * sizeof(int));
                                    str[0] = '\0';
                                    break;
                            case 2: src = atoi(str);
                                    if(src >= V || src < 0)
                                    {
                                        printf("\nIndex of src vertex in input.txt is invalid\n");
                                        return 1;
                                    }
                                    str[0] = '\0';
                                    break;
                            default:if((lineno - 3) >= V)    // Detecting incorrect input from file
                                    {
                                        printf("\nError at line %d in input.txt, cannot accept input for vertex %d\n",lineno,lineno-3);
                                        return 1;
                                    }
                                    if(chkWgt == 0)
                                    {
                                        curVer = atoi(str);
                                        
                                        if(curVer >= V || curVer < 0)
                                        {
                                            printf("\nError at line %d in input.txt, vertex number= %d out of range\n",lineno,curVer);
                                            return 1;
                                        }
                                        str[0] = '\0';
                                        chkWgt = 1;
                                    }
                                    else
                                    {
                                        curWgt = atoi(str);
                                        if(curWgt < 0)
                                        {
                                            printf("\nError at line %d in input.txt, cannot accept negative weights\n",lineno);
                                            return 1;
                                        }
                                        str[0] = '\0';
                                        graph[lineno - 3][curVer] = curWgt;
                                        graph[curVer][lineno-3] = curWgt;
                                        chkWgt = 0;
                                    }
                                            
                        }
                    }
                    if(c == '\n')
                    {
                        printf("lineno: %d\n ",lineno);
                        ++lineno;
                    }
                }
                else
                {
                    int i;
                    for(i=0;str[i] != '\0';i++);
                    str[i] = c;
                    str[i+1] = '\0';
                }
            }
            fclose(fp);

            if(str[0] != '\0')                    // Reading the last weight before EOF
            {
                curWgt = atoi(str);
                graph[lineno - 3][curVer] = curWgt;
                graph[curWgt][lineno - 3] = curWgt;
            }

            printf("\nAdjacency matrix of graph\n");

            for(i=0;i<V;i++)
            {
                for(j=0;j<V;j++)
                {
                    printf("%d ",graph[i][j]);
                }
                printf("\n");
            }

        }
        else
        {
            printf("Exiting.\n");
            exit(0);
        }

        operations = 0;                           // Resetting heap operations
    }
    

   

    return 0;
}
