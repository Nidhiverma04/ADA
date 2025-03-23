#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>

using namespace std;

string findKey(string key) {
    stringstream ss(key);
    string term;
    vector<int> powers;

    while (getline(ss, term, '+')) {
        if (term == "1") {
            powers.push_back(0);  
        } else if (term == "x") {
            powers.push_back(1);  
        } else if (term.find("x^") != string::npos) {
            int power = stoi(term.substr(2));  
            powers.push_back(power);
        }
    }

    int max_power = *max_element(powers.begin(), powers.end());
    string binary_key(max_power + 1, '0');

    for (int power : powers) {
        binary_key[max_power - power] = '1';
    }

    return binary_key;
}

string xor1(string a, string b) {
    string result = "";
    for (int i = 0; i < b.length(); i++) {
        result += (a[i] == b[i]) ? '0' : '1';
    }
    return result;
}

string divide(string data, string key) {
    int key_len = key.length();
    string current = data.substr(0, key_len);

    for (int i = key_len; i <= data.length(); ++i) {
        if (current[0] == '1') {
            current = xor1(current, key);
        } else {
            current = xor1(current, string(key_len, '0'));
        }
        current.erase(0, 1);
        if (i < data.length()) {
            current += data[i];
        }
    }

    return current;
}

int main() {
    cout << "Enter the generator polynomial: ";
    string polynomial;
    cin >> polynomial;

    string key = findKey(polynomial);

    cout << "Enter the data: ";
    string data;
    cin >> data;

    int deg = 0;
    for (char ch : polynomial) {
        if (ch == '^') {
            deg = max(deg, polynomial[polynomial.find('^') + 1] - '0');
        }
    }

    string padded_data = data + string(deg, '0');

    cout << endl << "Appended zeroes: " << padded_data << endl;

    string remainder = divide(padded_data, key);
    cout << "Remainder: " << remainder.substr(0, deg) << endl;
    string encoded = data + remainder.substr(0, deg);

    cout << "Binary Key: " << key << endl;
    cout << "Encoded Data with Checksum: " << encoded << endl;

    string receiver = divide(encoded, key);
    cout << "Receiver's side: " << receiver << endl;

    if (receiver == string(key.length() - 1, '0')) {
        cout << "\nSuccessfully received" << endl;
    } else {
        cout << "\nCorrupted data received" << endl;
    }

    return 0;
}