#include "Sudoku.h"
Sudoku::Sudoku()
{
  int i;
  ct = 0;
  for (i = 0;i < 81;++i)
  {
    setQues(i, 0);
    setAns(i, 0);
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
    setQues(i, temp);
    setAns(i, temp);
  }
}

void Sudoku::solve()
{
  int i;
  if(SudokuIsCorrect())solving();
  cout << ct <<endl;
  if (ct == 1)
  {
    showSudoku(out);
  }
}

void Sudoku::solving()
{
  int i;
  int num;
  int index;
  index = getNextZeroIndex();
    if(ct > 1)
    {
      cout << 2 << endl;
      exit(1);
    }
    if (index == -1)
    {
      if (SudokuIsCorrect()) 
      {
        for(i = 0;i < 81;++i)
          setOut(i, getAns(i));
        ct ++;
      }
      return;
    }
    for(num = 1;num <= 9;++num)
    {
      setAns(index, num);
      if(isCorrect(index, num)){
        setQues(index, num);
        solving();
      }
      setQues(index, 0);
    }
    setAns(index, 0);
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
  int i;
  for(i = 0;i < 81;++i)
  {
    ques[i] = -1;
    if (!isCorrect(i, ans[i])) 
    {
      return false;
    }
    ques[i] = ans[i];
  }
  return true;
}

bool Sudoku::isCorrect(int x, int num)
{
  int i, row = x / 9, col = x % 9;
  int block = (row / 3)* 27 + (col / 3)*3;  
  if (ans[x] == 0) return true;
  for(i = 0;i < 9;i++)
  {
    if(getQues(row * 9 + i) == num)
    {
      return false;
    }    else if(getQues(col + i * 9) == num)
    {
      return false;
    }    else if((i+1) / 3 == 0 && getQues(block+i)==num)
    {
      return false;
    }    else if((i+1) / 3 == 1 && getQues(block + 9 + i % 3)==num)
    {
      return false;
    }    else if((i+1) / 3 == 2 && getQues(block + 18 + i % 3)==num)
    {
      return false;
    }
  } 
  return true;
}

int Sudoku::getNextZeroIndex()
{
  int i;
  for(i = 0;i < 81;++i)
  {
    if(ques[i] == 0)
      return i;
  }
  return -1;
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
    cout << out[i];
    cout << (((i+1) % 9) == 0 ? "\n" : " ");
  }
}


void Sudoku::fileInput()
{
  ifstream inFile("ques", ios::in);
  int i;
  if(!inFile)
  {
    cout << "File open failed." << endl;
  } else{
    for (i = 0;i < 81;++i)
    {
      inFile >> ques[i];
      ans[i] = ques[i];
    }
  }
}
