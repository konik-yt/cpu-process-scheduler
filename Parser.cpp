#include "Parser.h"

#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;

int loadProcessesFromFile(const string& path, Process out[], int maxCount) {
    ifstream file(path);
    if (!file) {
        cout << "Could not open " << path << "\n";
        return -1;
    }

    int count = 0;
    int lineNumber = 0;
    bool seenText = false;
    string line;

    while (getline(file, line)) {
        lineNumber++;

        // Skip blank lines.
        size_t firstChar = line.find_first_not_of(" \t\r");
        if (firstChar == string::npos) continue;

        // Skip a header line such as "pid arrival burst priority" if it is the first line with text.
        bool isFirstTextLine = !seenText;
        seenText = true;
        if (isFirstTextLine && isalpha(static_cast<unsigned char>(line[firstChar]))) continue;

        istringstream in(line);
        int pid, arrival, burst, priority;
        string extra;
        if (!(in >> pid >> arrival >> burst >> priority) || (in >> extra)) {
            cout << "Line " << lineNumber << ": expected 4 whole numbers: pid arrival burst priority\n";
            return -1;
        }
        if (arrival < 0 || burst < 1 || priority < 0) {
            cout << "Line " << lineNumber << ": arrival and priority must be 0 or more, burst must be 1 or more\n";
            return -1;
        }
        for (int i = 0; i < count; i++) {
            if (out[i].pid == pid) {
                cout << "Line " << lineNumber << ": PID " << pid << " appears twice\n";
                return -1;
            }
        }
        if (count == maxCount) {
            cout << "Line " << lineNumber << ": too many processes, the limit is " << maxCount << "\n";
            return -1;
        }

        out[count] = Process(pid, arrival, burst, priority);
        count++;
    }

    if (count == 0) {
        cout << path << " has no processes\n";
        return -1;
    }
    return count;
}
