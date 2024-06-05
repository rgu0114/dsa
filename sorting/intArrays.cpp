#include <iostream>
using namespace std; 
#include <vector>

/* = index of x in b ---or the length of b if x is not in b. */
static int linearSearch(const vector<int> &b, int x) {
  int i = 0;

  while (i < b.size() && b[i] != x) {
    i++;
  }

  return i;
}

/* Return a value i that satisfies R: b[i] <= x < b[i+1] */
static int binarySearch(const vector<int> &b, int x) {
  // {P:b[i] <= x < b[j] and -1 <= i < j <= b.length}, i.e.
  //          0--------i------------j-------- b.length
  // post: b |       |<=x|    ?   |>x|      |
  //          -------------------------------
  int i = -1;
  int j = b.size();

  while (j > i + 1) {
    int k = (i + j) / 2;
    if (b[k] <= x) {
      i = k;
    } else {
      j = k;
    }
  }

  return i;
}

/** Return the position of the minimum value of b[h..k].<br>
Precondition: h < k. */
static int min(const vector<int> &b, int h, int k) {
  int minIndex = h;

  for (int i = 0; i < b.size(); i++) {
    if (b[i] < b[minIndex]) {
      minIndex = i;
    }
  }

  return minIndex;
}

/** Sort b --put its elements in ascending order. */
static void selectionSort(vector<int> &b) {
  int j = 0;

  while (j < b.size()) {
    int minVal = min(b, j, b.size() - 1);

    int temp = b[j];
    b[j] = b[minVal];
    b[minVal] = temp;

    j++;
  }
}

/** Precondition: b[h..k-1] is sorted, and b[k] contains a value.<br>
    Sort b[h..k] */
static void insertValue(vector<int> &b, int h, int k) {
  while (h < k && b[k] > b[k - 1]) {
    // swap b[k] and b[k - 1]. if k - 1 = h, this swap would guarantee sorted order
    int temp = b[k - 1];
    b[k - 1] = b[k];
    b[k] = temp;
    k--;
  }
}

/** Sort b[h..k] --put its elements in ascending order. */
static void insertionSort(vector<int> &b, int h, int k) {
  int i = h;
  while (i <= k) {
    insertValue(b, h, i);
    i++;
  }
}