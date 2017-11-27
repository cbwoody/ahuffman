#ifndef __ADAPTIVEHUFFMAN_H__
#define __ADAPTIVEHUFFMAN_H__
#include <string>
#include <fstream>

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
    bool DEBUG = true;

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
    };

    /**
     * Pointer to the root of the tree.
     **/
    node *root;

    int encode(string *msg, char **result, int rbuff_size);
    int decode(string *msg, char **result, int rbuff_size);

    /**
     * Constructor for the adaptive huffman tree will build the zero node from
     * the alphabet given.
     * @param alphabet a pointer to a string of characters that will be used 
     * as the alphabet.
     **/
    AdaptiveHuffman(string alphabet)
    {   
	root = new node;
	root->count = 0;
        root->key = '\0';
        root->left = nullptr;
        root->right = nullptr;
        root->parent = nullptr;
        root->next = nullptr;
        root->prev = nullptr;

        char c;
        ifstream file(alphabet);

        if(!file)
        {
            cout << "Could not open file." << endl;
            exit(1);
        }
        else
        {
            while (file >> c)
            {
                insertZeroNode(c);
            }
            file.close();
        }
    }

    //Deconstructor
    //~AdaptiveHuffman();

    /**
     * Creates a new node to be inserted in the zero node. It will walk the 
     * tree to the right until it gets to the end, and create an empty parent
     * node. Then the left child of this parent node will be set as the value
     * node. The character c will be stored in the value node.
     **/
    void insertZeroNode(char c)
    {
        node* newValNode;
	newValNode = new node;
        newValNode->count = 0;
        newValNode->key = c;
        newValNode->left = nullptr;
        newValNode->right = nullptr;
        newValNode->parent = nullptr;
        newValNode->next = nullptr;
        newValNode->prev = nullptr;

        node* newEmptNode;
	newEmptNode = new node;
        newEmptNode->count = 0;
        newEmptNode->key = 'p';
        newEmptNode->left = nullptr;
        newEmptNode->right = nullptr;
        newEmptNode->parent = nullptr;
        newEmptNode->next = nullptr;
        newEmptNode->prev = nullptr;

        node* current;
        node* p;
        p = root;
        current = root->right;
        while(current != NULL)
        {
            p = current;
            current = current->right;
        }
        p->right = newEmptNode;
        newEmptNode->parent = p;
        
        newEmptNode->left = newValNode;
        newValNode->parent = newEmptNode;
        
	//after every insertion the tree will print
	if (DEBUG)
	{
	    printZeroNode(root);
	    cout << endl;
	    cout << "_____________________________" << endl;
	}
    }

    /**
    * 
    **/
    void printZeroNode(node* p)
    {
	int cnt = 0;
	char letter;
	string path;

	if (p == root)
	{
	    cout << "At root" << endl;
	    p = p->right;
	}
	while (p != NULL)
	{
	    //cout << "Count = " << cnt << endl;
	    cout << (p->left)->key << endl;
	    letter = p->left->key;
	    path = getCode(root, letter);
	    cout << path << endl;
	    //cnt++;
	    p = p->right;
	}
    }

    string getCode(node* p, char c)
    {
	node* current;
	string path;

	if (p->left)
	{
		if (p->left->key == c)
		{
		    current = p->left;
		    path = pathToRoot(current);
		    return path;
		}
		else
		{
		    getCode(p->left, c);
		}
	}
	if (p->key == c)
		{
		    current = p;
		    path = pathToRoot(current);
		    return path;
		}
	if (p->right)
	{
		if (p->right->key == c)
		{
		    current = p->right;
		    path = pathToRoot(current);
		    return path;
		}
		else
		{
		    getCode(p->right, c);
		}
	}
    }

    string pathToRoot(node* p)
    {
	node* current = p;
	string path;
	while(current->parent != NULL)
	{
	    current = current->parent;
	    if (current->left == p)
	    {
		path = path + "0";
	    }
	    else
	    {
		path = path + "1";
	    }
	    p = current;
	}
	return path;
    }

    /**
    * Prints the tree.
    * @param p root node to start printing from.
    **/
	void print(node* p)
	{
		if (p != NULL)
		{
			if (p->left)
			{
				print(p->left);
			}
			cout << endl;
			cout << "Printed key: " << p->key << endl;
			if (DEBUG)
			{
				cout << endl;
				if ((p->parent) != NULL)
				{
					cout << " printed parent: " << (p->parent)->key;
				}
				else
				{
					cout << " Printed Parent is NULL. ";
				}
				if ((p->left) != NULL)
				{
					cout << ", printed left: " << (p->left)->key;
				}
				else
				{
					cout << " Printed left is NULL. ";
				}
				if ((p->right) != NULL)
				{
					cout << ", printed right: " << (p->right)->key;
				}
				else
				{
					cout << " Printed right is NULL. ";
				}
			}
			if (p->right)
			{
				print(p->right);
			}
		}
		else
		{
			return;
		}
	}
};

#endif
