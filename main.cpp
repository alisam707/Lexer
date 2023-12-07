#include "Lex.h"
#include "Par.h"
#include <ctype.h>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>

using namespace std;

int main() {
  ifstream inFile;
  ofstream outFile("output.txt");
  string filename;
  string line;

  cout << "Enter test case name (ex: test.txt): ";
  cin >> filename;

  inFile.open(filename.c_str());

  // Make sure file is opened
  if (!inFile.is_open()) {
    cerr << "Failed to open the file.\n";
    cerr << "Please enter correct file.\n";
    exit(1);
  } /*else {
    cout << "SOURCE CODE:\n\n";
    outFile << "SOURCE CODE:\n\n";
    while (getline(inFile, line)) {
      cout << line << endl;
      outFile << line << endl;
    }
  }

  cout << "\n\nOUTPUT:\n";
  cout << endl;

  outFile << "\n\nOUTPUT:\n";
  outFile << endl;
*/
  Parser check;

  inFile.clear();
  inFile.seekg(0);

  // run parser
  check.RAT23F(inFile, outFile);
  inFile.close();

  cout << endl;
  outFile << endl;

  outFile.close();
  cout << "see output.txt for results" << endl;

  return 0;
}
