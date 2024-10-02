University of Central Florida
CGS 3763 Operating System Concepts
Assignment 6
Due, Thursday, March 14, 2024 for maximum 100%
Friday, March 15, 2024 for maximum 90%
Saturday, March 16, 2024 for maximum 80%
Sunday, March 17, 2024 for maximum 70%
Deliverables
To complete this assignment you must submit your OSManagement.c to Webcourses.
Project description
This project will require students to simulate the behaviors of an operating system with a series of
assignments.
Assignment Scope
1. Memory management with dynamic partitions.
C programming language integrated development environment (IDE)
1. Code::Blocks ~ NOT Mac compatible
2. Visual Studio Code
3. Atom
4. https://replit.com/
5. XCode
Assignment Scope: Memory Management
1. First Fit Implementation:
a. Input memory blocks with size and processes with size.
b. Initialize all memory blocks as free.
c. Start by picking each process and check if it can be assigned to current block.
d. If size-of-process <= size-of-block if yes then assign and check for next process.
e. If not then keep checking the further blocks.
2. Best Fit Implementation:
a. Input memory blocks with size and processes with size.
b. Initialize all memory blocks as free.
c. Start by picking each process and find the minimum block size that can be assigned to
current process i.e., find min(blockSize[1], blockSize[2],.....blockSize[n]) >
processSize[current], if found then assign it to the current process.
d. If not, then leave that process and keep checking the further processes.
3. Worst Fit Implementation:
a. Input memory blocks with size and processes with size.
b. Initialize all memory blocks as free.
c. Start by picking each process and find the maximum block size that can be assigned to
current process i.e., find max(blockSize[1], blockSize[2],.....blockSize[n]) >
processSize[current], if found then assign it to the current process.
d. If not, then leave that process and keep checking the further processes.
2
4. Next Fit Implementation:
a. Input memory blocks with size and processes with size.
b. Initialize all memory blocks as free.
c. Start by picking each process and check if it can be assigned to the current block, if yes,
allocate it the required memory and check for next process but from the block where we
left not from starting.
d. If the current block size is smaller, keep checking the further blocks.
Tasks
Activity
OSManagement.c 1. Update source code file OSManagement.c
preprocessor 2. Declare the following macros (a.k.a., global constants)
a. MEMORY as value 4
b. FIRST as value 0
c. BEST as value 1
d. WORST as value 2
e. NEXT as value 3
3. Add function prototype for functions
a. memoryManagement
b. displayProcess
c. firstFit
d. worstFit
e. bestFit
f. nextFit
main 4. Update the main function to do the following
a. Update the decision-making logic to determine which OS function to
run based on the following
i. 4 (i.e., MEMORY) = memoryManagement()
displayMenu 5. Update function displayMenu to do the following
a. Write a printf statement to display the OS Management Menu option 4.
Memory Management
i. Update decision making logic to validate the user’s input is
between values 0 and 4, inclusive; if not, set variable choice
equal to -1 (i.e., INVALID)
memoryManagement 6. Write function memoryManagement to do the following
a. Return type void
b. Empty parameter list
c. Write a looping construct to loop for each of the four memory
management algorithms
i. Declare a one-dimensional array, data type integer, to store the
sizes of the memory blocks (i.e. blockSize) initialized with
values 70, 20, 45, 65, 40, 80
ii. Declare a one-dimensional array, data type integer, to store the
sizes of the processes (i.e. processSize) initialized with values
15, 35, 25, 45, 60, 20
iii. Declare a variable, data type integer, to store the number of
blocks (i.e. blocks)
iv. Declare a variable, data type integer, to store the number of
processes (i.e. processes)
3
v. Write decision making logic based on the value of the looping
variable (i.e. algorithm)
1. When algorithm is equal to FIRST, call function
firstFit, passing arguments blockSize, blocks,
processSize, and processes
2. When algorithm is equal to BEST, call function
bestFit, passing arguments blockSize, blocks,
processSize, and processes
3. When algorithm is equal to WORST, call function
worstFit, passing arguments blockSize, blocks,
processSize, and processes
4. When algorithm is equal to NEXT, call function
nextFit, passing arguments blockSize, blocks,
processSize, and processes
nextFit 7. Write function nextFit to do the following
a. Return type void
b. Parameter list includes
i. One-dimensional array, data type integer, contains the block
sizes (i.e. blockSize)
ii. Parameter contains the number of blocks, data type integer (i.e.
blocks)
iii. One-dimensional array, data type integer, contains the process
sizes (i.e. processSize)
iv. Parameter contains the number of processes, data type integer
(i.e. processes)
c. Declare a one-dimensional array, data type integer, to store the block id
that a process is allocated to (i.e. allocation), size is parameter
processes
d. Declare a variable, data type integer, to store the block allocation for a
process, initialize to 0 (i.e. id)
e. Call function memset, passing arguments
i. Array allocation
ii. -1 (i.e. INVALID)
iii. sizeof(allocation)
f. Using a looping construct, loop through the number of processes
i. Using a looping construct, loop while id is less than the number
of blocks
1. If the current block size (i.e. index id) is greater than or
equal to the current process size (i.e. index of outer
looping variable)
a. Update the allocation array to set the element
at index of the outer looping variable equal to
variable id
b. Reduce available memory of the current block
size (i.e. index id) by the process size (i.e.
index of the outer looping variable)
c. break out of the inner loop
ii. Update the value of variable id to set the next index in array
blockSize by adding 1 to variable id then modulus the total by
the number of blocks
4
g. Call function displayProcess passing arguments allocation, processes,
and processSize
firstFit 8. Write function firstFit to do the following
a. Return type void
b. Parameter list includes
i. One-dimensional array, data type integer, contains the block
sizes (i.e. blockSize)
ii. Parameter contains the number of blocks, data type integer (i.e.
blocks)
iii. One-dimensional array, data type integer, contains the process
sizes (i.e. processSize)
iv. Parameter contains the number of processes, data type integer
(i.e. processes)
c. Declare a one-dimensional array, data type integer, to store the block id
that a process is allocated to (i.e. allocation), size is parameter
processes
d. Call function memset, passing arguments
i. Array allocation
ii. -1 (i.e. INVALID)
iii. sizeof(allocation)
e. Using a looping construct, loop through the number of processes
i. Using a looping construct, loop the number of blocks
1. If the current block size (i.e. index of the inner looping
variable) is greater than or equal to the current process
size (i.e. index of outer looping variable)
a. Update the allocation array to set the element
at index of the outer looping variable equal to
the inner looping variable
b. Reduce available memory of the current block
size (i.e. index of the inner looping variable) by
the process size (i.e. index of the outer looping
variable)
c. break out of the inner loop
f. Call function displayProcess passing arguments allocation, processes,
and processSize
bestFit 9. Write function bestFit to do the following
a. Return type void
b. Parameter list includes
i. One-dimensional array, data type integer, contains the block
sizes (i.e. blockSize)
ii. Parameter contains the number of blocks, data type integer (i.e.
blocks)
iii. One-dimensional array, data type integer, contains the process
sizes (i.e. processSize)
iv. Parameter contains the number of processes, data type integer
(i.e. processes)
5
c. Declare a one-dimensional array, data type integer, to store the block id
that a process is allocated to (i.e. allocation), size is parameter
processes
d. Call function memset, passing arguments
i. Array allocation
ii. -1 (i.e. INVALID)
iii. sizeof(allocation)
e. Using a looping construct, loop through the number of processes
i. Declare a variable, data type integer, to store the current best fit
value (i.e. bestIdx) initialized to -1 (i.e. INVALID)
ii. Using a looping construct, loop the number of blocks
1. If the current block size (i.e. index of the inner looping
variable ) is greater than or equal to the current process
size (i.e. index of outer looping variable)
a. If the value of bestIdx is equal to -1 (i.e.
INVALID)
i. Set variable bestIdx equal to the
current block (i.e. the inner looping
variable)
b. Else if the value of the block size at index
bestIdx is greater than or equal to the value of
the block size at index of the inner looping
variable
i. Set variable bestIdx equal to the
current block (i.e. the inner looping
variable)
iii. If the value of variable bestIdx is not equal to -1 (i.e.
INVALID)
1. Update the allocation array to set the element at index
of the outer looping variable equal to variable bestIdx
2. Reduce available memory of the current block size (i.e.
index bestIdx) by the process size (i.e. index of the
outer looping variable)
f. Call function displayProcess passing arguments allocation, processes,
and processSize
worstFit 10. Write function worstFit to do the following
a. Return type void
b. Parameter list includes
i. One-dimensional array, data type integer, contains the block
sizes (i.e. blockSize)
ii. Parameter contains the number of blocks, data type integer (i.e.
blocks)
iii. One-dimensional array, data type integer, contains the process
sizes (i.e. processSize)
iv. Parameter contains the number of processes, data type integer
(i.e. processes)
c. Declare a one-dimensional array, data type integer, to store the block id
that a process is allocated to (i.e. allocation), size is parameter
processes
d. Call function memset, passing arguments
6
i. Array allocation
ii. -1 (i.e. INVALID)
iii. sizeof(allocation)
e. Using a looping construct, loop through the number of processes
i. Declare a variable, data type integer, to store the current worst
fit value (i.e. wstIdx) initialized to -1 (i.e. INVALID)
ii. Using a looping construct, loop the number of blocks
1. If the current block size (i.e. index of the inner looping
variable ) is greater than or equal to the current process
size (i.e. index of outer looping variable)
a. If the value of wstIdx is equal to -1 (i.e.
INVALID)
i. Set variable wstIdx equal to the
current block (i.e. the inner looping
variable)
b. Else if the value of the block size at index
wstIdx is less than the value of the block size
at index of the inner looping variable
i. Set variable wstIdx equal to the
current block (i.e. the inner looping
variable)
iii. If the value of variable wstIdx is not equal to -1 (i.e.
INVALID)
1. Update the allocation array to set the element at index
of the outer looping variable equal to variable wstIdx
2. Reduce available memory of the current block size (i.e.
index wstIdx) by the process size (i.e. index of the
outer looping variable)
f. Call function displayProcess passing arguments allocation, processes,
and processSize
displayProcess 11. Write function displayProcess to do the following
a. Return type void
b. Parameter list includes
i. One-dimensional array, data type integer, that stores the block
number allocations (i.e. allocation)
ii. Parameter that contains the number of processes, data type
integer (i.e. processes)
iii. One-dimensional array, data type integer, that stores the
processes (i.e. processSize)
c. Write a looping construct to loop through the processes (i.e.
processSize)
i. Display to the console the process number (i.e use the looping
variable plus 1)
ii. Display to the console the process size (i.e. processSize array
at the current looping index)
iii. Display to the console the memory block assigned based on the
following logic
1. If the value stored at the current index of array
processSize if -1 (i.e. INVALID), output Not
Allocated
7
2. Else, output the current allocation (i.e. allocation)
OSManagement executable
Test Case 1 Test Case 1 passes
Test Case 2 Test Case 2 passes
Test Case 3 Test Case 3 passes
Test Case 4 Test Case 4 passes
Test Case 5 Test Case 5 passes
Test Case 6 Test Case 6 passes
Test Case 7 Test Case 7 passes
Test Case 8 Test Case 8 passes
Source compiles with no errors
Source compiles with no warnings
Source runs with no errors
Source includes comments
Test Cases
Action Expected outcome
Test Case 1 Run executable The executable runs
The output in the command prompt should be similar
to Figure 1 displayMenu function output
Test Case 2 User enters invalid menu option
value other than 0, 1, 2, 3, or 4
The output in the command prompt should be similar
to Figure 1 displayMenu function output
Test Case 3 User enters menu option value 4 The output in the command prompt should be similar
to Figure 2 memoryManagement function output
Test Case 4 User enters menu option value 4;
nextFit function
The output in the command prompt should be similar
to Figure 3 nextFit function output
Test Case 5 User enters menu option value 4;
firstFit function
The output in the command prompt should be similar
to Figure 4 firstFit function output
Test Case 6 User enters menu option value 4;
bestFit function
The output in the command prompt should be similar
to Figure 5 bestFit function output
Test Case 7 User enters menu option value 4;
worstFit function
The output in the command prompt should be similar
to Figure 6 worstFit function output
Test Case 8 User enters menu option value 0 End of functionality;
