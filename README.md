LAB-1(23 January 2025)
-------------------
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
-------------------
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
