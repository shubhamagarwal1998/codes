#include<iostream>
#include<fstream>
using namespace std;
#define N 9
class sudoku
{
	int a[N][N];
	int sgrid[N][N];
	static int nosq;
	static int nomq;
	static int nopq;
	public:
		void play(int B)
		{
		    sudoku s1;
		   if(B==1)
			{
             s1.qsimple();
			}
			else if(B==2)
			{
             s1.qmed();
			}
			else
			{
             s1.qpro();
			}
		    int ch,i,j;
            cout<<endl;
             int b[40][2],k=0;
            for(i=0;i<N;i++)
                {
                for(j=0;j<N;j++)
                {
                if(s1.a[i][j]!=0)
                {
                b[k][0]=i;
                b[k][1]=j;
                k++;
                }
                }
                }
            do
            {
            cout<<"Enter:-\n1 To enter value in sudoku\n2 To see the solution\n3 To exit"<<endl;
            cout<<"REMEMBER if u see the solution then you no longer will be able to play ahead this level and you will automatically be exited from the level"<<endl;
            cin>>ch;
                if(ch==1)
                {
                  cout<<"Enter the row number and column number where you want to insert"<<endl;
                  int row,col,num;
                  cin>>row>>col;
                  row-=1;
                  col-=1;
                  cout<<"Enter number (between 1 to 9) to be inserted"<<endl;
                  cin>>num;
                  if(row<0||row>8||col<0||col>8)
                  {
                      cout<<"Unable to insert value.Please enter correct values"<<endl;
                  }
                  else
                  {

                       for(i=0;i<k;i++)
                        {
                         if(row==b[i][0]&& col==b[i][1])
                           {
                               cout<<"Value can't be inserted as it already exists"<<endl;
                               break;
                           }
                        }
                        if(i==k)
                            s1.a[row][col]=num;
                            cout<<"Now the grid becomes"<<endl;
                            s1.disp(s1.a);
                  }
                }
                else if(ch==2)
                {
                    cout<<"Here is the desired solution"<<endl;
                  if(s1.SSudoku()==true)
                    s1.disp(s1.sgrid);
                  else
                cout<<"Solution does not exist"<<endl;
                break;
              }
                else if(ch!=3)
                {
                    cout<<"Enter correct choice"<<endl;
                }
            }while(ch!=3);
		}
        void disp(int arr[N][N]) //for displaying sudoku
        {
            int i,j;
            for(i=0;i<N;i++)
            {
                for(j=0;j<N;j++)
                {
                    cout<<arr[i][j]<<" ";
                    if((j+1)%3==0)
                        cout<<"\t";
                }
                cout<<endl;
                if((i+1)%3==0)
                    cout<<"\n";
            }
		}
		void qsimple()// for question of simple level
		{
		    int i,j,c=0,k=0;
		    string ch[5];
		    ifstream fin("simple1.txt");
		    if(!fin)
                cout<<"File does not exist"<<endl;
            else
		    {
		        while(c<5)
                {
                getline(fin,ch[c]);
                c++;
                }
            for(i=0;i<N;i++)
            {
                for(j=0;j<N;j++)
              {
                  a[i][j]=ch[nosq][k]-48;
                  k++;
              }
            }
            nosq++;
            if(nosq==5)
                nosq=0;
            disp(a);
            for(i=0;i<N;i++)
            for(j=0;j<N;j++)
             sgrid[i][j]=a[i][j];
           		}
           		fin.close();
		}
		void qmed()// for question of medium level
		{
         int i,j,c=0,k=0;
		    string ch[5];
		    ifstream fin("inter1.txt");
		    if(!fin)
                cout<<"File does not exist"<<endl;
            else
		    {
		        while(c<5)
                {
                getline(fin,ch[c]);
                c++;
                }
            for(i=0;i<N;i++)
            {
                for(j=0;j<N;j++)
              {
                  a[i][j]=ch[nomq][k]-48;
                  k++;
              }
            }
            nomq++;
            if(nomq==5)
                nomq=0;
            disp(a);
            for(i=0;i<N;i++)
            for(j=0;j<N;j++)
             sgrid[i][j]=a[i][j];
		    }
		    fin.close();
		}
		void qpro()// for question of pro level
		{
          int i,j,c=0,k=0;
		    string ch[5];
		    ifstream fin("hard.txt");
		    if(!fin)
                cout<<"File does not exist"<<endl;
            else
		    {
		        while(c<5)
                {
                getline(fin,ch[c]);
                c++;
                }
            for(i=0;i<N;i++)
            {
                for(j=0;j<N;j++)
              {
                  a[i][j]=ch[nopq][k]-48;
                  k++;
              }
            }
            nopq++;
            if(nopq==5)
                nopq=0;
            disp(a);
            for(i=0;i<N;i++)
            for(j=0;j<N;j++)
             sgrid[i][j]=a[i][j];
           		}
           		fin.close();
         for(i=0;i<N;i++)
         for(j=0;j<N;j++)
         sgrid[i][j]=a[i][j];
		}
		//solution starts
		bool Find_0_location(int &r, int &c)
        {
        for (r= 0; r<N; r++)
        for (c = 0; c<N; c++)
            if (sgrid[r][c] == 0)
                return true;
        return false;
        }
		bool UsedInRow(int r, int n)
        {
        for (int c=0; c<N; c++)
        if (sgrid[r][c] == n)
            return true;
        return false;
        }
        bool UsedInCol(int c, int n)
        {
        for (int r= 0; r<N; r++)
        if (sgrid[r][c] == n)
            return true;
        return false;
        }
        bool UsedInsubg(int subgStartRow, int subgStartCol, int n)
        {
        for (int r= 0; r<3; r++)
        for (int c= 0; c<3; c++)
        if (sgrid[r+subgStartRow][c+subgStartCol] == n)
                return true;
        return false;
        }
        bool Safe(int r, int c, int n)
        {
    /* Check if 'n' is not already placed in current row,current column and current 3x3 subgrid */
    return !UsedInRow(r, n) && !UsedInCol(c, n) && !UsedInsubg(r-r%3 , c-c%3, n)&& sgrid[r][c]==0;
        }
		//main Program for solution
		bool SSudoku()
        {
    int r, c;
    // If there is no unassigned location, we are done
    if (!Find_0_location(r, c))
       return true; // success
    for (int n= 1; n<= 9; n++)
    {
        // if it doesn't exist
        if (Safe(r, c, n))
        {
            // assigning temporary value
            sgrid[r][c] = n;
            // return, if true
            if (SSudoku())
                return true;
            // false then try again
            sgrid[r][c] = 0;
        }
    }
    return false; // triggers backtracking
}
};
int sudoku:: nosq=0;
int sudoku:: nomq=0;
int sudoku:: nopq=0;
int main()
{	//TITLE of the game.
	cout<<"********************LETS SUDOKU********************"<<endl;
	cout<<"press enter to start.";
	cin.ignore();
	sudoku s;
	cout<<"**SETTINGS**"<<endl;
	int A=0,B,f=0;
	while(A!=4)
	{
		cout<<"enter:"<<endl<<"1.To read INSTRUCTIONS."<<endl<<"2.To choose DIFFICULTY LEVEL"<<endl<<"3.To START the game"<<endl<<"4.To END the game and EXIT"<<endl;
		cin>>A;
		if(A==1)
		{
			cout<<"INSTRUCTIONS"<<endl;
			cout<<"1.Row and Column constraint:-\nAll cells may contain no more than 1 value AND The value must be between 1 and n (if the grid is of order n*n.Here the order is limited to 9*9)"<<endl;
			cout<<"NOTE:For a puzzle to be a true Sudoku puzzle, it can have one (and only one) solution. There can be no ambiguity in Sudoku."<<endl;
		}
		else if(A==2)
		{
			cout<<"enter:"<<endl<<"1.EASY"<<endl<<"2.MEDIUM"<<endl<<"3.PRO-LEVEL"<<endl;
			cin>>B;
			f=1;
			if(B!=1 && B!=2 && B!=3)
               {
               cout<<"Enter correct choice"<<endl;
               f=0;
               }
		}
		else if(A==3)
		{
		    if(f==1)
		    {
            f=0;
			cout<<"Here's your question sudoku grid.\nENJOY PLAYING!!!!!!!!!!!!"<<endl;
            s.play(B);
		    }
		    else
            {
            cout<<"First choose the difficulty level.Without it game can't be started"<<endl;
            }
		}
        else if(A!=4)
            cout<<"Enter correct choice"<<endl;
        else
           cout<<"Thanks for playing!!!!!!!!!!!!!!!....................."<<endl;
	}
}
