#include <iostream>
#include <fstream>
#include <cstdlib>
#include <iomanip>
#include <algorithm>
#include <ctype.h>
#include <cctype>
#include <cstring>
#include <array>
#include <map>

using namespace std;

int main(int argc, char *argv[])
{
   string fileName = "";

   if (argc == 1)
   {
      cout << "NO SPECIFIED INPUT FILE NAME." << endl;
      exit(1);
   }
   else if (argc >= 2)
   {
      fileName = string(argv[1]);
   }

   ifstream file;
   string line;
   map<string, int> zeroVowelCount;
   map<string, int> oneVowelCount;
   map<string, int> twoVowelCount;
   map<string, int> threeVowelCount;
   int noVowel = 0;
   int oneVowel = 0;
   int twoVowel = 0;
   int threeVowel = 0;
   int totalWordCount = 0;
   int nonBlankLinesCount = 0, lineCount = 0;
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
                     totalWordCount++;
                     string word = "";
                     word = line.substr(0, i);
                     word.erase(std::remove_if(word.begin(), word.end(), ::isspace), word.end());
                     line = line.substr(i + 1);
                     i = 0;
                     char splitWord[word.length()];
                     strcpy(splitWord, word.c_str());
                     int vowelCount = 0;

                     for (int j = 0; j < sizeof(splitWord); j++)
                     {
                        if ((tolower(splitWord[j]) == 'a' || tolower(splitWord[j]) == 'e' || tolower(splitWord[j]) == 'i' || tolower(splitWord[j]) == 'o' || tolower(splitWord[j]) == 'u') && vowelCount <= 3)
                        {
                           vowelCount++;
                        }
                     }
                     if (vowelCount == 0)
                     {
                        noVowel++;
                        if (zeroVowelCount.find(word) == zeroVowelCount.end())
                        {
                           zeroVowelCount[word] = 1;
                        }
                        else
                        {
                           zeroVowelCount[word]++;
                        }
                     }
                     else if (vowelCount == 1)
                     {
                        oneVowel++;
                        if (oneVowelCount.find(word) == oneVowelCount.end())
                        {
                           oneVowelCount[word] = 1;
                        }
                        else
                        {
                           oneVowelCount[word]++;
                        }
                     }
                     else if (vowelCount == 2)
                     {
                        twoVowel++;
                        if (twoVowelCount.find(word) == twoVowelCount.end())
                        {
                           twoVowelCount[word] = 1;
                        }
                        else
                        {
                           twoVowelCount[word]++;
                        }
                     }
                     else if (vowelCount >= 3)
                     {
                        threeVowel++;
                        if (threeVowelCount.find(word) == threeVowelCount.end())
                        {
                           threeVowelCount[word] = 1;
                        }
                        else
                        {
                           threeVowelCount[word]++;
                        }
                     }
                  }
               }
            }
         }
      }
      if (lineCount == 0)
      {
         cout << "File is empty." << endl;
         exit(1);
      }
      cout << "Number of words in the file: " << totalWordCount << endl;
      cout << "Number of words with no vowels in the file: " << noVowel << endl;
      cout << "Number of words with one vowel in the file: " << oneVowel << endl;
      cout << "Number of words with two vowels in the file: " << twoVowel << endl;
      cout << "Number of words with three or more vowels in the file: " << threeVowel << endl;

      map<string, int>::iterator it;
      if (zeroVowelCount.size() > 0)
      {
         cout << "\nList of Words with no vowels and their number of occurrences:" << endl;
         for (it = zeroVowelCount.begin(); it != zeroVowelCount.end(); it++)
         {
            cout << it->first << ": " << it->second << endl;
         }
      }
      if (oneVowelCount.size() > 0)
      {
         cout << "\nList of Words with one vowel and their number of occurrences:" << endl;
         for (it = oneVowelCount.begin(); it != oneVowelCount.end(); it++)
         {
            cout << it->first << ": " << it->second << endl;
         }
      }
      if (twoVowelCount.size() > 0)
      {
         cout << "\nList of Words with two vowels and their number of occurrences:" << endl;
         for (it = twoVowelCount.begin(); it != twoVowelCount.end(); it++)
         {
            cout << it->first << ": " << it->second << endl;
         }
      }
      if (threeVowelCount.size() > 0)
      {
         cout << "\nList of Words with three or more vowels and their number of occurrences:" << endl;
         for (it = threeVowelCount.begin(); it != threeVowelCount.end(); it++)
         {
            cout << it->first << ": " << it->second << endl;
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