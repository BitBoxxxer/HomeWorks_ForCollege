#include <iostream>
#include <vector>
using namespace std;
template <typename T>
class Mtrx {
	vector<vector<T>> mtx;
	void rectangle() {
		int msz = 0;// max size
		for (const auto& row : mtx) {
			if (row.size() > msz)
				msz = row.size();
		}
		for (auto& row : mtx) {
			row.resize(msz);
		}
	}
public:
	Mtrx(const vector<vector<T>>& m) {
		mtx = m;
		rectangle();
	}
	int get_cols() {
		return mtx[0].size();
	}
	int get_rows() {
		return mtx.size();
	}
	void print_m() {
		for (const auto& i : mtx) {
			for (const auto& j : i) {
				cout << j << ' ';
			}
			cout << endl;
		}
	}
	void magic_mtx() {
		if ((mtx.size() == mtx[0].size()) and (mtx.size()!=0)){
			for (int i = 0; i < mtx.size(); i++) {
				T sm_cls = 0, sm_rws = 0, gd = 0, pd = 0;

				for (int j = 0; j < mtx[0].size(); j++) {
					sm_cls += mtx[i][j];
					sm_rws += mtx[j][i];
					gd += mtx[i][j];
					pd += mtx[j][mtx[0].size() - i - 1];
				}

				if ((gd != pd) or (sm_cls != sm_rws) or (gd != sm_cls)) {
					cout << "Not a magic >:'(";
					return;
				}
			}
			cout << "magiiiiiiic" << endl;
		}
		else
			cout << "Not a magic >:'(";
	}
};

int main()
{
	Mtrx<int> m({ {1,2,3}, {3,4,5}, {5,6,7,6}, {7,1,9 }, {1} });

	cout << "Rows: " << m.get_rows()<<endl;
	cout << "Columns: " << m.get_cols()<<endl;
	cout << "Matrix print:" << endl << endl;
	m.print_m();
	m.magic_mtx();
}
