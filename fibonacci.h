
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<limits.h>

#define min(a,b) (a>b?b:a)
#define max(a,b) (a>b?a:b)

extern int operations;

struct FibHeap
{
    struct node* HEAD;
    int n;
    int min;
}*H = NULL,*H1 = NULL,*H2 = NULL;

struct node
{
    struct node* parent;
    //stores the distance
    int key; 
    //stores the vertex number  
    int vertex;
    int degree;
    struct node* child;
    struct node* left;
    struct node* right;
    int mark;
};
//print function for each tree in the fibonacci heap
void printTree(struct node* current) 
{ 
    struct node* temp = current;
    do{
        if (current!=NULL)
        {
            printf("%d L(%d)R(%d)P(%d)M(%d)D(%d)| ",current->key,current->left->key,current->right->key,current->parent== NULL ? -1:current->parent->key,current->mark,current->degree);
            printTree(current->child);
            current = current->right;
        } 
    }while(current!=temp);
} 
  
// print function for fibonacci heap 
void printHeap(struct FibHeap* fibHeap) 
{ 
    struct node* current = fibHeap->HEAD;
    struct node* temp = current;
    if (current!=NULL)
    {
        do{
        printf("%d L(%d)R(%d)P(%d)M(%d)D(%d)| ",current->key,current->left->key,current->right->key,current->parent== NULL ? -1:current->parent->key,current->mark,current->degree);
        printTree(current->child);
        printf("Entered\n");
        //printf("|%d|%d|%d|\n",current->left->key,current->key,current->right->key); 
        current =  current->right;
        }while(current!=temp);
    }
    
} 
struct FibHeap* createHeap()
{
    struct FibHeap* temp = (struct FibHeap*)malloc(sizeof(struct FibHeap));
    temp->n = 0;
    temp->min = 1000000;
    temp->HEAD = NULL;
    operations += 6;
    return temp;

}

//inserts x to the fib heap
void FibHeapInsert(struct FibHeap** fibHeap,int key,int vertex)
{
    struct node* new_node = (struct node *)malloc(sizeof(struct node));
    new_node->parent = NULL;
    new_node->key = key;
    new_node->degree = 0;
    new_node->child = NULL;
    new_node->vertex = vertex;
    new_node->mark = 0;

    if ((*fibHeap)->HEAD==NULL)
    {
        (*fibHeap)->HEAD = new_node;
        new_node->left = new_node;
        new_node->right = new_node;
        (*fibHeap)->n = (*fibHeap)->n + 1;
        (*fibHeap)->min = key;
        operations += 25;
    }
    else
    {
        new_node->right = (*fibHeap)->HEAD;
        new_node->left = (*fibHeap)->HEAD->left;
        (*fibHeap)->HEAD->left->right = new_node;
        (*fibHeap)->HEAD->left = new_node;
        if((*fibHeap)->HEAD->key>key)
        {
            (*fibHeap)->HEAD=new_node;
            (*fibHeap)->min = key;
            operations += 42;
        }
        else
            operations += 36;        
        (*fibHeap)->n = (*fibHeap)->n + 1;
    }
}

//print function for each tree in the fibonacci heap
void total_nodes(struct node* current,int *total) 
{ 
    struct node* temp = current;
    operations += 2;
    do{
        if (current!=NULL)
        {
            *total+=1;
            total_nodes(current->child,total);
            current = current->right;
            operations += 6;
        }
        else
            ++operations;
        ++operations;
    }while(current!=temp);
} 

void FibHeapInsertTree(struct FibHeap** fibHeap,struct node* tree)
{
   
    if ((*fibHeap)->HEAD==NULL)
    {
        (*fibHeap)->HEAD = tree;
        tree->left = tree;
        tree->right = tree;
        tree->parent = NULL;

        int temp_total = 0;
        total_nodes(tree,&temp_total);
        (*fibHeap)->n = temp_total;
        (*fibHeap)->min = tree->key;
        operations += 19;
    }
    else
    {
        //printTree(tree->child);
        tree->parent = NULL;
        tree->right = (*fibHeap)->HEAD;
        tree->left = (*fibHeap)->HEAD->left;
        (*fibHeap)->HEAD->left->right = tree;
        (*fibHeap)->HEAD->left = tree;
        if((*fibHeap)->HEAD->key>tree->key)
        {
            (*fibHeap)->HEAD = tree;
            (*fibHeap)->min = tree->key;
        }
        int temp_total = 1;
        total_nodes(tree->child,&temp_total);
        (*fibHeap)->n = (*fibHeap)->n + temp_total;  
        operations += 37;
    }
}
struct FibHeap* fibHeapUnion(struct FibHeap* h1,struct FibHeap* h2)
{
    struct FibHeap* h = createHeap();
    
    //concatenating the root lists
    h->min = min(h1->min,h2->min);
    h->HEAD = h->min == h1->min ? h1->HEAD : h2->HEAD;
    operations += 8;
    //performing union of the heaps
    if (h->HEAD == h1->HEAD)
    {   // H                            
        // L1----------------R1 --> L2----------------R2 -->
        h1->HEAD->left->right = h2->HEAD;
        h2->HEAD->left->right = h1->HEAD;
        struct node* temp = h2->HEAD->left;
        h2->HEAD->left = h1->HEAD->left;
        h1->HEAD->left = temp;     
        operations += 28;          
    }
    else
    {
        h2->HEAD->left->right = h1->HEAD;
        h1->HEAD->left->right = h2->HEAD;
        struct node* temp = h1->HEAD->left;
        h1->HEAD->left = h2->HEAD->left;
        h2->HEAD->left = temp;
        operations += 28;
    }
    h->n = h1->n +  h2->n;
    operations += 4;
    //returning new heap
    return h;
}


int count_root_list_length(struct node* h)
{
    int count = 0;
    struct node* current = h;
    struct node* temp = current;
    operations += 5;
    do{
        count+=1;
        current = current->right;
        operations += 4;
    }while(current!=temp);
    ++operations;
    return count;
}


void fib_heap_link(struct FibHeap** h,struct node** y,struct node** x)
{
 
    

    //to remove y from h 
    struct node* temp = ((*y)->left);
    temp->right = (*y)->right;
    (*y)->right->left = temp;
    (*y)->left = (*y);
    (*y)->right = (*y);


    temp = (*x)->child;
    if (temp == NULL)
    {
        (*x)->child = (*y);
        (*y)->parent = (*x);
        operations += 26;
    }
    else
    {
        (*x)->child = (*y);
        (*y)->parent = (*x);
        (*y)->right = temp;
        (*y)->left = temp->left;
        temp->left->right = (*y);
        temp->left = (*y);
        operations += 37;
    }
  
    (*x)->degree = (*x)->degree + 1;
    (*y)->mark = 0;
    operations += 6;

    //printf("%d %d %d %d\n",(*x)->key,(*x)->child->key,(*y)->right->key,(*y)->left->key);
    

}
void consolidate(struct FibHeap** h)
{
    struct node** A = (struct node **)malloc(sizeof(struct node*)*((*h)->n));
    operations += 4;

    for (int i=0;i<(*h)->n;i++)
    {
        A[i] = NULL;
        ++operations;
    }

    struct node* current = (*h)->HEAD;
    struct node* temp = current;

    int root_list_length = count_root_list_length(current);

    operations += 7;

    //for each node current in the root list of h
    while(root_list_length>0)
    {
        struct node* x = current;
        struct node* temp = current->right;

        int d = x->degree;

        operations += 7;

        while (A[d]!=NULL)
        {
            struct node* y = A[d];
            operations += 3;
            if (x->key >= y->key)
            {
                struct node* temp = x;
                x = y;
                y = temp;
                operations += 8;
            }
            else 
                ++operations;
                
            fib_heap_link(h,&y,&x);
            A[d] = NULL;
            d = d+1;
            operations += 6;
        }
        A[d] = x;
        current = temp;
        root_list_length-=1;
        operations += 5;
    }
    //rebuilding heap 
    (*h)->HEAD = NULL;
    (*h)->min = 0;
    int tempNo = (*h)->n;
    operations += 7;
    for (int i=0;i<tempNo;i++)
    {
        if (A[i]!=NULL)
        {
            FibHeapInsertTree(h,A[i]);
            operations += 3;           
        }
        else
            ++operations;
        
    }
}
struct node* fibExtractMin(struct FibHeap** h)
{
    int min = 0;
    struct node* ptr = NULL;
    operations += 2;
    if ((*h)->HEAD!=NULL)
    {
        min = (*h)->min;
        ptr = (*h)->HEAD;
        int count = (*h)->HEAD->degree;
        struct node* current = (*h)->HEAD->child;
        operations += 16;
        
        //we have inserted all the child trees of the given tree header
        while (count>0)
        {
            
            struct node* temp = current->right;
            //number of nodes in the tree which is the current child

            int temp_total = 1;
            total_nodes(current->child,&temp_total);
           
            (*h)->n = (*h)->n - temp_total;

            
            FibHeapInsertTree(h,current);
            
            current = temp;
            count = count - 1;
            operations += 17;            
            
        }
        
        //to delete the min node
        if ((*h)->n >1)
        {
            int flag = 0;
            (*h)->HEAD->left->right = (*h)->HEAD->right;
            (*h)->HEAD->right->left = (*h)->HEAD->left;
            (*h)->HEAD = (*h)->HEAD->right;
            (*h)->n = (*h)->n - 1;
            (*h)->min = (*h)->HEAD->key; 
            consolidate(h);
            operations += 32;
              
        } 
        else if((*h)->n == 1)
        {
            (*h)->HEAD = NULL;
            (*h)->min = 0;
            (*h)->n = 0;
            operations += 10;
            
        }
    }

    return ptr;
}


//print function for each tree in the fibonacci heap
void searchTree(struct node* current,int x,struct node** ptr) 
{ 
    struct node* temp = current;
    operations += 2;
    do{
        if (current!=NULL)
        {
            if (current!=NULL && current->key == x)
            {
                (*ptr) = current;
                operations += 5;
            }
            else
                operations += 3;
            
            searchTree(current->child,x,ptr);
            current = current->right;
            operations += 6;
        } 
        operations += 2;
    }while(current!=temp);
} 
  
// print function for fibonacci heap 
void searchHeap(struct FibHeap* fibHeap,int x,struct node** ptr) 
{ 
    struct node* current = fibHeap->HEAD;
    struct node* temp = current;
    operations += 4;
    do{
        if (current!=NULL && current->key == x)
        {
            (*ptr) = current;
            operations += 5;
        }
        else
            operations +=3;
        searchTree(current->child,x,ptr);
        current =  current->right;
        operations += 6;
    }while(current!=temp);   
} 

void cut(struct FibHeap** h,struct node* x,struct node* y)
{
    
    //remove x from the child list of y, decrementing y.degree
    if (y->degree == 1)
    {
        y->child = NULL;
        y->degree-=1;
        operations += 3;
    }
    else if(y->child == x){
        y->child = y->child->right;
        y->child->left = x->left;
        x->left->right = y->child;
        y->degree-=1;
        operations += 13;
    }
    else if (y->child!=x)
    {
        x->left->right = x->right;
        x->right->left = x->left;
        y->degree-=1;
        operations += 12;
    }
    //add x to the root list of h
    FibHeapInsertTree(h,x);
    printf("%d: x",x->key);
    x->mark = 0;
    operations += 4;
}
void cascadingCut(struct FibHeap** h,struct node* y)
{
    struct node* z = y->parent;
    operations += 2;
    if (z!=NULL)
    {
        if (y->mark == 0)
        {
            y->mark = 1;
            operations += 3;
        }
        else
        {
            cut(h,y,z);
            cascadingCut(h,z);
            operations += 6;
        }
    }
}
//utility function to decrease the key of a node.
void fibHeapDecreaseKey(struct FibHeap** h,int x,int k)
{
    if (k>x)
        printf("Error new key is greater than the current key\n");
    
    //first search for the node with value x in the heap
    struct node *ptr = NULL;
    searchHeap(*h,x,&ptr);

    ptr->key = k;
    struct node* y = ptr->parent;

    operations += 10;
    if (y!=NULL && ptr->key<y->key)
    {
        cut(h,ptr,y);
        cascadingCut(h,y);
        operations += 8;
    }
    else
        operations += 3;
    
    if (ptr->key<(*h)->min)
    {
        (*h)->HEAD = ptr;
        (*h)->min = ptr->key;
        operations += 9;
    }
    else
        operations += 3;

    //now ptr stores a pointer to the node containing the value of x
    // printf("pointer data: %d",ptr->key); 
}


void fibHeapDelete(struct FibHeap** h,int x)
{
    //first search for the node with value x in the heap
    struct node *ptr = NULL;
    searchHeap(*h,x,&ptr);
    operations += 4;

    if (ptr == NULL)
    {
        printf("\nThe node is not present\n");
        ++operations;
        return;
    }
    fibHeapDecreaseKey(h,x,-100000);
    fibExtractMin(h);
    operations += 4;

}