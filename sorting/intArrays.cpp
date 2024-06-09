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

static int partition(vector<int> &b, int h, int k) {
  int j = h;
  int i = k;
  // 
        //          h---------------------------k
        // pre:  b |x|     ?                     |  for some x
        //          -----------------------------
        // 
        //          h---------------------------k
        // post: b |   <= x      |x|     >= x    |
        //          -----------------------------
        // {inv P: b[h+1..i-1] <= b[h] = x <= b[j+1..k]}, i.e.
        //  
        //          h---------j-------i------------k
        // post: b |   <= x  |x|  ?    |    >= x    |
        //          --------------------------------
  while (j < i) {
    if (b[j + 1] <= b[j]) {
      // next element smaller than or equal to 'x', should be to the left of j index
      int temp = b[j + 1];
      b[j + 1] = b[j];
      b[j] = temp;
      j++;
    } else {
      // next element greater than 'x', should be in position i & update i
      int temp = b[i];
      b[i] = b[j + 1];
      b[j + 1] = temp;
      i--;
    }
  }
  return j;
}

/** Sort b[h..k] */
static void quickSort(vector <int> &b, int h, int k) {
  if (k + 1 - h < 2) return;
  int mid = partition(b, h, k);
  quickSort(b, h, mid - 1);
  quickSort(b, mid + 1, k);
}

/** Segments b[h..e] and b[e+1..k] are already sorted.<br>
    Permute their values so that b[h..k] is sorted.
           h--------------e-------------k
    pre: b|    sorted     |    sorted    |
           -------------------------------
            h----------------------------k
    inv:  b|    sorted  |                 |
           -------------------------------
            h--------------e-------------k
    post: b|            sorted            |
            ------------------------------
*/
static void merge(vector <int> &b, int h, int e, int k) {
  int a[e + 1 - h] = {};

  for (int i = 0; i < e + 1; i++) {
    a[i] = b[i];
  }

  int a_pt = 0;
  int b_pt = e + 1;
  int pt = h;

  while (a_pt < e + 1 && b_pt < k) {
    if (a[a_pt] < b[b_pt]) {
      b[pt] = a[a_pt];
      a_pt++;
    } else {
      b[pt] = b[b_pt];
      b_pt++;
    }
    pt++;
  }

  if (a_pt < e + 1) {
    while (a_pt < e + 1) {
      b[pt] = a[a_pt];
      a_pt;
      pt++;
    }
  }
}


/** Sort b[h..k]. */
static void mergeSort(vector<int> &b, int h, int k) {
  if (h >= k) return;
  int med = (h + k) / 2;
  mergeSort(b, h, med);
  mergeSort(b, med + 1, k);
  merge(b, h, med, k);
}


/** Swap the values of b so that the negative ones are
      first, then the 0's, and finally the positive ones.
      In the original problem, the negative values are red
      balls, 0's are white balls, positive values are blue balls*/
static void DutchNationalFlag(vector<int> &b) {
  //        0------------------------------------ b.length
  // pre: b|              ?                      |
  //        -------------------------------------
  // 
  //        0------------------------------------ b.length
  // post:b|   <0    |    = 0     |    >0        |
  //        -------------------------------------
  int h = 0;
  int k = 0;
  int t = b.length-1
  //        0-------h-------k------t------------- b.length
  // inv :b|  <0   |  = 0  |   ?    |    >0      |
  //        -------------------------------------

  while (k < t + 1) {
    if (b[k] < 0) {
      int temp = b[h];
      b[h] = b[k];
      b[k] = temp;
      h++;
      k++;
    } else if (b[k] == 0) {
      k++;
    } else {
      int temp = b[t];
      b[t] = b[k];
      b[k] = temp;
      t--;
    }
  }
}