#include <iostream>
#include <string>
#include "calculator.hpp"

using namespace std; // simplify so that I don't have to use std::

int main(int argc, char *argv[]) {
    if (argc != 2) { // check if correct input
        cout << "Usage: " << argv[0] << " <filename>" << endl; // output incorrect usage message
        return 1; // return 1 to show incorrect usage
    }

    string filename = argv[1]; // store filename
    vector<string> numbers = load_numbers_from_file(filename); // load all the numbers into an array

    for (const string &number : numbers) { // for number in numbers
        cout << "Number: " << number << endl; // output the number

        if (is_valid_double(number)) { // check if it is a valid number
            cout << "  Valid double number" << endl; // output that it is valid

            string result = add_numbers(number, "-123.456"); // add with -123.456
            cout << "  " << number << " + (-123.456) = " << result << endl; // display output of addition
        } else {
            cout << "  Invalid double number" << endl; // else state that it is not a valid double
        }

        cout << endl; // add another endline
    }

    return 0; // return that the program has run successfully
}
