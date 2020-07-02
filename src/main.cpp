#include <avl.h>
#include <iostream>

using namespace std;


int main()
{
    avl_tree tree;

    tree.add_data(50);
    tree.add_data(25);
    tree.display();
}
