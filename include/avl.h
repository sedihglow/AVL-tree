#ifndef AVL_H
#define AVL_H

#include <iostream>
using namespace std;

class avl_node {
    public:
        avl_node();
        avl_node(int data);
        ~avl_node();

        int add_data(int data);
        int* get_data();
        avl_node*& get_right();
        avl_node*& get_left();
        
        int*& get_height();
        int get_left_height_data();
        int get_right_height_data();
        int get_left_left_height_data();
        int get_left_right_height_data();
        int get_right_left_height_data();
        int get_right_right_height_data();

    private:
        int *mdata;
        int *mheight;
        avl_node *mright;
        avl_node *mleft;
};

class avl_tree 
{
    public:
        avl_tree();
        ~avl_tree();
        int add_data(int data);
        bool check_avl();

        void display();
    private:
        avl_node* insert_data(avl_node *&node, int data);
        void in_order(avl_node *node);

        void rebalance(avl_node *&node);
        avl_node* left_rotate(avl_node *&node);
        avl_node* right_rotate(avl_node *&node);
        avl_node* right_left_rotate(avl_node *&node);
        avl_node* left_right_rotate(avl_node *&node);

        bool avl_check(avl_node *node);


        avl_node *mroot;
};
#endif
