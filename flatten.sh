#!/usr/bin/env sh

Covid_inputDir="/f/GitHub/DNA_Fingerprints/original_files/Covid_*"
Sars_inputDir="/f/GitHub/DNA_Fingerprints/original_files/SARS*"
Mers_inputDir="/f/GitHub/DNA_Fingerprints/original_files/MERS*"
outputDir="/f/GitHub/DNA_Fingerprints/input_files/"

for file in $Covid_inputDir
do
	cp $file temp.fasta
	sed -i '1d' temp.fasta
	echo '$' >> temp.fasta
	newFile=${file:42:9}
	awk '{ printf("%s",$0); }  END {printf("\n");}' < temp.fasta > $outputDir/$newFile.txt
	rm -f temp.fasta
done

for file in $Sars_inputDir
do
	cp $file temp.fasta
	sed -i '1d' temp.fasta
	echo '$' >> temp.fasta
	newFile=${file:42:13}
	awk '{ printf("%s",$0); }  END {printf("\n");}' < temp.fasta > $outputDir/$newFile.txt
	rm -f temp.fasta
done

for file in $Mers_inputDir
do
	cp $file temp.fasta
        sed -i '1d' temp.fasta
	echo '$' >> temp.fasta
	newFile=${file:42:13}
	awk '{ printf("%s",$0); }  END {printf("\n");}' < temp.fasta > $outputDir/$newFile.txt
	rm -f temp.fasta
done

