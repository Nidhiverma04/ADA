LAB-1(23 January 2025)
----------------------
QUES 1 ->  
AIM : To calculate the cosine similarity between two text files by analyzing word frequency and identifying common words.
WORKING : 1. Start  
          2. Read and Process Files:  
             - Open files and remove stop words.  
             - Store remaining words in a list.  
          3. Create Word Frequency Dictionaries:  
             - Count occurrences of each word and store them in a dictionary.  
          4. Find Common Words:  
             - Identify words present in both dictionaries.  
             - Multiply their frequencies and store in a new dictionary.  
          5. Compute Cosine Similarity:  
             - Compute magnitude of each dictionary:  sqrt [sum (freq[word] * freq[word])]
             - Compute dot product of common words.  
             - Calculate similarity: a.b / |a|*|b|  
          6. Print Cosine Similarity Value  
          7. Stop
        
OUTPUT :        Input -                                                                           Output - Cosine Similarity value: 0.875
                file 1 : Machine learning is a subset of artificial intelligence.
                file 2 : Machine learning, a branch of artificial intelligence.                                                  
                                              
TIME COMPLEXITY : O(n + m), n = len(file1) and m = len(file2)
SPACE COMPLEXITY : O(n+m)

QUES 2 ->  
AIM : To generate an n × n magic square, where the sum of each row, column, and diagonal is the same.
WORKING : 1. Start  
          2. Input: Read an odd integer n (size of the magic square).  
          3. Initialize:  
             - Create an n × n matrix filled with 0.  
             - Set starting position at the first row, middle column.  
          4. Place Numbers:  
             - For each number i from 1 to n²:  
               - Place i at the current position (row, col).  
               - Calculate new position:  
                 - Move up-left (row-1, col-1).  
                 - If out of bounds, wrap around.  
               - If the new position is occupied, move down instead.  
          5. Print Magic Square  
          6. Stop  
        
OUTPUT :        Input - Enter size (n x n): 3                                                             Output - Magic Square:
                                                                                                                    8 1 6
                                                                                                                    3 5 7
                                                                                                                    4 9 2                                               
                                              
TIME COMPLEXITY : O(n²)
SPACE COMPLEXITY : O(n²)

QUES 3 ->  
AIM : To find a peak element in a 1D array, where a peak is an element that is greater than its neighbors.
WORKING : 1. Start  
          2. Input: Read array size `n` and `n` elements.  
          3. Check Boundary Conditions:  
             - If first element is greater than the second, return index `0`.  
             - If last element is greater than the second last, return index `n-1`.  
          4. Binary Search for Peak:  
             - Compute `mid = (low + high) / 2`.  
             - If `arr[mid]` is greater than both neighbors, return `mid`.  
             - If `arr[mid] < arr[mid+1]`, search the right half.  
             - Else, search the left half.  
          5. Print Peak Element  
          6. Stop 
        
OUTPUT :        Input - Enter size: 6                                                                  Output - Peak element: 7
                        Enter elements: 1 3 4 7 2 5                                                         
                                                                                                                                                                         
TIME COMPLEXITY : O(log n)
SPACE COMPLEXITY : O(1)

QUES 4 ->  
AIM : To find a peak element in a 2D array, where a peak is an element that is greater than or equal to its neighbors.
WORKING : 1. Start  
          2. Input: Read the number of rows `m` and columns `n`, followed by the elements of the 2D array.  
          3. Recursive Search for Peak:  
             - Start by searching in the middle column (`mid = (start_col + end_col) / 2`).  
             - Find the maximum element in the middle column across all rows.  
             - If the middle element is greater than or equal to its neighbors (left and right), return the element as the peak.  
          4. Recursion based on neighbors:  
             - If the element to the right is greater, search the right half of the array (i.e., from `mid + 1` to `end_col`).  
             - If the element to the left is greater, search the left half of the array (i.e., from `start_col` to `mid - 1`).  
          5. Print Peak Element  
          6. Stop  
        
OUTPUT :        Input - Enter size (m x n): 4 5                                                           Output - Peak element: 20
                        Enter elements: 
                        1 3 20 4 1
                        2 9 8 7 1
                        3 5 4 2 1
                        1 2 3 4 5                                                        
                                                                                                                                                                         
TIME COMPLEXITY : O(m log n), m = rows, n = cols
SPACE COMPLEXITY : O(1)

LAB-2(30 January 2025)
----------------------

QUES 1 ->  
AIM : To measure the execution time of Bubble Sort for varying array sizes and plot the complexity graph.
WORKING : 1. Start  
          2. Input:  
             - The program generates arrays of sizes (2, 4, 8, 16, ..., 25000).  
             - For each size, the array is filled with elements in descending order.  
          3. Bubble Sort:  
             - For each array, the Bubble Sort algorithm is executed 100 times to ensure consistent timing.  
             - After each sort, the sorted array is discarded, and the next iteration is performed.  
          4. Measure Time:  
             - Use `clock()` to measure the time taken for each sorting operation.  
             - The time is recorded for 100 iterations, and the average time per sort is calculated.  
          5. Store Results:  
             - The array size is written to `size.csv`.  
             - The average time per sort is written to `time.csv`.  
          6. Output: The program outputs "done" after completing the measurements.  
          7. Stop 
        
OUTPUT : Two CSV files are generated:
        - `size.csv`: Contains the array sizes for which the sort was performed.
        - `time.csv`: Contains the average time taken for each array size (in seconds).                       
                                              
TIME COMPLEXITY : O(n²)
SPACE COMPLEXITY : O(1)

![image](https://github.com/user-attachments/assets/b6df1b31-f29b-41f3-96b8-ffef802f2efd)


QUES 2 ->  
AIM : To measure the execution time of Insertion Sort for varying array sizes and plot the complexity graph.
WORKING : 1. Start  
          2. Input:  
             - The program generates arrays of sizes (2, 4, 8, 16, ..., 25000).  
             - For each size, the array is filled with elements in descending order(worst case), ascending for best case.  
          3. Bubble Sort:  
             - For each array, the Insertion Sort algorithm is executed 100 times to ensure consistent timing.  
             - After each sort, the sorted array is discarded, and the next iteration is performed.  
          4. Measure Time:  
             - Use `high_resolution_clock::now()` to measure the time taken for each sorting operation.  
             - The time is recorded for 100 iterations, and the average time per sort is calculated duration_cast<nanoseconds>.  
          5. Store Results:  
             - The array size is written to `size.csv`.  
             - The average time per sort is written to `time.csv`.  
          6. Output: The program outputs "done" after completing the measurements.  
          7. Stop 
        
OUTPUT : Two CSV files are generated:
        - `size.csv`: Contains the array sizes for which the sort was performed.
        - `time.csv`: Contains the average time taken for each array size (in seconds).                       
                                              
TIME COMPLEXITY : O(n²), worst && O(n), best
SPACE COMPLEXITY : O(1)

![image](https://github.com/user-attachments/assets/ce65964f-3e1a-4387-b15d-780b4c6f6ce8)


QUES 3 ->  
AIM : To measure the execution time of Magic Square for varying array sizes and plot the complexity graph.  
WORKING : 1. Start  
          2. Input:  
             - The program generates Magic Squares of sizes \(3, 5, 7, ..., 25001\).  
             - For each size, a Magic Square is created using a standard method (starting from the middle of the top row and filling numbers in a specific pattern).  
          3. Magic Square Algorithm:  
             - Initialize a 2D array of size \(n \times n\) with zeros.  
             - Start placing numbers from 1 to \(n^2\) in the square, following the rule:
               - Place the next number in the position above and to the left of the previous one.
               - If that position is already filled, place the number directly below the previous number.  
          4. Measure Time:  
             - Use `high_resolution_clock::now()` to measure the time taken for each Magic Square generation.  
             - The time is recorded for 5 iterations per size, and the average time is calculated in microseconds using `duration_cast<microseconds>`.  
          5. Store Results:  
             - The size of the Magic Square is written to `size.csv`.  
             - The average time taken for generating the Magic Square is written to `time.csv`.  
          6. Output: The program outputs "done" after completing the measurements.  
          7. Stop   
        
OUTPUT : Two CSV files are generated:  
        - `size.csv`: Contains the array sizes for which the sort was performed.  
        - `time.csv`: Contains the average time taken for each array size (in seconds).                         
                                              
TIME COMPLEXITY : O(n²)
SPACE COMPLEXITY : O(n²)

![image](https://github.com/user-attachments/assets/c3949b24-78cc-406a-bad5-699566d2fa9a)


QUES 4 ->
AIM : To measure the execution time of Quick Sort for varying array sizes and output the results to CSV files.  

WORKING : 1. Start  
          2. Input:  
             - The program generates arrays of sizes \(13, 26, 52, 104, ..., 90000\), where each array size is determined by the formula (n = n log(n)).  
             - For each size, the array is initialized with elements from 0 to \(n-1\).  
          3. Quick Sort Algorithm:  
             - The program executes Quick Sort 10 times for each array to ensure consistent timing.  
             - The partitioning step picks the first element as the pivot, and elements are rearranged such that elements less than the pivot are on the left, and elements greater than the pivot are on the right.  
          4. Measure Time:  
             - Use `clock_t` to measure the time taken for each sorting operation.  
             - The time is recorded for 10 iterations, and the average time is calculated using `double(end - start) / CLOCKS_PER_SEC`.  
          5. Store Results:  
             - The array size is written to `size.csv`.  
             - The average time taken for sorting each array is written to `time.csv`.  
          6. Output: The program outputs "done at end" after completing the measurements.  
          7. Stop  

OUTPUT : Two CSV files are generated:    
          - `size.csv`: Contains the array sizes for which the sort was performed.    
          - `time.csv`: Contains the average time taken for sorting each array (in seconds).  

TIME COMPLEXITY :   - Best & Average Case: O(n log n) due to the divide-and-conquer nature of the algorithm.  
                    - Worst Case: O(n²) when the pivot is always the smallest or largest element.
SPACE COMPLEXITY : O(log n) for the recursion stack in the average case.

![image](https://github.com/user-attachments/assets/6fde7bce-157e-463b-8879-3e44f959ea49)

![image](https://github.com/user-attachments/assets/d5fb4901-dc38-49f9-a3c9-9184d119c6b1)

QUES 5 ->  
AIM : To measure the execution time of Selection Sort for varying array sizes and plot the complexity graph.
WORKING : 1. Start  
          2. Input:  
             - The program generates arrays of sizes (2, 4, 8, 16, ..., 25000).  
             - For each size, the array is filled with elements in descending order.  
          3. Bubble Sort:  
             - For each array, the Selection Sort algorithm is executed 100 times to ensure consistent timing.  
             - After each sort, the sorted array is discarded, and the next iteration is performed.  
          4. Measure Time:  
             - Use `clock()` to measure the time taken for each sorting operation.  
             - The time is recorded for 100 iterations, and the average time per sort is calculated.  
          5. Store Results:  
             - The array size is written to `size.csv`.  
             - The average time per sort is written to `time.csv`.  
          6. Output: The program outputs "done" after completing the measurements.  
          7. Stop 
        
OUTPUT : Two CSV files are generated:
        - `size.csv`: Contains the array sizes for which the sort was performed.
        - `time.csv`: Contains the average time taken for each array size (in seconds).                       
                                              
TIME COMPLEXITY : O(n²)
SPACE COMPLEXITY : O(1)

![image](https://github.com/user-attachments/assets/ba7a5629-587c-4d14-9451-1df720492d43)


LAB-3(6 February 2025)
----------------------
QUES 1 ->  
AIM : To implement and analyze the Fractional Knapsack Problem using QuickSort for sorting items based on different criteria.  
WORKING : 1. Start   
          2. Input:  
             - The program initializes items with random weights (1-7) and profits (1-20).  
             - The profit-to-weight ratio is computed for each item.  
             - The knapsack capacity is set to 20.  
          3. Sorting Strategy (QuickSort):  
             - The items are sorted based on:
               - Weight (ascending)
               - Profit (descending)
               - Profit-to-weight ratio (descending)  
          4. Fractional Knapsack Algorithm:  
             - The program iterates over the sorted items and fills the knapsack:
               - If an entire item can fit, it's fully included.
               - If not, a fraction of it is added to maximize the total profit.  
          5. Measure Performance:  
             - The algorithm is executed three times, each with a different sorting criterion.  
             - The final profit is calculated and displayed for each case.  
          6. Output:  
             - The program prints the randomly generated item data.  
             - It then prints the total profit obtained when sorting by:
               - Weight
               - Profit
               - Profit-to-weight ratio  
          7. Stop  
          
OUTPUT :  weight : 25  
          profit : 38   
          ratio : 39     

TIME COMPLEXITY : O(n log n)  
                    - Sorting (QuickSort): O(n log n)   
                    - Knapsack Filling: O(n) 

SPACE COMPLEXITY : O(n)  
