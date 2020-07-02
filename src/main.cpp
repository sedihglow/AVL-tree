#include <avl.h>
#include <iostream>

using namespace std;


int main()
{
    avl_tree tree;

    tree.add_data(50);
    tree.add_data(25);
    tree.add_data(75);
    tree.add_data(65);
    tree.add_data(35);
    tree.display();
}
