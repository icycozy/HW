// n-ary tree to binary tree: "transform.cpp"
#ifndef NAryTree_To_BinaryTree
#define NAryTree_To_BinaryTree

#include "tree.hpp"

BinaryTree *Transform(const NAryTree *node)
{
    // @argu node(pointer to NAryTree): pointer to the root of the n-ary tree you want to transform
    BinaryTree *u = (BinaryTree*)malloc(sizeof(BinaryTree)), *son;
    (*u).val = (*node).val;
    int n = (*node).children.size();
    if (!n)
    {
        (*u).lson = (*u).rson = nullptr;
        return u;
    }
    (*u).lson = Transform((*node).children[0]);
    son = (*u).lson;
    for (int i = 1; i < n; i++)
    {
        (*son).rson = Transform((*node).children[i]);
        son = (*son).rson;
    }
    return u;
}

#endif