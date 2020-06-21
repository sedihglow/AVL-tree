#include <avl.h>

node::node()
{
    mdata = NULL;
    mright = mleft = mparent = NULL;
}

node::node(int data)
{
    add_data(data);
    mright = mleft = mparent = NULL;
}

node::~node()
{
    if (mdata)
        delete mdata;
    if (right)
        delete mright;
    if (left)
        delete mleft;
    mdata = NULL;
    mright = mleft = mparent = NULL;
}

int node::add_data(int data)
{
    mdata = new int;
    if(!data)
        return EXIT_FAILURE;

    *mdata = data;

    return EXIT_SUCCESS;
}
