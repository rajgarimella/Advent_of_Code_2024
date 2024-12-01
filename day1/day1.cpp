#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <string>
#include <unordered_map>


  

std::pair<std::vector<int>, std::vector<int>> load_input(const std::string filepath) {
  std::ifstream inputFile(filepath);
  if (!inputFile.is_open()) {
      std::cerr << "Error opening file.\n";
  }

  std::vector<int> v1, v2;
  int a, b;
  while (inputFile >> a >> b) {
      v1.push_back(a);
      v2.push_back(b);
  }
  inputFile.close();

  return std::make_pair(v1, v2);
  
} 

int distance(int a, int b) {
  return a > b ? a - b: b - a;
}

int computeTotalDistance(const std::vector<int>& list1, const std::vector<int>& list2) {
  int total = 0;
  for (int i = 0; i < list1.size(); i++) {
    total += distance(list1[i], list2[i]);
  }
  return total;
}

std::unordered_map<int, int> countOccurances(const std::vector<int>& vec) {
  std::unordered_map<int, int> counter;
  for (auto e : vec) {
    counter[e]++;
  }
  return counter;
}

int computeSimilarity(std::vector<int>& list, const std::unordered_map<int, int>& occurances) {
  int total = 0;
  for (auto e : list) {
    if (occurances.contains(e)) {
      total +=e * occurances.at(e);
    }

  }
  return total;
}


int main() {
  auto lists = load_input("input.txt");
  std::vector<int> list1 = lists.first;
  std::vector<int> list2 = lists.second;
  std::sort(list1.begin(),list1.end());
  std::sort(list2.begin(),list2.end());
  std::cout << computeTotalDistance(list1, list2) << std::endl;

  std::unordered_map<int, int> occurances = countOccurances(list2);
  std::cout << computeSimilarity(list1, occurances) << std::endl;

  return 0;
}