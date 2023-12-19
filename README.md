# QueryHandling-RoundRobin-Simulation

This C program simulates a simple query handling system using the Round Robin scheduling algorithm. It separates queries into two types: Faculty and Student queries, and processes them based on their arrival times and burst times.

## Features
- Two Query Types: The program handles two types of queries - Faculty and Student queries.
- Time Quantum: The user can set the time quantum for the Round Robin algorithm.
- Input Validation: The program ensures the correctness of user inputs, such as the number of queries, arrival times, and burst times.
- Sorting: Queries are sorted based on their arrival times for efficient processing.
- Round Robin Scheduling: The main processing is done using the Round Robin scheduling algorithm, considering the time quantum.
- Output Summary: The program provides a detailed summary of the execution, including total time spent, average turnaround time, and average waiting time.

## Instructions for Execution
1. Run the program and follow the on-screen instructions.
2. Enter the number of queries (between 0 and 120) and the time quantum.
3. For each query, enter the query type (1 for Faculty, 2 for Student), query ID, arrival time, and burst time.
4. Ensure that the arrival time of the next query is less than the completion time of the previous query.
5. Burst time must be entered such that (Arrival Time + Burst Time) is less than 120.

## Compilation and Execution
Compile the program using a C compiler, for example:
```bash
gcc query_handling.c -o query_handling
```
Run the compiled executable:
```bash
./query_handling
```
Follow the on-screen instructions to input queries and observe the Round Robin scheduling simulation.
