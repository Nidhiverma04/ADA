#include <iostream>
#include <cmath>
#include <chrono>
#include <fstream>
#include <fstream>
#include <sstream>
#include <unordered_set>
#include<map>
#include <unordered_map>
#include<algorithm>
#include<vector>
#include<cmath>

using namespace std::chrono;
using namespace std;

bool isCommonWord(const string& word) {
    static const unordered_set<string> articles = {"a", "an", "the", "is", "am", "are", "of", "on", "in", "to", 
                                                    "and", "or", "that", "it", "this", "for", "with", "as", "was"};
    return articles.find(word) != articles.end();
}

map<string,int> create_dictionary(vector<string> arr){
    map<string,int> temp;
    for(int i = 0;i<arr.size();i++){
        temp[arr[i]]++;
    }
    return temp;
}

map<string, int> find_common_words(map<string, int> dict1, map<string, int> dict2){
    map<string, int> merged;
    for (const auto& pair : dict2) {
        if(dict1.find(pair.first) != dict1.end())
            merged[pair.first] = dict1[pair.first] * pair.second;
    }
    return merged;
}

float dot_product(map<string, int> dict1, map<string, int> dict2, map<string, int> merged){
    float mod_one = 0.0f, mod_two = 0.0f, dot_prod = 0.0f;
    float cosine = 0.0f;

    for (const auto& pair : dict1) {
        mod_one += pair.second * pair.second;
    }

    for (const auto& pair : dict2) {
        mod_two += pair.second * pair.second;
    }

    for (const auto& pair : merged) {
        dot_prod += pair.second;
    }

    mod_one = sqrt(mod_one);
    mod_two = sqrt(mod_two);

    cosine = dot_prod / (mod_one * mod_two);

    return cosine;
}

vector<string> process_file(string name){
    ifstream file ;
    file.open(name);
    vector<string> arr;
    string line, word;
    int count = 0;
    while(getline(file, line)){
        istringstream stream(line);
        while (stream >> word) {
            transform(word.begin(), word.end(), word.begin(), ::tolower);
            auto it = std::remove_if(word.begin(), word.end(), ::ispunct);
            word.erase(it, word.end());
            if (!isCommonWord(word)) {
                arr.push_back(word);
                count++;
            }
        }
    }
    file.close();

    return arr;
}

int main() {
    ofstream file, f;
    file.open("time.csv");
    f.open("size.csv");

    int idx = 0, id = 0;
    for (int i = 2; i <= 25000; i*=2) {
        int s = i;
        int** arr = new int* [s];
        for (int j = 0; j <s; j++) {
            arr[j] = new int[s];
        }

        auto start = high_resolution_clock::now();
        for (int q = 0; q < 10; q++) {
            vector<string> arr1 = process_file("file1.txt");
            vector<string> arr2 = process_file("file2.txt");

            map<string, int> dict1 = create_dictionary(arr1);
            map<string, int> dict2 = create_dictionary(arr2);

            map<string, int> merged = find_common_words(dict1, dict2);

            float cosine = dot_product(dict1, dict2, merged);
            f << arr1.size()+arr2.size() <<", ";
        }
        auto end = high_resolution_clock::now();
        auto dur = duration_cast<microseconds>(end - start)/10;
        file << dur.count() <<", ";

        for (int j = 0; j < s; j++) {
            delete[] arr[j];
        }
        delete[] arr;
    }

    file.close();
    f.close();
    return 0;
}
