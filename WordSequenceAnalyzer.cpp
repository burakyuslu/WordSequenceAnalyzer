// Author: Burak Yigit Uslu
// Submitted on 30th of October, 2023

#include <iostream>
#include <unordered_map>
#include <map>
#include <fstream>
#include <sstream>
#include <regex>
#include <sys/stat.h>
#include <filesystem>

using namespace std;

// helper function for sorting the map into a sorted vector
bool compareCountAndSeq(pair<string, int>& firstPair, pair<string, int>& secondPair) { 
    if( firstPair.second != secondPair.second){
        return firstPair.second > secondPair.second; 
    } else{
        return 0 > strcmp( firstPair.first.c_str(), secondPair.first.c_str());
    }
}

// helper function for sorting the map into a sorted vector
vector<pair<string, int>> sortMap(map<string, int>& map) 
{ 
    vector<pair<string, int> > sortedVector; 
    for (auto& it : map) { 
        sortedVector.push_back(it); 
    } 
 
    sort(sortedVector.begin(), sortedVector.end(), compareCountAndSeq); 
    return sortedVector;
} 

int main(int argc, char** argv) {
    cout << "Word sequence analyzer started..." << endl;

    // Check that the program is invoked with correct number of arguments with the defined syntax
    // and initialize the input and output paths
    string pathToInputFile, pathToOutputFolder;
    if (argc != 5){
        cerr << "Program invoked with incorrect number of arguments. \nCorrect invocation of the program: ./program-name -i <path-to-input-file> -o <path-to-output-file>" << endl;
        return 1;
    }
    
    if (strcmp( argv[1], "-i") != 0){
        cerr << "Input path specified incorrectly. \nCorrect invocation of the program: ./program-name -i <path-to-input-file> -o <path-to-output-file>" << endl;
        return 1;

    } else { // initialize the input Path
        pathToInputFile = argv[2];
    }

    if(strcmp( argv[3], "-o")  != 0){ // if no output path is specified, by default output to the same path as the program
        cerr << "Output path specified incorrectly. \nCorrect invocation of the program: ./program-name -i <path-to-input-file> -o <path-to-output-file>" << endl;
        return 1;
    } else {
            pathToOutputFolder = argv[4];
    }

    // read the given input file
    ifstream input(pathToInputFile);
    if ( ! input.is_open()) {
        cerr << "Cannot open the specified input file. Please check the given input directory." << std::endl;
        return 1;
    }

    // check that output directory is a valid directory
    struct stat sb;
    if (  stat(pathToOutputFolder.c_str(), &sb) != 0) {
        cerr << "Cannot open the specified output directory. Please check the specified output directory." << std::endl;
        return 1;
    }


    // process the input file line by line find all word sequences in that line (since we separate sequences by line breaks)
    string currentLine;
    map<string, int> wordSequences; // use a hashmap to hold the word sequences and the corresponding counts.  
    regex wordSeparatingCharacters("[ /,\t-]+"); // regex for separators between words
    int longestSequenceOfWords = 0;

    while( getline(input, currentLine)){

        // convert current line to all lower case since the sequences are considered case insensitive
        transform(currentLine.begin(), currentLine.end(), currentLine.begin(), ::tolower); 

        // parse the current line into an array of words
        vector<string> arrOfWordsInCurrentLine;
        sregex_token_iterator iter( currentLine.begin(), currentLine.end(), wordSeparatingCharacters, -1);
        for (sregex_token_iterator iteratorDelimiter; iter != iteratorDelimiter; ++iter) {
            arrOfWordsInCurrentLine.push_back((iter->str()));
        }

        if(arrOfWordsInCurrentLine.size() > longestSequenceOfWords){
            longestSequenceOfWords = arrOfWordsInCurrentLine.size(); // find the longest sequence of words (one with most element)
        }

        while(arrOfWordsInCurrentLine.size() != 0){

            string currentWordSequence = "";
            for (string& currentWord : arrOfWordsInCurrentLine){
                currentWordSequence = currentWordSequence + currentWord + " ";
                wordSequences[currentWordSequence] += 1;
            }

            // we have considered every sequence in that line that starts with the current first word in the vector
            // so we remove it and continue to consider every sequence that starts with the originally 2nd word in the line
            arrOfWordsInCurrentLine.erase(arrOfWordsInCurrentLine.begin());    
        }
    }

    input.close(); // we have collected all the word sequences in our hashmap, we don't need the input file anymore

    // if there are already files with the names we want to create, delete them first
    for(int i = 1; i <= longestSequenceOfWords; i++){
        string fileToRemove = pathToOutputFolder + "/occurrence_length_" + to_string(i) + ".csv";
        filesystem::remove( fileToRemove);
    }

    vector<pair <string, int>> sortedSequenceAndValues = sortMap(wordSequences);

    for (auto const& [currentWordSeq, count] : sortedSequenceAndValues){

        // find the length of the word sequence we have
        vector<string> arrOfWordsInCurrentSequence;
        sregex_token_iterator iter( currentWordSeq.begin(), currentWordSeq.end(), wordSeparatingCharacters, -1);
        for (sregex_token_iterator iteratorDelimiter; iter != iteratorDelimiter; ++iter) {
            arrOfWordsInCurrentSequence.push_back((iter->str()));
        }
        int lengthOfCurrentSeq = arrOfWordsInCurrentSequence.size();

        // determine the corresponding file name and path based on the length
        string outputFileNameAndPath = pathToOutputFolder + "/occurrence_length_" + to_string(lengthOfCurrentSeq) + ".csv";
        ofstream outputFile(outputFileNameAndPath, ios::app);

        // write to the file
        outputFile << currentWordSeq.substr(0, currentWordSeq.size()-1) << "," << count << std::endl;
        outputFile.close();
    }

    cout << "Program execution finished successfully." << endl;
    return 0;
}

