#include <iostream>
#include <fstream>
#include <cstdlib>
#include <iomanip>
#include <algorithm>
#include <ctype.h>
#include <cstring>
#include <array>
#include <vector>

using namespace std;

int main(int argc, char *argv[])
{
    string fileName = "";
    string flag = "";

    if (argc == 1)
    {
        cout << "NO SPECIFIED INPUT FILE NAME." << endl;
        exit(1);
    }
    else if (argc == 2)
    {
        fileName = string(argv[1]);
    }
    else if (argc == 3)
    {
        fileName = string(argv[1]);
        flag = string(argv[2]);
    }
    else
    {
        cout << "UNRECOGNIZED FLAG " << string(argv[3]) << endl;
        exit(1);
    }
    ifstream file;
    string line;

    int lineCount = 0;
    int nonBlankLinesCount = 0;
    int wordCount = 0;
    int integerCount = 0;
    int nameCount = 0;

    bool printInt = false;
    bool printName = false;

    if (flag == "-all")
    {
        printInt = true;
        printName = true;
    }
    else if (flag == "-ints")
    {
        printInt = true;
    }
    else if (flag == "-names")
    {
        printName = true;
    }
    else
    {
        flag.erase(std::remove_if(flag.begin(), flag.end(), ::isspace), flag.end());
        if (flag != "")
        {
            cout << "UNRECOGNIZED FLAG " << flag << endl;
            return 0;
        }
    }
    file.open(fileName.c_str());
    if (file)
    {
        while (getline(file, line))
        {
            lineCount++;
            string noWhitespace = line;
            noWhitespace.erase(std::remove_if(noWhitespace.begin(), noWhitespace.end(), ::isspace), noWhitespace.end());
            if (noWhitespace != "")
            {
                nonBlankLinesCount++;
                for (int i = 0; i < line.length(); i++)
                {
                    while (line.substr(0, 1) == " ")
                    {
                        line = line.substr(1, line.length());
                    }
                    if (line.length() > 0)
                    {
                        if (i + 1 == line.length() || line.substr(i, 1) == " ")
                        {
                            string word = "";
                            wordCount++;
                            word = line.substr(0, i);

                            line = line.substr(i + 1);
                            i = 0;
                            char splitWord[word.length()];
                            strcpy(splitWord, word.c_str());
                            bool integer = true;
                            bool name = true;
                            if (isalpha(splitWord[0]) || splitWord[0] == '_')
                            {
                                for (int j = 1; j < sizeof(splitWord); j++)
                                {
                                    if (!(isalnum(splitWord[j]) || splitWord[j] == '_' || splitWord[j] == '@'))
                                    {
                                        name = false;
                                    }
                                }
                            }
                            else
                            {
                                name = false;
                            }
                            if (isdigit(splitWord[0]) || splitWord[0] == '-' || splitWord[0] == '+')
                            {
                                for (int j = 1; j < sizeof(splitWord); j++)
                                {
                                    if (!isdigit(splitWord[j]))
                                    {
                                        integer = false;
                                    }
                                }
                            }
                            else
                            {
                                integer = false;
                            }
                            if (name)
                            {
                                nameCount++;
                            }
                            if (integer)
                            {
                                integerCount++;
                            }
                        }
                    }
                }
            }
        }
        if (lineCount - nonBlankLinesCount == lineCount)
        {
            cout << "File is empty." << endl;
        }
        else
        {
            cout << "Total Number of Lines: " << lineCount << endl;
            cout << "Number of non-blank lines: " << nonBlankLinesCount << endl;
            cout << "Number of Words: " << wordCount << endl;
            if (printInt)
            {
                if (integerCount > 0)
                {
                    integerCount--;
                }
                cout << "Number of Integers: " << integerCount << endl;
            }
            if (printName)
            {
                if (nameCount > 0)
                {
                    nameCount--;
                }
                cout << "Number of Names: " << nameCount << endl;
            }
        }
        file.close();
    }
    else
    {
        cout << "CANNOT OPEN THE FILE " << fileName << endl;
        exit(1);
    }
    return 0;
}