//Madhuri Maniar
//MVM190002
//September 5, 2020
#include <iostream>
#include<fstream>
#include <string>
#include <sstream>
using namespace std;
//function prototypes
void printOut();
void drawNorth(ofstream&, bool, int, const string&, const string&);
void drawSouth(ofstream&, bool, int, const string&, const string&);
void drawEast(ofstream&, bool, int, const string&, const string&);
void drawWest(ofstream&, bool, int, const string&, const string&);

int main() {
/////////////////////////////////////////////////////////////////////////////////////////

////////////////////          DO  NOT CHANGE CODE BELOW THIS               //////////////

/////////////////////////////////////////////////////////////////////////////////////////

    ifstream infile("paint_base.txt");

    ofstream outfile("paint.txt", ios::binary);

    string c;

    if (infile)

        while (getline(infile, c))

            outfile << c << "\n";

    infile.close();

    outfile.close();

/////////////////////////////////////////////////////////////////////////////////////////

////////////////////          DO  NOT CHANGE CODE ABOVE THIS               //////////////

/////////////////////////////////////////////////////////////////////////////////////////

    //add your code here
    //creates a new 50x50 canvas every time you open the file
    outfile.open("paint.txt", ios::out);
    for (int i = 0; i < 50; i++) {
        for (int j = 0; j < 50; j++) {
            outfile<<" ";
        }
        outfile<<endl;
    }
    outfile.close();
    string input;
    //prompt user for name of the input file
    cout<<"Enter name of the input file. "<<endl;
    //reads the user input and opens that file
    getline(cin, input);
    infile.open(input);
    //opens the outfile in input and output mode to not delete the canvas created
    outfile.open("paint.txt", ios::in | ios::out);
    //if the file does not exist
    if (infile.fail())
        cout << "Error in opening file. " << endl;
    //if the file does exist
    else if (infile) {
        string pos1, pos2, pos3, pos4, pos5;
        string line, penmode, bold, print, direction, IgnoreLine;
        int distance, posNS=0, posEW=0,NewposNS,NewposEW;
        bool pendown;
        //shifts over one every time the file opens
        outfile.seekp(1L, ios::beg);
        //reading each line from text file
        while (getline(infile, line, '\n')) {

            //splitting up each character in each line of the file using the comma as a delimiter
            stringstream linestream(line);
            getline(linestream, pos1, ',');
            getline(linestream, pos2, ',');
            getline(linestream, pos3, ',');
            getline(linestream, pos4, ',');
            getline(linestream, pos5, ',');
            //assigns variables to each position
            penmode = pos1;
            direction = pos2;
            //checks to make sure the distance is an int
            try{
                distance=stoi(pos3);
            }
            catch (invalid_argument& e) {
                continue;
            }
            //checks to make sure the distance is not a negative
            if(distance<0)
                continue;
            //checks for an empty space instead of a char
            for (int i = 0; i < (int)line.length(); ++i) {
                if (line[i] == ' ')
                    continue;
            }
            //checks for extra spaces in the code
            int index = (int)line.find(' ');
            if (index>0)
                continue;
            //checks for extra commas
            index = (int)line.find(",,");
            if (index>0)
                continue;
            //checks for no commas
            index = (int)line.find(',');
            if (index==0)
                continue;
            //checks for extra comma after commands
            if (line.back()== ',')
                continue;

            //penmode
            //if the penmode is 1, the pen is up; no print
            if (penmode == "1")
                pendown = false;
            //if the penmode is 2, the pen is down; yes print
            else if (penmode == "2")
                pendown = true;
            //if the penmode isn't one or two
            else
                continue;

            //checks if there is a B or P in the command based on the length of command
            if (line.length() >= 5 && line.length() <= 6) {
                pos4 = "null";
                pos5 = "null";
            }
            //checks to make sure the commands is the correct length
            if (line.length()<5 || line.length()>10)
                continue;

            //for direction north
            if (direction == "N") {
                //checks to make sure the pointer has gone too north and out of the canvas
                NewposNS = posNS - distance;
                if (NewposNS>49 || NewposNS<0){
                } else {
                    //when the pointer is inside the bounds, execute
                    drawNorth(outfile, pendown, distance, pos4, pos5);
                    posNS = NewposNS;
                }
            }
                //for direction south
            else if (direction == "S") {
                //checks to make sure the pointer has gone too south and out of the canvas
                NewposNS = posNS + distance;
                if (NewposNS>49 || NewposNS<0){
                } else {
                    //when the pointer is inside the bounds, execute
                    drawSouth(outfile, pendown, distance, pos4, pos5);
                    posNS = NewposNS;
                }
            }
                //for direction east
            else if (direction == "E") {
                //checks to make sure the pointer has gone too east and out of the canvas
                NewposEW = posEW + distance;
                if (NewposEW>50 || NewposEW<0){
                } else {
                    //when the pointer is inside the bounds, execute
                    drawEast(outfile, pendown, distance, pos4, pos5);
                    posEW = NewposEW;
                }
            }
                //for direction west
            else if (direction == "W") {
                //checks to make sure the pointer has gone too west and out of the canvas
                NewposEW = posEW - distance;
                if (NewposEW>50 || NewposEW<0){
                } else {
                    //when the pointer is inside the bounds, execute
                    drawWest(outfile, pendown, distance, pos4, pos5);
                    posEW = NewposEW;
                }
            }
            else {
                continue;
            }

            //checks to make sure the pen is not up and bold and the same time
            if (penmode=="1" && pos4=="B")
                continue;
            //checks for extra P's
            if(pos4=="P"&&pos5=="P")
                continue;
            //checks for extra B's
            if (pos4=="B"&&pos5=="B")
                continue;
            //checks for flipped bold and print commands
            if (pos4=="P"&&pos5=="B")
                continue;

            //prints out to console every time print is called
            if (pos4 == "P" || pos5 == "P") {
                printOut();
            }
        }
    }
}
//function to print out lines from the output file to the console
void printOut()
{
    string linep;
    ifstream input("paint.txt");
    while (input)
    {
        //reads every line from the output file and prints to console
        getline(input, linep);
        cout<<linep<<endl;
    }
    cout<<endl;
    cout<<endl;
    input.close();
}

//if the direction is north
void drawNorth(ofstream& outfile, bool pendown, int distance, const string& pos4, const string& pos5)
{
    //when the pen is up, nothing prints and the pointer is moved north an amount of times
    if (!pendown){
        for (int i = 0; i < distance; ++i){
            outfile.seekp(-51, ios::cur);
        }
    }
    //when the pen is down, a character prints out moving north
    if (pendown){
        for (int i = 0; i < distance; i++){
            outfile.seekp(-52, ios::cur);
            //when both P and B are in the command
            if (pos5 == "P" && pos4 == "B") {
                outfile.put('#');
            }
            //when only B is in the command
            else if (pos4 == "B") {
                outfile.put('#');
            }
            //when only P is in the command
            else if (pos4 == "null"||pos4=="P") {
                outfile.put('*');
            }
            outfile.flush();
        }
    }
}
//if the direction is south
void drawSouth(ofstream& outfile, bool pendown, int distance, const string& pos4, const string& pos5)
{
    //when the pen is up, nothing prints and the pointer is moved south an amount of times
    if (!pendown){
        for (int i = 0; i < distance; ++i){
            outfile.seekp(51, ios::cur);
        }
    }
    //when the pen is down, a character prints out moving south
    if (pendown){
        for (int i = 0; i < distance; i++){
            outfile.seekp(-1, ios::cur);
            outfile.seekp(51, ios::cur);
            //when both P and B are in the command
            if (pos5 == "P" && pos4 == "B") {
                outfile.put('#');
            }
            //when only B is in the command
            else if (pos4 == "B") {
                outfile.put('#');
            }
            //when only P is in the command
            else if (pos4 == "null"||pos4=="P") {
                outfile.put('*');
            }
            outfile.flush();
        }
    }
}
//if the direction is east
void drawEast(ofstream& outfile, bool pendown, int distance, const string& pos4, const string& pos5)
{
    //when the pen is up, nothing prints and the pointer is moved east an amount of times
    if (!pendown){
        for (int i = 0; i < distance; ++i){
            outfile.seekp(1, ios::cur);
        }
    }
    //when the pen is down, a character prints out moving east
    if (pendown){
        for (int i = 0; i < distance; i++){
            outfile.seekp(1, ios::cur);
            //moves the pointer back one space every time it moves forward
            if (distance<=1||i!=distance)
                outfile.seekp(-1, ios::cur);
            //when both P and B are in the command
            if (pos5 == "P" && pos4 == "B") {
                outfile.put('#');
            }
            //when only B is in the command
            else if (pos4 == "B") {
                outfile.put('#');
            }
            //when only P is in the command
            else if (pos4 == "null"||pos4=="P") {
                outfile.put('*');
            }
            outfile.flush();
        }
    }
}
//if the direction is west
void drawWest(ofstream& outfile, bool pendown, int distance, const string& pos4, const string& pos5)
{
    //when the pen is up, nothing prints and the pointer is moved west an amount of times
    if (!pendown){
        for (int i = 0; i < distance; ++i){
            outfile.seekp(-1, ios::cur);
        }
    }
    //when the pen is down, a character prints out moving west
    if (pendown){
        for (int i = 0; i < distance; i++){
            if (distance<=1||i!=distance)
                outfile.seekp(-1, ios::cur);
            outfile.seekp(-1, ios::cur);
            //when both P and B are in the command
            if (pos5 == "P" && pos4 == "B") {
                outfile.put('#');
            }
            //when only B is in the command
            else if (pos4 == "B") {
                outfile.put('#');
            }
            //when only P is in the command
            else if (pos4 == "null"||pos4=="P") {
                outfile.put('*');
            }
            outfile.flush();
        }
    }
}




