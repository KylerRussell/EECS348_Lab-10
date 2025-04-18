#ifndef __CALCULATOR_HPP
#define __CALCULATOR_HPP

#include <string>
#include <vector>

using namespace std;

bool is_valid_double(const string &str); // Check if a string represents a valid double number

string add_numbers(const string &num1, const string &num2); // Add two string-formatted double numbers

vector<string> load_numbers_from_file(const string &filename); // Load numbers from a file

string reverse_string(const string &str); // Helper function to reverse a string

bool all_zeros(const string &str); // Check if all characters in a string are zeros

double parse_number(const string &str); // Convert string to double

#endif // __CALCULATOR_HPP
