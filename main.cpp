#include "Test.h"
#include <iostream>
using namespace std;

// A Huffman tree node
struct MinHeapNode
{
    char data;                // One of the input characters
    int freq;                 // Frequency of the character
    MinHeapNode *left, *right; // Left and right child

    MinHeapNode(char data, int freq)
    {
        left = right = NULL;
        this->data = data;
        this->freq = freq;
    }
};

int getNodeF(int nodeSon)
{
    if(nodeSon%2 == 0)
        return (nodeSon-2)/2;
    else
        return (nodeSon-1)/2;
}

void isNode(vector<MinHeapNode*>* heap, int nodeFat, int nodeSon)
{
    MinHeapNode* tempo = (*heap)[nodeFat];
    (*heap)[nodeFat] = (*heap)[nodeSon];
    (*heap)[nodeSon] = tempo;
}

void insertMinHeap(vector<MinHeapNode*>* heap, MinHeapNode* node)
{
    heap->push_back(node);
    int nodeSon = 0;
    int nodeFat = 0;
    nodeSon = heap->size() - 1;

    while(nodeSon != 0)
    {
        nodeFat = getNodeF(nodeSon);

        if((*heap)[nodeSon]->freq > (*heap)[nodeFat]->freq)
            break;

        isNode(heap, nodeFat, nodeSon);
        nodeSon = nodeFat;
    }
}

void addNode(vector<MinHeapNode*>* heap, MinHeapNode* left, MinHeapNode* right)
{
    MinHeapNode* newNode = new MinHeapNode('$', left->freq + right->freq);
    newNode->right = right;
    newNode->left = left;

    insertMinHeap(heap, newNode);
}

void miHeap(vector<MinHeapNode*>* heap)
{
    int nodePos = 0;
    int left = nodePos*2+1;
    int right = nodePos*2+2;
    int ultimo = 0;

    while(left < (int)heap->size())
    {
        if(right < (int)heap->size())
            ultimo = (*heap)[left]->freq < (*heap)[right]->freq ? left : right;
        else
            ultimo = left;

        if((*heap)[nodePos]->freq > (*heap)[ultimo]->freq)
            isNode(heap, nodePos, ultimo);
        else
            break;

        nodePos = ultimo;
        left = nodePos*2+1;
        right = nodePos*2+2;
    }
}

MinHeapNode* isTop(vector<MinHeapNode*>* heap)
{
    MinHeapNode* node = (*heap)[0];
    (*heap)[0] = (*heap)[heap->size() - 1];
    heap->erase(heap->end()-1);

    miHeap(heap);
    return node;
}

void printCodes(map<char,string>* answer, MinHeapNode* root, string str)
{
    if(!root)
        return;

    if (root->data != '$')
        (*answer)[root->data] = str;

    printCodes(answer, root->left, str + "0");
    printCodes(answer, root->right, str + "1");
}

map<char,string> getHuffman(vector<char> characters, vector<int> frequencies)
{
    vector<MinHeapNode*> nodes;
    vector<MinHeapNode*> min_heap;

    for(int i = 0; i < (int)characters.size(); i++)
        nodes.push_back(new MinHeapNode(characters[i], frequencies[i]));

    for(int i = 0; i < (int)nodes.size(); i++)
        insertMinHeap(&min_heap, nodes[i]);

    while(min_heap.size() > 1)
    {
        MinHeapNode* left = isTop(&min_heap);
        MinHeapNode* right = isTop(&min_heap);
        addNode(&min_heap, left, right);
    }

    map<char,string> answer;
    printCodes(&answer, min_heap[0], "");
    return answer;
}

int main ()
{
    test();
    return 0;
}
