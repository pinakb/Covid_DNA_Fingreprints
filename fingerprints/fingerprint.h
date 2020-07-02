#ifndef FINGERPRINT_H
#define FINGERPRINT_H
#include<string>
#include<iostream>
#include<sstream>
#include<fstream>
#define MAX_CHAR 5
using namespace std;

class fingerprint
{
    public:
        struct node{
            int startIndex;
            int endIndex;
            int nodeId;
            int childCounter=0;
            node* child[MAX_CHAR];
            node* parent;
        };

        fingerprint();
        virtual ~fingerprint();


        //function prototypes
        void readFile(string input);
        void buildTree();

        //variables


    private:
        //function prototypes
        void findPath(node* root, string seq);
        string getEdgeLabel(node* variable);
        int getChildIndex(char c);
        int getCommonLength(string label, string suffix);
        void leafCounter(node* r);


        //variables
        node* root = (node*) malloc(sizeof(node));
        string sequence="";
        int nodeCount=1;
        int leafCount=0;
        int counter=0;
        ofstream outfile;
        string ReportPath = "F:/GitHub/DNA_Fingerprints/input_files/Report.txt";
        int sequence_len;
        string testSequence;

};

#endif // FINGERPRINT_H
