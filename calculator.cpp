// include header files in program
#include "calculator.hpp"
#include <fstream>
#include <iostream>
#include <cmath>

using namespace std;

bool is_valid_double(const string &str) { // implement validation function
    if (str.empty()) { // check if string is empty
        return false; // if empty return false
    }

    size_t i = 0;
    if (str[i] == '+' || str[i] == '-') {  // Check for sign
        i++; // move the index forward if there is a sign
    }

    if (i >= str.length()) {// check if there are digits after sign
        return false; // if not return false
    }

    bool has_digits_before_point = false;
    while (i < str.length() && str[i] >= '0' && str[i] <= '9') { // check for digits before decimal point
        has_digits_before_point = true;
        i++; // move the index forward
    }

    if (i >= str.length()) { // if reached the end of the string
        return has_digits_before_point; // have a valid integer
    }

    if (str[i] == '.') { // check for decimal point
        i++; // move the index forward

        if (i >= str.length() || str[i] < '0' || str[i] > '9') { // Must have at least one digit after decimal point
            return false;
        }

        while (i < str.length() && str[i] >= '0' && str[i] <= '9') {  // check for digits after decimal point
            i++; // move the index forward
        }
    }

    return i >= str.length(); // if end of the string reached, the number is valid
}

string reverse_string(const string &str) { // function to reverse a string
    string reversed;
    for (int i = str.length() - 1; i >= 0; i--) {
        reversed.push_back(str[i]);
    }
    return reversed;
}


bool all_zeros(const string &str) { // function to check if all characters in a string are zeros
    for (char c : str) {
        if (c != '0') {
            return false;
        }
    }
    return true;
}


string remove_leading_zeros(const string &num) { //  function to remove leading zeros from an integer part
    size_t pos = 0;
    while (pos < num.length() - 1 && num[pos] == '0') {
        pos++;
    }
    return num.substr(pos);
}


string add_integer_strings(const string &a, const string &b) { // function to add two integer strings
    string result;
    int carry = 0;
    int i = a.length() - 1;
    int j = b.length() - 1;

    while (i >= 0 || j >= 0 || carry > 0) {
        int sum = carry;
        if (i >= 0) {
            sum += (a[i] - '0');
            i--;
        }
        if (j >= 0) {
            sum += (b[j] - '0');
            j--;
        }

        carry = sum / 10;
        result.push_back('0' + (sum % 10));
    }

    return reverse_string(result);
}


string subtract_integer_strings(const string &a, const string &b) { //  function to subtract two integer strings (assumes a >= b)
    string result;
    int borrow = 0;
    int i = a.length() - 1;
    int j = b.length() - 1;

    while (i >= 0) {
        int digit = (a[i] - '0') - borrow;

        if (j >= 0) {
            digit -= (b[j] - '0');
            j--;
        }

        if (digit < 0) {
            digit += 10;
            borrow = 1;
        } else {
            borrow = 0;
        }

        result.push_back('0' + digit);
        i--;
    }

    return remove_leading_zeros(reverse_string(result));
}



int compare_integer_strings(const string &a, const string &b) { // returns: 1 if |a| > |b|, 0 if |a| == |b|, -1 if |a| < |b|
    if (a.length() > b.length()) return 1;
    if (a.length() < b.length()) return -1;


    for (size_t i = 0; i < a.length(); i++) { // same length, compare digit by digit
        if (a[i] > b[i]) return 1;
        if (a[i] < b[i]) return -1;
    }

    return 0; // equal
}

string add_numbers(const string &num1, const string &num2) {
    // check if either number is negative
    bool is_num1_negative = num1[0] == '-';
    bool is_num2_negative = num2[0] == '-';

    // extract number parts without signs
    string num1_abs = is_num1_negative ? num1.substr(1) : num1;
    string num2_abs = is_num2_negative ? num2.substr(1) : num2;

    // handle leading plus sign
    if (num1_abs[0] == '+') num1_abs = num1_abs.substr(1);
    if (num2_abs[0] == '+') num2_abs = num2_abs.substr(1);

    // find decimal positions
    size_t num1_decimal = num1_abs.find('.');
    size_t num2_decimal = num2_abs.find('.');

    // extract integer and fractional parts
    string num1_int = (num1_decimal == string::npos) ?
    num1_abs : num1_abs.substr(0, num1_decimal);
    string num2_int = (num2_decimal == string::npos) ?
    num2_abs : num2_abs.substr(0, num2_decimal);

    string num1_frac = (num1_decimal == string::npos) ?
    "" : num1_abs.substr(num1_decimal + 1);
    string num2_frac = (num2_decimal == string::npos) ?
    "" : num2_abs.substr(num2_decimal + 1);

    // remove leading zeros from integer parts
    num1_int = remove_leading_zeros(num1_int);
    num2_int = remove_leading_zeros(num2_int);

    // if integer part is empty, set to "0"
    if (num1_int.empty()) num1_int = "0";
    if (num2_int.empty()) num2_int = "0";

    // pad fractional parts to equal length
    size_t max_frac_len = max(num1_frac.length(), num2_frac.length());
    num1_frac.resize(max_frac_len, '0');
    num2_frac.resize(max_frac_len, '0');

    // special case for -0
    if (is_num1_negative && num1_int == "0" && all_zeros(num1_frac)) {
        is_num1_negative = false; // treat -0 as 0
    }
    if (is_num2_negative && num2_int == "0" && all_zeros(num2_frac)) {
        is_num2_negative = false; // treat -0 as 0
    }

    // set up result
    string result;

    // different signs case
    if (is_num1_negative != is_num2_negative) {
        int compare = compare_integer_strings(num1_int, num2_int);
        if (compare == 0) {
            // integer parts are equal, compare fractional parts
            for (size_t i = 0; i < max_frac_len; i++) {
                if (num1_frac[i] > num2_frac[i]) {
                    compare = 1;
                    break;
                } else if (num1_frac[i] < num2_frac[i]) {
                    compare = -1;
                    break;
                }
            }
        }

        // if both numbers are equal in magnitude but opposite signs, result is zero
        if (compare == 0) {
            return "0";
        }

        // determine which number has the larger magnitude
        bool result_negative;
        string larger_int, smaller_int, larger_frac, smaller_frac;

        if ((compare > 0 && !is_num1_negative) || (compare < 0 && is_num1_negative)) {
            result_negative = false;
            larger_int = (compare > 0) ? num1_int : num2_int;
            smaller_int = (compare > 0) ? num2_int : num1_int;
            larger_frac = (compare > 0) ? num1_frac : num2_frac;
            smaller_frac = (compare > 0) ? num2_frac : num1_frac;
        } else {
            result_negative = true;
            larger_int = (compare < 0) ? num2_int : num1_int;
            smaller_int = (compare < 0) ? num1_int : num2_int;
            larger_frac = (compare < 0) ? num2_frac : num1_frac;
            smaller_frac = (compare < 0) ? num1_frac : num2_frac;
        }

        // subtract fractional parts
        string frac_result;
        int borrow = 0;

        for (int i = max_frac_len - 1; i >= 0; i--) {
            int digit = (larger_frac[i] - '0') - borrow;

            if (digit < (smaller_frac[i] - '0')) {
                digit += 10;
                borrow = 1;
            } else {
                borrow = 0;
            }

            digit -= (smaller_frac[i] - '0');
            frac_result.push_back('0' + digit);
        }

        frac_result = reverse_string(frac_result);

        // if we have a borrow, subtract it from the integer subtraction
        string int_result;
        if (borrow) {
            int_result = subtract_integer_strings(larger_int, "1");
        } else {
            int_result = larger_int;
        }

        // subtract integer parts
        int_result = subtract_integer_strings(int_result, smaller_int);

        // build the final result
        if (result_negative && int_result != "0") {
            result += "-";
        }

        result += int_result;

        // add decimal part if non-zero
        bool has_non_zero = false;
        for (char c : frac_result) {
            if (c != '0') {
                has_non_zero = true;
                break;
            }
        }

        if (has_non_zero) {
            result += ".";
            // remove trailing zeros
            while (!frac_result.empty() && frac_result.back() == '0') {
                frac_result.pop_back();
            }
            result += frac_result;
        }
    }
    // same signs case
    else {
        // add fractional parts
        string frac_result;
        int carry = 0;

        for (int i = max_frac_len - 1; i >= 0; i--) {
            int sum = carry + (num1_frac[i] - '0') + (num2_frac[i] - '0');
            carry = sum / 10;
            frac_result.push_back('0' + (sum % 10));
        }

        frac_result = reverse_string(frac_result);

        // add integer parts (with carry from fraction)
        string int_result = add_integer_strings(num1_int, num2_int);
        if (carry) {
            int_result = add_integer_strings(int_result, "1");
        }

        // build the final result
        if (is_num1_negative) {
            result += "-";
        }

        result += int_result;

        // add decimal part if non-zero
        bool has_non_zero = false;
        for (char c : frac_result) {
            if (c != '0') {
                has_non_zero = true;
                break;
            }
        }

        if (has_non_zero) {
            result += ".";
            // remove trailing zeros
            while (!frac_result.empty() && frac_result.back() == '0') {
                frac_result.pop_back();
            }
            result += frac_result;
        }
    }

    // if the result is just "0" make sure we don't have "-0"
    if (result == "-0") {
        return "0";
    }

    return result;
}

vector<string> load_numbers_from_file(const string &filename) {
    vector<string> numbers;
    ifstream file(filename);

    if (!file.is_open()) {
        cerr << "Error: Could not open file " << filename << endl;
        return numbers;
    }

    string line;
    while (getline(file, line)) {
        // remove whitespace
        line.erase(0, line.find_first_not_of(" \t\r\n"));
        line.erase(line.find_last_not_of(" \t\r\n") + 1);

        if (!line.empty()) {
            numbers.push_back(line);
        }
    }

    file.close();
    return numbers;
}

double parse_number(const string &str) {
    if (!is_valid_double(str)) {
        return 0.0; // invalid number
    }

    bool is_negative = false;
    size_t i = 0;

    // check for sign
    if (str[i] == '+') {
        i++;
    } else if (str[i] == '-') {
        is_negative = true;
        i++;
    }

    double result = 0.0;

    // parse integer part
    while (i < str.length() && str[i] >= '0' && str[i] <= '9') {
        result = result * 10 + (str[i] - '0');
        i++;
    }

    // parse decimal part
    if (i < str.length() && str[i] == '.') {
        i++;
        double decimal_place = 0.1;

        while (i < str.length() && str[i] >= '0' && str[i] <= '9') {
            result += (str[i] - '0') * decimal_place;
            decimal_place *= 0.1;
            i++;
        }
    }

    return is_negative ? -result : result;
}
