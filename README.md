# Sudoku Solver
## made using minisat boolean satisfiability solver
### (this project contains modifications to the minisat satisifiability solver. The files modified in this project are:-
 1. Main.cc
 2. Solver.h , Solver.cc
 3. Sudoku.h, Sudoku.cc (new files)


This Sudoku solver reads a Sudoku puzzle and converts it into a CNF formula based on the puzzle constraints.
The minisat solver then tries to solve this CNF formula. 
The output is again presented as a solved Sudoku.

BUILDING:  
(supported on Linux machines having gcc)  
export MROOT=&lt;sudokuSatSolver-dir&gt;  
cd core  
make  


USAGE:  
core/minisat sudokuPuzzleFile  

If a solution is found, the solver returns SAT, else it returns UNSAT.  

The Sudoku puzzle should be presented in an input file specified at the command line.  
Digits 1-9 fill up the specfied positions.  
Unspecified positions represented by '0'.  

(The file "sudoku1" in core directory is an example)  
Here is an example :-   
~  
0 0 5 1 0 0 2 0 8  
0 0 0 0 7 0 0 4 9  
7 8 0 0 2 0 6 0 5  
0 9 0 7 6 2 0 0 0  
0 4 7 0 0 0 8 9 0  
0 0 0 9 8 4 0 2 0  
9 0 8 0 3 0 0 5 1  
5 7 0 0 1 0 0 0 0  
6 0 3 0 0 9 7 0 0  
~

For more information on the directory structure please read minisatREADME.  
The original license can be found in minisatLICENSE.  
