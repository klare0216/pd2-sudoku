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
    void setQues(int index, int num);
    void setAns(int index, int num);
    void setOut(int index,int num);
    void addCt();
    int getQues(int index);
    int getAns(int index);
    int getOut(int index);
    bool isCorrect(int x);
    bool isCorrect2(int x, int num);
    void showSudoku();
    void showSudoku(int x[]);
    void fileInput();
    
    void qaEqual();
    void addElement(int index, int num, int v);
    bool SudokuIsCorrect();
    void solving(int index);
    void change();
    int COL[9][10], ROW[9][10], BLOCK[9][10];
    int out[81];
    int ques[81];
    int ans[81];
    int ct;
    int n;
};
