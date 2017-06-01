#ifndef BINARYNODE_H_INCLUDED
#define BINARYNODE_H_INCLUDED

#include <iostream>
using namespace std;

class BinaryNode
{
public:
    BinaryNode* left;
    BinaryNode* right;
    char value;
    int frequency;

    BinaryNode(char value, int frequency);
};

#endif // BINARYNODE_H
