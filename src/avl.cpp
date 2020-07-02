#include <avl.h>

                /* node functions */
avl_node::avl_node()
{
    mdata = NULL;
    mheight = NULL;
    mright = mleft = NULL;
}

avl_node::avl_node(int data)
{
    add_data(data);

    mheight = new int;
    if (!mheight) {
        cerr << "avl_node: mheight failed to allocate" << endl;
        exit(EXIT_FAILURE);
    }

    *mheight = 0;

    mright = mleft = NULL;
}

avl_node::~avl_node()
{
    if (mdata)
        delete mdata;
    if (mheight)
        delete mheight;
    if (right)
        delete mright;
    if (left)
        delete mleft;
    mdata = NULL;
    mright = mleft = NULL;
}

int avl_node::add_data(int data)
{
    mdata = new int;
    if(!data) {
        cerr << "add_data: mdata failed to allocate" << endl;
        exit(EXIT_FAILURE);
    }

    *mdata = data;

    return 0;
}

int* avl_node::get_data()
{
    return mdata;
}

avl_node*& avl_node::get_right()
{
    return mright;
}
avl_node*& avl_node::get_left()
{
    return mleft;
}

int*& avl_node::get_height()
{
    return mheight;
}

int avl_node::get_left_height_data()
{
    return (mleft) ? *mleft->get_height() : 0;

}
int avl_node::get_right_height_data()
{
    return (mright) ? *mright->get_height() : 0;
}


            /* avl_tree functions */
avl_tree::avl_tree()
{
    mroot = NULL;
}

avl_tree::~avl_tree()
{
     

}

int avl_tree::add_data(int data)
{
    mroot = insert_data(mroot, data);
    if (!mroot) {
        cerr << "add_data: failed to allocate mroot" << endl;
        exit(EXIT_FAILURE);
    }
    return 0;
}


avl_node* avl_tree::insert_data(avl_node *&node, int data)
{
    if (!node) {
        node = new avl_node(data);
        if (!node) {
            cerr << "insert_data: new node failed to allocate" << endl;
            exit(EXIT_FAILURE);
        }
    } else if (data >= *node->get_data()) {
        node->get_right() = insert_data(node->get_right(), data);


    } else { // data < *node->get_data()
       node->get_left() = insert_data(node->get_left(), data);

    }
    
    *node->get_height() = 1 + max(node->get_left_height_data(), 
                                  node->get_right_height_data());
    return node;
}


void avl_tree::display()
{
    in_order(mroot);
}

void avl_tree::in_order(avl_node *node)
{
    if (!node)
        return;

    in_order(node->get_left());
    cout << *node->get_data() << " " << *node->get_height() << endl;
    in_order(node->get_right());
}
