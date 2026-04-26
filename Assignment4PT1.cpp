#include <iostream>
#include <string>
using namespace std;

void swap_chars(string& word, int i, int j)
{
    char temp = word[i];
    word[i] = word[j];
    word[j] = temp;
}

void print_permutations(string& word, int start)
{
    if (start == word.length() - 1)
    {
        cout << word << endl;
        return;
    }

    for (int i = start; i < word.length(); i++)
    {
        swap_chars(word, start, i);

        print_permutations(word, start + 1);

        swap_chars(word, start, i); // backtrack
    }
}

int main()
{
    string word;

    cout << "Enter a string: ";
    cin >> word;

    print_permutations(word, 0);

    return 0;
}