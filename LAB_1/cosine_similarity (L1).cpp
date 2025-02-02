// 23 Jan 2025 Q4
#include<iostream>
#include <fstream>
#include <sstream>
#include <unordered_set>
#include<map>
#include <unordered_map>
#include<algorithm>
#include<vector>
#include<cmath>
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

int main(){

    vector<string> arr1 = process_file("file1.txt");
    vector<string> arr2 = process_file("file2.txt");

    map<string, int> dict1 = create_dictionary(arr1);
    map<string, int> dict2 = create_dictionary(arr2);

    map<string, int> merged = find_common_words(dict1, dict2);

    float cosine = dot_product(dict1, dict2, merged);
    cout<<"Cosine Similarity value : "<<cosine;
}



// ofstream file;

//     file.open("file1.txt");

//     if (!file.is_open())
//     {
//         cout << "Error in creating file!" << endl;
      
//         return 1;
//     }
//     file<<"Machine learning is a subset of artificial intelligence that focuses on building systems that can learn from and make decisions based on data. It uses statistical techniques to enable computers to improve their performance on a task through experience. Common applications include recommendation systems, fraud detection, and natural language processing.";
//     cout << "File created successfully." << endl;

//     file.close();

//     file.open("file2.txt");

//     if (!file.is_open())
//     {
//         cout << "Error in creating file!" << endl;
      
//         return 1;
//     }
//     file<<"Machine learning, a branch of artificial intelligence, aims to develop systems capable of learning from data and making decisions. It relies on statistical methods to help computers enhance their performance through experience. Popular applications include recommendation systems, fraud detection, and NLP.";
//     cout << "File created successfully." << endl;

//     file.close();
//     return 0;
