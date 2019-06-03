#include "RowAndCol.h"

using namespace tbb;

RowAndCol::RowAndCol(
	int** a, int** b, int row_a, int col_b, int dim, int& temp) :
	a(a),            
	b(b),            
	row_a(row_a),    
	col_b(col_b),    
	dim(dim),
	temp(temp)
{}

task* RowAndCol::execute()
{
	for (int i = 0; i < dim; i++) {
		temp += a[row_a][i] * b[col_b][i];
	}
	return NULL;
}