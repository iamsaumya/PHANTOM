#include<bits/stdc++.h>
#include<windows.h>
#include<cwchar>
using namespace std;

#define ROW 9
#define COL 20
typedef pair<int,int> Ans;
// Creating a shortcut for int, int pair type
typedef pair<int, int> Pair;

// Creating a shortcut for pair<int, pair<int, int>> type
typedef pair<double, pair<int, int> > pPair;

void gotoxy( int column, int line )
  {
  COORD coord;
  coord.X = column;
  coord.Y = line;
  SetConsoleCursorPosition(
    GetStdHandle( STD_OUTPUT_HANDLE ),
    coord
    );
  }

int wherex()
  {
  CONSOLE_SCREEN_BUFFER_INFO csbi;
  COORD                      result;
  if (!GetConsoleScreenBufferInfo(
         GetStdHandle( STD_OUTPUT_HANDLE ),
         &csbi
         ))
    return -1;
  return result.X;
  }
//HELLO
int wherey()
  {
  CONSOLE_SCREEN_BUFFER_INFO csbi;
  COORD                      result;
  if (!GetConsoleScreenBufferInfo(
         GetStdHandle( STD_OUTPUT_HANDLE ),
         &csbi
         ))
    return -1;
  return result.Y;
  }


// A structure to hold the necessary parameters
struct cell
{
	// Row and Column index of its parent
	// Note that 0 <= i <= ROW-1 & 0 <= j <= COL-1
	int parent_i, parent_j;
	// f = g + h
	double f, g, h;
};

// A Utility Function to check whether given cell (row, col)
// is a valid cell or not.
bool isValid(int row, int col)
{
	// Returns true if row number and column number
	// is in range
	return (row >= 0) && (row < ROW) &&
		(col >= 0) && (col < COL);
}

// A Utility Function to check whether the given cell is
// blocked or not
bool isUnBlocked(int grid[][COL], int row, int col)
{
	// Returns true if the cell is not blocked else false
	if (grid[row][col] == 1)
		return (true);
	else
		return (false);
}

// A Utility Function to check whether destination cell has
// been reached or not
bool isDestination(int row, int col, Pair dest)
{
	if (row == dest.first && col == dest.second)
		return (true);
	else
		return (false);
}

// A Utility Function to calculate the 'h' heuristics.
double calculateHValue(int row, int col, Pair dest)
{
	// Return using the distance formula
	return ((double)sqrt ((row-dest.first)*(row-dest.first)
						+ (col-dest.second)*(col-dest.second)));
}
/* void showanswer(deque<Ans>Check_Answer){
    set<Ans>::const_iterator itr;
    cout<<"Answer:"<<endl;
    for(itr = Check_Answer.begin();itr!=Check_Answer.end();++itr){
        cout<<(*itr)->first<<" "<<(*itr)->second<<endl;
    }
} */
// A Utility Function to trace the path from the source
// to destination
void tracePath(cell cellDetails[][COL], Pair dest, int grid[][COL],Pair src )
{
int x_cor,y_cor=51;
	printf ("\nThe Path is ");
	int row = dest.first;
	int col = dest.second;

	stack<Pair> Path;

	while (!(cellDetails[row][col].parent_i == row
			&& cellDetails[row][col].parent_j == col ))
	{
		Path.push (make_pair (row, col));
		int temp_row = cellDetails[row][col].parent_i;
		int temp_col = cellDetails[row][col].parent_j;
		row = temp_row;
		col = temp_col;
	}
    int ans;
	Path.push (make_pair (row, col));
    deque<Ans>Answer;
    deque<Ans>Check_Answer;
	while (!Path.empty())
	{
		pair<int,int> p = Path.top();
		Path.pop();
		Check_Answer.push_back(make_pair(p.first,p.second));
	}
	int i,x,y,Key;
	int a= src.first, b=src.second;
    cout<<"You have \x03 Lifelines"<<endl;
	cout<<"Enter -1,-1 to terminate answer"<<endl;
    while(true){
            cin>>Key;
            if(Key==0)
                a=b=-1;
            else if(Key==8){
                a=a-1;
            }
            else if(Key==2){
                a=a+1;
            }
            else if(Key==6){
                b=b+1;
            }
            else if(Key==4){
                b=b-1;
            }
            else if(Key==9){
                a=a-1;
                b=b+1;
            }
            else if(Key==7){
                a=a-1;
                b=b-1;
            }
            else if(Key==3){
                a=a+1;
                b=b+1;
            }
            else if(Key==1){
                a=a+1;
                b=b-1;
            }

            if(a==-1 && b==-1){
               break;
                }
            else if(grid[a][b]==0){
                cout<<"You cannot make IAF jets flyover pakistan governed territory!!\n";
                y_cor+=2;
                continue;
            }
            else {
                x=9*b;
               y=3+(5*a);
                    for(i=0;i<4;i++)
            {
               gotoxy(x,y);
               cout<<"\xB1\xB1\xB1\xB1\xB1\xB1\xB1\xB1";
               y++;
            }
                gotoxy(0,y_cor);
                Answer.push_back(make_pair(a,b));
            }
        }
    if(Answer == Check_Answer)
        cout<<"BOOM BOOM BOOM!!\n\nJ-e-M camp has been eradicated."<<endl;
    else {
        cout <<"Oops This was no brainer dude! Anyway Try again next time :p"<<endl;
    }
}


// A Function to find the shortest path between
// a given source cell to a destination cell according
// to A* Search Algorithm
void aStarSearch(int grid[][COL], Pair src, Pair dest)
{
	// If the source is out of range
	if (isValid (src.first, src.second) == false)
	{
		printf ("Source is invalid\n");
		return;
	}

	// If the destination is out of range
	if (isValid (dest.first, dest.second) == false)
	{
		printf ("Destination is invalid\n");
		return;
	}

	// Either the source or the destination is blocked
	if (isUnBlocked(grid, src.first, src.second) == false ||
			isUnBlocked(grid, dest.first, dest.second) == false)
	{
		printf ("Source or the destination is blocked\n");
		return;
	}

	// If the destination cell is the same as source cell
	if (isDestination(src.first, src.second, dest) == true)
	{
		printf ("We are already at the destination\n");
		return;
	}

	// Create a closed list and initialise it to false which means
	// that no cell has been included yet
	// This closed list is implemented as a boolean 2D array
	bool closedList[ROW][COL];
	memset(closedList, false, sizeof (closedList));

	// Declare a 2D array of structure to hold the details
	//of that cell
	cell cellDetails[ROW][COL];

	int i, j;

	for (i=0; i<ROW; i++)
	{
		for (j=0; j<COL; j++)
		{
			cellDetails[i][j].f = FLT_MAX;
			cellDetails[i][j].g = FLT_MAX;
			cellDetails[i][j].h = FLT_MAX;
			cellDetails[i][j].parent_i = -1;
			cellDetails[i][j].parent_j = -1;
		}
	}

	// Initialising the parameters of the starting node
	i = src.first, j = src.second;
	cellDetails[i][j].f = 0.0;
	cellDetails[i][j].g = 0.0;
	cellDetails[i][j].h = 0.0;
	cellDetails[i][j].parent_i = i;
	cellDetails[i][j].parent_j = j;

	/*
	Create an open list having information as-
	<f, <i, j>>
	where f = g + h,
	and i, j are the row and column index of that cell
	Note that 0 <= i <= ROW-1 & 0 <= j <= COL-1
	This open list is implenented as a set of pair of pair.*/
	set<pPair> openList;

	// Put the starting cell on the open list and set its
	// 'f' as 0
	openList.insert(make_pair (0.0, make_pair (i, j)));

	// We set this boolean value as false as initially
	// the destination is not reached.
	bool foundDest = false;

	while (!openList.empty())
	{
		pPair p = *openList.begin();

		// Remove this vertex from the open list
		openList.erase(openList.begin());

		// Add this vertex to the closed list
		i = p.second.first;
		j = p.second.second;
		closedList[i][j] = true;

	/*
		Generating all the 8 successor of this cell

			N.W N N.E
			\ | /
			\ | /
			W----Cell----E
				/ | \
			/ | \
			S.W S S.E

		Cell-->Popped Cell (i, j)
		N --> North	 (i-1, j)
		S --> South	 (i+1, j)
		E --> East	 (i, j+1)
		W --> West		 (i, j-1)
		N.E--> North-East (i-1, j+1)
		N.W--> North-West (i-1, j-1)
		S.E--> South-East (i+1, j+1)
		S.W--> South-West (i+1, j-1)*/

		// To store the 'g', 'h' and 'f' of the 8 successors
		double gNew, hNew, fNew;

		//----------- 1st Successor (North) ------------

		// Only process this cell if this is a valid one
		if (isValid(i-1, j) == true)
		{
			// If the destination cell is the same as the
			// current successor
			if (isDestination(i-1, j, dest) == true)
			{
				// Set the Parent of the destination cell
				cellDetails[i-1][j].parent_i = i;
				cellDetails[i-1][j].parent_j = j;

				tracePath (cellDetails, dest,grid,src);
				foundDest = true;
				return;
			}
			// If the successor is already on the closed
			// list or if it is blocked, then ignore it.
			// Else do the following
			else if (closedList[i-1][j] == false &&
					isUnBlocked(grid, i-1, j) == true)
			{
				gNew = cellDetails[i][j].g + 1.0;
				hNew = calculateHValue (i-1, j, dest);
				fNew = gNew + hNew;

				// If it isnt on the open list, add it to
				// the open list. Make the current square
				// the parent of this square. Record the
				// f, g, and h costs of the square cell
				//			 OR
				// If it is on the open list already, check
				// to see if this path to that square is better,
				// using 'f' cost as the measure.
				if (cellDetails[i-1][j].f == FLT_MAX ||
						cellDetails[i-1][j].f > fNew)
				{
					openList.insert( make_pair(fNew,
											make_pair(i-1, j)));

					// Update the details of this cell
					cellDetails[i-1][j].f = fNew;
					cellDetails[i-1][j].g = gNew;
					cellDetails[i-1][j].h = hNew;
					cellDetails[i-1][j].parent_i = i;
					cellDetails[i-1][j].parent_j = j;
				}
			}
		}

		//----------- 2nd Successor (South) ------------

		// Only process this cell if this is a valid one
		if (isValid(i+1, j) == true)
		{
			// If the destination cell is the same as the
			// current successor
			if (isDestination(i+1, j, dest) == true)
			{
				// Set the Parent of the destination cell
				cellDetails[i+1][j].parent_i = i;
				cellDetails[i+1][j].parent_j = j;

				tracePath(cellDetails, dest,grid,src);
				foundDest = true;
				return;
			}
			// If the successor is already on the closed
			// list or if it is blocked, then ignore it.
			// Else do the following
			else if (closedList[i+1][j] == false &&
					isUnBlocked(grid, i+1, j) == true)
			{
				gNew = cellDetails[i][j].g + 1.0;
				hNew = calculateHValue(i+1, j, dest);
				fNew = gNew + hNew;

				// If it isnt on the open list, add it to
				// the open list. Make the current square
				// the parent of this square. Record the
				// f, g, and h costs of the square cell
				//			 OR
				// If it is on the open list already, check
				// to see if this path to that square is better,
				// using 'f' cost as the measure.
				if (cellDetails[i+1][j].f == FLT_MAX ||
						cellDetails[i+1][j].f > fNew)
				{
					openList.insert( make_pair (fNew, make_pair (i+1, j)));
					// Update the details of this cell
					cellDetails[i+1][j].f = fNew;
					cellDetails[i+1][j].g = gNew;
					cellDetails[i+1][j].h = hNew;
					cellDetails[i+1][j].parent_i = i;
					cellDetails[i+1][j].parent_j = j;
				}
			}
		}

		//----------- 3rd Successor (East) ------------

		// Only process this cell if this is a valid one
		if (isValid (i, j+1) == true)
		{
			// If the destination cell is the same as the
			// current successor
			if (isDestination(i, j+1, dest) == true)
			{
				// Set the Parent of the destination cell
				cellDetails[i][j+1].parent_i = i;
				cellDetails[i][j+1].parent_j = j;

				tracePath(cellDetails, dest,grid,src);
				foundDest = true;
				return;
			}

			// If the successor is already on the closed
			// list or if it is blocked, then ignore it.
			// Else do the following
			else if (closedList[i][j+1] == false &&
					isUnBlocked (grid, i, j+1) == true)
			{
				gNew = cellDetails[i][j].g + 1.0;
				hNew = calculateHValue (i, j+1, dest);
				fNew = gNew + hNew;

				// If it isnt on the open list, add it to
				// the open list. Make the current square
				// the parent of this square. Record the
				// f, g, and h costs of the square cell
				//			 OR
				// If it is on the open list already, check
				// to see if this path to that square is better,
				// using 'f' cost as the measure.
				if (cellDetails[i][j+1].f == FLT_MAX ||
						cellDetails[i][j+1].f > fNew)
				{
					openList.insert( make_pair(fNew,
										make_pair (i, j+1)));

					// Update the details of this cell
					cellDetails[i][j+1].f = fNew;
					cellDetails[i][j+1].g = gNew;
					cellDetails[i][j+1].h = hNew;
					cellDetails[i][j+1].parent_i = i;
					cellDetails[i][j+1].parent_j = j;
				}
			}
		}

		//----------- 4th Successor (West) ------------

		// Only process this cell if this is a valid one
		if (isValid(i, j-1) == true)
		{
			// If the destination cell is the same as the
			// current successor
			if (isDestination(i, j-1, dest) == true)
			{
				// Set the Parent of the destination cell
				cellDetails[i][j-1].parent_i = i;
				cellDetails[i][j-1].parent_j = j;

				tracePath(cellDetails, dest,grid,src);
				foundDest = true;
				return;
			}

			// If the successor is already on the closed
			// list or if it is blocked, then ignore it.
			// Else do the following
			else if (closedList[i][j-1] == false &&
					isUnBlocked(grid, i, j-1) == true)
			{
				gNew = cellDetails[i][j].g + 1.0;
				hNew = calculateHValue(i, j-1, dest);
				fNew = gNew + hNew;

				// If it isnt on the open list, add it to
				// the open list. Make the current square
				// the parent of this square. Record the
				// f, g, and h costs of the square cell
				//			 OR
				// If it is on the open list already, check
				// to see if this path to that square is better,
				// using 'f' cost as the measure.
				if (cellDetails[i][j-1].f == FLT_MAX ||
						cellDetails[i][j-1].f > fNew)
				{
					openList.insert( make_pair (fNew,
										make_pair (i, j-1)));

					// Update the details of this cell
					cellDetails[i][j-1].f = fNew;
					cellDetails[i][j-1].g = gNew;
					cellDetails[i][j-1].h = hNew;
					cellDetails[i][j-1].parent_i = i;
					cellDetails[i][j-1].parent_j = j;
				}
			}
		}

		//----------- 5th Successor (North-East) ------------

		// Only process this cell if this is a valid one
		if (isValid(i-1, j+1) == true)
		{
			// If the destination cell is the same as the
			// current successor
			if (isDestination(i-1, j+1, dest) == true)
			{
				// Set the Parent of the destination cell
				cellDetails[i-1][j+1].parent_i = i;
				cellDetails[i-1][j+1].parent_j = j;

				tracePath (cellDetails, dest,grid,src);
				foundDest = true;
				return;
			}

			// If the successor is already on the closed
			// list or if it is blocked, then ignore it.
			// Else do the following
			else if (closedList[i-1][j+1] == false &&
					isUnBlocked(grid, i-1, j+1) == true)
			{
				gNew = cellDetails[i][j].g + 1.414;
				hNew = calculateHValue(i-1, j+1, dest);
				fNew = gNew + hNew;

				// If it isnt on the open list, add it to
				// the open list. Make the current square
				// the parent of this square. Record the
				// f, g, and h costs of the square cell
				//			 OR
				// If it is on the open list already, check
				// to see if this path to that square is better,
				// using 'f' cost as the measure.
				if (cellDetails[i-1][j+1].f == FLT_MAX ||
						cellDetails[i-1][j+1].f > fNew)
				{
					openList.insert( make_pair (fNew,
									make_pair(i-1, j+1)));

					// Update the details of this cell
					cellDetails[i-1][j+1].f = fNew;
					cellDetails[i-1][j+1].g = gNew;
					cellDetails[i-1][j+1].h = hNew;
					cellDetails[i-1][j+1].parent_i = i;
					cellDetails[i-1][j+1].parent_j = j;
				}
			}
		}

		//----------- 6th Successor (North-West) ------------

		// Only process this cell if this is a valid one
		if (isValid (i-1, j-1) == true)
		{
			// If the destination cell is the same as the
			// current successor
			if (isDestination (i-1, j-1, dest) == true)
			{
				// Set the Parent of the destination cell
				cellDetails[i-1][j-1].parent_i = i;
				cellDetails[i-1][j-1].parent_j = j;

				tracePath (cellDetails, dest,grid,src);
				foundDest = true;
				return;
			}

			// If the successor is already on the closed
			// list or if it is blocked, then ignore it.
			// Else do the following
			else if (closedList[i-1][j-1] == false &&
					isUnBlocked(grid, i-1, j-1) == true)
			{
				gNew = cellDetails[i][j].g + 1.414;
				hNew = calculateHValue(i-1, j-1, dest);
				fNew = gNew + hNew;

				// If it isnt on the open list, add it to
				// the open list. Make the current square
				// the parent of this square. Record the
				// f, g, and h costs of the square cell
				//			 OR
				// If it is on the open list already, check
				// to see if this path to that square is better,
				// using 'f' cost as the measure.
				if (cellDetails[i-1][j-1].f == FLT_MAX ||
						cellDetails[i-1][j-1].f > fNew)
				{
					openList.insert( make_pair (fNew, make_pair (i-1, j-1)));
					// Update the details of this cell
					cellDetails[i-1][j-1].f = fNew;
					cellDetails[i-1][j-1].g = gNew;
					cellDetails[i-1][j-1].h = hNew;
					cellDetails[i-1][j-1].parent_i = i;
					cellDetails[i-1][j-1].parent_j = j;
				}
			}
		}

		//----------- 7th Successor (South-East) ------------

		// Only process this cell if this is a valid one
		if (isValid(i+1, j+1) == true)
		{
			// If the destination cell is the same as the
			// current successor
			if (isDestination(i+1, j+1, dest) == true)
			{
				// Set the Parent of the destination cell
				cellDetails[i+1][j+1].parent_i = i;
				cellDetails[i+1][j+1].parent_j = j;

				tracePath (cellDetails, dest,grid,src);
				foundDest = true;
				return;
			}

			// If the successor is already on the closed
			// list or if it is blocked, then ignore it.
			// Else do the following
			else if (closedList[i+1][j+1] == false &&
					isUnBlocked(grid, i+1, j+1) == true)
			{
				gNew = cellDetails[i][j].g + 1.414;
				hNew = calculateHValue(i+1, j+1, dest);
				fNew = gNew + hNew;

				// If it isnt on the open list, add it to
				// the open list. Make the current square
				// the parent of this square. Record the
				// f, g, and h costs of the square cell
				//			 OR
				// If it is on the open list already, check
				// to see if this path to that square is better,
				// using 'f' cost as the measure.
				if (cellDetails[i+1][j+1].f == FLT_MAX ||
						cellDetails[i+1][j+1].f > fNew)
				{
					openList.insert(make_pair(fNew,
										make_pair (i+1, j+1)));

					// Update the details of this cell
					cellDetails[i+1][j+1].f = fNew;
					cellDetails[i+1][j+1].g = gNew;
					cellDetails[i+1][j+1].h = hNew;
					cellDetails[i+1][j+1].parent_i = i;
					cellDetails[i+1][j+1].parent_j = j;
				}
			}
		}

		//----------- 8th Successor (South-West) ------------

		// Only process this cell if this is a valid one
		if (isValid (i+1, j-1) == true)
		{
			// If the destination cell is the same as the
			// current successor
			if (isDestination(i+1, j-1, dest) == true)
			{
				// Set the Parent of the destination cell
				cellDetails[i+1][j-1].parent_i = i;
				cellDetails[i+1][j-1].parent_j = j;

				tracePath(cellDetails, dest,grid,src);
				foundDest = true;
				return;
			}

			// If the successor is already on the closed
			// list or if it is blocked, then ignore it.
			// Else do the following
			else if (closedList[i+1][j-1] == false &&
					isUnBlocked(grid, i+1, j-1) == true)
			{
				gNew = cellDetails[i][j].g + 1.414;
				hNew = calculateHValue(i+1, j-1, dest);
				fNew = gNew + hNew;

				// If it isnt on the open list, add it to
				// the open list. Make the current square
				// the parent of this square. Record the
				// f, g, and h costs of the square cell
				//			 OR
				// If it is on the open list already, check
				// to see if this path to that square is better,
				// using 'f' cost as the measure.
				if (cellDetails[i+1][j-1].f == FLT_MAX ||
						cellDetails[i+1][j-1].f > fNew)
				{
					openList.insert(make_pair(fNew,
										make_pair(i+1, j-1)));

					// Update the details of this cell
					cellDetails[i+1][j-1].f = fNew;
					cellDetails[i+1][j-1].g = gNew;
					cellDetails[i+1][j-1].h = hNew;
					cellDetails[i+1][j-1].parent_i = i;
					cellDetails[i+1][j-1].parent_j = j;
				}
			}
		}
	}

	// When the destination cell is not found and the open
	// list is empty, then we conclude that we failed to
	// reach the destiantion cell. This may happen when the
	// there is no way to destination cell (due to blockages)
	if (foundDest == false)
		printf("Failed to find the Destination Cell\n");

	return;
}
void makegrid(int grid[][COL],Pair src, Pair dest)
{
	system("CLS");
	cout<<"\n\n";
	int i,j,k,l,m;
        {
    for(m=0;m<COL;m++)
		{
		cout<<"--------|";
	    }
	    cout<<endl;
	for(i=0;i<ROW;i++)
	{
		for(k=0;k<4;k++)
			{
		     for(j=0;j<COL;j++)
			{
				for(l=0;l<2;l++)
				{
					if(grid[i][j]==1){
                        if(src.first==i && src.second == j){
                                cout<<"\xB0IAF";
                            }
                        else if(dest.first==i && dest.second == j){
                                cout<<"\xB0JeM";
                            }

                        else{
                            if(grid[i][j]==1)
                                cout<<"    ";
                            }
					}
					else
                        cout<<"\xDB\xDB\xDB\xDB";
			 	}
			 	cout<<"|";
			}
			cout<<"\n";
		}
		for(m=0;m<COL;m++)
		{
		cout<<"--------|";
	    }
	    cout<<"\n";
	}
}

}

inline void wait ( short seconds )
{
  clock_t endwait;
  endwait = clock() + seconds * CLOCKS_PER_SEC;
  while (clock() < endwait);
}

inline void CountDown()
{
   gotoxy(190,18);
	cout <<"Time Left"<<endl;

	for (short minutes = 0; minutes >= 0; minutes--)
	{
		for (short seconds = 10; seconds >= 0; seconds--)
		{
		    if(seconds>=10)
		    {
            gotoxy(192,20);
		        cout << minutes << ':' << seconds;
		    }

            else
		    {
                gotoxy(192,20);
                cout << minutes <<":0"<< seconds;
             }
			wait(1);
		}
      }
	gotoxy(0,48);
}
// Driver program to test above function
int main()
{
		/* Description of the Grid-
	1--> The cell is not blocked
	0--> The cell is blocked */

	//grid 1
   int grid1[ROW][COL] =
	{
		{ 1, 0, 1, 1, 1, 1, 0, 1, 1, 1},
		{ 1, 1, 1, 0, 1, 0, 1, 0, 1, 1 },
		{ 1, 1, 1, 0, 1, 1, 0, 1, 0, 1 },
		{ 0, 0, 1, 0, 1, 0, 0, 0, 0, 1 },
		{ 1, 1, 1, 0, 1, 1, 1, 0, 1, 0 },
		{ 1, 1, 1, 1, 0, 1, 0, 1, 0, 0 },
		{ 0, 1, 0, 0, 0, 1, 0, 0, 0, 1 },
		{ 0, 1, 1, 1, 1, 1, 0, 1, 1, 1 },
		{ 1, 0, 1, 0, 0, 0, 1, 0, 0, 1 }
	};

	// Source is the left-most bottom-most corner
	Pair src1 = make_pair(8, 0);

	// Destination is the left-most top-most corner
	Pair dest1 = make_pair(0, 0);


	//grid 2
	int grid2[ROW][COL] =
	{
		{ 1, 0, 1, 1, 1, 1, 0, 1, 1,1,0,0,0,0,1},
		{ 1, 1, 0, 0, 1, 1, 1, 0, 1,1,1,0,1,0,1},
		{ 1, 1, 1, 0, 1, 1, 0, 1,0,1,1,0,0,1,0},
		{ 0, 0, 0, 1, 1, 0, 0, 0, 0,0,1,1,1,1,1},
		{ 1, 1, 0, 0, 1, 1, 1, 0, 1,0,1,0,1,1},
		{ 1, 0, 1, 1, 0, 1, 1, 1, 0,1,0,0,1,0,1},
		{ 1, 0, 0, 0, 0, 0, 1, 0, 1,0,0,1,0,1,0},
		{ 1, 0, 1, 1, 1, 1, 0, 1, 1,1,0,1,1,0,1},
		{ 1, 1, 0, 1, 0, 0, 0, 0, 0,1,1,0,0,0,1}
	};

	// Source is the left-most bottom-most corner
	// Source is the left-most bottom-most corner
	Pair src2 = make_pair(0, 0);

	// Destination is the left-most top-most corner
	Pair dest2 = make_pair(8, 14);


	int grid3[ROW][COL] =
	{
				   {1,0,0,0,1,0,0,0,0,0,0,0,1,1,0,0,0,0,1,0},
				   {0,1,1,1,0,0,1,1,1,0,1,1,1,0,1,1,1,1,0,1},
				   {1,0,0,0,1,0,0,0,1,0,1,0,1,0,1,0,0,0,1,0},
				   {1,1,1,0,0,1,1,1,1,1,0,1,0,1,0,1,0,1,1,1},
				   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,1,0},
				   {1,0,1,1,1,1,0,0,1,1,0,1,0,0,1,0,1,1,0,1},
				   {1,0,1,0,0,0,1,0,0,0,1,0,1,0,0,0,0,0,1,0},
				   {0,0,0,1,1,0,1,0,1,1,1,0,1,0,1,1,1,0,1,0},
				   {1,1,1,1,0,0,0,1,1,0,0,0,0,1,1,0,0,1,1,0}
	};
     system("color 0B");
	// Source is the left-most bottom-most corner
	Pair src3 = make_pair(8,0);

	// Destination is the left-most top-most corner
	Pair dest3 = make_pair(6,0);

	//grid 4
	int grid4[ROW][COL] =
	{       	   {0,0,1,1,1,0,1,0,1,0,1,1,0,0,0,0,1,1,1,0},
				   {0,1,0,0,1,0,1,1,0,0,0,1,1,0,1,1,0,0,0,1},
				   {1,0,1,0,1,1,0,0,1,0,1,0,1,0,1,0,0,0,0,1},
				   {0,1,1,0,1,0,1,1,1,0,1,1,1,0,0,1,0,1,1,1},
				   {1,0,1,0,1,0,1,0,1,1,0,1,0,0,1,1,0,0,1,0},
				   {0,0,1,1,0,1,0,0,0,0,0,0,1,1,0,0,0,0,0,1},
				   {1,0,0,0,0,0,0,0,1,1,0,0,0,0,0,1,0,1,0,1},
				   {0,0,1,1,0,1,0,1,0,0,1,0,0,1,1,0,1,1,0,1},
				   {1,1,0,0,1,0,1,0,1,0,0,1,1,0,1,1,0,1,1,0}
	};

	// Source is the left-most bottom-most corner
	Pair src4 = make_pair(8,0);

	// Destination is the left-most top-most corner
	Pair dest4 = make_pair(4,0);
    string ans;
	char choice,opt;
    cout<<"\t\t\t-------------S . P . F------------\n";
    cout<<"\t\t\t------(SHORTEST PATH FINDER)------\n";

	do
	{
		cout<<"\n\tPRESS :\n  \t (E)EASY\n  \t (M)MEDIUM \n  \t (H)HARD \n  \t (X)EXTREME\n";
	    cin>>choice;
		switch(choice)
	  {
		case 'E':
		         makegrid(grid1,src1,dest1);
		         fflush(stdin);  // fflush to change the theme.
		         system("color F3");
		         CountDown();
                 aStarSearch(grid1, src1, dest1);
                break;

		case 'M':
		         makegrid(grid2,src2,dest2);
                 fflush(stdin);
		         system("color F1");
		         CountDown();
                 aStarSearch(grid2, src2, dest2);
                break;

		case 'H':
		         makegrid(grid3,src3,dest3);
                 fflush(stdin);
		         system("color F5");
		         CountDown();
	             aStarSearch(grid3, src3, dest3);
		    	break;

	   case 'X': makegrid(grid4,src4,dest4);
                 fflush(stdin);
		         system("color F4");
		         CountDown();
                 aStarSearch(grid4, src4, dest4);
		        break;

		default:cout<<"\nInvalid Choice\n";
	}

	  cout<<"\n Press Y to try another difficulty : ";
	  cin>>opt;
	}while(opt=='y'||opt=='Y');


	return(0);
}

