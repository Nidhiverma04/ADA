#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_set>
#include <map>
#include <vector>
#include <algorithm>
#include <ctime>
#include <iomanip>
#include <math.h>
using namespace std;

bool isCommonWord(const string &word) {
    static const unordered_set<string> articles = {"a", "an", "the", "is", "am", "are", "of", "on", "in", "to",
                                                   "and", "or", "that", "it", "this", "for", "with", "as", "was"};
    return articles.find(word) != articles.end();
}

map<string, int> create_dictionary(vector<string> &arr) {
    map<string, int> temp;
    for (const auto &word : arr) {
        temp[word]++;
    }
    return temp;
}

map<string, int> find_common_words(map<string, int> &dict1, map<string, int> &dict2) {
    map<string, int> merged;
    for (const auto &pair : dict2) {
        if (dict1.find(pair.first) != dict1.end())
            merged[pair.first] = dict1[pair.first] * pair.second;
    }
    return merged;
}

float dot_product(map<string, int> &dict1, map<string, int> &dict2, map<string, int> &merged) {
    float mod_one = 0.0f, mod_two = 0.0f, dot_prod = 0.0f;

    for (const auto &pair : dict1) {
        mod_one += pair.second * pair.second;
    }

    for (const auto &pair : dict2) {
        mod_two += pair.second * pair.second;
    }

    for (const auto &pair : merged) {
        dot_prod += pair.second;
    }

    return dot_prod / (sqrt(mod_one) * sqrt(mod_two));
}

vector<string> generate_words(int n) {
    vector<string> arr;
    for (int i = 0; i < n; ++i) {
        arr.push_back("word" + to_string(i)); // Generating unique words
    }
    return arr;
}

double measureTime(int n) {
    vector<string> arr1 = generate_words(n);
    vector<string> arr2 = generate_words(n);

    map<string, int> dict1 = create_dictionary(arr1);
    map<string, int> dict2 = create_dictionary(arr2);

    clock_t start = clock();
    for (int i = 0; i < 200; ++i) {
        map<string, int> merged = find_common_words(dict1, dict2);
        float cosine = dot_product(dict1, dict2, merged);
    }
    clock_t end = clock();

    double time_taken = double(end - start) / CLOCKS_PER_SEC;
    cout << setprecision(8) << time_taken / 200 << ", ";
    return time_taken / 200;
}

int main() {
    int sizes[13];
    double times[13];
    int n = 10;

    for (int i = 0; i < 13; ++i) {
        sizes[i] = n;
        times[i] = measureTime(n);
        n *= 2;
    }

    cout << "\nSizes for plotting: ";
    for (int i = 0; i < 13; ++i) {
        cout << sizes[i] << ", ";
    }

    cout << "\nTimes for plotting: ";
    for (int i = 0; i < 13; ++i) {
        cout << times[i] << ", ";
    }
    cout << endl;

    return 0;
}
