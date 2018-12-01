#include <iostream>
#include <vector>
#include <ctime>

std::vector<int> downSort(int n) {
    std::vector<int> res;
    for (int i = n; i > 0; i--) {
        res.push_back(i);
    }
    return res;
}

std::vector<int> upSort(int n) {
    std::vector<int> res;
    for (int i = 0; i < n; i++) {
        res.push_back(i);
    }
    return res;
}

std::vector<int> randomSort(int n) {
    std::vector<int> res;
    srand(time(0));
    for (int i = 0; i < n; i++) {
        int num = rand() % 1000;
        res.push_back(num);
    }
    return res;
}



void shellSort(std::vector<int> &arr, int n){
    // Start with a big gap, then reduce the gap 
    for (int gap = n/2; gap > 0; gap /= 2) { 
        // Do a gapped insertion sort for this gap size. 
        // The first gap elements a[0..gap-1] are already in gapped order 
        // keep adding one more element until the entire array is 
        // gap sorted  
        for (int i = gap; i < n; i += 1) { 
            // add a[i] to the elements that have been gap sorted 
            // save a[i] in temp and make a hole at position i 
            int temp = arr[i]; 
  
            // shift earlier gap-sorted elements up until the correct  
            // location for a[i] is found 
            int j;             
            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap) {
                arr[j] = arr[j - gap]; 
            }
              
            //  put temp (the original a[i]) in its correct location 
            arr[j] = temp; 
        } 
    } 
}



void insertionSort(std::vector<int> arr, int n) 
{ 
   int i, key, j; 
   for (i = 1; i < n; i++) 
   { 
       key = arr[i]; 
       j = i-1; 
       while (j >= 0 && arr[j] > key) 
       { 
           arr[j+1] = arr[j]; 
           j = j-1; 
       } 
       arr[j+1] = key; 
   } 
} 


// To find gap between elements 
int getNextGap(int gap) { 
    // Shrink gap by Shrink factor 
    gap = (gap*10)/13; 
    if (gap < 1) 
        return 1; 
    return gap; 
} 
  
// Function to sort a[0..n-1] using Comb Sort 
void combSort(std::vector<int> &a, int n) 
{ 
    // Initialize gap 
    int gap = n; 
  
    // Initialize swapped as true to make sure that 
    // loop runs 
    bool swapped = true; 
  
    // Keep running while gap is more than 1 and last 
    // iteration caused a swap 
    while (gap != 1 || swapped == true) 
    { 
        // Find next gap 
        gap = getNextGap(gap); 
  
        // Initialize swapped as false so that we can 
        // check if swap happened or not 
        swapped = false; 
  
        // Compare all elements with current gap 
        for (int i=0; i<n-gap; i++) 
        { 
            if (a[i] > a[i+gap]) 
            {
                int tmp = a[i];
                a[i] =  a[i+gap];
                a[i+gap] = tmp;
                swapped = true; 
            } 
        } 
    } 
} 

void compSort(std::vector<int> &arr, int size) {
    double fakt = 1.2473309; // фактор уменьшения
    int step = size - 1;

    while (step >= 1) {
        for (int i = 0; i + step < size; ++i) {
            if (arr[i] > arr[i + step]) {
                std::swap(arr[i], arr[i + step]);
            }
        }
        step /= fakt;
    }
} 


int main() {
    int k;
    int tb1, te1, result1;
    int tb2, te2, result2;
    int tb3, te3, result3;
    std::vector<int> v1;
    std::vector<int> v2;
    std::vector<int> v3;

// тест времени шелла
    for (int i = 1; i < 11; i++) {
        k = i * 100;

        v1 = upSort(k);
        v2 = downSort(k);
        v3 = randomSort(k);

        tb1 = clock();
        shellSort(v1, v1.size());
        te1 = clock();
        result1 = te1 - tb1;
        std::cout << "SHELL UP " << k << "time: " << result1 << "\n";

        tb2 = clock();
        shellSort(v2, v2.size());
        te2 = clock();
        result2 = te2 - tb2;
        std::cout << "SHELL DOWN " << k << "time: " << result2 << "\n";

        tb3 = clock();
        shellSort(v3, v3.size());
        te3 = clock();
        result3 = te3 - tb3;
        std::cout << "SHELL RANDOM " << k << "time: " << result3 << "\n";

        std::cout << "\n";

    }

// тест времени сортировки слиянием

    for (int i = 1; i < 11; i++) {
        k = i * 100;

        v1 = upSort(k);
        v2 = downSort(k);
        v3 = randomSort(k);

        tb1 = clock();
        insertionSort(v1, v1.size()); 
        te1 = clock();
        result1 = te1 - tb1;
        std::cout << "insertionSort UP " << k << "time: " << result1 << "\n";

        tb2 = clock();
        insertionSort(v2, v2.size());
        te2 = clock();
        result2 = te2 - tb2;
        std::cout << "insertionSort DOWN " << k << "time: " << result2 << "\n";

        tb3 = clock();
        insertionSort(v3, v3.size());
        te3 = clock();
        result3 = te3 - tb3;
        std::cout << "insertionSort RANDOM " << k << "time: " << result3 << "\n";

        std::cout << "\n";

    }
    std::cout << "\n\n\n";

// тест времени сортировки расческой
    for (int i = 1; i < 11; i++) {
        k = i * 100;

        v1 = upSort(k);
        v2 = downSort(k);
        v3 = randomSort(k);

        tb1 = clock();
        compSort(v1, v1.size());
        te1 = clock();
        result1 = te1 - tb1;
        std::cout << "COMB UP " << k << "time: " << result1 << "\n";

        tb2 = clock();
        compSort(v2, v2.size());
        te2 = clock();
        result2 = te2 - tb2;
        std::cout << "GOMB DOWN " << k << "time: " << result2 << "\n";

        tb3 = clock();
        compSort(v3, v3.size());
        te3 = clock();
        result3 = te3 - tb3;
        std::cout << "COMB RANDOM " << k << "time: " << result3 << "\n";

        std::cout << "\n";

    }
    return 0;
}