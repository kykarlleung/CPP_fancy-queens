#include <iostream>
#include <cmath>
#include "windows.h"
using namespace std;

bool ok(int q[], int c)
{
	for (int i = 0; i < c; ++i)
		if (q[i] == q[c] || abs(q[i] - q[c]) == c - i)
			return false;
	return true;
}

void print(int q[])
{
	int numberOfSolution = 5; /*******change *******/
   	static int solution = 0;
   	int i, j, k, l;
   	int column = 10;
   	typedef char box[5][10];   // box is now a data type: a 5x7 2D array of characters
	box bb, wb, *board[8][8]; // bb and wb are boxes (5x7 arrays).  board is an 8x8 array of pointers to boxes.
                             // You don't have to clean up the board after printing, because it's not static,
                             // so it'll be reinitialized the next time you call the funtion.

   // Fill in bb (black box) and wb (white box).  They each represent a square of the chessboard.
   // You only need to create one of each, since the chessboard can contain many pointers to the same box.
	for (i=0; i<5; i++)
		for (j=0; j<column; j++) 
		{
        	bb[i][j] = ' ';
        	wb[i][j] = char(219);
		}
   
   // Create 2 more boxes to represent the queens, by drawing a picture of each queen in the 2D array.
	static box bq = {{char(219),char(219),char(219),char(219),char(219),char(219),char(219),char(219),char(219),char(219)},
                     {char(219),char(221),' '	   ,char(219),' '	   ,' '		 ,char(219),' '      ,char(222),char(219)},
                     {char(219),char(221),' '      ,' '      ,' '      ,' '      ,' '      ,' '      ,char(222),char(219)},
                     {char(219),char(221),' '      ,' '      ,' '      ,' '      ,' '      ,' '      ,char(222),char(219)},
                     {char(219),char(219),char(219),char(219),char(219),char(219),char(219),char(219),char(219),char(219)} };
               
	static box wq = {{' '      ,' '      ,' '      ,' '      ,' '      ,' '      ,' '      ,' '      ,' '      ,' '      },
                     {' '      ,char(222),char(219),' '      ,char(219),char(219),' '      ,char(219),char(221),' '		 },
                     {' '      ,char(222),char(219),char(219),char(219),char(219),char(219),char(219),char(221),' '      },
                     {' '      ,char(222),char(219),char(219),char(219),char(219),char(219),char(219),char(221),' '      },
                     {' '      ,' '      ,' '      ,' '      ,' '      ,' '      ,' '      ,' '      ,' '      ,' '      } };

   // Fill board with pointers to bb and wb in alternate positions.
	for(i=0; i<8; i++)
    	for(j=0; j<8; j++)
        	if((i+j)%2 == 0)
        		board[i][j] = &wb;
        	else
            	board[i][j] = &bb; 
		
   	for(i=0; i<8; i++)
    	for(j=0; j<8; j++)
			if (q[j]==i)
			{
				if((i+j)%2 == 0)
        			board[i][j] = &bq;
        		else
            		board[i][j] = &wq;
			}
	 
   // Set up the current solution on the chessboard by placing pointers to bq and wq in the appropriate squares.
   // Place black queens on white squares and white queens on black squares, so that you will be able to see them when printing.
   // Write the code.
   
    
	if(solution == numberOfSolution)
		exit(1); 
   cout << "Solution #" << ++solution << ":\n ";
 
   // Print upper border
	for (i=0; i<column*8; i++)
		cout << '_';
	cout << "\n";

   // Print the board
	for (i=0; i<8; i++)          // for each board row
		for (k=0; k<5; k++) 
		{   // for each box row
			cout << char(179);
			for (j=0; j<8; j++)    // for each board column
				for (l=0; l<column; l++) // for each box column
				// board[i][j] is the box pointer in the ith row, jth column of the board.
				// *board[i][j] is the box being pointed to.
				// (*board[i][j])[k][l] is the kth row, lth column of the box.
					cout << (*board[i][j])[k][l];
					cout << char(179) << "\n";
		}

   // Print lower border
	cout << " ";
		for (i=0; i<column*8; i++)
	cout << char(196);
	cout << "\n\n";
}

void next(int q[], int c)
{
	if (c == 8)
    	print(q);
	else for (q[c] = 0; q[c]<8; ++q[c])
    	if (ok(q, c))
        	next(q, c+1);
}

int main() 
{
	SetConsoleOutputCP(437);
	int q[8]={0};
	int c=0;
	bool setRowToNegativeOne = true;
	int infiniteLoop = 0;
	
	while (infiniteLoop == 0)
	{
		while (c<8)
		{
			if (setRowToNegativeOne == true)	//if this is NC, set 
				q[c]=-1;							//set row == -1
			while (q[c]<8)
			{
				q[c]++;							//NR
				if (q[c]==8)					//if row == 8
				{
					c--;						//BACKTRACK
					if (c==-1)					//if col == -1, end program
						return 0;
					continue;					//goto NR and check again
				}
				if(ok(q,c))					//if it Passes the Row and Up&Down Diagonal Test
					break;						//goto NC
			}
			c++;								//NC
			setRowToNegativeOne = true;			//set a boolean to save it is NC
		}
		next (q,c);							//Print the Queens
		cout << endl;
		c--;									//BACKTRACK to find all the solutions
		if (c==-1)
			return 0;
		setRowToNegativeOne = false;
	}
	return 0;
}
