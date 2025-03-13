#include <iostream>
#include <fstream>
#include <queue>
#include <set>
#include <map>
#include <vector>
#include <string>
#include <cmath>

using namespace std;

void error(string word1, string word2, string msg)
{
    cout << "Error: " << msg << " (" word1 << ", " << word2 << ")" << endl;
    return;
}


bool edit_distance_within(const std::string& str1, const std::string& str2, int d)
{
    int n = str1.size();
    int m = str2.size();

    vector<vector<int>> dp(n + 1, vector<int>(m+1));

    for (int i = 0; i <=n; ++i)
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
            char c1 = tolower(str1[i-1]);
            char c2 = tolower(str2[j-1]);

            if (c1 == c2)
            {
                dp[i][j] = dp[i-1][j-1];
            }
            else
            {
                dp[i][j] = min({dp[i-1][j], dp[i][j-1], dp[i-1][j-1]});
            }
        }
    }

    return dp[n][m] <= d;
}


bool is_adjacent(const string& word1, const string& word2)
{
    if (word1 == word2) {return 0;}

    int n = word1.size();
    int m = word2.size();

    vector<vector<int>> dp(n + 1, vector<int>(m+1));

    for (int i = 0; i <=n; ++i)
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
            char c1 = tolower(str1[i-1]);
            char c2 = tolower(str2[j-1]);

            if (c1 == c2)
            {
                dp[i][j] = dp[i-1][j-1];
            }
            else
            {
                dp[i][j] = min({dp[i-1][j], dp[i][j-1], dp[i-1][j-1]});
            }
        }
    }

    return dp[n][m] == 1;

}

vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list)
{
    queue<vector<string>> ladder_queue;
    vector<string> initial_ladder;
    initial_ladder.push_back(begin_word);
    ladder_queue.push_back(initial_ladder);

    set<string> visited;
    visited.insert(begin_word);

    while(!ladder_queue.empty())
    {
        vector<string> ladder = ladder_queue.front();
        ladder_queue.pop();
        string last_word = ladder.back();

        for (const string &word : word_list)
        {
            if (is_adjacent(last_word, word))
            {
                if (visited.find(word) == visited.end())
                {
                    visited.insert(word);
                    vector<string> new_ladder = ladder;
                    new_ladder.push_back(word);
                    if (word == end_word)
                    {
                        return new_ladder;
                    }
                    ladder_queue.push(new_ladder);
                }
            }
        }
    }
    return vector<string>();
}
void load_words(set<string> & word_list, const string& file_name);
void print_word_ladder(const vector<string>& ladder);
void verify_word_ladder();
