#include "fingerprint.h"
#include<string>
#include<iostream>
#include<sstream>
#include<fstream>
#include<algorithm>
#include<set>

using namespace std;


fingerprint::fingerprint()
{
    for(int i=0; i<MAX_CHAR; i++)
    {
        root->child[i]=NULL;
    }
    root->parent = NULL;
    root->childCounter=0;
}

fingerprint::~fingerprint()
{
    //dtor
}

int fingerprint::getChildIndex(char c)
{
    static set<char>indexSet(sequence.begin(), sequence.end());
    set<char>::iterator itr;
    int index=0;
    for(itr= indexSet.begin(); itr!=indexSet.end(); ++itr)
    {
        if(*itr ==c)
        {
            return index;
        }
        index++;
    }
}

string fingerprint::getEdgeLabel(node* variable)
{
    int st; int ed;
    st = variable->startIndex;
    ed= variable->endIndex;
    string temp = sequence.substr(st, (ed-st)+1);
    return temp;
}

int fingerprint:: getCommonLength(string label, string suffix)
{
    int x=0;
    while(label[x]==suffix[x])
    {
        x++;
    }
    return x;
}

void fingerprint::readFile(string input)
{
    ifstream infile;
    infile.open(input.c_str(), ios::in);

    if(!infile)
    {
        cout<<"error in opening file";
    }
    else
    {
        infile>>sequence;
    }
    //cout<<sequence;
}

void fingerprint::buildTree()
{

    root->nodeId = sequence.length() + nodeCount;
    sequence_len = sequence.length();
    outfile.open(ReportPath.c_str(), ios::out);
    for(int i =0; i<sequence.length(); i++)
    {
        string seq = sequence.substr(i, (sequence.length()-i));
        //outfile<<"Inserting: "<<seq<<endl;
        outfile<<"-----------------------------------"<<endl;
        findPath(root, seq);
    }
    cout<<"Length of sequence: "<<sequence.length()<<endl;
    cout<<"total number of Internal Nodes: "<<nodeCount<<endl;
    outfile.close();
    leafCounter(root);
    cout<<"total number of leaves: "<<counter<<endl;
}

void fingerprint::findPath(node* root, string suffix)
{
    node* curr = root;
    node* temp = root;

    if(curr->childCounter ==0)
    {
        curr->childCounter+=1;
        node* leaf = (node*)malloc(sizeof(node));
        char c= suffix[0];
        int index = getChildIndex(c);
        curr->child[index] = leaf;
        leaf->startIndex = sequence_len- suffix.length();
        leaf->endIndex = sequence_len - 1;
        leafCount++;
        leaf->nodeId = leafCount;
        leaf->parent = curr;

        //log
//        outfile<<"leaf edge label: "<<getEdgeLabel(leaf)<<endl;
//        outfile<<"leaf start index: "<<leaf->startIndex<<endl;
//        outfile<<"leaf end index: "<<leaf->endIndex<<endl;
//        outfile<<"leaf node id: "<<leaf->nodeId<<endl;
//        outfile<<"************************************"<<endl;
        //end of log
        goto RET;
    }
    else if(curr->childCounter >0)
    {
        for(int i=0; i<MAX_CHAR; i++)
        {
            if(curr->child[i]==NULL && i!= MAX_CHAR-1)
            {
                continue;
            }
            else if(curr->child[i]==NULL && i== MAX_CHAR-1)
            {
            INS:
                curr->childCounter += 1;
                node* leaf = (node*)malloc(sizeof(node));
                char c= suffix[0];
                int index = getChildIndex(c);
                curr->child[index] = leaf;
                leaf->startIndex = sequence_len- suffix.length();
                leaf->endIndex = sequence_len - 1;
                leafCount++;
                leaf->nodeId = leafCount;
                leaf->parent = curr;
                //log
//                outfile<<"leaf edge label: "<<getEdgeLabel(leaf)<<endl;
//                outfile<<"leaf start index: "<<leaf->startIndex<<endl;
//                outfile<<"leaf end index: "<<leaf->endIndex<<endl;
//                outfile<<"leaf node id: "<<leaf->nodeId<<endl;
//                outfile<<"************************************"<<endl;
                //end of log
                goto RET;
            }
            else
            {//start1
                temp = curr->child[i];
                string label = getEdgeLabel(temp);
                if(label[0]!=suffix[0])
                {
                    if(i==MAX_CHAR-1)
                    {
                        goto INS;
                    }
                    else
                    {
                        continue;
                    }
                }
                else
                {//start2

                        int commonLength = getCommonLength(label, suffix);
                        if(commonLength == label.length())
                        {
                            string remainingString = suffix.substr(commonLength, (suffix.length() - commonLength));
                                //logs
//                            outfile<<"for temp "<<temp->nodeId<<endl;
//                            outfile<<"temp edge Label: "<<getEdgeLabel(temp)<<endl;
//                            outfile<<"Remaining string to be inserted: "<<remainingString<<endl;
//                            outfile<<"************************************"<<endl;
                                //end of logs
                            findPath(temp, remainingString);
                        }
                        else
                        {//start3
                            int commonLength = getCommonLength(label, suffix);
                            node* internalNode = (node*) malloc(sizeof(node));
                            internalNode->childCounter =0;
                            for(int p=0; p<MAX_CHAR; p++)
                            {
                                internalNode->child[p]=NULL;
                            }
                            nodeCount++;
                            internalNode->nodeId = (sequence_len+nodeCount);
                            internalNode->startIndex = temp->startIndex;
                            internalNode->endIndex = internalNode->startIndex+commonLength-1;
                            temp->startIndex = internalNode->endIndex +1;
                            string edgeLabel = getEdgeLabel(internalNode);
                            int index1 = getChildIndex(edgeLabel[0]);
                            curr->child[index1] = internalNode;
                            edgeLabel = getEdgeLabel(temp);
                            int index2 = getChildIndex(edgeLabel[0]);
                            internalNode->child[index2] = temp;
                            internalNode->childCounter +=1;
                            temp->parent = internalNode;
                            internalNode->parent = curr;
                            string remainingString = suffix.substr(commonLength, (suffix.length()-commonLength));
                            //logs
//                          outfile<<"for internalNode "<<internalNode->nodeId<<endl;
//                          outfile<<"internal Node edge Label: "<<getEdgeLabel(internalNode)<<endl;
//                          outfile<<"for temp "<<temp->nodeId<<endl;
//                          outfile<<"temp edge Label: "<<getEdgeLabel(temp)<<endl;
//                          outfile<<"Remaining string to be inserted: "<<remainingString<<endl;
//                          outfile<<"************************************"<<endl;
                            //end of logs
                            findPath(internalNode, remainingString);
                    }//end3
                    goto RET;
                }//end2
            }//end1
        }
    }
RET:
    return;
}


void fingerprint::leafCounter(node* r)
{
    node* curr = r;
    node* temp = NULL;
    for(int z =0; z<MAX_CHAR; z++)
    {
        if(curr->child[z] !=NULL)
        {
            temp = curr->child[z];
            string elabel= getEdgeLabel(temp);
            if(elabel[(elabel.length())-1]=='$')
            {
                counter++;
            }
            else
            {
                leafCounter(temp);
            }
        }
    }
}
