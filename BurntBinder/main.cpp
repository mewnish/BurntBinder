#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

bool bindFiles(const vector<string>& fileNames, const string& outputFileName) {
    ofstream outputFile(outputFileName, ios::binary | ios::out);
    if (!outputFile) {
        cerr << "Error opening output file " << outputFileName << endl;
        return false;
    }

    for (const auto& fileName : fileNames) {
        ifstream inputFile(fileName, ios::binary | ios::in);
        if (!inputFile) {
            cerr << "Error opening input file " << fileName << endl;
            return false;
        }

        inputFile.seekg(0, ios::end);
        streampos fileSize = inputFile.tellg();
        inputFile.seekg(0, ios::beg);

        vector<char> buffer(fileSize);
        if (!inputFile.read(buffer.data(), fileSize)) {
            cerr << "Error reading file " << fileName << endl;
            return false;
        }

        outputFile.write(buffer.data(), fileSize);

        inputFile.close();
    }

    outputFile.close();
    return true;
}

int main() {
    vector<string> filesToBind = { "file1.txt", "file2.txt", "file3.txt" }; // Example file names
    string outputFileName = "output.bin"; // Output file name

    if (bindFiles(filesToBind, outputFileName)) {
        cout << "Files bound successfully into " << outputFileName << endl;
    }
    else {
        cerr << "Error binding files" << endl;
        return 1;
    }

    return 0;
}
