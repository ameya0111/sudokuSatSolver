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

#include "Sudoku.h"

void Sudoku::aImpliesNotB(int a, int b){   //try to send positive a and b , just to be sure.
	clause.clear();
	clause.push_back(-a);
	clause.push_back(-b);
	clauseDB.push_back(clause);
}

void Sudoku::createCNF(){

	//add the constraint that each element must have a value in 1 to 9.
	for(int i = 1 ; i <= 81 ; i++){
		clause.clear();
		for(int j = 1 ; j <= 9 ; j++){
			clause.push_back(elmvalToVar(i,j));
		}
		clauseDB.push_back(clause);
	} 

	//add the constraint that each element can have only one value
	for(int elm = 1 ; elm <= 81 ; elm++){
		for(int val1 = 1 ; val1 <= 9 ; val1++){
			for(int val2 = val1 + 1 ; val2 <= 9 ; val2++)
			{	
				aImpliesNotB(elmvalToVar(elm,val1),elmvalToVar(elm,val2));
			}
		} 
	}

	//add the constraint that each row will have unique values
	for(int elm = 1 ; elm <= 81 ; elm++){
		int rowNum = ((elm - 1)/9) + 1 ; 
		for(int rowEl = 1 ; rowEl <= 9 ; rowEl++){
			int elm2 = (rowNum - 1)*9 + rowEl ; 
			if(elm2 != elm){
				for(int val = 1 ; val <= 9 ; val++)
					aImpliesNotB(elmvalToVar(elm,val),elmvalToVar(elm2,val));	
			}
		} //for(int rowEl .....
	} //for(int elm = ....

	//add the constraint that each column will have unique values
	for(int elm = 1 ; elm <= 81 ; elm++){
		int colNum = elm % 9; 
		if(colNum == 0)
			colNum = 9;
		
		for(int colEl = 1 ; colEl <= 9 ; colEl++){
			int elm2 = (colEl - 1)*9 + colNum ; 
			if(elm2 != elm){
				for(int val = 1 ; val <= 9 ; val++)
					aImpliesNotB(elmvalToVar(elm,val),elmvalToVar(elm2,val));	
			}
		} //for(int colEl .....
	} //for(int elm = ....

	//add the constraint that each 3x3 box will have unique values
	for(int elm = 1 ; elm <= 81 ; elm++){
		int colNum = elm % 9; 
		if(colNum == 0)
			colNum = 9;
		int rowNum = ((elm - 1)/9) + 1 ; 
		int subCx = ((rowNum - 1)/3) + 1; 
		int subCy = ((colNum - 1)/3) + 1;
		for(int i = 1 ; i <= 3 ; i++){
			for(int j = 1 ; j <= 3 ; j++){
				int elm2 = (27*(subCx-1) +3*(subCy - 1) + 9*(i-1) + j) ;
				if(elm2 != elm){
					for(int val = 1 ; val <= 9 ; val++)
						aImpliesNotB(elmvalToVar(elm,val),elmvalToVar(elm2,val));	
					} //if 
				}//for(int j = 
		}//for(int i =
	}//for(int elm = 
	
}


void Sudoku::displayInput(){
	for(unsigned int i = 1 ; i < elem.size() ; i++){
		std::cout << elem[i] << " " ;
		if(i%9 == 0){
			std::cout << std::endl ;
		}
	}
}

void Sudoku::displayResult(std::vector<int> & model){

	for(unsigned int i = 0 ; i < model.size() ; i++){
		int element = varToElm(model[i]);
		int val = varToValue(model[i]);
		int colNum = element % 9; 
		if(colNum == 0)
			colNum = 9;
		int rowNum = ((element - 1)/9) + 1 ; 
		result[rowNum][colNum] = val ;
	}
	for(int i = 1 ; i <= 9 ; i++){
		for(int j = 1 ; j <= 9 ; j++){
			std::cout << result[i][j] << " " ;
		}
		std::cout << std::endl ; 
	}
}


void Sudoku::readSudoku(std::string filename){
	std::fstream sudoku_desc(filename.c_str(), std::fstream::in);	
	elem.push_back(-1);   //making 0th element -1
	if(sudoku_desc.is_open()){
		int rowCount = 0 ;
		std::string line;
		while(std::getline(sudoku_desc,line)){	
			rowCount++;
			if(rowCount > 9){
				std::cerr << "Please keep number of rows equal to 9" << std::endl ; 
				exit(-1);
			}
			std::stringstream ss(line);
			int nextInt;
			int colCount = 0;
			while(ss >> nextInt){
				colCount++ ; 
				if(colCount > 9){
					std::cerr << "Please keep number of columns equal to 9" << std::endl ; 
					exit(-1);
				}
				if(nextInt < 0 || nextInt > 9){
					std::cerr << "Please fill Sudoku box with numbers in 0 to 9 range" << std::endl;
					exit(-1);
				}
				elem.push_back(nextInt);
			}
			if(colCount < 9){
				std::cerr << "Please keep number of columns equal to 9" << std::endl ; 
				exit(-1);
			}

		}
		if(rowCount < 9){
			std::cerr << "Please keep number of rows equal to 9" << std::endl ; 
			exit(-1);
		}
	}
}
