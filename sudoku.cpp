/*
ILP to solve Sudoku Puzzles
Using Gurobi Solver
To compile, Gurobi License is needed
All Gurobi libraries must be in path, i.e. libgurobi_g++5.2.a and libgurobi.so.7.0.2
Use "-std=c++11" as compile parameter
*/

#include "gurobi_c++.h"
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <ctime>

using namespace std;

#define sd 3
#define n (sd*sd)

string itos(int i){
	
	stringstream s;
	s << i;
	return s.str();
}

void solveSudoku(vector< vector<int> > values){

	try{
		GRBEnv env = GRBEnv();
		GRBModel model = GRBModel(env);
		GRBVar vars[n][n][n];

		int i, j, v;

		// Create 3-D array of model variables
		for( i = 0; i < n; i++ ){
			for( j = 0; j < n; j++ ){
				for( v = 0; v < n; v++ ){
					string s = "G_" + itos(i) + "_" + itos(j) + "_" + itos(v);
					vars[i][j][v] = model.addVar(0.0, 1.0, 0.0, GRB_BINARY, s);
				}
			}
		}

		// Add constraints

		// Each cell must take one value
		for( i = 0; i < n; i++ ){
			for( j = 0; j < n; j++ ){
				GRBLinExpr expr = 0;
				for (v = 0; v < n; v++){
					expr += vars[i][j][v];
				}
				string s = "V_" + itos(i) + "_" + itos(j);
				model.addConstr(expr, GRB_EQUAL, 1.0, s);
			}
		}

		// Each value appears once per row
		for( i = 0; i < n; i++ ){
			for( v = 0; v < n; v++ ){
				GRBLinExpr expr = 0;
				for( j = 0; j < n; j++ ){
					expr += vars[i][j][v];
				}
				string s = "R_" + itos(i) + "_" + itos(v);
				model.addConstr(expr == 1.0, s);
			}
		}

		// Each value appears once per column
		for( j = 0; j < n; j++ ){ 
			for( v = 0; v < n; v++ ){
				GRBLinExpr expr = 0;
				for( i = 0; i < n; i++ ){
					expr += vars[i][j][v];
				}
				string s = "C_" + itos(j) + "_" + itos(v);
				model.addConstr(expr == 1.0, s);
			}
		}

		// Each value appears once per sub-grid
		for( v = 0; v < n; v++ ){
			for( int i0 = 0; i0 < sd; i0++ ){
				for( int j0 = 0; j0 < sd; j0++ ){
					GRBLinExpr expr = 0;
					for( int i1 = 0; i1 < sd; i1++ ){
						for( int j1 = 0; j1 < sd; j1++ ){
							expr += vars[i0*sd+i1][j0*sd+j1][v];
						}
					}
					string s = "Sub_" + itos(v) + "_" + itos(i0) + "_" + itos(j0);
					model.addConstr(expr == 1.0, s);
				}
			}
		}

		// Fix variables associated with pre-specified cells
		for( i = 0; i < n; i++ ){
			for( j = 0; j < n; j++ ){
				int val = values[i][j];
				if (val != 0){
					vars[i][j][val-1].set(GRB_DoubleAttr_LB, 1.0);
					
					// Presence Rule
					// Same row
					for( int k = 0; k < n; k++ ){
						for( int x = 0; x < n; x++ ){
							if( x != val-1 )
								vars[i][k][x].set(GRB_DoubleAttr_LB, 0.0);
						}
					}
					// Same column
					for( int k = 0; k < n; k++ ){
						for( int x = 0; x < n; x++ ){
							if( x != val-1 )
								vars[k][j][x].set(GRB_DoubleAttr_LB, 0.0);
						}
					}
					// Same box
					int box_no = 3 * (i/3) + j/3;
					int row = 3 * (box_no / 3);
					int col = 3 * (box_no % 3);
					for( int p = row; p < row + 3; p++ ){
						for( int q = col; q < col + 3; q++){
							for( int x = 0; x < n; x++ ){
								if( x != val-1 ){
									//cout << row << " : " << col << " : " << p << " : " << q << " : " << x << endl;
									vars[p][q][x].set(GRB_DoubleAttr_LB, 0.0);
								}
							}
						}
					}
				}
			}
		}

		// parameter for no output
		model.set(GRB_IntParam_OutputFlag, 0);

		// Optimize model
		model.optimize();

		// Write model to file
		// model.write("sudoku.lp");

		/*cout << endl;
		for( i = 0; i < n; i++ ){
			for( j = 0; j < n; j++ ){
				for( v = 0; v < n; v++ ){
	    			if( vars[i][j][v].get(GRB_DoubleAttr_X) > 0.5)
						cout << v+1;
				}
			}
	    	cout << endl;
		}
		cout << endl;*/
	}
	catch(GRBException e){
		cout << "Error code = " << e.getErrorCode() << endl;
		cout << e.getMessage() << endl;
	}
	catch (...){
		cout << "Error during optimization" << endl;
	}
}

int main(int argc, char *argv[]){


	int row, col, count;
	float time, avg, max;
	string input;
	vector< vector<int> > values(n,vector<int>(n));
	vector<float>::iterator itr;
	clock_t total_clocks;
	vector<float> times;

	// input is a string of length 81
	// eg : "005300000800000020070010500400005300010070006003200080060500009004000030000009700"
	ifstream infile(argv[1]);
	count = 0, avg = 0, max = 0;
	while(getline(infile,input)){
		// In Unix/Linux like systems, getline only uses '\n' to read new lines
		// In windows, getline uses both '\n' & '\r' to read new lines
		if(input.back() == '\r')
			input.pop_back();
		if(input.length() != 81){
			cout<<"Invalid input"<<endl;
			break;
		}
		for(row = 0; row < n; row++){
			for(col = 0; col < n; col++){
				if(input[row*n+col] >= '0' && input[row*n+col] <= '9'){
					values[row][col] = input[row*n+col] - '0';
				}
				else
					values[row][col] = 0;
			}
		}
		total_clocks = clock();
		solveSudoku(values);
		total_clocks = clock() - total_clocks;
		time = (float)total_clocks/CLOCKS_PER_SEC;
		//cout<<"puzzle no "<<count+1<<" : "<<time<<" seconds"<<endl;
		times.push_back(time);
		avg += time;
		count++;
		if(time > max)
			max = time;
	}
	avg = (float)avg/count;
	cout<<"max is "<<max<<" & avg is "<<avg<<endl;
	cout<<"count is "<<count<<endl;
	sort(times.begin(),times.end());
	/*for(itr = times.begin();itr != times.end(); itr++){
		cout<<*itr<<endl;
	}*/
	return 0;
}