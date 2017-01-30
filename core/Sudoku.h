/*****************************************************************************************[Sudoku.cc]
Copyright (c) 2017 : Ameya Shashikant Khandekar

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and
associated documentation files (the "Software"), to deal in the Software without restriction,
including without limitation the rights to use, copy, modify, merge, publish, distribute,
sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or
substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT
NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT
OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
**************************************************************************************************/

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <cassert>

class Sudoku{
    std::vector< int > clause;
	int result[10][10];
public:
	std::vector<int> elem;
	std::vector< std::vector<int> > clauseDB;
	Sudoku(std::string filename) {
		readSudoku(filename);
	}
	void readSudoku(std::string);
	void displayInput();
	void createCNF();
	void aImpliesNotB(int,int);
	void displayResult(std::vector<int> &);

	inline int elmvalToVar(int elm, int val){
		return (9*(elm - 1) + val);
	}
	inline int varToElm(int var){
		return ( (var%9 == 0) ? (var/9) : ((var/9) + 1)) ;
	}
	inline int varToValue(int var){
		return ( (var%9 == 0) ? 9 : (var%9) ) ;
	}

};
