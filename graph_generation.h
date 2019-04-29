#include<stdio.h>
#include<stdlib.h>
#include <time.h>
 
//#define MAX_VERTICES 30
//#define MAX_EDGES 10
#define MAX_WEIGHT 100
#define uSourceVertex 0
typedef unsigned char vertex;
 
int numberOfVertices;
int gen_graph(){
 
    /*number of nodes in a graph*/
    // srand ( time(NULL) );
    // int numberOfVertices = rand() % MAX_VERTICES;

    printf("Enter the number of vertices in the graph: ");
    scanf("%d",&numberOfVertices);
    
 
    /*number of maximum edges a vertex can have*/
    // srand ( time(NULL) );
    // int maxNumberOfEdges = rand() % MAX_EDGES;
    int maxNumberOfEdges;
    printf("Enter the number of edges in the graph: ");
    scanf("%d",&maxNumberOfEdges);

    if (maxNumberOfEdges>=(numberOfVertices*(numberOfVertices+1))/2)
    {
        maxNumberOfEdges = (numberOfVertices*(numberOfVertices+1))/2;
        printf("\nWarning: Max possible edge limit exceeded, hence edges truncated to %d\n",(numberOfVertices*(numberOfVertices+1))/2);
    };
   // maxNumberOfEdges%= ((numberOfVertices*(numberOfVertices+1))/2) + 1;

    
    /*graphs is 2 dimensional array of pointers*/
    if( numberOfVertices == 0)
        numberOfVertices++;
    vertex ***graph;
    printf("Total Vertices = %d\n, Max Number of Edges = %d\n",numberOfVertices, maxNumberOfEdges);
 
    /*generate a dynamic array of random size*/
    if ((graph = (vertex ***) malloc(sizeof(vertex **) * numberOfVertices)) == NULL){
        printf("Could not allocate memory for graph\n");
        exit(1);
    }
 
    /*generate space for edges*/
    int vertexCounter = 0;
    /*generate space for vertices*/
    int edgeCounter = 0;
 
    for (vertexCounter = 0; vertexCounter < numberOfVertices; vertexCounter++){
        if ((graph[vertexCounter] = (vertex **) malloc(sizeof(vertex *) * maxNumberOfEdges)) == NULL){
            printf("Could not allocate memory for edges\n");
            exit(1);
        }
        for (edgeCounter = 0; edgeCounter < maxNumberOfEdges; edgeCounter++){
            if ((graph[vertexCounter][edgeCounter] = (vertex *) malloc(sizeof(vertex))) == NULL){
                printf("Could not allocate memory for vertex\n");
                exit(1);
            }
        }
    }
    FILE *fp;
    fp = fopen("input1.txt", "w"); 
    fprintf(fp,"%d\n",numberOfVertices);
    fprintf(fp,"%d\n",uSourceVertex);

    /*start linking the graph. All vetrices need not have same number of links*/
    vertexCounter = 0;edgeCounter = 0;
    for (vertexCounter = 0; vertexCounter < numberOfVertices; vertexCounter++){
        printf("%d: ",vertexCounter); //line no
        for (edgeCounter=0; edgeCounter < maxNumberOfEdges; edgeCounter++){
            if (rand()%2 == 1){ /*link the vertices*/
                int linkedVertex = rand() % numberOfVertices;
                graph[vertexCounter][edgeCounter] = graph[linkedVertex];

                int foo1 = rand()%MAX_WEIGHT;
                printf("%d %d ", linkedVertex,foo1);
                fprintf(fp,"%d %d ", linkedVertex,foo1);
            }
            else{ /*make the link NULL*/
                graph[vertexCounter][edgeCounter] = NULL;
            }
        }
        printf("\n");
        if (vertexCounter!=numberOfVertices-1)
            fprintf(fp,"%c",'\n');
        // else
        //     fprintf(fp,"%c",'\0');
    }
    fclose(fp);
    return 1;
}