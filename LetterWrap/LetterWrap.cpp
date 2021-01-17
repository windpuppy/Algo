// LetterWrap.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
using namespace std;

void letterWrap(char letter, int count)
{
    // i goes from 4 to 1, represents current row we are printing at
    for (int i = count; i > 0; --i)
    {
        char c = letter;

        // j goes from 0 to i, represents current colunm we are printing at
        for (int j = 0; j < i; ++j)
        {
            // k goes from 0 to current column index (ie. always start with the total count!)
            for (int k = 0; k < count - j; ++k)
            {
                cout << c;
            }

            cout << " ";
            
            if (c != 'Z')
                c++;
            else
                c = 'A';
        }

        cout << endl;
    }

    cout << endl;
}

int main()
{
    letterWrap('C', 4);
    letterWrap('A', 5);
}



