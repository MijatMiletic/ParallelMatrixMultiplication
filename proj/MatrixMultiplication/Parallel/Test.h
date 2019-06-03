#include <string>
#include <vector>

using namespace std;

/**
* Poredi test matricu dobijen cpp-om sa kontrolnim fajlom dobijenim 
* pajton sktriptom.
*/
bool compare_files(string python_txt_file, int** test_matrix, int dim);

/**
* cita, mnozi paralelno, mnozi serijski, testira oba rezultata, poredi ih 
* utvrdjuje ubrzanje i zapisuje rezultate.
*/
void solve(string in_file_name, string out_file_name, vector<double>& sts,
	vector<double>& pts, vector<double>& speedup);

/**
* poziva metodu solve(string, string) za sve dimenzije zadate u nizu DIMENSIONS
*/
void solve_all();