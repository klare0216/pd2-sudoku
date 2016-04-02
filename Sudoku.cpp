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
}

void Sudoku::changeRow(int a, int b)
{
  int i, temp[27];
  for (i = 0;i < 27;i++)
  {
    temp[i] = getAns(a * 27 + i);
    setAns(a * 27 + i, getAns(b * 27 + i)); 
  }
  for (i = 0;i < 27;i++)
  {
    setAns(b * 27 + i, temp[i]); 
  }
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
  int num;
  int index;
  int conti = true;
  index = getNextZeroIndex();
    if(ct > 1) exit(1);
    if (index == -1)
    {
      ct ++;
      showSudoku();
      return;
    }
    for(num = 1;num <= 9;++num)
    {
      setAns(index, num);
      if(isCorrect(index)){
        setQues(index, num);
        solve();
      }
      setQues(index, 0);
    }
    setAns(index, 0);
}

void Sudoku::setQues(int index, int num)
{
  ques[index] = num;
}

void Sudoku::setAns(int index, int num)
{
  ans[index] = num;
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


bool Sudoku::isCorrect(int x)
{
  int i, row = x / 9, col = x % 9;
  int block = (row / 3)* 27 + (col / 3)*3;

  for(i = 0;i < 9;i++)
  {
    if(getQues(row * 9 + i) == getAns(x))
    {
      return false;
    }    else if(getQues(col + i * 9) == getAns(x))
    {
      return false;
    }    else if((i+1) / 3 == 0 && getQues(block+i)==getAns(x))
    {
      return false;
    }    else if((i+1) / 3 == 1 && getQues(block + 9 + i % 3)==getAns(x))
    {
      return false;
    }    else if((i+1) / 3 == 2 && getQues(block + 18 + i % 3)==getAns(x))
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
  cout << ct << endl;
  for(i = 0;i < 81;++i)
  {
    cout << ans[i];
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
