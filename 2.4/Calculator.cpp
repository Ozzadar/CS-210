/*
 * Calculator.cpp
 *
 *  Date: January 3rd 2022
 *  Author: Paul Mauviel
 */

#include <iostream>
#include <string>

// Remove "using namespace std" as importing entire namespaces is bad practice
// Bringing in cout, cin, and endl, string, and getline separately just to follow the conventions being taught
using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::getline;

// Function to get a user text response and get the first character. Return '0' if no input is given.
char getUserResponseFirstCharacter() {
    string userResponse;
    getline(cin, userResponse);

    if (userResponse.length() > 0) return userResponse[0];
    return '0';
}

// Fixed return type of main (returns int) and added standard argument list
// Since there is no rubric requirement for what this course considers "best practice" in this assignment,
// curly braces are moved to the same line as declaration as that is my preferred style.
int main(int argc, char** argv) {
    // Removed unused variable "statement"

    // Changed operands to float to support good divisions and renamed variables for clarity
    double leftOperand, rightOperand;
    char operation;

    // Added semi-colon, spacing to declaration
    // Also used single-quotes to mark it a character. Renamed variable for clarity.
    char userResponse = 'y';

    // changed to new variable name, added spacing for clarity
    // Added upper-case Y to while condition to meet specifications
    // moved curly braces to same line as while as that is my preferred style
    while (userResponse == 'y' || userResponse == 'Y') {
        cout << "Enter expression" << endl;
        // Properly ordered the operands
        cin >> leftOperand >> operation >> rightOperand;
        cin.ignore(99999, '\n');

        // single quotes to denote a character, remove the semi-colon and wrap the statement in curly braces for style
        // Although the curly braces are unnecessary, it's good practice leaving them there in-case it needs extending
        // in the future and to avoid accidental bugs.
        if (operation == '+') {
            // changed the input stream operator to output stream
            cout << leftOperand << " + " << rightOperand << " = " << leftOperand + rightOperand << endl;
        }

        // Removed semi-colon and wrapped statement in curly braces. See note above for reasoning.
        if (operation == '-') {
            // changed the input stream operator to output stream
            cout << leftOperand << " - " << rightOperand << " = " << leftOperand - rightOperand << endl;
        }

        // wrapped statement in curly braces. See note above for reasoning.
        if (operation == '*') {
            // add semicolon to statement, changed output string to match operation being performed
            cout << leftOperand << " * " << rightOperand << " = " << leftOperand * rightOperand << endl;
        }

        // wrapped statement in curly braces. See note above for reasoning.
        if (operation == '/') {
            // changed output string to match operation being performed
            cout << leftOperand << " / " << rightOperand << " = " << leftOperand / rightOperand << endl;
        }

        cout << "Do you wish to evaluate another expression? " << endl;
        userResponse = getUserResponseFirstCharacter();

        /*
         * This little block of code was added to ensure we only get the expected response from the user as
         * specified by Prompt item 3c.
         *
         * "If the user types “Y” or “y,” the program should ask for a new arithmetic expression.
         *  If the user types “N” or “n,” the program should terminate with the message: “Program Finished.”"
         *
         *  It does not specify what should be done in the case that a different response is provided -- therefore
         *  I went the route of asking the user again. This will ensure that typos don't accidentally quit the
         *  application.
         */
        while (userResponse != 'y' && userResponse != 'Y' && userResponse != 'n' && userResponse != 'N') {
            cout << "Incorrect Response. Please answer y/n. " << endl;
            userResponse = getUserResponseFirstCharacter();
        }
    }

    // Added exit message that was missing.
    cout << "Program Finished." << endl;
}





