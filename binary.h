// Dijkstra's Algorithm

#include<stdio.h>
#include<stdlib.h>
#include<limits.h>

//////////////////////////////////////// BINARY HEAP OPERATIONS //////////////////////////////////////////////////

struct minheap
{
    struct node_binary *harr;                      // Heap array pointer   
    int capacity;                   // Capacity is maximum allowable heap size
    int heapsize;
};

struct node_binary
{
    int vertex;
    int distance;
};

int parent(int i) 
{ 
    return (i-1)/2; 
} 
  
int left(int i) 
{ 
    return (2*i + 1); 
} 

int right(int i) 
{ 
    return (2*i + 2); 
} 

void swap(struct node_binary *x, struct node_binary *y) 
{ 
    struct node_binary temp = *x; 
    *x = *y; 
    *y = temp; 
} 

void MinHeapify(int i, struct minheap *m) 
{ 
    int l = left(i); 
    int r = right(i); 
    int smallest = i;
    operations += 6; 
    if (l < m->heapsize && m->harr[l].distance < m->harr[i].distance) 
    {
        smallest = l; 
        operations += 2;
    }
    operations += 8;

    if (r < m->heapsize && m->harr[r].distance < m->harr[smallest].distance) 
    {
        smallest = r; 
        operations += 2;
    }
    operations += 8;

    if (smallest != i) 
    { 
        swap(&m->harr[i], &m->harr[smallest]); 
        MinHeapify(smallest,m);
        operations += 8; 
    } 
    operations += 2;
}

struct node_binary BinaryExtractMin(struct minheap *m)   // Argument is pointer to heap size variable
{
    if (m->heapsize <= 0) 
    {
        struct node_binary root;
        root.distance = root.vertex = INT_MAX;
        operations += 5;
        return root;
    } 
    else
        ++operations;
    if (m->heapsize == 1) 
    { 
        m->heapsize--;
        struct node_binary root = m->harr[0]; 
        operations += 6;
        return root; 
    } 
    else
        ++operations;
  
    // Store the minimum value, and remove it from heap 
    struct node_binary root = m->harr[0]; 
    m->harr[0] = m->harr[m->heapsize-1]; 
    m->heapsize--; 
    MinHeapify(0,m); 
    operations += 10;
  
    return root; 
} 
  
void insertKey(int vertex, int distance, struct minheap *m) 
{ 
    if (m->heapsize == m->capacity) 
    { 
        printf("\nOverflow: Could not insertKey\n"); 
        return; 
    } 
    operations += 2;
    // First insert the new key at the end 
    m->heapsize++; 
    int i = m->heapsize - 1; 
    m->harr[i].vertex = vertex;
    m->harr[i].distance = distance; 
    operations += 13;
  
    // Fix the min heap property if it is violated 
    while (i != 0 && m->harr[parent(i)].distance > m->harr[i].distance) 
    { 
       swap(&m->harr[i], &m->harr[parent(i)]); 
       i = parent(i);
       operations += 8; 
    } 
    operations += 8;
} 
