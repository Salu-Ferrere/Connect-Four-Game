#include "Grid.hpp"
#include <iostream>
using namespace std;

//Initializes grid to GC_EMPTY with a size of Row x Column, with minimum size of 4x4
Grid::Grid(unsigned int rows, unsigned int columns){

	//C4Grid = new vector<vector <Cell> >;

	if(rows < 4){
		this->rows = 4;
	}else{
		this->rows = rows;
	}

	if(columns < 4){
		this-> columns = 4;
	} else{
		this->columns = columns;
	}



	for(unsigned int i = 0; i < (this->rows); i++){
		std::vector<Cell> v;
		for(unsigned int j = 0; j < (this->columns); j++){

			v.push_back(GC_EMPTY);
		}
		C4Grid.push_back(v);
	}

}

//places players disc in column, disc will sit on top most recent disc in that column or at the bottom
//if column is empty returning true, false will be returned if column is full, disc type is GC_EMPTY
//or an invalid column number is entered.
bool Grid::insertDisc(unsigned int column, Cell disc){
	if(disc == GC_EMPTY || column >= columns){
		return false;
	}
	if(C4Grid[0][column] != GC_EMPTY){
		return false;
	}
	if(C4Grid[rows-1][column] == GC_EMPTY){
		C4Grid[rows-1][column] = disc;
		return true;
	}
	for(unsigned int ii = 0; ii < rows-1; ii++ ){
		if(C4Grid[ii+1][column] != GC_EMPTY){
			C4Grid[ii][column] = disc;
			return true;
		}
	}
	return false;
}

//returns the disc type at the specified column and row position, if position invalid
//returns GC_EMPTY
Grid::Cell Grid::cellAt(unsigned int row, unsigned int column) const{
	if(row >= rows || column >= columns){
		return GC_EMPTY;
	}
	return C4Grid[row][column];
}

//resets grid to all GC_EMPTY cell types
void Grid::reset(){
	for(unsigned int i = 0; i < this->rows; i++){
		for(unsigned int j = 0; j < this->columns; j++){
			C4Grid[i][j] = GC_EMPTY;
		}
	}
}

//returns number of rows
unsigned int Grid::rowCount() const{
	return this->rows;

}

//returns number of columns
unsigned int Grid::columnCount() const{
	return this->columns;
}

//removes horizontal connect 4 replacing cell with GC_EMPTY
void Grid::removeHorizontal(unsigned int r, unsigned int c){

	Cell cell = C4Grid[r][c];
	for(unsigned int i = c; i < c+4; i++){
		C4Grid[r][i] = GC_EMPTY;
	}


	for(unsigned int i = c + 4; i < columns; i++){
		if (C4Grid[r][i] == cell){
			C4Grid[r][i] = GC_EMPTY;
		} else {
			return;
		}
	}
	return;
}

//removes vertical connect 4 replacing cell with GC_EMPTY
void Grid::removeVertical(unsigned int r, unsigned int c){

	Cell cell = C4Grid[r][c];
	for(unsigned int i = r; i < r+4; i++){
		C4Grid[i][c] = GC_EMPTY;
	}

	for(unsigned int i = r+4; i < rows; i++){
		if (C4Grid[i][c] == cell){
			C4Grid[i][c] = GC_EMPTY;
		} else {
			return;
		}
	}


	return;
}

//removes diagonal connect 4 replacing cell with GC_EMPTY
void Grid::removeDiagonal(unsigned int r, unsigned int c){

	Cell cell = C4Grid[r][c];
	for(unsigned int i = 0; i < 4; i ++){
		C4Grid[r+i][c+i] = GC_EMPTY;
	}
	unsigned int num = rows - r ;
	if(num > columns - c){
		num = columns - c;
	}

	for(unsigned int i = 4; i < num; i++){
		if (C4Grid[r+i][c+i] == cell){
			C4Grid[r+i][c+i] = GC_EMPTY;
		} else {
			return;
		}
	}

	return;
}

//removes opposite diagonal connect 4 replacing cell with GC_EMPTY
void Grid::removeDiagonalOp(unsigned int r, unsigned int c){

	Cell cell = C4Grid[r][c];
	for(unsigned int i = 0; i < 4; i ++){
		C4Grid[r+i][c-i] = GC_EMPTY;
	}
	unsigned int num = rows - r ;
	if(num > c+1){
		num = c + 1;
	}

	for(unsigned int i = 4; i < num; i++){
		if (C4Grid[r+i][c-i] == cell){
			C4Grid[r+i][c-i] = GC_EMPTY;
		} else {
			return;
		}
	}

	return;
}

//swaps empty cell with cell above it, then making the above cell empty,
//Effectively dropping all pieces down after a connect 4 is made
void Grid::cleanGrid(){
	for(int i = this->rows -1; i > 0; i--){
		for(int j = this->columns; j >= 0; j--){
			if(C4Grid[i][j] == GC_EMPTY){
				C4Grid[i][j] = C4Grid[i-1][j];
				C4Grid[i-1][j] = GC_EMPTY;

		}
	}
}

}

//no heap allocated memory, so destructor resets grid to origional state upon termination
Grid::~Grid(){
	reset();

}
