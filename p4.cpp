//
// Created by Kevin Lundeen on 10/21/20.
// For Seattle University, CPSC 5005, P4.Triage
//
// TODO: complete all indicated code


#include <algorithm>
#include <stdexcept>
#include <fstream>
#include <iostream>
#include <string>
#include "Patient.h"
#include "PatientPriorityQueue.h"

using namespace std;

/**
 * Prints help menu.
 */
void help() {
    cout << "add <priority-code> <patient-name>" << endl
         << "            Adds the patient to the triage system." << endl
         << "            <priority-code> must be one of the 4 accepted priority codes:"
         << endl
         << "                1. immediate 2. emergency 3. urgent 4. minimal"
         << endl
         << "            <patient-name>: patient's full legal name (may contain spaces)"
         << endl
         << "next        Announces the patient to be seen next. Takes into account the"
         << endl
         << "            type of emergency and the patient's arrival order."
         << endl
         << "peek        Displays the patient that is next in line, but keeps in queue"
         << endl
         << "list        Displays the list of all patients that are still waiting"
         << endl
         << "            in the order that they have arrived."
         << endl
         << "load <file> Reads the file and executes the command on each line"
         << endl
         << "help        Displays this menu" << endl
         << "quit        Exits the program" << endl;
}

/**
 * Prints welcome message.
 */
void welcome() {
    cout << "------------------------------------------------" << endl;
    cout << "__________ Welcome to Arkham Hospital __________" << endl;
    cout << "------------------------------------------------" << endl;
}

/**
 * Prints farewell message.
 */
void goodbye() {
    cout << endl;
    cout << "---------------------------------------------------------" << endl;
    cout << "We'll see you next time! Same bat time, same bat channel!" << endl;
    cout << "---------------------------------------------------------" << endl;
}

/**
 * Delimits (by space) the string from user or file input.
 * @param s string from user or file input (return value is also erased from it)
 * @return the substring of s up to the first space (or to end of string if no
 *         spaces)
 */
string delimitBySpace(string &s) {
    const char delimiter = ' ';
    string result;
    int pos = s.find(delimiter);
    if (pos != string::npos) {
        result = s.substr(0, pos);
        s.erase(0, pos + 1);
    } else {
        result = s;
    }
    return result;
}


void trimString(string &s) {
    //https://www.toptip.ca/2010/03/trim-leading-or-trailing-white-spaces.html
    int start = s.find_first_not_of(" ");
    s.erase(0,start);

    int end = s.find_last_not_of(" ");
    if (string::npos != end)
        s.erase(end+1);
}

/**
 * Adds the patient to the waiting room.
 * @param line     command line
 * @param priQueue queue to manipulate
 */
void addPatientCmd(string line, PatientPriorityQueue &priQueue) {
    string priority, name;

    // get priority and name
    priority = delimitBySpace(line);
    if (priority.length() == 0) {
        cout << "Error: no priority code given." << endl;
        return;
    }
    name = line;
    if (name.length() == 0) {
        cout << "Error: no patient name given." << endl;
        return;
    }

    // TODO: add logic to remove leading/trailing spaces
    trimString(name);
    // TODO: validate priority is between 1 and 4
    //make upper case for consistency
    transform(priority.begin(), priority.end(), priority.begin(), ::toupper);
    if (priority == "IMMEDIATE") {
        Patient patient(name, Patient::IMMEDIATE);
        priQueue.enqueue(patient);
    }
    else if (priority == "EMERGENCY") {
        Patient patient(name, Patient::EMERGENCY);
        priQueue.enqueue(patient);
    }
    else if (priority == "URGENT") {
        Patient patient(name, Patient::URGENT);
        priQueue.enqueue(patient);

    }
    else if (priority == "MINIMAL") {
        Patient patient(name, Patient::MINIMAL);
        priQueue.enqueue(patient);
    }
    else {
        cout << "Patient: " + name + " not added, invalid priority code." << endl;
        return;
    }
    cout << "Added patient \"" + name + "\" to the priority system" << endl;

}

/**
 * Displays the next patient in the waiting room that will be called.
 * @param priQueue queue to manipulate
 */
void peekNextCmd(PatientPriorityQueue &priQueue) {
    Patient p = priQueue.peek();
    cout << "The next patient is: " << p.toString() << endl;
}

/**
 * Removes a patient from the waiting room and displays the name on the screen.
 * @param priQueue queue to manipulate
 */
void removePatientCmd(PatientPriorityQueue &priQueue) {
    // TODO: removes and shows next patient to be seen
    try {
        Patient p = priQueue.dequeue();
        cout << "The doctor will now see: " << p.toString() << endl;
    }
    catch (exception e) {
        cout << "There are no patients waiting." << endl;
    }
}

/**
 * Displays the list of patients in the waiting room.
 * @param priQueue queue to manipulate
 */
void showPatientListCmd(PatientPriorityQueue &priQueue) {
    cout << "# patients waiting: " << priQueue.size() << endl;
    // TODO: shows patient detail in arbitrary heap order (root first)
    for (int i = 0; i < priQueue.size(); ++i) {
        Patient p = priQueue.peek(i);
        cout << p.toString() << endl;
    }
}

// forward declare:
void execCommandsFromFileCmd(string filename, PatientPriorityQueue &priQueue);

/**
 * Process the line entered from the user or read from a file.
 * @param line     command text
 * @param priQueue queue to manipulate
 * @return         false to quit; true otherwise
 */
bool processLine(string line, PatientPriorityQueue &priQueue) {
    // get command
    //most common use case is to trim an added space between the command prompt and user command
    trimString(line);
    string cmd = delimitBySpace(line);
    if (cmd.length() == 0) {
        cout << "Error: no command given.";
        return false;
    }

    // process user input
    if (cmd == "help")
        help();
    else if (cmd == "add")
        addPatientCmd(line, priQueue);
    else if (cmd == "peek")
        peekNextCmd(priQueue);
    else if (cmd == "next")
        removePatientCmd(priQueue);
    else if (cmd == "list")
        showPatientListCmd(priQueue);
    else if (cmd == "load")
        execCommandsFromFileCmd(line, priQueue);
    else if (cmd == "quit")
        return false;
    else
        cout << "Error: unrecognized command: " << cmd << endl;

    return true;
}

/**
 * Reads a text file with each command on a separate line and executes the
 * lines as if they were typed into the command prompt.
 * @param filename  of file with text commands
 * @param priQueue  queue to manipulate
 */
void execCommandsFromFileCmd(string filename, PatientPriorityQueue &priQueue) {
    ifstream infile;
    infile.open(filename);
    if (infile) {
        string line;
        while (getline(infile, line)) {
            cout << endl << "triage> " << line;
            cout << endl;
            processLine(line, priQueue);
        }
    } else {
        cout << "Error: could not open file." << endl;
    }
    infile.close();
}

/**
 * Main entry into triage program.
 * @return EXIT_SUCCESS
 */
int main() {
    welcome();

    // process commands
    PatientPriorityQueue priQueue;
    string line;
    do {
        cout << endl << "triage> ";
        getline(cin, line);
    } while (processLine(line, priQueue));

    goodbye();
    return EXIT_SUCCESS;
}

//part of in-class exercise on hashing
int hashCode(string &s) {
    int strLength = s.length();
    if (strLength == 0)
        return 0;
    else
        return 100 * s[0] + 10 * s[strLength / 2] + s[strLength - 1];
}

