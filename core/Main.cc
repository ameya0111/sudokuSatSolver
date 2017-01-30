/*****************************************************************************************[Main.cc]
Copyright (c) 2003-2006, Niklas Een, Niklas Sorensson
Copyright (c) 2007-2010, Niklas Sorensson

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

/*
Modified by :- Ameya Khandekar
January 29 2017 :- 
Substantial modifications to the Main.cc file to drive the sudokuSolver.
Also removed some of the printStats and SIGNAL handling functions found in the original software.
*/



#include <errno.h>
#include <iostream>
#include <string>
#include <signal.h>
#include <zlib.h>

#include "utils/System.h"
#include "utils/ParseUtils.h"
#include "utils/Options.h"
#include "core/Dimacs.h"
#include "core/Solver.h"
#include "core/Sudoku.h"


using namespace Minisat;

void printStats(Solver&) ;
static Solver* solver;

int main(int argc, char** argv)
	{
    try {
        setUsageHelp("USAGE: %s [options] <input-file> <result-output-file>\n\n  where input may be either in plain or gzipped DIMACS.\n");
        
#if defined(__linux__)
        fpu_control_t oldcw, newcw;
        _FPU_GETCW(oldcw); newcw = (oldcw & ~_FPU_EXTENDED) | _FPU_DOUBLE; _FPU_SETCW(newcw);
        //printf("WARNING: for repeatability, setting FPU to use double precision\n");
#endif
		std::string filename(argv[1]);
		Sudoku sudoku(filename);        
		sudoku.createCNF();   
		Solver S;
        S.verbosity = 0;

    	for(int i = 1; i <= 729 ; i++)
        	S.newVar();
        solver = &S;
		for(int i = 0 ; i < (int) sudoku.clauseDB.size() ; i++ ) {
    
    	    vec<Lit> clause_to_be_added ;
			for(int j = 0 ; j < (int) sudoku.clauseDB[i].size() ; j++){
    	    
    	        int k  = sudoku.clauseDB[i][j] ;
    	        if(k > 0)
    	            clause_to_be_added.push(mkLit( k - 1)) ;
    	        else
    	            clause_to_be_added.push(~mkLit(abs(k) - 1));
    	    }
    	
        	S.addClause_(clause_to_be_added);    
    
    	}
		std::vector<int> model ;	
        vec<Lit> dummy;
        for(unsigned int i = 1 ; i < sudoku.elem.size() ; i++){
			if(sudoku.elem[i] != 0){
				int var_to_add = sudoku.elmvalToVar(i,sudoku.elem[i]) ;
				dummy.push(mkLit(var_to_add - 1));  // add the constraints based on input.		
			}	
		}
		std::cout << "input :- " << std::endl ; 
		sudoku.displayInput() ; 
		lbool ret = S.solveLimited(dummy);
            if (ret == l_True){
            	std::cout << "SAT , solution is :- " << std::endl ;
				S.dumpModel(model);
				sudoku.displayResult(model);
			}
			else if (ret == l_False)
				std::cout << "UNSAT" << std::endl ; 
            else
				std::cout << "INDET" << std::endl ; 
    } catch (OutOfMemoryException&){
        printf("===============================================================================\n");
        printf("INDETERMINATE\n");
        exit(0);
    }
}


void printStats(Solver& solver)
{
    double cpu_time = cpuTime();
    double mem_used = memUsedPeak();
    printf("restarts              : %"PRIu64"\n", solver.starts);
    printf("conflicts             : %-12"PRIu64"   (%.0f /sec)\n", solver.conflicts   , solver.conflicts   /cpu_time);
    printf("decisions             : %-12"PRIu64"   (%4.2f %% random) (%.0f /sec)\n", solver.decisions, (float)solver.rnd_decisions*100 / (float)solver.decisions, solver.decisions   /cpu_time);
    printf("propagations          : %-12"PRIu64"   (%.0f /sec)\n", solver.propagations, solver.propagations/cpu_time);
    printf("conflict literals     : %-12"PRIu64"   (%4.2f %% deleted)\n", solver.tot_literals, (solver.max_literals - solver.tot_literals)*100 / (double)solver.max_literals);
    if (mem_used != 0) printf("Memory used           : %.2f MB\n", mem_used);
    printf("CPU time              : %g s\n", cpu_time);
}

