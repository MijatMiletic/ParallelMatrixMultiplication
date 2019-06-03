#include "tbb/task.h"

using namespace tbb;

class RowAndAllCols : public task {
/*!
	Za dati red iz matrice A 'row' i 
	svaku kolonu u matrici B, kreira podzadtak RowAndCol
	koji mnozi odgovarajuce elemente i stavlja ih 
	u bafer na odgovarajuce mesto. I nakon sto svi 
	podzadaci zavrse, presipa bafer u matricu A, u 
	red koji je prosledjen parametrom 'row'.
*/

private:
	int** a;		  /* Matrica A */
	int** b;		  /* Matrica B */
	int row, dim;     /* Red u matrici A */
	int* temp;        /* Bafer */
	task_list tasks;  
public:
	RowAndAllCols(int** a, int** b, int row, int dim);
	task* execute();
	~RowAndAllCols() { delete[] temp; }
};
