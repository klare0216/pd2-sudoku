#include <iostream>
#include <cstdlib>
#include <fstream>
#include <cstdlib>
#include <ctime>
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
    void showSudoku(int x[]);
    void fileInput();
    private:    
    void solveForCheck();
    void Equal(int a[], int b[]); //let b[x]=a[x]
    void addElement(int index, int num, int v); // v=1 pudh, v=-1 pop element
    bool SudokuIsCorrect();
    bool SudokuIsFull();
    bool isCorrect2(int x, int num);
    void solving();
    void digging(int index);
    void change();
    void setPossibleArray(int row, int col);
    void setPossibleArray(int index);
    int findLessPossibleIndex();
    int blank(int x[]);
    void initializeCRB();
    void initializeAns();
    int COL[9][10], ROW[9][10], BLOCK[9][10];
    int P[9][9];
    int out[81];
    int ans[81];
    int ct; //how many solutions
};
