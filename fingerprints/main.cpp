#include<iostream>
#include"fingerprint.h"

using namespace std;

int main()
{
    string input = "F:/GitHub/DNA_Fingerprints/input_files/Covid_Ind.txt";
    fingerprint f;
    f.readFile(input);
    f.buildTree();
}
