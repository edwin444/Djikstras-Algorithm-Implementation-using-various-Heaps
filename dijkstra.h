#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<limits.h>

////////////////////////////////////////// DIJKSTRA'S ALGORITHM ////////////////////////////////////////////////

int printSolution(int dist[], int V) 
{ 
   printf("Vertex\t\tDistance from Source\n"); 
   for (int i = 0; i < V; i++) 
      printf("%d\ttt\t%d\n", i, dist[i]); 
} 

struct FibHeap* dijkstra_f(int **graph,int V, int src, struct FibHeap** h) // dijkstra returns head of binomial heap
{ 
    // The output array.  dist[i] will hold the shortest distance from src to i
    int dist[V];                          // Index of array is vertex number and each element holds distance of that vertex from src vertex 
    int sptSet[V];

    // Initialize all distances as INFINITE and stpSet[] as false 
    for (int i = 0; i < V; i++) 
       dist[i] = INT_MAX, sptSet[i] = 0; 

    // Distance of source vertex from itself is always 0 
    dist[src] = 0; 
    FibHeapInsert(h,0,src);
    //printHeap(*h);

    // Find shortest path for all vertices 
    for (int count = 0; count < V-1; count++) 
    { 
      // Pick the minimum distance vertex from the set of vertices not 
      // yet processed. u is always equal to src in the first iteration. 
 
      struct node *u = (fibExtractMin(h));

      
      // Mark the picked vertex as processed 
      sptSet[u->vertex] = 1; 

      // Update dist value of the adjacent vertices of the picked vertex. 
      for (int v = 0; v < V; v++) 
      {
        // Update dist[v] only if is not in sptSet, there is an edge from  
        // u to v, and total weight of path from src to  v through u is  
        // smaller than current value of dist[v] 
        if (!sptSet[v] && graph[u->vertex][v] && dist[u->vertex] != INT_MAX && dist[u->vertex]+graph[u->vertex][v] < dist[v]) 
        {
           dist[v] = dist[u->vertex] + graph[u->vertex][v];
           FibHeapInsert(h,dist[v],v);
        }   
            
       }
        
       
    }
    // print the constructed distance array 
    printSolution(dist, V); 

    return *h;
 
}
void dijkstra_binary(int **graph,int V, int src, struct minheap *h) 
{ 
    // The output array.  dist[i] will hold the shortest distance from src to i
    int dist[V];                          // Index of array is vertex number and each element holds distance of that vertex from src vertex 
    int sptSet[V];

    // Initialize all distances as INFINITE and stpSet[] as false 
    for (int i = 0; i < V; i++) 
       dist[i] = INT_MAX, sptSet[i] = 0; 

    // Distance of source vertex from itself is always 0 
    dist[src] = 0; 
    insertKey(src,0,h);

    // Find shortest path for all vertices 
    for (int count = 0; count < V-1; count++) 
    { 
      // Pick the minimum distance vertex from the set of vertices not 
      // yet processed. u is always equal to src in the first iteration. 
      struct node_binary u = BinaryExtractMin(h); 

      // Mark the picked vertex as processed 
      sptSet[u.vertex] = 1; 

      // Update dist value of the adjacent vertices of the picked vertex. 
      for (int v = 0; v < V; v++) 

        // Update dist[v] only if is not in sptSet, there is an edge from  
        // u to v, and total weight of path from src to  v through u is  
        // smaller than current value of dist[v] 
        if (!sptSet[v] && graph[u.vertex][v] && dist[u.vertex] != INT_MAX  
                                      && dist[u.vertex]+graph[u.vertex][v] < dist[v]) 
        {
           dist[v] = dist[u.vertex] + graph[u.vertex][v]; 
           insertKey(v,dist[v],h);
        }
    } 

    // print the constructed distance array 
    printSolution(dist, V); 
} 
struct node_binomial* dijkstra_binomial(int **graph,int V, int src, struct node_binomial *h) // dijkstra returns head of binomial heap
{ 
    // The output array.  dist[i] will hold the shortest distance from src to i
    int dist[V];                          // Index of array is vertex number and each element holds distance of that vertex from src vertex 
    int sptSet[V];

    // Initialize all distances as INFINITE and stpSet[] as false 
    for (int i = 0; i < V; i++) 
       dist[i] = INT_MAX, sptSet[i] = 0; 

    // Distance of source vertex from itself is always 0 
    dist[src] = 0; 
    insert(&h,0,src);

    // Find shortest path for all vertices 
    for (int count = 0; count < V-1; count++) 
    { 
      // Pick the minimum distance vertex from the set of vertices not 
      // yet processed. u is always equal to src in the first iteration. 
      struct node_binomial u = *BinomialExtractMin(&h);

      // Mark the picked vertex as processed 
      sptSet[u.vertex] = 1; 

      // Update dist value of the adjacent vertices of the picked vertex. 
      for (int v = 0; v < V; v++) 

        // Update dist[v] only if is not in sptSet, there is an edge from  
        // u to v, and total weight of path from src to  v through u is  
        // smaller than current value of dist[v] 
        if (!sptSet[v] && graph[u.vertex][v] && dist[u.vertex] != INT_MAX  
                                      && dist[u.vertex]+graph[u.vertex][v] < dist[v]) 
        {
           dist[v] = dist[u.vertex] + graph[u.vertex][v]; 
           insert(&h,dist[v],v);
        }
    } 

    // print the constructed distance array 
    printSolution(dist, V); 

    return h;
} 