No.884 Uncommon Words from Two Sentences
====
We are given two sentences `A` and `B`.  (A sentence is a string of space separated words.  Each word consists only of lowercase letters.)

A word is uncommon if it appears exactly once in one of the sentences, and does not appear in the other sentence.

Return a list of all uncommon words. 

You may return the list in any order.

## Problem requirements
  
The problem is just asking "finding the word only appears once in the two sentences". It involves counting & finding words. So it is natural to use a map (hashmap) to solve it.  

## How To (In C++)
### 1. Two pointers and map
```C++
vector<string> uncommonFromSentences(string A, string B) {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    vector<string> res;
    string word;
    map<string, int> map1;
    A = A + " " + B;
    int i = 0, j=0;
    while (i < A.size()) {
        word = "";
        j = (j <= A.size() - 1) ? A.find(" ", j) : string::npos;
        if (j != string::npos) {
            while (i != j) word += A[i++];
        }
        else {
            while (i != A.size()) word += A[i++];
        }
        i++; j++;
        if (map1.count(word))map1[word] += 1;
        else map1.insert(pair<string, int>(word, 1));
    }
    map<string, int>::iterator it;
    for (it = map1.begin(); it != map1.end(); it++) {
        if (it->second == 1) res.push_back(it->first);
    }

    return res;

}
```
The idea is simple: split words from the two sentences, add words into a map and counts the number of each word. When all words are inserted, those word only count once are put into the result array.  
  
**Time complexity:**   
Inserting words and outputing to result array both need $O(n)$ time, so the total time is $O(n)$.  
  
**Space complexity:**  
$O(n)$ for the map.  

### 2. Optimized way
Because C++ does not have a method to directly split words from a string, we need to implement in our way. Method 1 use two pointer to locate words. The following method use `istringstream` to do that, which not making it faster but making the code more readable.  

```C++
vector<string> uncommonFromSentences(string A, string B) {
    // combine the two strings for simplicity and construct an istringstream
    istringstream combined(A + " " + B);

    // our word will be put in this variable by getline
    string word;

    // keep track of word occurrences
    unordered_map<string, int> counts;

    // get the next word and increase its count in our map
    while (getline(combined, word, ' '))
        counts[word] += 1;

    // put the words with an occurrence of 1 in our result vector
    vector<string> result;
    for(auto &p : counts) {
        if(p.second == 1)
            result.push_back(p.first);
    }

    return result;
}
```
Also notice how the map is iterated by `foreach`.  
  
Another way to get words is not combining `A` and `B`, and use only one pointer:  
```C++
std::vector<std::string> uncommonFromSentences(std::string A, std::string B)
  {
      std::map<std::string, int> ma;

      std::string tmp;

      for(size_t i = 0; i < A.size(); i++)
      {
          if(A[i] != ' ')
          {
              tmp.push_back(A[i]);
          }
          else
          {
              ma[tmp]++;
              tmp = "";
          }
      }

      if(!tmp.empty())
      {
          ma[tmp]++;
      }

      tmp = "";

      for(size_t i = 0; i < B.size(); i++)
      {
          if(B[i] != ' ')
          {
              tmp.push_back(B[i]);
          }
          else
          {
              ma[tmp]++;
              tmp = "";
          }
      }

      if(!tmp.empty())
      {
          ma[tmp]++;
      }

      std::vector<std::string> res;

      for(const auto &el: ma)
      {
          if(el.second == 1)
          {
              res.push_back(el.first);
          }
      }

      return res;
  }
```

    
    
