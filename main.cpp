/*
Ethan Edwards, Joe Coon
   CS 349: Problem Solving in a Team Programming Environment
       --> Taught by Dr. Gurman Gill; Sonoma State University
 */

#include <chrono> // https://en.cppreference.com/w/cpp/chrono/hh_mm_ss
#include <string>
#include <fstream>
#include <iostream>

std::string calcTimeDiff(int sp1, int sp2, int dist);
float convertUnits(float convTime);

int main(){
    int speed1 = 1, speed2 = 1, distance = 1;
    std::fstream inFile("input.txt"), outFile("testout.txt");
    std::string timeDiff;

    // File input stuff
    if (inFile.is_open()) {
        while (speed1 + speed2 + distance != 0) {
            inFile >> distance;
            inFile >> speed1;
            inFile >> speed2;
            inFile.ignore();
            timeDiff = calcTimeDiff(speed1, speed2, distance);

            // Logic for organizing output
            outFile << timeDiff << std::endl;
            std::cout << timeDiff << std::endl;
        }
    }
    inFile.close();
    outFile.close();
}

/*
 * Calculate the difference in time travelled for two different speeds over 1 distance.
 * Returns a string in the form "x.xxxxxxx:x.xxxxxxxx:x.xxxxxxxx".
 */
std::string calcTimeDiff(int sp1, int sp2, int dist){
    float hours, min, sec;
    std::string result;

    if (dist == 0) { //return 0 if there is no distance travelled, avoid NaN output
        hours = min = sec = 0;
    }
    else {
        hours = sp1 >= sp2
                ? ((float)sp1 / dist) - ((float)sp2 / dist)
                : ((float)sp2 / dist) - ((float)sp1 / dist);
        min = convertUnits(hours);
        sec = convertUnits(min);
    }

    //build string from values
    result.append(std::to_string(hours));
    result.append(":");
    result.append(std::to_string(min));
    result.append(":");
    result.append(std::to_string(sec));

    return result;
}

/*
 * convert the float time down by a factor of 60, works for hours and minutes.
 */
float convertUnits(float convTime) {
    while (convTime > 1 && convTime > 0) {
        convTime--;
    }
    return convTime * 60;
}