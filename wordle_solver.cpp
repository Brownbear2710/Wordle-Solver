#include<bits/stdc++.h>
using namespace std;

vector<string> wordList;
set<char> notPresent, correct, isPresent;
map<char, vector<int>> notPosition, position;

void load();
void throwRandomWords(int turn);
void cutOff();

int main()
{
    cout << "+ -> in position\n- -> not in position\nx -> not in word\n";
    load();
    for(int i = 0 ; i < 4; i++)
    {
        throwRandomWords(i);
        cutOff();
        if(wordList.size() == 1)
        {
            cout << "The word is: " << wordList[0];
            return 0;
        }
    }

    cout << "Possible ans:\n";
    for(auto word : wordList)
    {
        cout << word << endl;
    }
    getchar();
    return 0;
}


void load()
{
    ifstream istrm;
    istrm.open("List.txt");
    int i = 0;
    while(i < 12972)
    {
        string s;
        getline(istrm, s);
        for(int j = 0; j < 5; j++)
        {
            s[j] = tolower(s[j]);
        }
        wordList.push_back(s);
        i++;
    }
    istrm.close();
    sort(wordList.begin(),wordList.end());
}

void throwRandomWords(int turn)
{
    string word[] = {"crane", "night", "cloud", "swamy", "probe"};
    string input, output;
    if(turn > 3 && wordList.size() <= 7) output = wordList[0];
    else output = word[turn];

    // if(turn == 4)/////
    // {
    //     for(auto it : wordList) cout << it << "\n";
    // }
    cout << "Try " << turn+1 << ": " << output << "\nState: ";
    cin >> input;
    for(int i = 0; i < 5; i++)
    {
        if(input[i] == '-')
        {
            isPresent.insert(output[i]);
            notPosition[output[i]].push_back(i);
        }
        else if(input[i] == '+')
        {
            correct.insert(output[i]);
            position[output[i]].push_back(i);
        }
        else
        {
            notPresent.insert(output[i]);
        }
    }
}

void cutOff()
{
    vector<string> wordList2;
    for(auto s: wordList)
    {
        bool flag = 1;
        for(auto letter: correct)
        {
            bool checker  = 0;
            for(auto v: position[letter])
            {
                if(s[v] == letter) checker = 1;
                else checker = 0;
                if(!checker) break;
            }
            if(!checker)
            {
                flag = checker;
                break;
            }
        }
        for(int i = 0; i < 5; i++)
        {
            if(notPresent.find(s[i]) != notPresent.end())
            {
                flag = 0;
                break;
            }
        }
        for(int i = 0; i < 5; i++)
        {
            for(auto pos: notPosition[s[i]])
            {
                if(pos == i) flag = 0;
            }
        }
        for(auto letter: isPresent)
        {
            bool checker = 0;
            for(int i = 0; i < 5; i++)
            {
                if(s[i] == letter) checker = 1;
            }
            if(!checker) flag = 0;
        }
        if(flag) wordList2.push_back(s);
    }
    swap(wordList, wordList2);
    wordList2.clear();
}
