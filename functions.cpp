#include "functions.h"
#include <iostream>

using namespace std;

void findBridges()
{
    int countVertices, v1, v2, ifEdge=0, expVertices;   // creating graph - adjacency list
    Node * help,* helpDel,* foundBridges;
    bool * visited;
    cin >> countVertices;
    expVertices = countVertices - 2;
    Node ** Table;
    foundBridges = NULL;
    Table = new Node * [countVertices];
    visited = new bool[countVertices];
    for(int i = 0; i < countVertices; i++)
    {
        Table[i] = NULL;
        visited[i] = false;
    }
    while(cin >> v1 >> v2)
    {
        help = new Node;
        help->vertice = v2;
        help->next = Table[v1];
        Table[v1] = help;
        help = new Node;
        help->vertice = v1;
        help->next = Table[v2];
        Table[v2] = help;
    }

    DFS(0, expVertices, Table, visited, foundBridges);  // searching for bridges

    for(int i = 0; i < countVertices; i++)  // free space
    {
        help = Table[i];
        while(help)
        {
            helpDel = help;
            help = help->next;
            delete helpDel;
        }
    }
    delete [] Table;
    delete [] visited;

    while(foundBridges) // output
    {
        cout << foundBridges->vertice << " ";
        ifEdge ^= 1;
        if(!ifEdge) cout << endl;
        help = foundBridges;
        foundBridges = foundBridges->next;
        delete [] help;
    }
    return;
}

void DFS(int v, int expVertices, Node ** Table, bool * visited, Node * &foundBridges)   // depth-first search
{
    Node * helpDFS, * checkList;
    visited[v] = true;
    checkList = Table[v];
    while(checkList)    // check all edges of the vertice
    {
        if(visited[checkList->vertice])
        {
            checkList = checkList->next;
        }
        else
        {
            if(!checkConsistance(v, checkList->vertice, expVertices, Table))
            {
                Node * print;
                print = new Node;
                print->vertice = checkList->vertice;
                print->next = foundBridges;
                foundBridges = print;
                print = new Node;
                print->vertice = v;
                print->next = foundBridges;
                foundBridges = print;
            }
            checkList = checkList->next;
        }
    }
    for(helpDFS = Table[v]; helpDFS; helpDFS = helpDFS->next) if(!visited[helpDFS->vertice]) DFS(helpDFS->vertice, expVertices, Table, visited, foundBridges);
    return;
}

bool checkConsistance(int va, int vb, int expVertices, Node ** Table)   // va, vb - removed vertices
{
    Node * helpCheck;
    Stack myStack;
    int myCount = 0, x, y, start = 0;
    while((start == va) || (start == vb)) start++;  // vertex 0 may be excluded
    myStack.push(start);
    bool * visited2;
    visited2 = new bool[expVertices+2];
    for(int i = 0; i < (expVertices+2); i++)
    {
        visited2[i] = false;
    }
    visited2[va] = true;
    visited2[vb] = true;
    visited2[start] = true;
    while(!myStack.empty())
    {
        x = myStack.top();
        myStack.pop();
        myCount++;
        for(helpCheck = Table[x]; helpCheck; helpCheck = helpCheck->next)
        {
            y = helpCheck->vertice;
            if(!visited2[y])
            {
                visited2[y] = true;
                myStack.push(y);
            }
        }
    }
    delete [] visited2;
    if(myCount == expVertices) return true;
    return false;
}

Stack::Stack()
{
    verticeStack = NULL;
}

Stack::~Stack()
{
    while(verticeStack) pop();
}

bool Stack::empty(void)
{
    return !verticeStack;
}

int Stack::top(void)
{
    return verticeStack->vertice;
}

void Stack::push(int v)
{
    Node * pushEl = new Node;
    pushEl->vertice = v;
    pushEl->next = verticeStack;
    verticeStack = pushEl;
}

void Stack::pop(void)
{
    if(verticeStack)
    {
        Node * popEl = verticeStack;
        verticeStack = verticeStack->next;
        delete popEl;
    }
}
