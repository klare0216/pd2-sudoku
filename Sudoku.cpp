#include "Sudoku.h"
Sudoku::Sudoku()
{
  int i,j;
  ct = 0;
  n = 0;
  for (i = 0;i < 81;++i)
  {
    ques[i] = 0;
    ans[i] = 0;
    out[i] = 0;
  }
  for (i = 0;i < 9;++i)
  {
    for (j = 0;j < 10;++j)
    {
      COL[i][j] = ROW[i][j] = BLOCK[i][j] = 0;
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

  qaEqual();
  for(i = 0;i < 81;i++)
  {
    if(getAns(i) == a)
    {
      setAns(i, b); 
    }else if (getAns(i) == b){
      setAns(i, a);
    }
  }

  qaEqual();
}


void Sudoku::changeRow(int a, int b)
{
  int i, temp[27];

  qaEqual();
  for (i = 0;i < 27;++i)
  {
    temp[i] = getAns(a * 27 + i);
    setAns(a * 27 + i, getAns(b * 27 + i)); 
  }
  for (i = 0;i < 27;i++)
  {
    setAns(b * 27 + i, temp[i]); 
  }
  qaEqual();
}

void Sudoku::changeCol(int a, int b)
{
  int temp[27];
  int i;

  qaEqual();
  for(i = 0;i < 27;++i)
  {
    temp[i] = getAns(a * 3 + (i / 3) * 9 + i % 3);
    setAns((a * 3 + (i / 3) * 9 + i % 3),getAns(b * 3 + (i / 3) * 9 + i % 3));
  }
  for(i = 0;i < 27;++i)
  {
    setAns((b * 3 + (i / 3) * 9 + i % 3),temp[i]);  
  }
  qaEqual();
}

void Sudoku::rotate(int n)
{
  int i = 1;

  qaEqual();
  while( n != 0)
  {
    n--;
    for(i = 0;i < 81;++i)
    { 
      setAns((i % 9) * 9 + (8 - i / 9), getQues(i));
    }
    for(i = 0;i <81;++i)
    {
      setQues(i,getAns(i));
    }
  }
  qaEqual();
}

void Sudoku::flip(int n)
{
  int i, j;

  qaEqual();
  if(n == 0)
  {
    for(i = 0;i < 36;++i)
    { 
      setAns((72 - (i/9)*9 +i%9), getQues(i));
      setAns(i,getQues(72 - (i/9)*9 +i%9));
    }
  }
  else if(n == 1)
  {
    for(j = 0;j <= 4 ;++j)
    {
      for(i = 0;i < 9;++i)
      {
        setAns((8-j+i*9), getQues(i*9+j)); 
        setAns(i*9+j, getQues(8-j+i*9)); 
      }
    }
  }
  qaEqual();
}

void Sudoku::transform()
{

  showSudoku();
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
  int temp;
  for (i = 0;i < 81;i++)
  {
    cin >> temp;
    addElement(i, temp, 1); 
  }

  qaEqual();
}

void Sudoku::solve()
{
  int i;
  for(int fk = 0;fk < 9;fk++)
  {
    for(int fkk = 0;fkk <10;fkk++)
    {
      ROW[fk][fkk] = COL[fk][fkk] = BLOCK[fk][fkk] = 0;
    }
  } 
  for(i = 0;i < 81;++i)
  {
    addElement(i, ans[i], 1);
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
  //cout << "index : " <<index << endl;
  //showSudoku(ans);
  /*for(int j = 0;j < 9;++j)
  {
    for(int k = 0;k < 10;++k)
    {
      cout << COL[j][k] << " ";
    }
    cout << endl;
  }*/

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

void Sudoku::qaEqual()
{
  int i;
  for(i = 0;i < 81;i++)
    ques[i] = ans[i];

}

void Sudoku::setQues(int index, int num)
{
  ques[index] = num;
}

void Sudoku::setAns(int index, int num)
{
  ans[index] = num;
}

void Sudoku::setOut(int index, int num)
{
  out[index] = num;
}

void Sudoku::addCt()
{
  ct++;
}

int Sudoku::getQues(int index)
{
  return ques[index];
}

int Sudoku::getAns(int index)
{
  return ans[index];
}

int Sudoku::getOut(int index)
{
  return out[index];
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

bool Sudoku::isCorrect(int x)
{
  int i, row = x / 9, col = x % 9;
  int block = (row / 3)* 27 + (col / 3)*3; 
  int num;
  bool tof = true;

  if ((num = ans[x]) == 0) return true; 
  ans[x] = -1;

  for(i = 0; tof && i < 9;i++)
  {
    if((ans[row * 9 + i]) == num)
    {
      tof = false;
    } else if(ans[col + i * 9] == num)
    {
      tof = false;
    } else if((i+1) / 3 == 0 && ans[block + i] == num)
    {
      tof = false;
    } else if((i+1) / 3 == 1 && ans[block + 9 + i % 3] == num)
    {
      tof = false;
    } else if((i+1) / 3 == 2 && ans[block + 18 + i % 3] == num)
    {
      tof = false;
    }
  } 
  ans[x] = num;
  //if (!tof) cout << "false index: " << x << endl;
  return tof;
}

bool Sudoku::isCorrect2(int x, int num)
{
  int row = x / 9, col = x % 9;
  int block = ((row / 3) * 3) + (col / 3);
  if (num == 0) return true;
  if(COL[col][num] > 0 || ROW[row][num] > 0 || BLOCK[block][num] > 0) return false;
  else return true;
}

void Sudoku::showSudoku()
{
  int i;
  for(i = 0;i < 81;++i)
  {
    cout << ans[i];
    cout << (((i+1) % 9) == 0 ? "\n" : " ");
  }
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
  int i, temp;
  if(!inFile)
  {
    cout << "File open failed." << endl;
  } else{
    for (i = 0;i < 81;++i)
    {
      inFile >> temp;
      addElement(i, temp, 1);
    }
  }
}

void Sudoku::addElement(int index, int num, int v)
{
  int col = index % 9;
  int row = index / 9;
  if(v == 1) ans[index] = num;
  COL[col][num] += v;
  ROW[row][num] += v;
  BLOCK[((row / 3) * 3) + (col / 3)][num] += v;

}
