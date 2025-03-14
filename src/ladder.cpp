#include <iostream>
#include <fstream>
#include <queue>
#include <set>
#include <map>
#include <vector>
#include <string>
#include <cmath>
#include "ladder.h"

using namespace std;

void error(string word1, string word2, string msg)
{
    cout << "Error: " << msg << " (" << word1 << ", " << word2 << ")" << endl;
    //return;
}


bool edit_distance_within(const std::string& str1, const std::string& str2, int d)
{
    int n = str1.size();
    int m = str2.size();
    vector<vector<int>> dp(n + 1, vector<int>(m + 1));

    for (int i = 0; i <= n; ++i)
    { 
        dp[i][0] = i;
    }

    for (int j = 0; j <= m; ++j) 
    {
        dp[0][j] = j;
    }
        
    for (int i = 1; i <= n; ++i) 
    {
        for (int j = 1; j <= m; ++j) 
        {
            if (tolower(str1[i-1]) == tolower(str2[j-1])) 
            {
                dp[i][j] = dp[i-1][j-1];
            } 
            else 
            {
                dp[i][j] = 1 + min({dp[i-1][j], dp[i][j-1], dp[i-1][j-1]});
            }
        }
    }
    return dp[n][m] <= d;
}


bool is_adjacent(const string& word1, const string& word2)
{
    return edit_distance_within(word1, word2, 1);
}

vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list)
{
    if (begin_word == end_word) {return {};}

    queue<vector<string>> ladder_queue;
    set<string> visited;
    ladder_queue.push({begin_word});
    visited.insert(begin_word);

    while (!ladder_queue.empty()) 
    {
        auto ladder = ladder_queue.front();
        ladder_queue.pop();
        string current = ladder.back();

        if (current == end_word) {return ladder;}

        vector<string> neighbors;

        string temp = current;
        for (int i = current.size() - 1; i >= 0; --i) 
        {
            char original = temp[i];

            for (char c = 'a'; c <= 'z'; ++c) {
                if (c == original) {continue;}
                temp[i] = c;

                if (word_list.count(temp) && !visited.count(temp)) 
                {
                    neighbors.push_back(temp);
                    visited.insert(temp);
                }
            }

            temp[i] = original;
        }

        for (int i = 0; i <= current.size(); ++i) 
        {
            for (char c = 'a'; c <= 'z'; ++c) 
            {
                string inserted = current.substr(0, i) + c + current.substr(i);

                if (word_list.count(inserted) && !visited.count(inserted)) 
                {
                    neighbors.push_back(inserted);
                    visited.insert(inserted);
                }
            }
        }

        for (int i = 0; i < current.size(); ++i) 
        {
            string deleted = current.substr(0, i) + current.substr(i+1);
            if (word_list.count(deleted) && !visited.count(deleted)) 
            {
                neighbors.push_back(deleted);
                visited.insert(deleted);
            }
        }

        for (const auto& neighbor : neighbors) 
        {
            vector<string> new_ladder = ladder;
            new_ladder.push_back(neighbor);
            if (neighbor == end_word) {return new_ladder;}
            ladder_queue.push(new_ladder);
        }
    }
    return {};
}

void load_words(set<string> & word_list, const string& file_name)
{
    ifstream file(file_name);

    if (!file)
    {
        error(file_name, "", "Unable to open file");
        return;
    }
    string word;
    while (file >> word)
    {
        transform(word.begin(), word.end(), word.begin(), ::tolower);
        word_list.insert(word);
    }
    file.close();

}

void print_word_ladder(const vector<string>& ladder)
{
    if (ladder.empty())
    {
        cout << "No word ladder found." << endl;
        return;
    }
    cout << "Word ladder found: ";
    for (int i = 0; i < ladder.size(); ++i)
    {
        cout << ladder[i] << " ";
    }
    cout << endl;
}


void verify_word_ladder()
{
    set<string> word_list;
    load_words(word_list, "/home/agseetha/ics46/HW9/src/small.txt");

    string begin_word, end_word;
    cout << "Start word: "; 
    cin >> begin_word;
    cout << "End word: ";
    cin >> end_word;

    transform(begin_word.begin(), begin_word.end(), begin_word.begin(), ::tolower);
    transform(end_word.begin(), end_word.end(), end_word.begin(), ::tolower); 

    if (begin_word == end_word) 
    {
        error(begin_word, end_word, "Start and end words must be different");
        return;
    }

    if (word_list.find(end_word) == word_list.end()) 
    {
        error(begin_word, end_word, "End word is not in the list");
        return;
    }

    vector<string> ladder = generate_word_ladder(begin_word, end_word, word_list);
    print_word_ladder(ladder);
}
