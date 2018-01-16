#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <iostream>

struct Node
{
    Node * next;
    int vertice;
};

class Stack
{
        Node * verticeStack;

    public:
        Stack();
        ~Stack();
        bool empty(void);
        int top(void);
        void push(int v);
        void pop(void);
};

void findBridges();

void DFS(int v, int expVertices, Node ** Table, bool * visited, Node * &foundBridges);

bool checkConsistance(int va, int vb, int expVertices, Node ** Table);

#endif
