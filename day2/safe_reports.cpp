#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>


bool isValidReport(const std::vector<int>& report) {
  int decreasingMultiplier = report[1] < report[0] ? 1 : -1;

  for (int i = 1; i < report.size(); i++) {
    int change = report[i-1] - report[i];
    if (change * decreasingMultiplier < 1 || change * decreasingMultiplier > 3) {
      return false;
    }
  }
  return true;
}

bool validIfSkipFirst(const std::vector<int>& report) {
    int decreasingMultiplier = report[2] < report[1] ? 1 : -1;
    for (int i = 2; i < report.size(); i++) {
      int change = report[i-1] - report[i];
      if (change * decreasingMultiplier < 1 || change * decreasingMultiplier > 3) {
        return false;
    }
  }
  return true;
}

bool validIfSkipLast(const std::vector<int>& report) {
  int decreasingMultiplier = report[1] < report[0] ? 1 : -1;

  for (int i = 0; i < report.size()-1; i++) {
    int change = report[i-1] - report[i];
    if ((change * decreasingMultiplier < 1 || change * decreasingMultiplier > 3)) {
      return false;
    } 
  }
  return true;
}
bool validGivenSkipKth(const std::vector<int>& report, int skipIndex) {
  int decreasingMultiplier = report[1] < report[0] ? 1 : -1;
  if (skipIndex ==1) {
    decreasingMultiplier = report[2] < report[0] ? 1 : -1;
  } else if (skipIndex == 0) {
    decreasingMultiplier = report[2] < report[1]  ? 1 : -1;
  }

  for (int i = 1; i < report.size(); i++) {
    int prev = i-1;
    int curr = i;
    if (curr == skipIndex) {curr++;}
    else if (prev == skipIndex) {prev--;}
    
    int change = report[prev] - report[curr];
    if ((change * decreasingMultiplier < 1 || change * decreasingMultiplier > 3)) {
      return false;
    } 
  }
  return true;
}

bool isAlmostValidReport(const std::vector<int>& report) {
  if (validIfSkipFirst(report)) {
    return true;
  }

  if (validIfSkipLast(report)) {
    return true;
  }

  for (int s = 0; s < report.size(); s++) {
    if (validGivenSkipKth(report, s)) {
      return true;
    }
  }
  return isValidReport(report);
}



std::pair<int,int> numValidReports(const std::string& filepath) {
  std::ifstream inputFile(filepath);
  if (!inputFile) {
      std::cerr << "Error opening file." << std::endl;
      exit(1);
  }


  int totalValidReports = 0;
  int totalAlmostValidReports = 0;
  
  std::string line;
  while (std::getline(inputFile, line)) {
    std::vector<int> numbers;
    std::istringstream lineStream(line);
    int value;
    while (lineStream >> value) { 
      numbers.push_back(value);
    }
    totalValidReports += isValidReport(numbers);
    totalAlmostValidReports += isAlmostValidReport(numbers);
  }
  inputFile.close();

  return std::make_pair(totalValidReports, totalAlmostValidReports);
}


// 483 too high
// 462 too low
int main() {
  auto info = numValidReports("input.txt");
  std::cout << info.first << std::endl;
  std::cout << info.second << std::endl;


  return 0;
}