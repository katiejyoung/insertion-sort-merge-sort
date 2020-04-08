# Insertion Sort and Merge Sort
### The Program:
Implement merge sort and insertion sort to sort an array/vector of integers.  Name your programs “mergesort” and “insertsort”.  Both programs should read inputs from a file called “data.txt” where the first value of each line is the number of integers that need to be sorted, followed by the integers.

### Modify code:
Now that you have verified that your code runs correctly using the data.txt input file, you can modify the code to collect running time data.  Instead of reading arrays from the file data.txt and sorting, you will now generate arrays of size n containing random integer values from 0 to 10,000 to sort.  Use the system clock to record the running times of each algorithm for n = 5000, 10000, 15000, 20,000, etc.  You may need to modify the values of n if an algorithm runs too fast or too slow to collect the running time data. Output the array size n and time to the terminal.  Name these new programs insertTime and mergeTime.

## To Run the Program:
1. Give yourself permission to the compiler using: "chmod 777 compileall".
2. Run "compileall" to compile the code.
3. To run insertsort, type "insertsort". To run mergesort, type "mergesort".
4. To run insertTime, type "insertTime". To run mergeTime, type "mergeTime."
