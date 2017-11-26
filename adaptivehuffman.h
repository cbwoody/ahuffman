#ifndef __ADAPTIVEHUFFMAN_H__
#define __ADAPTIVEHUFFMAN_H__
#include <string>

using namespace std;

// /**
//  * A node within the huffman tree. It has pointers to its right and left children,
//  *  its parent, and also pointers to its right-to-left next node and previous node. 
//  **/
// class Node
// {
// public:
//     /**
//      * Node is a structure containing the Huffman Node pointers and the values for key 
//      * (the char value from the alphabet) and count (the number of times the character 
//      * has been seen).
//      **/
//     struct node
//     {
//         node *left,
//              *right,
//              *parent,
//              *next,
//              *prev;
//         int count;
//         char key;
//     }

//     /**
//      * Constructor with no parameters, initializes count to 0 and
//      * sets everything else to null.
//      **/
//     HuffmanNode()
//     {
//         node *newNode = new node;
//         newNode->count = 0;
//         newNode->key = NULL;
//         newNode->left = nullptr;
//         newNode->right = nullptr;
//         newNode->parent = nullptr;
//         newNode->next = nullptr;
//         newNode->prev = nullptr;
//     }
// };


class AdaptiveHuffman
{
public:
    /**
     * Node is a structure containing the Huffman Node pointers and the values for key 
     * (the char value from the alphabet) and count (the number of times the character 
     * has been seen).
     **/
    struct node
    {
        node *left,
             *right,
             *parent,
             *next,
             *prev;
        int count;
        char key;
    }

    int encode(string *msg, char **result, int rbuff_size);
    int decode(string *msg, char **result, int rbuff_size);

    /**
     * Pointer to the root of the tree.
     **/
    *root;

    /**
     * Constructor for the adaptive huffman tree will build the zero node from
     * the alphabet given.
     * @param alphabet a pointer to a string of characters that will be used 
     * as the alphabet.
     **/
    AdaptiveHuffman(string *alphabet)
    {
        for(char& c : alphabet)
        {
            insertZeroNode(c);
        }
    }

    //Deconstructor
    ~AdaptiveHuffman();
    
    /**
     * Returns value of if the root is null.
     **/
    bool isEmpty()
    {
        return root == NULL;
    }

    /**
     * Creates a new node to be inserted in the zero node. It will walk the 
     * tree to the right until it gets to the end, and create an empty parent
     * node. Then the left child of this parent node will be set as the value
     * node. The character c will be stored in the value node.
     **/
    void insertZeroNode(char c)
    {
        node* newValNode;
        newValNode->count = 0;
        newValNode->key = c;
        newValNode->left = nullptr;
        newValNode->right = nullptr;
        newValNode->parent = nullptr;
        newValNode->next = nullptr;
        newValNode->prev = nullptr;

        node* newEmptNode;
        newEmptNode->count = 0;
        newEmptNode->key = NULL;
        newEmptNode->left = nullptr;
        newEmptNode->right = nullptr;
        newEmptNode->parent = nullptr;
        newEmptNode->next = nullptr;
        newEmptNode->prev = nullptr;

        if (isEmpty())
        {
            root = newEmptNode;
        }
        else
        {
            node* current;
            node* p;
            p = root;
            current = root->right;
            while(current)
            {
                p = current;
                current = current->right;
            }
            p->right = newEmptNode;
            newEmptNode->parent = p;
            
            newEmptNode->left = newValNode;
            newValNode->parent = newEmptNode;
        }
    }
};

#endif