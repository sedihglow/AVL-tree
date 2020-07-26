#include <avl.h>
#include <iostream>

using namespace std;


int main()
{
    avl_tree tree;

    tree.add_data(50);
    tree.add_data(200);

/*
    tree.add_data(60);
    tree.add_data(25);
    tree.add_data(35);
    tree.add_data(10);
    tree.add_data(5);
    */
    tree.add_data(25);
    tree.add_data(100);
    tree.add_data(300);
    tree.add_data(150);

    tree.display();

    cout << tree.check_avl() << endl;
}
