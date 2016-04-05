#include "Sudoku.h"
Sudoku::Sudoku()
{
  int i,j;
  ct = 0;
  n = 0;
  for (i = 0;i < 81;++i)
  {
    ans[i] = 0;
    out[i] = 0;
  }
  for (i = 0;i < 9;++i)
  {
    for (j = 0;j < 10;++j)
    {
      if(j == 0)
      {
        COL[i][j] = ROW[i][j] = BLOCK[i][j] = 9;
      } else{
        COL[i][j] = ROW[i][j] = BLOCK[i][j] = 0;
      }
    }
  }
}

void Sudoku::giveQuestion()
{
  cout << "0 4 0 2 1 0 0 0 0\n8 0 7 0 0 0 0 9 0\n2 0 0 8 0 0 4 0 1\n3 0 0 0 0 2 9 0 5\n0 0 5 7 0 8 6 0 0\n7 0 6 5 0 0 0 0 4\n5 0 1 0 0 4 0 0 9\n0 6 0 0 0 0 7 0 8\n0 0 0 0 2 7 0 5 0"<<endl;
}

void Sudoku::changeNum(int a, int b)
{
  int i;

  for(i = 0;i < 81;i++)
  {
    if(ans[i] == a)
    {
      ans[i] = b; 
    }else if (ans[i] == b){
      ans[i]=a;
    }
  }

}

void Sudoku::changeRow(int a, int b)
{
  int i, temp[27];

  for (i = 0;i < 27;++i)
  {
    temp[i] = ans[a * 27 + i];
    ans[a * 27 + i] = ans[b * 27 + i]; 
  }
  for (i = 0;i < 27;i++)
  {
    ans[b * 27 + i] = temp[i]; 
  }
}

void Sudoku::changeCol(int a, int b)
{
  int temp[27];
  int i;

  for(i = 0;i < 27;++i)
  {
    temp[i] = ans[a * 3 + (i / 3) * 9 + i % 3];
    ans[a * 3 + (i / 3) * 9 + i % 3] = ans[b * 3 + (i / 3) * 9 + i % 3];
  }
  for(i = 0;i < 27;++i)
  {
    ans[b * 3 + (i / 3) * 9 + i % 3] = temp[i];  
  }
}

void Sudoku::rotate(int n)
{
  int i = 1;
  int temp[81];
  Equal(ans, temp);
  while( n != 0)
  {
    n--;
    for(i = 0;i < 81;++i)
    {
      int col = i % 9, row = i / 9;
      ans[col * 9 + (8 - row)] = temp[i];
    }
  }
}

void Sudoku::flip(int n)
{
  int i, j;
  int temp[81];
  Equal(ans, temp);
  if(n == 0)
  {
    for(i = 0;i < 36;++i)
    { 
      ans[2 - (i/9)*9 +i%9] =  temp[i];
      ans[i] = temp[72 - (i/9)*9 +i%9];
    }
  }
  else if(n == 1)
  {
    for(j = 0;j <= 4 ;++j)
    {
      for(i = 0;i < 9;++i)
      {
        ans[8-j+i*9] = temp[i*9+j]; 
        ans[i*9+j] = temp[8-j+i*9]; 
      }
    }
  }
}

void Sudoku::transform()
{
  showSudoku(ans);
  readIn();
  change();
}

void Sudoku::change()
{
  changeNum(1,2);
  rotate(2);
}

void Sudoku::readIn()
{
  int i;
  for (i = 0;i < 81;i++)
  {
    cin >> ans[i];
  }
}

void Sudoku::solve()
{
  int i;
  for(i = 0;i < 81;++i)
  {
    addElement(i, ans[i], 1);
  }
  for(i = 0;i < 81;++i)
  {
    setPossibleArray(i);
  }
  if(SudokuIsCorrect()) 
  {
    solving(0);
  }
  cout << ct <<endl;
  if (ct == 1)
  {
    showSudoku(out);
  }
}

void Sudoku::solving(int index)
{
  int i;
  int num;
  int x;

  if (ct > 1) return;
  while (index < 81 && ans[index] != 0) ++index;
  if (index == 81)
  {
    if (SudokuIsCorrect()) 
    {
      for(i = 0;i < 81;++i)
        out[i] = ans[i];
      ct ++;
    }
    return;
  }
//  cout << "index : " <<index << endl;
//  showSudoku(ans);
  /*
  for(int j = 0;j < 9;++j)
    {
    for(int k = 0;k < 10;++k)
    {
    cout << BLOCK[j][k] << " ";
    }
    cout << endl;
    }
    */
// if (index > 40) exit(1);
  for(num = 1;num <= 9;++num)
  {
    ans[index] = num;
    if(isCorrect2(index, num)){
      addElement(index, num, 1);
      solving(index + 1);
      if (ct > 1) return;
      addElement(index, num, -1);
    }
  }
  ans[index] = 0;
}

void Sudoku::Equal(int a[], int b[])
{
  int i;
  for(i = 0;i < 81;i++)
    b[i] = a[i];

}

bool Sudoku::SudokuIsCorrect()
{
  int i, j;
  for(i = 0;i < 9;++i)
  {
    for(j = 1;j < 10;++j)
    {
      if (COL[i][j] > 1 || ROW[i][j] > 1 || BLOCK[i][j] > 1) return false;
    }
  }
  return true;
}

bool Sudoku::isCorrect2(int x, int num)
{
  int row = x / 9, col = x % 9;
  int block = ((row / 3) * 3) + (col / 3);
  if (num == 0) return true;
  if(COL[col][num] > 0 || ROW[row][num] > 0 || BLOCK[block][num] > 0) return false;
  else return true;
}

void Sudoku::showSudoku(int x[])
{
  int i;
  for(i = 0;i < 81;++i)
  {
    cout << x[i];
    cout << (((i+1) % 9) == 0 ? "\n" : " ");
  }
}

void Sudoku::fileInput()
{
  ifstream inFile("ques1", ios::in);
  int i;
  if(!inFile)
  {
    cout << "File open failed." << endl;
  } else{
    for (i = 0;i < 81;++i)
    {
      inFile >> ans[i];
    }
  }
}

void Sudoku::addElement(int index, int num, int v)
{
  int col = index % 9;
  int row = index / 9;
  if (num == 0) return;
  if (v == 1) ans[index] = num;
  COL[col][num] += v;
  ROW[row][num] += v;
  BLOCK[((row / 3) * 3) + (col / 3)][num] += v;
  COL[col][0] -= v;
  ROW[row][0] -= v;
  BLOCK[((row / 3) * 3) + (col / 3)][0] -= v;
}

void Sudoku::setPossibleArray(int index)
{
  if (ans[index] != 0) 
  {
    P[index] = 0;
    return;
  }

  int col = index % 9;
  int row = index / 9;

  P[index] = COL[col][0] + ROW[row][0] + BLOCK[((row / 3) * 3) + (col / 3)][0]; 
}

int Sudoku::findLessPossibleIndex()
{
  int i, min_p = 0, min_index = -1;
  for(i = 0;i < 81;++i)
  {
    if (min_p > 0 || P[i] < min_p)
    {
      min_p = P[i];
      min_index = i;
    }
  }
  return min_index;
}
