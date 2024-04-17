#include <algorithm>
#include <fstream>
#include <iostream>
#include <locale>
#include <sstream>
#include <vector>

int main() {
  setlocale(LC_ALL, "C");

  std::ifstream inputFile("File.csv"); 
  if (!inputFile.is_open()) {
    std::cerr << "Error opening input file!" << std::endl;
    return 1;
  }

  std::vector<double> mmValues;
  std::string line;
  while (std::getline(inputFile, line)) {
    std::stringstream ss(line);
    double value;
    if (ss >> value) {
      mmValues.push_back(value);
    }
  }
  inputFile.close();

  std::ofstream csvFile("outputValues.csv");
  if (!csvFile.is_open()) {
    std::cerr << "Error creating output file!" << std::endl;
    return 1;
  }

  for (const auto &mmValue : mmValues) {
    std::stringstream stream;
    stream.imbue(std::locale("C")); 
    stream.precision(10);
    stream << mmValue / 10.0; 
    std::string cmValueStr = stream.str();
    for (auto &ch : cmValueStr) {
      if (ch == '.') {
        ch = ','; 
        break;
      }
    }
    csvFile << cmValueStr << "\n";
  }

  csvFile.close();

  return 0;
}