#include <unordered_map>
#include <queue>
#include <functional>
#include <string>
#include <cstdlib>
#include <cstdio>
using namespace std;

class pair_string_hasher
{
  hash<string> str_hash;
  hash<size_t> int_hash;
public:
  size_t operator()(const pair<string, string> &p) const {
    return int_hash(str_hash(p.first) + str_hash(p.second));
  }
};

struct heapElem {
  pair<string, string> twogram;
  int count;

  heapElem() {}
  heapElem(const pair<string, string> &tg, int c) : twogram(tg), count(c) {}

  bool operator<(const heapElem &rhs) const {
    // We need a minheap
    if (count != rhs.count) {
      return count > rhs.count;
    } else if (twogram.first != rhs.twogram.first) {
      return twogram.first < rhs.twogram.first;
    } else {
      return twogram.second < rhs.twogram.second;
    }
  }
};

vector<pair<string, string>> twograms(string str, int k) {
  vector<pair<string, string>> result;
  unordered_map<pair<string, string>, int, pair_string_hasher> hashmap;

  const char delim[] = " .,!?";
  char *cstr = const_cast<char*>(str.c_str());
  char *pch = strtok(cstr, delim);
  if (pch == nullptr) {
    return result;
  } 

  string str1 = pch, str2;
  while ((pch = strtok(nullptr, delim)) != nullptr) {
    str2 = pch;
    ++hashmap[make_pair(str1, str2)];
    str1 = str2;
  }

  auto it = hashmap.begin();
  priority_queue<heapElem> heap;
  while (it != hashmap.end() && k--) {
    heap.push(heapElem(it->first, it->second));
    ++it;
  }
  while (it != hashmap.end()) {
    heapElem e(it->first, it->second);
    if (e < heap.top()) {
      heap.pop();
      heap.push(e);
    }
    ++it;
  }

  while (!heap.empty()) {
    result.push_back(heap.top().twogram);
    heap.pop();
  }

  reverse(result.begin(), result.end());
  return result;
}

int main(void) {
  string strs[] = {
    "",
    "oops",
    "hahahahah",
    "I love Apple pie, especially sweet Apple pie",
    "hi hi hi hi hi hi hi do whatever you want until you do not want to do whatever you want and that is it. do do do do do do do do do do"
  };

  for (int i = 0; i < sizeof(strs) / sizeof(strs[0]); ++i) {
    auto top3 = twograms(strs[i], 3);
    printf("Top 3 two-grams of \"%s\":\n", strs[i].c_str());
    for (auto &p : top3) {
      printf("  \"%s\"-\"%s\"\n", p.first.c_str(), p.second.c_str());
    }
  }

  return 0;
}
