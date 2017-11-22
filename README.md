## Design and Implementation of Algorithms to Solve the Sudoku Puzzle

Sudoku is a logical puzzle that has achieved international popularity. There have been a
number of computer solvers developed for this puzzle. Various Artificial Intelligence
techniques such as constraint propagation, forward checking, minimum remaining
heuristic,etc have been developed to solve constraint satisfaction problems. The objective
of this project is to optimize the algorithm for solving sudoku puzzles using artificial
techniques combined with a heuristic approach to prune the search space of the puzzle . 

### Prerequisites
```
Gurobi Optimizer 
```
### Installing
[Download page](http://www.gurobi.com/registration/download-reg)

Copy the Gurobi distribution to the destination directory
and extract the contents. Extraction is done with the following command:
```
tar xvfz gurobi7.5.1_linux64.tar.gz
```
This command will create a sub-directory /opt/gurobi751/linux64 that contains the complete
Gurobi distribution. Your <installdir> (which we'll refer to throughout this document) will be
/opt/gurobi751/linux64.

The Gurobi Optimizer makes use of several executable files. In order to allow these les to be found
when needed, you will have to modify a few environment variables:
```
• GUROBI_HOME should point to your <installdir> .
• PATH should be extended to include <installdir>/bin .
• LD_LIBRARY_PATH should be extended to include <installdir>/lib .

```
Users of the bash shell should add the following lines to their .bashrc files:
```
export GUROBI_HOME="/opt/gurobi751/linux64"
export PATH="${PATH}:${GUROBI_HOME}/bin"
export LD_LIBRARY_PATH="${LD_LIBRARY_PATH}:${GUROBI_HOME}/lib"

```
Users of the csh shell should add the following lines to their .cshrc files:
```
setenv GUROBI_HOME /opt/gurobi751/linux64
setenv PATH ${PATH}:${GUROBI_HOME}/bin
setenv LD_LIBRARY_PATH ${LD_LIBRARY_PATH}:${GUROBI_HOME}/lib

```
If LD_LIBRARY_PATH is not already set, use the following instead:
```
export LD_LIBRARY_PATH="${GUROBI_HOME}/lib"
or
setenv LD_LIBRARY_PATH ${GUROBI_HOME}/lib

```
These paths should be adjusted to reect your chosen <installdir> .

[Retrieving Your Gurobi License](https://user.gurobi.com/download/licenses/current)
