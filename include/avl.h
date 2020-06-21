#ifndef AVL_H
#define AVL_H

#include <iostream>
using namespace std;

class node {
    public:
        node();
        node(int data);
        ~node();

        int add_data(int data);

    private:
        int *mdata;
        node *mright;
        node *mleft;
        node *mparent;
};

class avl_tree 
{
    public:
        avl_tree();
        ~avl_tree();
    private:
        node *root;
        
};
#endif
