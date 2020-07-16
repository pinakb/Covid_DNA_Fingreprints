# Covid_DNA_Fingreprints
Coronavirus represents a family of viruses which is the main pathogen in SARS (2003-2004), MERS (2012-2014), and in the novel coronavirus COVID-19 (Dec-2019).
Testing for COVID-19 relies on our ability to extract and amplify the part of the DNA that is unique to a strain. Since the viral genetic material is RNA, a process called Reverse Transcription PCR is used to first convert the extracted RNA into a DNA, and then the DNA copies are target amplified in order to ascertain if the strain is COVID-19 (positive) or not (negative). Identifying unique parts of these DNA strains becomes more important from COVID-19 testing point of view and from Vaccine development point of view. 

# Goal
Capturing shortest fingerprints of DNA strains which are unique to only one particular strain in the family of viruses. Identify "DNA fingerprints" for each of the 'k' strains. Here, a "DNA fingerprint" for a given strain 's_i' is defined to be a shortest unique substring of 's_i' - i.e., a substring that is present only in strain 's_i', and is the shortest possible such candidate.

# Dataset
COVID-19, MERS and SARS DNA sequences were obtained from NCBI Virus database. The NCBI Virus database has more than 3,000 genomes for this family of viruses.
For more information visit : https://www.ncbi.nlm.nih.gov/labs/virus/vssi/#/

Used Virus Strains:

1) Covid_Australia
2) Covid_Brazil
3) Covid_India
4) Covid_USA
5) Covid_Wuhan
6) MERS_2012_KF600620
7) MERS_2014_KY581694
8) MERS_2014_USA_KP223131
9) SARS_2003_GU553363
10) SARS_2017_MK062179

# Implementation
Build Genralized Suffix Tree (GST) of 'k' strains. 
Using the GST identify the nodes corresponding to short shared substrings instead of long shared substrings for which GSTs are traditionally used for. Short shared matches upon single character extension gurantees unique fingerprint for a given sequence 's_i'.
Implemenation of Graph coloring scheme to color the nodes in GST based upon string origins in a post-order traversal manner.

# Limitations:
1) Max value of 'k' is set to 10. Due to hardware limitations no more than 10 virus strains could be used.
2) Min value of 'k' is set to 2. This is obvious since a single strain will always be unique.

# Output:

1) Covid Australia fingerprint: ATACAGTG
2) Covid Brazil fingerprint: CGCGCTC
3) Covid India fingerprint: ACTAAGGA
4) Covid USA fingerprint: ACTTACCG
5) Covid Wuhan fingerprint: GTACAGTGAACAATGCTAGGGAGAGCTGCCTATATGGAAGAGCCCTAATGTGTAAAATTAATTTTAGTAGTGCTATCCCCATGTGATTTTAATAGCTTCTTAGGAGAATGACAAAAAAAAAAAAA
6) MERS_2012_KF600620 fingerprint: CAGGAGG
7) MERS_2014_KY581694 fingerprint: AACCTCG
8) MERS_2014_USA_KP223131 fingerprint: CAAGGGG
9) SARS_2003_GU553363 fingerprint: CCCCTTG
10) SARS_2017_MK062179 fingerprint: GTCCCC

# Testing the Sequences for their uniqueness

![image](https://user-images.githubusercontent.com/39387132/87611451-f2ed2300-c6bc-11ea-9ee8-96d445e196c3.png)
