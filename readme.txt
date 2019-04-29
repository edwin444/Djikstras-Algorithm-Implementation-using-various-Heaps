README FILE

1. Adjacency matrix is used to represent the graph in Dijkstra's algorithm.

   Example of adjacency matrix A

        DESTINATION

        0    3    5
  SRC   3    0    0
        5    0    0

   The row index represents the src vertex and column index represents the destination vertex.
   For example, the edge cost from vertex 0 to vertex 1 is 3 -> A[0][2] = 3

2. Format of input in input file :

   Line 1 - Number of vertices
   Line 2 - The src vertex number
   
   At line 3, the neighbours of first node along with weights on associated arcs is 
   entered in the following format : 

   [Vertex 1] [Edge weight 1] [Vertex 2] [Edge weight 2] and so on ..

   Line 4 - List of neighbours of second vertex along with weights on associated arcs
   in the above format.

   etc.

   


