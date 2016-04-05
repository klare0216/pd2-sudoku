#include <iostream>
#include <cstdlib>
#include <fstream>
using namespace std;
class Sudoku{
  public:
    Sudoku();
    void giveQuestion();
    void readIn();
    void solve();
    void changeNum(int a, int b);
    void changeRow(int a, int b);
    void changeCol(int a, int b);
    void rotate(int n);
    void flip(int n);
    void transform();
    bool isCorrect2(int x, int num);
    void showSudoku(int x[]);
    void fileInput();
    private:    
    void Equal(int a[], int b[]); //let b[x]=a[x]
    void addElement(int index, int num, int v);
    bool SudokuIsCorrect();
    void solving(int index);
    void change();
    void setPossibleArray(int index);
    int findLessPossibleIndex();
    int COL[9][10], ROW[9][10], BLOCK[9][10];
    int P[81];
    int out[81];
    int ans[81];
    int ct;
    int n;
};
