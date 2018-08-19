// Name:Rueben Tiow
// Last Modified:10/30/2017
// Program: Implementation of strassen's algorithm. Works only with square matrices
// powers of 2.
#include <vector>
#include <iostream>

using namespace std;

vector<vector<int> > matrixAdd(vector<vector<int> > A, int aRLow, int aRHigh, int aCLow, int aCHigh,
                               vector<vector<int> > B, int bRLow, int bRHigh, int bCLow, int bCHigh) {
	int size = min(((aRHigh - aRLow) + 1),((bRHigh - bRLow) + 1));
	int tempaRLow = aRLow;
	int tempbRLow = bRLow;
    vector<vector<int> > C;
    for (int i = 0; i < size; i++) {
        vector<int> c;
        for (int j = 0; j < size; j++) {
            c.push_back(A[aCLow][tempaRLow] + B[bCLow][tempbRLow]);
            tempaRLow++;
            tempbRLow++;
        }
        tempaRLow = aRLow;
        tempbRLow = bRLow;
        aCLow++;
        bCLow++;
        C.push_back(c);
    }
	return C;
}

vector<vector<int> > matrixSub(vector<vector<int> > A, int aRLow, int aRHigh, int aCLow, int aCHigh,
                               vector<vector<int> > B, int bRLow, int bRHigh, int bCLow, int bCHigh) {
	int size = min(((aRHigh - aRLow) + 1),((bRHigh - bRLow) + 1));
	int tempaRLow = aRLow;
	int tempbRLow = bRLow;
    vector<vector<int> > C;
    for (int i = 0; i < size; i++) {
        vector<int> c;
        for (int j = 0; j < size; j++) {
            c.push_back(A[aCLow][tempaRLow] - B[bCLow][tempbRLow]);
            tempaRLow++;
            tempbRLow++;
        }
        tempaRLow = aRLow;
        tempbRLow = bRLow;
        aCLow++;
        bCLow++;
        C.push_back(c);
    }
	return C;
}

vector<vector<int> > strassen(vector<vector<int> > A, int aRLow, int aRHigh, int aCLow, int aCHigh,
                              vector<vector<int> > B, int bRLow, int bRHigh, int bCLow, int bCHigh) {
	int size = min( ((aRHigh - aRLow) + 1),((bRHigh - bRLow) + 1));
	vector<vector<int> > C;
	if (size == 1) {
		vector<int> c;
		c.push_back(A[aRLow][aRHigh] * B[bRLow][bRHigh]);
		C.push_back(c);
	}
	else {
		//Partitions A, B, and C
		int midRA = (aRLow + aRHigh) / 2;
		int midCA = (aCLow + aCHigh) / 2;
		int midRB = (bRLow + bRHigh) / 2;
		int midCB = (bCLow + bCHigh) / 2;
		int mid = (size / 2) - 1;
		//Calc p1
		vector<vector<int> > s1 = matrixSub(B, bRLow, midRB, midCB+1, bCHigh, B, midRB+1, bRHigh, midCB+1, bCHigh);
		vector<vector<int> > p1 = strassen(A, aRLow, midRA, aCLow, midCA, s1, 0, mid, 0, mid);
		//Calc p2
		vector<vector<int> > s2 = matrixAdd(A, aRLow, midRA, aCLow, midCA, A, aRLow, midRA, midCA+1, aCHigh);
		vector<vector<int> > p2 = strassen(s2, 0, mid, 0, mid, B, midRB + 1, bRHigh, midCB + 1, bCHigh);
		//Calc p3
		vector<vector<int> > s3 = matrixAdd(A, midRA+1, aRHigh, aCLow, midCA, A, midRA+1, aRHigh, midCA+1, aCHigh);
		vector<vector<int> > p3 = strassen(s3, 0, mid, 0, mid, B, bRLow, midRB, bCLow, midCB);
		//Calc p4
		vector<vector<int> > s4 = matrixSub(B, midRB+1, bRHigh, bCLow, midCB, B, bRLow, midRB, bCLow, midCB);
		vector<vector<int> > p4 = strassen(A, midRA + 1, aRHigh, midCA + 1, aCHigh, s4, 0, mid, 0, mid);
		//Calc p5
		vector<vector<int> > s5 = matrixAdd(A, aRLow, midRA, aCLow, midCA, A, midRA + 1, aRHigh, midCA + 1, aCHigh);
		vector<vector<int> > s6 = matrixAdd(B, bRLow, midRB, bCLow, midCB, B, midRB + 1, bRHigh, midCB + 1, bCHigh);
		vector<vector<int> > p5 = strassen(s5, 0, mid, 0, mid, s6, 0, mid, 0, mid);
		//Calc p6
		vector<vector<int> > s7 = matrixSub(A, aRLow, midRA, midCA + 1, aCHigh, A, midRA + 1, aRHigh, midCA + 1, aCHigh);
		vector<vector<int> > s8 = matrixAdd(B, midRB + 1, bRHigh, bCLow, midCB, B, midRB + 1, bRHigh, midCB + 1, bCHigh);
		vector<vector<int> > p6 = strassen(s7, 0, mid, 0, mid, s8, 0, mid, 0, mid);
		//Calc p7
		vector<vector<int> > s9 = matrixSub(A, aRLow, midRA, aCLow, midCA, A, midRA + 1, aRHigh, aCLow, midCA);
		vector<vector<int> > s10 = matrixAdd(B, bRLow, midRB, bCLow, midCB, B, bRLow, midRB, midCB + 1, bCHigh);
		vector<vector<int> > p7 = strassen(s9, 0, mid, 0, mid, s10, 0, mid, 0, mid);
		//Compute final sub-matrices
		vector<vector<int> > c11 = matrixAdd(matrixSub(matrixAdd(p5, 0, mid, 0, mid, p4, 0, mid, 0, mid), 0, mid, 0, mid,
                                                 p2, 0, mid, 0, mid), 0, mid, 0, mid, p6, 0, mid, 0, mid);
		vector<vector<int> > c12 = matrixAdd(p1, 0, mid, 0, mid, p2, 0, mid, 0, mid);
		vector<vector<int> > c21 = matrixAdd(p3, 0, mid, 0, mid, p4, 0, mid, 0, mid);
		vector<vector<int> > c22 = matrixSub(matrixSub(matrixAdd(p5, 0, mid, 0, mid, p1, 0, mid, 0, mid), 0, mid, 0, mid,
                                                 p3, 0, mid, 0, mid), 0, mid, 0, mid, p7, 0, mid, 0, mid);
		//Set result into matrix
		for (int i = 0; i <= mid; i++) {
			vector<int> c;
			for (int j = 0; j <= mid; j++) {
				c.push_back(c11[i][j]);
			}
			for (int j = 0; j <= mid; j++) {
				c.push_back(c21[i][j]);
			}
			C.push_back(c);
		}
		for (int i = 0; i <= mid; i++) {
			vector<int> c;
			for (int j = 0; j <= mid; j++) {
				c.push_back(c12[i][j]);
			}
			for (int j = 0; j <= mid; j++) {
				c.push_back(c22[i][j]);
			}
			C.push_back(c);
		}
	}
	return C;
}

int main() {
    int input;
	int size;
	vector<vector<int> > A;
	vector<vector<int> > B;
	cout << "Strassen Matrix Multiplication Program" << endl;
	cout << "Enter a size for a square matrix: ";
	cin >> size;
	cout << "Input data for the first Matrix A" << endl;
	for (int i = 0; i < size; i++) {
		vector<int> aCol;
        cout << "Column:" << i+1 << endl;
		for (int j = 0; j < size; j++) {
			cin >> input;
			aCol.push_back(input);
		}
		A.push_back(aCol);
	}
	cout << "Matrix A:" << endl;
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			cout << A[j][i] << " ";
		}
		cout << endl;
	}
	cout << endl << "Input data for the second Matrix B" << endl;
	for (int i = 0; i < size; i++) {
		vector<int> bCol;
		cout << "Column:"<< i+1 << endl;
		for (int j = 0; j < size; j++) {
			cin >> input;
			bCol.push_back(input);
		}
		B.push_back(bCol);
	}
	cout << "Matrix B:"<< endl;
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			cout << B[j][i] << " ";
		}
		cout << endl;
	}
	vector<vector<int> > C = strassen(A, 0, size-1, 0, size-1, B, 0, size-1, 0, size-1);
	cout << endl << "The answer:" << endl;
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			cout << C[j][i] << " ";
		}
		cout << endl;
	}
	return 0;
}
