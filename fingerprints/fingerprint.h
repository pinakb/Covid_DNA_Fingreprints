#ifndef FINGERPRINT_H
#define FINGERPRINT_H
#include<string>
#include<iostream>
#include<sstream>
#include<fstream>
#include<vector>
#include<set>
#define MAX_CHAR 6
using namespace std;

class fingerprint
{
    public:
        //Node structure definition
        struct node{
            int startIndex;
            int endIndex;
            int nodeId;
            int childCounter=0;
            string color;
            bool visited;
            node* child[MAX_CHAR];
            node* parent;
        };

        //ctor
        fingerprint();
        virtual ~fingerprint();
        //end of ctor

        //function prototypes
        void readFile(string input);
        void buildTree();

        //variables
        string ReportPath;

    private:
        //function prototypes
        void findPath(node* root, string seq);
        string getEdgeLabel(node* variable);
        int getChildIndex(char c);
        int getCommonLength(string label, string suffix);
        void leafCounter(node* r);
        void pruneLeavesAndColor(vector<int> endIndices);
        void pac(node* root, int prevIndex, int currIndex, string c);
        set<string> visitChildren(node* root);
        void colorNodes(node* root);
        void deleteTree(node* root);
        string getFingerprint(string c);
        void searchFP(string *retString, node* root, string c);


        //variables
        ofstream outfile;

        int fileCounter=0;
        vector<string> database;
        vector<string> colors{ "red", "blue", "green", "yellow", "orange", "cyan", "magenta", "gold", "silver", "bronze" };
        string mix = "white";
        node* root = new node();
        string sequence="";
        int nodeCount=1;
        int leafCount=0;
        int counter=0;
        int sequence_len;
        string testSequence;

};

#endif // FINGERPRINT_H
