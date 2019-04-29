// Dijkstra's Algorithm

#include<stdio.h>
#include<stdlib.h>
#include<limits.h>

//////////////////////////////////////// BINOMIAL HEAP OPERATIONS //////////////////////////////////////////////////

struct node_binomial
{
    int num;
    int vertex;
    int degree;
    struct node_binomial *fchild;
    struct node_binomial *sibling;
};

struct node_binomial* combineTrees(struct node_binomial *head, struct node_binomial *prev, struct node_binomial *t1, struct node_binomial *t2)  // t2 comes after t1 // prev points to node_binomial before t1 
{
    if(t2->num > t1->num)
    {
        t1->sibling = t2->sibling;
        t2->sibling = t1->fchild;
        t1->fchild = t2;
        t1->degree += 1;
        operations += 9;
    }
    else
    {
        if(prev != NULL)
            prev->sibling = t2;
        else
            head = t2;
        t1->sibling = t2->fchild;
        t2->fchild = t1;
        t2->degree += 1;
        operations += 9;
    }
    ++operations;
    return head;
}

struct node_binomial* merge(struct node_binomial *h1, struct node_binomial *h2)
{
    struct node_binomial *p = h1;
    struct node_binomial *q = h2;
    struct node_binomial *dummy = (struct node_binomial*)malloc(sizeof(struct node_binomial)); // assigning a dummy node_binomial
    dummy->fchild = NULL;
    dummy->sibling = NULL;
    struct node_binomial *S = dummy;
    operations += 10;

    while(p != NULL && q != NULL)
    {
        if(p->degree <= q->degree)
        {
            S->sibling = p;
            S = p;
            p = p->sibling;
            operations += 8;
        }
        else
        {
            S->sibling = q;
            S = q;
            q = q->sibling;
            operations += 8;
        }
        operations += 2;
    }

    if(p != NULL)
    {
        S->sibling = p;
        operations += 2;
    }
    else
    {
        S->sibling = q;
        operations += 2;
    }

    // Removing dummy node_binomial
    S = dummy->sibling;

    free(dummy);

    operations += 4;

    return S;
}

struct node_binomial* Union(struct node_binomial *h1, struct node_binomial *h2)
{
    struct node_binomial *h3 = merge(h1,h2);   // h3 is new head of merged heap

    if(h3 == NULL)
        return NULL;

    struct node_binomial *prevX = NULL;
    struct node_binomial *X = h3;
    struct node_binomial *nextX = h3->sibling;
    operations += 9;

    while(nextX != NULL)
    {

        if(X->degree == nextX->degree && (nextX->sibling == NULL || nextX->sibling->degree != nextX->degree))
        {
            h3 = combineTrees(h3,prevX,X,nextX);
            if(prevX == NULL)
                X = h3;
            else
                X = prevX->sibling;
            nextX = X->sibling;
            operations += 9;
            continue;
        }
        
        prevX = X;
        X = nextX;
        nextX = nextX->sibling;
        operations += 13;
        
    }
    ++operations;
    return h3;
}

void insert(struct node_binomial **h, int distance, int vertex)
{
    struct node_binomial *temph = (struct node_binomial*)malloc(sizeof(struct node_binomial));
    temph->degree = 0;
    temph->num = distance;
    temph->vertex = vertex;
    temph->fchild = NULL;
    temph->sibling = NULL;

    *h = Union(*h,temph);
    operations += 12;
}

struct node_binomial* getPrevMinNode(struct node_binomial *h)  // Get node_binomial preceding minNode
{
    struct node_binomial *cursor = h;
    struct node_binomial *prev = NULL;
    struct node_binomial *prevMinNode = NULL;
    struct node_binomial *minNode = h;
    operations += 6;

    while(cursor != NULL)
    {
        if(minNode->num > cursor->num)
        {
            minNode = cursor;
            prevMinNode = prev;
            operations += 4;
        }
        prev = cursor;
        cursor = cursor->sibling;
        operations += 7;        
    }
    ++operations;
    return prevMinNode;
}

struct node_binomial* BinomialExtractMin(struct node_binomial **h)
{
    if(*h == NULL)
    {
        printf("\nBinomial heap is empty\n");
        ++operations;
        return NULL;
    }
    struct node_binomial *temph = NULL;
    struct node_binomial *prevMinNode = getPrevMinNode(*h);
    struct node_binomial *minNode = NULL;
    struct node_binomial *cursor = *h;
    operations += 7;
    if(prevMinNode == NULL)
    {
        *h = cursor->sibling;
        minNode = cursor;
        temph = cursor->fchild;  
        operations += 7;     
    }
    else
    {
        cursor = prevMinNode->sibling;
        minNode = cursor;
        temph = cursor->fchild;
        prevMinNode->sibling = prevMinNode->sibling->sibling;
        operations += 10;
    }
    // reversing temph to store trees in ascending order

    if(temph != NULL)
    {
        struct node_binomial *c1 = temph;
        struct node_binomial *temp;
        struct node_binomial *prev = NULL; 
        while(c1->sibling != NULL)
        {
            temp = c1->sibling;
            c1->sibling = prev;
            prev = c1;
            c1 = temp;
            operations += 9;
        }
        c1->sibling = prev;  // Connecting the last node_binomial to the list
        temph = c1;
        operations += 9;
    }
    *h = Union(*h,temph);
    operations += 5;
    return minNode;
}