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
    return (mleft) ? *mleft->get_height() : -1;

}
int avl_node::get_right_height_data()
{
    return (mright) ? *mright->get_height() : -1;
}

int avl_node::get_left_left_height_data()
{
    if (mleft)
        if(mleft->mleft)
            return *mleft->mleft->get_height();

    return -1;
}
int avl_node::get_left_right_height_data()
{
    if (mleft)
        if (mleft->mright)
            return *mleft->mright->get_height();

    return -1;
}
int avl_node::get_right_left_height_data()
{
    if (mright)
        if(mright->mleft)
            return *mright->mleft->get_height();

    return -1;

}
int avl_node::get_right_right_height_data()
{
    if (mright)
        if (mright->mright)
            return *mright->mright->get_height();

    return -1;
}

            /* avl_tree functions */
avl_tree::avl_tree()
{
    mroot = NULL;
}

avl_tree::~avl_tree()
{
     

}

avl_node* avl_tree::left_rotate(avl_node *&node)
{
    avl_node *temp = node->get_right();
    node->get_right() = temp->get_left();
    temp->get_left() = node;

    *node->get_height() = 1 + max(node->get_left_height_data(), 
                                  node->get_right_height_data());
    
    *temp->get_height() = 1 + max(temp->get_left_height_data(), 
                                  temp->get_right_height_data());

    return temp;
}

avl_node* avl_tree::right_rotate(avl_node *&node)
{
    avl_node *temp = node->get_left();
    node->get_left() = temp->get_right();
    temp->get_right() = node;

    *node->get_height() = 1 + max(node->get_left_height_data(), 
                                  node->get_right_height_data());
    
    *temp->get_height() = 1 + max(temp->get_left_height_data(), 
                                  temp->get_right_height_data());
    return temp;
}

avl_node* avl_tree::right_left_rotate(avl_node *&node)
{
    node->get_right() = right_rotate(node->get_right());
    return left_rotate(node);
}

avl_node* avl_tree::left_right_rotate(avl_node *&node)
{
    node->get_left() = left_rotate(node->get_left());
    return right_rotate(node);
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

void avl_tree::rebalance(avl_node *&node)
{
    // Means left subtree is longer than the right subtree
    if (node->get_left_height_data() - node->get_right_height_data() > 1) {
        if (node->get_left_left_height_data() > 
            node->get_left_right_height_data()) {
            node = right_rotate(node);
            cout << "right rotate" << endl;
         } else {
            node = left_right_rotate(node);
            cout << "left right rotate" << endl;
         }
    } else {
        if (node->get_right_left_height_data() <
            node->get_right_right_height_data()) {
            node = left_rotate(node); 
            cout << "left rotate" << endl;
        } else {
            node = right_left_rotate(node);
            cout << "right left rotate" << endl;
        }
    }
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

        if (node->get_left_height_data() - node->get_right_height_data() > 1 ||
            node->get_left_height_data() - node->get_right_height_data() < -1)
            rebalance(node);
        
    } else { // data < *node->get_data()
        node->get_left() = insert_data(node->get_left(), data);

        if (node->get_left_height_data() - node->get_right_height_data() > 1 ||
            node->get_left_height_data() - node->get_right_height_data() < -1)
            rebalance(node);

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

bool avl_tree::check_avl()
{
    return avl_check(mroot);
}

bool avl_tree::avl_check(avl_node *node)
{
    bool ret = true;

    if (!node)
        return ret;

    if (node->get_left_height_data() - node->get_right_height_data() > 1 ||
        node->get_left_height_data() - node->get_right_height_data() < -1) {
        cout << "invalid node" << endl; 
        return false;
    }

    ret = avl_check(node->get_right());

    ret = avl_check(node->get_left());

    return ret;


}
