#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <cctype>
#include <iomanip>
#include <algorithm>

using namespace std;

int main() {
    string file1 = "Duomenys.txt";

    map<string, pair<int, set<int>>> wordMap;
    map<int, string> linkMap;
    ifstream file;
    string line, word;
    int lineNum = 1;

    file.open(file1);
    while (getline(file, line)) {
        size_t found = line.find_first_of(",.!:;?'()[]{}…’–&-.");
        while (found != string::npos) {
            line.erase(found, 1);
            found = line.find_first_of(",.!:;?'()[]{}…’–&-.", found + 1);
        }
        line.erase(remove(line.begin(), line.end(), '"'), line.end());
        istringstream iss(line);
        while (iss >> word) {
            wordMap[word].first++;
            wordMap[word].second.insert(lineNum);
        }
        lineNum++;
    }
    file.close();

    ofstream outFile;
    outFile.open("Zodziu_pasikartojimai.txt");
    for (const auto &entry : wordMap) {
        if (entry.second.first > 1) {
            outFile << entry.first << ", " << entry.second.first << endl;
        }
    }
    outFile.close();

    outFile.open("Zodziu_vieta_tekste.txt");
    outFile << "Zodis                Eilute"<< endl;
    for (const auto &entry : wordMap) {
        if (entry.second.first > 1) {
            outFile << left << setw(21) << entry.first;
            for (int line : entry.second.second) {
                outFile << line << ", ";
            }
            outFile << endl;
        }
    }
    outFile.close();

    file.open(file1);
    int linkNum = 0;
    vector<string> linkEndings = {".lt", ".com", ".org", ".net", ".int", ".edu", ".gov", ".mil", ".lt/", ".com/", ".org/", ".net/", ".int/", ".edu/", ".gov/", ".mil/"};
    while (getline(file, line)) {
        istringstream iss(line);
        while (iss >> word) {
            for (const string& ending : linkEndings) {
                if (word.find(ending) != string::npos) {
                    linkMap[linkNum++] = word;
                    break;
                }
            }
        }
    }
    file.close();

    outFile.open("Linkai.txt");
    for (const auto &entry : linkMap) {
        outFile << entry.first + 1 << ". " << entry.second << endl;
    }
    outFile.close();

    cout << "Duomenys apdoroti ir issaugoti failuose: Zodziu_pasikartojimai.txt, Zodziu_vieta_tekste.txt, Linkai.txt" <<endl;
}
