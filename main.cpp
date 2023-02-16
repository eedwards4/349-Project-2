/*
Ethan Edwards, Joe Coon
   CS 349: Problem Solving in a Team Programming Environment
       --> Taught by Dr. Gurman Gill; Sonoma State University

 "Speed Can Cost You" Program.
 */

#include <string>
#include <fstream>
#include <iostream>

using namespace std;

string calcTimeDiff(int sp1, int sp2, int dist);
float convertUnits(float convTime);
string timeFormatter(string timeRaw);
void initializeFiles(fstream& inFile, fstream& outFile, string& fname, int argc, const char* argv[]);


/*
 * Process input data on driver speeds into calculated travel time differences and
 * output it to a file.
 */
int main(int argc, const char* argv[]){
    int speed1 = 1, speed2 = 1, distance = 1;
    fstream inFile, outFile;
    string fname;

    initializeFiles(inFile, outFile, fname, argc, argv); //manage I/O files

    if (inFile.is_open()) {
        cout << "Opening " << fname  << "..." << endl;
        inFile >> distance;
        inFile >> speed1;
        inFile >> speed2;
        while (speed1 + speed2 + distance != 0) { //until terminal line has been read
            outFile << calcTimeDiff(speed1, speed2, distance) << endl; //generate a time difference string and output it

            inFile.ignore(); //ignore newline character, then grab values per line
            inFile >> distance;
            inFile >> speed1;
            inFile >> speed2;
        }
        cout << "Finished." << endl;
        inFile.close();
        outFile.close();
    }
    return 0;
}

/*
 * Calculate the difference in time travelled for two different speeds over 1 distance.
 * Returns a string in the form hh:mm:ss
 */
string calcTimeDiff(int sp1, int sp2, int dist){
    float hours, min, sec;
    string result;

    if (sp1 == 0 || sp2 == 0) { //return 0 if either speed is 0, avoid NaN output
        hours = min = sec = 0;
    }
    else {
        hours = sp1 <= sp2
                ? (dist / (float)sp1) - (dist / (float)sp2)
                : (dist / (float)sp2) - (dist / (float)sp1);
        min = convertUnits(hours);
        sec = convertUnits(min);
    }

    //build string from values
    result.append(to_string(hours));
    result.append(":");
    result.append(to_string(min));
    result.append(":");
    result.append(to_string(sec));

    return timeFormatter(result); //pass result formatted to hh:mm:ss
}

/*
 * convert the float time down by a factor of 60, works for hours and minutes.
 */
float convertUnits(float convTime) {
    while (convTime > 1) {
        convTime--;
    }
    return convTime * 60;
}

/*
 * Convert from float time to int time, and add leading 0s if necessary.
 * timeRaw must be a string formatted with floats in "hh:mm:ss" form.
 */
string timeFormatter(string timeRaw){
    string h, m, s;
    char sep = ':';

    h = timeRaw.substr(0, timeRaw.find('.'));
    if (stoi(h) < 10){h = "0" + h;}
    timeRaw.erase(0, timeRaw.find(':') + 1);
    m = timeRaw.substr(0, timeRaw.find('.'));
    if (stoi(m) < 10){m = "0" + m;}
    timeRaw.erase(0, timeRaw.find(':') + 1);
    s = timeRaw.substr(0, timeRaw.find('.'));
    if (stoi(s) < 10){s = "0" + s;}

    return h + sep + m + sep + s;
}


/*
 *  Manages file initialization by detecting program arguments and accordingly using supplied files
 *  or prompting the user for sufficient files to execute the rest of the program.
 *
 *  argv[1] is expected to contain an input filepath. argv[2] is expected to contain an output filepath.
 *  fname, inFile, and outFile are all expected to be declared, uninitialized variables.
 */
void initializeFiles(fstream& inFile, fstream& outFile, string& fname, int argc, const char* argv[]) {
    if (argc == 3) {
        fname = argv[1];
        inFile.open(argv[1]);
        outFile.open(argv[2]);
    }
    else if (argc == 2) {
        char yesno = '\0';
        fname = argv[1];
        cout << "Found " << fname << " for input file. Continue using " << fname << " for input? (y/n) ";
        cin >> yesno;
        if (yesno == 'n') {
            fname.clear();
            cout << "Enter the new input filename: ";
            cin >> fname;
        }
        inFile.open(fname);
    }
    while (!outFile.is_open()) {
        fname.clear();
        cout << "Please provide an existing filename to overwrite, or a new filename to create: ";
        cin >> fname;
        outFile = fstream(fname, ios::out); /*invoking the fstream constructor will create a new file
                                              if one does not already exist.*/
    }
    while (!inFile.is_open() && fname != "##") {
        fname.clear();
        cout << "No input file was found. Please provide a relative path and filename for an input file "
             << "(enter ## to close the program): ";
        cin >> fname;
        inFile.open(fname);
    }
}