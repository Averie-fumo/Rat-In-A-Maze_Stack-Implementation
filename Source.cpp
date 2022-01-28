#include <SFML/Graphics.hpp>
#include <conio.h>
#include <windows.h>
#include <ctime>
#include <cstdlib>
#include "myconsole.h"
#include "mygraphics.h"
#include <iostream>
using namespace std; 

template <typename T>
class stack
{
private :
	class Node
	{
	private :
		int x;
		int y; 
		Node* next;
	public :
		friend class list;
		Node()
		{
			next = nullptr;
		}
	};
	class list
	{
	  private :
		Node* head;
		Node* tail;
	  public :
		  friend class stack;
		list()
		{
			head = new Node;
			tail = new Node;
		}
		void insert_at_tail(int x, int y)
		{
			if (head == nullptr)
			{
				tail = new Node;
				head = new Node;
				head->x = x;
				head->y = y;
				tail->x = x;
				tail->y = y;
				head->next = nullptr;
				tail->next = nullptr;
			
			}
			else if (head->x == NULL)
			{
				head->x = y;
				head->y = y;
			}
			else if (head->next == nullptr)
			{
				Node* newnode = new Node;
				newnode->x = x;
				newnode->y = y;
				head->next = newnode;
				tail = newnode;
			}
			else
			{
				Node* newnode = new Node;
				newnode->x = x;
				newnode->y = y;
				Node* temp = tail;
				tail = newnode;
				temp->next = tail;
				tail->next = nullptr;
			}
		
		}
		int getx()
		{
			if (tail != nullptr)
				return tail->x;
			else if (head != nullptr)
				return head->x;
			else
				return NULL;
		}
		int gety()
		{
			if (tail != nullptr)
				return tail->y;
			else if (head != nullptr)
				return head->y;
			else
				return NULL;
		}
		void delete_at_tail()
		{
			Node* temp = tail;
			Node* curr = head;
			if (curr == nullptr)
				return;
			else if (curr->next == nullptr)
			{
				tail = head;
				head = NULL;
				tail = NULL;
				return;
			}
			while (curr->next != tail)
			{
				curr = curr->next;
			}
			tail = curr;
			tail->next = nullptr;
			delete temp;
			temp = nullptr;
		}
	};
private :
	list s;
	int num = 0;
public:
	void push(int x, int y)
	{
		num++;
		s.insert_at_tail(x, y);
	}
	void pop()
	{
		num--;
		s.delete_at_tail();
	}
	int getx()
	{
		return s.getx();
	}
	int gety()
	{
		return s.gety();
	}
	bool isEmpty()
	{
		if (num == 0)
			return true;
		return false; 
	}
};
void gotoxy(int x, int y)
{
	COORD coordinates;     // coordinates is declared as COORD
	coordinates.X = x;     // defining x-axis
	coordinates.Y = y;     //defining  y-axis
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coordinates);
}

bool take_maze(char** maze, int& srcx, int& srcy, int& destx , int& desty, int& rows, int& cols )
{
	for (int i = 0;i < rows;i++)
		for (int j = 0;j < cols;j++)
			maze[i][j] = ' ';

	int k ;
	for (int i = 0; i < rows;i++)
	{
		for (int j = 0;j < cols;j++)
		{
			k = rand() % 10  + 1;
			if (k == 9 || k==8)
			{
				maze[i][j] = '#';
			}
		}
	}
	//for (int i = 0, j = 0; j < cols;j++)
	//{
	//	maze[i][j] = '-';
	//}
	//for (int i = rows-1, j = 0; j < cols;j++)
	//{
	//	maze[i][j] = '-';

	//}
	//for (int i = 0, j = 0; i < rows;i++)
	//{
	//	maze[i][j] = '-';

	//}
	//for (int i = 0, j = cols-1; i < rows;i++)
	//{
	//	maze[i][j] = '-';
	//}
	cout << "Source X coordinate:" << endl;
	cin >> srcx;
	cout << "Source Y coordinate:" << endl;
	cin >> srcy;
	cout << "Destination X coordinate:" << endl;
	cin >> destx;
	cout << "Destination Y coordinate:" << endl;
	cin >> desty;

	if (srcx < 0 || destx < 0 || desty < 0 || srcy < 0)
		return false;
	if (srcx >= rows || destx >= rows || destx >= cols || desty >= cols)
		return false;
	return true;

}
void display_maze(int rows, int cols, char** maze)
{
	ClearScreen();
	//myRect(0, 0, rows * 50, cols * 50, RGB(0, 0, 0), RGB(255, 165, 0));
	int x = 0, y = 0;
	for (int i = 0;i < rows;i++)
	{
		x = 0;
		for (int j = 0;j < cols;j++)
		{
			if (maze[i][j] == ' ')
			{
				myRect(x, y, x+50, y+50, RGB(0, 0, 0), RGB(255, 165, 0));
				x = x + 50;
			}
			else if (maze[i][j] == '#')
			{
				myRect(x, y, x + 50, y + 50, RGB(0, 0, 0), RGB(0, 0, 255));
				x = x + 50;

			}
			else if (maze[i][j] == 'D'|| maze[i][j]=='R')
			{
				myRect(x, y, x + 50, y + 50, RGB(0, 0, 0), RGB(0, 255, 0));
				x = x + 50;
				
			}
			else if (maze[i][j] == '*')
			{
				myRect(x, y, x + 50, y+ 50, RGB(0, 0, 0), RGB(255, 0, 0));
				x = x + 50;
			}
			else if (maze[i][j] == '.')
			{
				myRect(x, y, x + 50, y+ 50, RGB(0, 0, 0), RGB(255, 255, 0));
				x = x + 50;
			}
			else if (maze[i][j] == '-')
			{
				myRect(x, y, x + 50, y + 50, RGB(0, 0, 0), RGB(0, 0, 0));
				x = x + 50;
			}
		}
		y = y + 50;
	}

	//for (int i = 0;i < rows;i++)
	//{
	//	for (int j = 0;j < cols;j++)
	//	{
	//		cout << maze[i][j];
	//	}
	//	cout << endl;
	//}

}
void place_rat_dest(int srcx, int srcy,int destx, int desty, char** maze)
{
	maze[srcx][srcy] = 'R';
	maze[destx][desty] = 'D';
}
bool left(char** maze, int& x, int& y, stack<int>& s)
{
	if (y!=0)
	if (maze[x][y - 1] ==' '|| maze[x][y-1]=='R'|| maze[x][y-1]=='D')
	{
		y--;
		maze[x][y] = '.';
		//cout << endl << x << "," << y; 
		s.push(x, y);
		return true;
	}
	return false;
}
bool right(char** maze, int& x, int& y, stack<int>& s,int cols)
{
	if (y!= cols-1)
	if (maze[x][y + 1]==' '|| maze[x][y + 1] == 'R'|| maze[x][y + 1] == 'D')
	{
		y++;
		maze[x][y] = '.';
		//cout << endl << x << "," << y;
		s.push(x, y);
		return true;
	}
	return false;
}
bool down(char** maze, int& x, int& y, stack<int>& s, int rows)
{
	if (x!= rows-1)
	if (maze[x + 1][y] == ' ' || maze[x + 1][y] == 'R' || maze[x+1][y] == 'D')
	{
		x++;
		maze[x][y] = '.';
		//cout << endl << x << "," << y;
		s.push(x, y);
		return true;
	}
	return false;
}
bool up(char** maze, int& x, int& y, stack<int>& s )
{
	//cout << x << "," << y;
	if (x!=0)
 	if (maze[x-1][y] ==' '|| maze[x - 1][y] == 'R'|| maze[x - 1][y] == 'D')
	{
		x--;
		maze[x][y] = '.';
		s.push(x, y);
		return true;
	}
	return false;
}
void movement(int srcx, int srcy, int destx, int desty, char** maze, stack<int>& s, int rows ,int cols)
{
	s.push(srcx, srcy);
	int x = srcx, y = srcy;
	bool flag = s.isEmpty();
	bool found = false;
	bool step_taken;
	while (!flag && !found)
	{
		ClearScreen();
		display_maze(rows, cols, maze);
		Sleep(450);
		step_taken = false;
			if (x < destx&& !step_taken)
			{
				step_taken = down(maze, x, y, s,rows);
			}
			if (x > destx&& !step_taken)
			{
				step_taken = up(maze, x, y, s);
			}
			if (y > desty&& !step_taken)
			{
				step_taken = left(maze, x, y, s);
			}
			if (y < desty && !step_taken)
			{
				step_taken = right(maze, x, y, s,cols);
			}
			else if (y !=0 && maze [x][y-1]==' '&&!step_taken)
				step_taken = left(maze, x, y, s);
			else if (y!=cols-1 && maze[x][y+1]==' '&&!step_taken)
				step_taken = right(maze, x, y, s, cols);
			else if (x!=0 && maze[x-1][y]==' '&& !step_taken)
				step_taken = up(maze, x, y, s);
			else if (x!= rows-1 && maze[x+1][y]==' ' && !step_taken)
				step_taken = down(maze, x, y, s, rows);

			 if (x == destx && y == desty)
			 {
				 found = true;
				 break;
			 }
			 if (step_taken == false)
			 {
				 maze[x][y] = '*';
				 s.pop();
				 x = s.getx();
				 y = s.gety();
			 }
		
			 if (s.isEmpty())
			 {
				 cout << "Stack is empty." << endl;
				 flag = true;
			 }
	}
	x = s.getx();
	y = s.gety();


	int xx, yy;
	while (!s.isEmpty())
	{
		s.pop();
		xx = s.getx();
		yy = s.gety();
	}
}
int main()
{
	Maximized();
	int srcx= 0 , srcy=0 ,destx=0 , desty = 0, rows= 0 , cols= 0;
	stack<int> Stack;
		cout << "Enter rows:" << endl;
		cin >> rows;
		cout << "Enter columns: " << endl;
		cin >> cols;
		char** maze = new char* [rows];
		for (int i = 0; i < rows;i++)
		{
			maze[i] = new char[cols];
		}
		if (!take_maze(maze, srcx, srcy, destx, desty, rows, cols))
			cout << "Coordinates entered are invalid." << endl;

		else
		{

			place_rat_dest(srcx, srcy, destx, desty, maze);

			movement(srcx, srcy, destx, desty, maze, Stack, rows, cols);
			display_maze(rows, cols, maze);
			PlaceCursor(0, rows + 4);
		}
		for (int i = 0; i < rows;i++)
		{
			delete maze[i];
			maze[i] = nullptr;
		}
		delete maze;
		maze = nullptr;	
}