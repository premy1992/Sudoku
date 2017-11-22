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

# Running the tests

This section will work through a simple C++ example in order to illustrate the use of the Gurobi
C++ interface. The example builds a model, optimizes it, and outputs the optimal objective value.

This is the source code for our example (also available in<installdir>/examples/c++/sudoku_c++.cpp )
Example sudoku_c++.cpp
[Gurobi Example Tour](http://www.gurobi.com/documentation/#)
  
## Example details
This example begins by including file gurobi_c++.h . Gurobi C++ applications should always start
by including this file.

## Creating the environment
```
GRBEnv env = GRBEnv();
```
 ## Creating the model
 ```
 GRBModel model = GRBModel(env);
 ```
 ## Adding variables to the model
 ```
 GRBVar x = model.addVar(0.0, 1.0, 0.0, GRB_BINARY, "x");
GRBVar y = model.addVar(0.0, 1.0, 0.0, GRB_BINARY, "y");
GRBVar z = model.addVar(0.0, 1.0, 0.0, GRB_BINARY, "z");
 ```
 ## Setting the objective
 ```
 model.setObjective(x + y + 2 * z, GRB_MAXIMIZE);
 
 ```
 ## Adding constraints to the model
  ```
 model.addConstr(x + 2 * y + 3 * z <= 4, "c0");
  ```
 ## Optimizing the model
  ```
 model.optimize();
  ```
 ## Reporting results - attributes
 ```
cout<< x.get(GRB_StringAttr_VarName) << " "
cout<< x.get(GRB_DoubleAttr_X) << endl;
cout<< y.get(GRB_StringAttr_VarName) << " "
cout<< y.get(GRB_DoubleAttr_X) << endl;
cout<< z.get(GRB_StringAttr_VarName) << " "
cout<< z.get(GRB_DoubleAttr_X) << endl;
 ```
## Error handling

Errors in the Gurobi C++ interface are handled through the C++ exception mechanism. In the
example, all Gurobi statements are enclosed inside a try block, and any associated errors would be
caught by the catch block.

## Building and running the example

To build and run the example, we refer the user to the files in <installdir>/examples/build .
For Linux platforms, the <installdir>/examples/build directory contains an example Makefile.
Typing make sudoku_c++ will build and run this example.
 

