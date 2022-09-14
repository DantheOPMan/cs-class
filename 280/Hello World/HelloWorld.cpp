#include <iostream>

using namespace std;

int main() {
  string firstName, lastName;
  cout << "Welcome to CS 280 in Fall 2022\nPlease enter your last name followed by your first name.\n";
  cin >> lastName >> firstName;
  cout << "Hello " + firstName + " " + lastName + " in CS 280\n";
  return 0;
}