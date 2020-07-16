#include<iostream>
#include"fingerprint.h"
using namespace std;

int main()
{
    fingerprint f;
    //Give input files
    string input1 = "F:/GitHub/DNA_Fingerprints/input_files/Covid_Aus.txt";
    f.readFile(input1);
    string input2 = "F:/GitHub/DNA_Fingerprints/input_files/Covid_Bra.txt";
    f.readFile(input2);
    string input3 = "F:/GitHub/DNA_Fingerprints/input_files/Covid_Ind.txt";
    f.readFile(input3);
    string input4 = "F:/GitHub/DNA_Fingerprints/input_files/Covid_USA.txt";
    f.readFile(input4);
    string input5 = "F:/GitHub/DNA_Fingerprints/input_files/Covid_Wuh.txt";
    f.readFile(input5);
    string input6 = "F:/GitHub/DNA_Fingerprints/input_files/SARS_2003_GU5.txt";
    f.readFile(input6);
    string input7 = "F:/GitHub/DNA_Fingerprints/input_files/SARS_2017_MK0.txt";
    f.readFile(input7);
    string input8 = "F:/GitHub/DNA_Fingerprints/input_files/MERS_2012_KF6.txt";
    f.readFile(input8);
    string input9 = "F:/GitHub/DNA_Fingerprints/input_files/MERS_2014_KY5.txt";
    f.readFile(input9);
    string input10 = "F:/GitHub/DNA_Fingerprints/input_files/MERS_2014_USA.txt";
    f.readFile(input10);

    //Output path
    string ReportPath = "F:/GitHub/DNA_Fingerprints/output.txt";
    f.ReportPath = ReportPath;

    //Get Fingerprints
    f.buildTree();
}
