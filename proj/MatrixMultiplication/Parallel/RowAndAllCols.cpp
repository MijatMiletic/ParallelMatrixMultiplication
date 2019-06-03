#include "RowAndAllCols.h"
#include "RowAndCol.h"


RowAndAllCols::RowAndAllCols(int** a, int** b, int row, int dim) :
	a(a),
	b(b),
	row(row),
	dim(dim)
{
	
	temp = new int[dim];			             /* Zauzimanje memorije za bafer i */
	for (int i = 0; i < dim; i++) {              /* postavljanje svih elemenata na nulu.*/
		temp[i] = 0;
	}
}

task* RowAndAllCols::execute()
{
	for (int i = 0; i < dim; i++) {
		tasks.push_back(*new(allocate_child())
			RowAndCol(a, b, row, i, dim, temp[i]));
	}

	set_ref_count(dim + 1);
	spawn_and_wait_for_all(tasks);                     /* Cekaj da svi zavrse pa */
													   /* tek onda isprazni bafer */
	// prazenjenje bafera u matricu A
	for (int i = 0; i < dim; i++) {
		a[row][i] = temp[i];
	}
	return NULL;
}