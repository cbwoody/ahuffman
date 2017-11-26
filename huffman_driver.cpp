#include <iostream>
#include <string>
#include "adaptivehuffman.h"

using namespace std;

int main(int argc, char const *argv[])
{
    if(argc != 4){
        // Invalid number of files
        cout << "Invald number of command line arguments" << endl;
        return 1;
    }
    string *alphabet_file_name = new string(argv[1]);
    AdaptiveHuffman tree(alphabet_file_name);

    string *message_file_name = new string(argv[2]);
    string *operation = new string(argv[3]);
    return 0;
}