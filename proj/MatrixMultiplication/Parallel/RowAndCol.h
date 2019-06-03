#include "tbb/task.h"

using namespace tbb;

class RowAndCol : public task {
/*!
	Dobija red u matrci A i kolonu u matrici B,
	monzi i sabira odgovarajuce elemente i
	rezultat smesta na odgovarajuce mesto u baferu.
*/

private:
	int** a;				/* Matrica A */
	int** b;				/* Matrica B */
	int row_a, col_b, dim;  /* Red u A, kolona u b, dimenzija*/
	int& temp;              /* Odgovarajuce mesto u baferu */
public:
	RowAndCol(int** a, int** b, int row_a,
		int col_b, int dim, int& temp);
	task* execute();
};