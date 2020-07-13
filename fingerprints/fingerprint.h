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
        void pruneLeavesAndColor(vector<int> endIndices);
        void pac(node* root, int index, string c);
        set<string> visitChildren(node* root);
        void colorNodes(node* root);
        void deleteTree(node* root);
        string getFingerprint(string c);
        void searchFP(string *retString, node* root, string c);


        //variables
        int fileCounter=0;
        vector<string> database;
        vector<string> colors{ "red", "blue", "green", "yellow", "orange", "cyan", "magenta", "gold", "silver", "bronze" };
        string mix = "white";
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
