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
    deleteTree(root);
    database.clear();
    colors.clear();
}

int fingerprint::getChildIndex(char c)
{
    static set<char>indexSet(sequence.begin(), sequence.end());
    set<char>::iterator itr;
//    int index= 0;
    for(itr= indexSet.begin(); itr!=indexSet.end(); ++itr)
    {
        if(*itr ==c)
        {
            if(*itr=='$')
                return 0;
            else if(*itr == 'A')
                return 1;
            else if(*itr == 'C')
                return 2;
            else if(*itr == 'G')
                return 3;
            else if(*itr == 'T')
                return 4;
            else
                return 5;
        }
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
    sequence+=to_string(fileCounter);
    database.push_back(sequence);
    fileCounter++;
}

void fingerprint::buildTree()
{
    if(database.size()>10)
    {
        cout<<"No more than 10 input files can be handled."<<endl;
        cout<<"Total number of input files: "<<database.size()<<endl;
        return;
    }

    root->nodeId = sequence.length() + nodeCount;
    sequence = "";
    vector<int> endIndices;
    int last=0;
    int prev=0;
    for(int x=0; x<database.size(); x++)
    {
        string temp = database[x];
        if(x==0)
        {
            last= temp.length()-1;
            endIndices.push_back(last+prev);
            prev = last+prev;
        }
        else
        {
            last = temp.length();
            endIndices.push_back(last+prev);
            prev = last+prev;
        }

    }


    outfile.open(ReportPath.c_str(), ios::out);
    //start of suffix insertion
    for(int y=0; y< database.size(); y++)
    {
        sequence += database[y];
    }
    sequence_len = sequence.length();
    cout<<"Insert sequence of length: "<<sequence_len<<endl;

    for(int i =0; i<sequence.length(); i++)
    {
        string seq = sequence.substr(i, (sequence.length()-i));
        findPath(root, seq);
    }
    cout<<"Suffix Tree Generated."<<endl;
    //end of suffix insertion

    //Coloring
    pruneLeavesAndColor(endIndices);
    cout<<"Pruning of leaves complete."<<endl;
    colorNodes(root);
    cout<<"Coloring of tree is complete"<<endl;
    for(int y=0; y<database.size(); y++)
    {
        string fp = getFingerprint(colors[y]);
        outfile<<"for color: "<<colors[y]<<" fingerprint: "<<fp<<endl;
    }
    cout<<"Check the report file to verify Fingerprints"<<endl;
    //end of coloring

    cout<<"total number of Internal Nodes: "<<nodeCount<<endl;
    leafCounter(root);
    cout<<"total number of leaves: "<<counter<<endl;
    outfile.close();
}

void fingerprint::findPath(node* root, string suffix)
{
    node* curr = root;
    node* temp = root;

    if(curr->childCounter ==0)
    {
        curr->childCounter+=1;
        node* leaf = new node();
        leaf->color = "black"; //default color
        for(int p=0; p<MAX_CHAR; p++)
        {
            leaf->child[p]=NULL;
        }
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
                node* leaf = new node();
                leaf->color= "black"; //default color
                for(int p=0; p<MAX_CHAR; p++)
                {
                    leaf->child[p]=NULL;
                }
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
                            node* internalNode = new node();
                            internalNode->color = "black"; //default color
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
            if(temp->nodeId <=sequence_len)
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

void fingerprint::pac(node* root, int prevIndex, int currIndex, string c)
{
    node* curr = root;
    node* temp = NULL;
    int last = currIndex+1;
    int first;
    if(prevIndex==0)
    {
        first = prevIndex+1;
    }
    else
    {
        first = prevIndex+2;
    }

    for(int z =0; z<MAX_CHAR; z++)
    {
        if(curr->child[z] !=NULL)
        {
            temp = curr->child[z];
            if(temp->nodeId >= first && temp->nodeId <= last)
            {
                temp->endIndex = currIndex;
                temp->color= c;
                temp->visited = true;
            }
            else
            {
                pac(temp, prevIndex, currIndex, c);
            }
        }
    }
}

void fingerprint::pruneLeavesAndColor(vector<int> endIndices)
{
    int currIndex=0;
    int prevIndex=0;
    for(int i=0; i<endIndices.size(); i++)
    {
        currIndex = endIndices[i];
        if(i==0)
        {
            prevIndex= 0;
        }
        else
        {
            prevIndex= endIndices[i-1];
        }
        string c = colors[i];
        pac(root, prevIndex, currIndex, c);

    }
}


set<string> fingerprint::visitChildren(node* root)
{
    set<string> childColor;
    for(int x=0; x<MAX_CHAR; x++)
    {
        if(root->child[x]==NULL)
            continue;
        else
        {
            node* temp = root->child[x];
            childColor.insert(temp->color);
        }
    }
    return childColor;
}

void fingerprint::colorNodes(node* root)
{
    if(root==NULL || root->visited == true)
    {
        return;
    }
    for(int i=0; i<MAX_CHAR; i++)
    {
        colorNodes(root->child[i]);
    }
    set<string> childColor = visitChildren(root);
    if(childColor.size()>1)
    {
        root->color = mix;
        root->visited = true;
    }
    else
    {
        auto itr = childColor.begin();
        root->color = *itr;
        root->visited = true;
    }
}

void fingerprint::searchFP(string *retString, node* root, string c)
{
    if(root == NULL)
    {
        return;
    }
    for(int i=0; i<MAX_CHAR; i++)
    {
        if(root->child[i]!= NULL)
        {

            node* temp = root->child[i];
            if(temp->color == c)
            {

                char tempFirstChar = sequence[temp->startIndex];
                string pathLabel="";
                node* frontTracer = root;
                node* backTracer = root;
                while(frontTracer->parent!= NULL)
                {
                    backTracer = frontTracer;
                    frontTracer = frontTracer->parent;
                    string elabel = getEdgeLabel(backTracer);
                    reverse(elabel.begin(), elabel.end());
                    pathLabel+=elabel;
                }
                reverse(pathLabel.begin(), pathLabel.end());
                pathLabel+=tempFirstChar;

                string finalString;
                string check = "$";
                size_t found = pathLabel.find(check);
                if (found != string::npos)
                {
                    continue;
                }

                if(*retString == "NULL" && pathLabel.length()>2)
                {
//                    outfile<<c<<" pathlabel: "<<pathLabel<<endl;
//                    outfile<<"--------------------------------------"<<endl;
                    *retString = pathLabel;
                }
                else
                {
                    if(retString->length()> pathLabel.length() && pathLabel.length()>2)
                    {
                        *retString = pathLabel;
//                        outfile<<c<<" pathlabel: "<<pathLabel<<endl;
//                        outfile<<"--------------------------------------"<<endl;
                    }
                }
            }
            else
            {
                    searchFP(retString, root->child[i], c);
            }
        }
        else
        {
            continue;
        }
    }
}


string fingerprint::getFingerprint(string c)
{
    string retString = "NULL";
    searchFP(&retString, root, c);
    return retString;
}


void fingerprint:: deleteTree(node* root)
{
    if(root == NULL)
    {
        return;
    }
    for(int i=0; i<MAX_CHAR; i++)
    {
        deleteTree(root->child[i]);
    }
    free(root);
}

