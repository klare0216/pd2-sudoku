#include "Sudoku.h"
Sudoku::Sudoku()
{
  int i,j;
  ct  = 0;
  for (i = 0;i < 81;++i)
    ans[i] = out[i] = P[i / 9][i % 9] = 0;
  initializeCRB();
}

void Sudoku::giveQuestion()
{ 
  srand(time(0));
  int rand_t, temp;
  int num[30] = {0,0,0,0,0,
                 0,1,0,0,0,
                 0,0,0,1,2,
                 0,4,5,6,7,
                 0,0,0,8,9,
                 0,0,2,0,0};
  int ques[81] = {0,0,6,0,0,3,0,0,0, 
                  0,0,0,8,9,0,0,0,0, 
                  4,0,5,0,0,0,0,0,0,
                  0,0,0,0,0,0,0,0,5,
                  0,2,0,0,0,1,0,0,0,
                  0,9,0,0,0,0,0,0,6,
                  0,3,0,0,0,0,8,0,0,
                  0,0,1,0,0,0,2,0,0,
                  0,0,0,0,4,5,0,0,0};
    /*  do {
    initializeAns();
    for(int i = 0;i < 10;i++)
    {
      rand_t = num[rand() % 30];
      if(isCorrect2(i, rand_t)) 
      {  
        addElement(i, rand_t, 1);
      } else i--;
    } 
    //showSudoku(ans);
    solveForCheck();
    if (ct == 0) continue;
    change();
    Equal(ans, ques);
    digging(0);
    break;
    while((81 - blank(ques)) > 24)
    {
      Equal(ques, ans);
      rand_t = rand() % 81;
      if (ans[rand_t] == 0) continue;
      ans[rand_t] = 0;
      ct = 0;
      solve();
      if (ct == 1)
      {
        ques[rand_t] = 0; 
      }

    }
  } while(ct != 1);
  */
  Equal(ques, ans);
  change();
  //cout << "///HINTS: " << 81 - blank(ans)<< endl;
  //cout << "///QUESSSS///" << endl;
  showSudoku(ans);
  //cout << "///solve///" << endl;
}

void Sudoku::digging(int index)
{
  int temp[81];
  //cout << "index: " << index << endl;
  //if (index ==  15) exit(0);
  if (index > 80) return;
  Equal(ans, temp);
  ans[index] = 0;
  solveForCheck();
  if (ct == 1) 
  {
    temp[index] = 0;
    Equal(temp, ans);
    digging(index + 1);
  } else{
    Equal(temp, ans);
    digging(index + 1);
  }
  index++;
}
int Sudoku::blank(int x[])
{
  int n = 0;
  for (int i = 0;i < 81;++i)
    if(x[i] == 0) n++;

  return n;
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
      ans[i] = a;
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
  int i = 0;
  int temp[81];
  while( n != 0)
  {
    n--;
    Equal(ans, temp);
    for(i = 0;i < 81;++i)
    {
      int col = i % 9, row = i / 9;
      ans[col * 9 + (8 - row)] = temp[i];
    }
  }
}

void Sudoku::flip(int n)
{
  int row, col;
  int temp[81];
  Equal(ans, temp);
  if(n == 0)
  {
    for(row = 0;row <= 4 ;++row)
    {
      for(col = 0;col < 9;++col)
      {
        ans[row * 9 + col] = temp[(8 - row)* 9 + col]; 
        ans[(8 - row)* 9 + col] = temp[row * 9 + col]; 
      }
    } 
  }
  else if(n == 1)
  {
    for(int j = 0;j <= 4 ;++j)
    {
      for(int i = 0;i < 9;++i)
      {
        ans[8-j+i*9] = temp[i*9+j]; 
        ans[i*9+j] = temp[8-j+i*9]; 
      }
    }
  }
}

void Sudoku::transform()
{
  readIn();
  change();
  showSudoku(ans);
}

void Sudoku::change()
{
  srand(time(0));
  changeNum(rand() % 9 + 1,rand() % 9 + 1);
  rotate(rand() % 100);
  flip(rand() % 2);
  changeRow(rand() % 3, rand() % 3);
  changeCol(rand() % 3, rand() % 3);
}

void Sudoku::readIn()
{
  int i;
  for (i = 0;i < 81;i++)
    cin >> ans[i];
}

void Sudoku::solveForCheck()
{
  int i, j;
  ct = 0;
  initializeCRB();
  for(i = 0;i < 81;++i)
    addElement(i, ans[i], 1);
  for(i = 0;i < 81;++i)
    setPossibleArray(i);
  if(SudokuIsCorrect())
    solving();
}


void Sudoku::solve()
{
  int i, j;
  ct = 0;
  initializeCRB();
  for(i = 0;i < 81;++i)
    addElement(i, ans[i], 1);
  for(i = 0;i < 81;++i)
    setPossibleArray(i);
  if(SudokuIsCorrect())
    solving();
  cout << ct <<endl;
  if (ct == 1)
  showSudoku(out);
}

void Sudoku::solving()
{
  int ans_blank = 0, p_blank = 0;
  int index = findLessPossibleIndex();
  if (ct > 1) return;
  /*count the blank of Sudoku*/
  for (int j = 0;j < 9;j++)
  {
    ans_blank += COL[j][0];
    for (int k = 0;k < 9;++k)
      if (P[j][k] > 0) p_blank++;
  }
  if (ans_blank != p_blank) return;
  /*if index < 0 check the ans*/
  if (index < 0)
  {
    if (SudokuIsFull() && SudokuIsCorrect()) 
    {
      for(int i = 0;i < 81;++i)
        out[i] = ans[i];
      ct ++;
    }
    return;
  }
  /*try num 1 to 9. if correct call solving()*/
  for(int num = 1;num <= 9;++num)
  {
    if(isCorrect2(index, num)){
      addElement(index, num, 1);
      solving();
      if (ct > 1) return;
      addElement(index, num, -1);
    }
  }
}

void Sudoku::Equal(int a[], int b[])
{
  int i;
  for(i = 0;i < 81;i++)
    b[i] = a[i];
}

bool Sudoku::SudokuIsFull()
{
  int i, j;
  for(i = 0;i < 9;++i)
  {
    if (COL[i][0] != 0) return false;
  }
  return true;
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
  if (COL[col][num] > 0 || ROW[row][num] > 0 || BLOCK[block][num] > 0) return false;
  else return true;
}

void Sudoku::showSudoku(int x[])
{
  int i;
  for(i = 0;i < 81;++i)
  {
    cout << x[i] << (((i+1) % 9) == 0 ? "\n" : " ");
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
      inFile >> ans[i];
  }
}

void Sudoku::addElement(int index, int num, int v)
{
  int col = index % 9;
  int row = index / 9;
  if (num == 0) return;
  if (v == 1) ans[index] = num;
  else ans[index] = 0;
  /*set how many`of non0*/
  COL[col][num] += v;
  ROW[row][num] += v;
  BLOCK[((row / 3) * 3) + (col / 3)][num] += v;
  /*set how many of 0*/
  COL[col][0] -= v;
  ROW[row][0] -= v;
  BLOCK[((row / 3) * 3) + (col / 3)][0] -= v;
  /*maintain P*/
  for(int i = 0;i < 9;++i)
  {
    setPossibleArray(row, i) ; //row's element
    setPossibleArray(i, col) ; //col's element
    setPossibleArray((row / 3)* 3 + i / 3, (col / 3)* 3 + i % 3); //block's element
  }
}

void Sudoku::setPossibleArray(int row, int col)
{
  int index = row * 9 + col;
  int temp = 9;
  if (ans[index] != 0) 
  {
    P[row][col] = 0;
    return;
  }
  for (int i = 1;i < 10;++i)
    temp -= COL[col][i] | ROW[row][i] | BLOCK[((row / 3) * 3) + (col / 3)][i]; 
  P[row][col] = temp;
}


void Sudoku::setPossibleArray(int index)
{
  int col = index % 9;
  int row = index / 9;
  setPossibleArray(row, col);
}

int Sudoku::findLessPossibleIndex()
{
  int i, j, min_p = 0, min_index = -1;
  for(i = 0;i < 9;++i)
  {
    for(j = 0;j < 9;++j)
    {
      if (P[i][j] != 0 && (min_p == 0 || P[i][j] < min_p))
      {
        min_p = P[i][j];
        min_index = i * 9 + j;
        if (min_p == 1) break;
      }
    }
  }
  return min_index;
}

void Sudoku::initializeCRB()
{
  for (int i = 0;i < 9;++i)
  {
    for (int j = 0;j < 10;++j)
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

void Sudoku::initializeAns()
{
  for(int i = 0;i < 81;++i)
    ans[i] = 0;
}

