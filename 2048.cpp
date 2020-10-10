/*

© Zacharias 2020

*/


#include <iostream>
#include <ctime>
#ifdef __cplusplus__
  #include <cstdlib>
#else
  #include <stdlib.h>
#endif
#include <iomanip>
#include <time.h>

using namespace std;

int board[4][4];
int dirLine[] = {1, 0, -1, 0};
int dirColumn[] = {0, 1, 0, -1};

pair<int, int> generateUnoccupiedPosition() {
	int occupied = 1, line, column;
	while(occupied){
		line = rand() % 4;
		column = rand() % 4;
		if(board[line][column] == 0)
			occupied = 0;
	}
	return make_pair(line, column);
}

void addPiece(){
	pair<int, int> pos = generateUnoccupiedPosition();
	board[pos.first][pos.second] = 2;
}

void newgame() {
	for(int i = 0; i < 4; ++i)
		for(int j = 0; j < 4; ++j)
			board[i][j] = 0;
	addPiece();
}

void sleepcp(int milliseconds) // Cross-platform sleep function
{
    clock_t time_end;
    time_end = clock() + milliseconds * CLOCKS_PER_SEC/1000;
    while (clock() < time_end)
    {
    }
}

void cls()
{
	#ifdef _WIN32
		system("cls");
	#else
		system("clear");
	#endif
}

void printUi(){
	sleepcp(2);
	cls();
	//system("cls");
	for(int i = 0; i < 4; ++i){
		
		for(int j = 0; j < 4; ++j)
			if(board[i][j] == 0)
				cout << setw(4)<<".";
			else
				cout << setw(4) <<board[i][j];
		cout << "\n";
	}
	cout<<"n: new game, w: up, s: down, d: right, a: left, q: quit\n";
}

bool canDoMove(int line, int column, int nextLine, int nextColumn){
	if(nextLine < 0 || nextColumn < 0 || nextLine >= 4 || nextColumn >= 4 
		|| (board[line][column] != board[nextLine][nextColumn] && board[nextLine][nextColumn] != 0))
		return false;
	return true;
}

void applyMove(int direction){

	int startLine = 0, startColumn = 0, lineStep = 1, columnStep = 1;
	if (direction == 0)
	{
		startLine = 3;
		lineStep = -1;
	}
	if (direction == 1)
	{
		startColumn = 3;
		columnStep = -1;
	}

	int newPice, canAddPice = 0;

	do{
		newPice = 0;

		for(int i = startLine; i >= 0 && i < 4; i += lineStep)
			for(int j = startColumn; j >= 0 && j < 4; j += columnStep){
				int nextI = i + dirLine[direction], nextJ = j + dirColumn[direction];
				//cout << i<<" "<<j<<" "<<nextI<<" "<<nextJ<<"\n";
				if(canDoMove(i, j, nextI, nextJ) && board[i][j]) {
					board[nextI][nextJ] += board[i][j];
					board[i][j] = 0;
					newPice = canAddPice = 1;
				}
			}
		printUi();
	} while(newPice);
	if(canAddPice)
		addPiece();
	

}

bool tryNoPosibleMoves(){
	int startLine = 0, startColumn = 0, lineStep = 1, columnStep = 1, newPice = 0, k = 0, canDoMore = 0;

	while(k < 3){
		if (k == 0)
		{
			startLine = 3;
			lineStep = -1;
		}
		if (k == 1)
		{
			startColumn = 3;
			columnStep = -1;
		}
		do{
			newPice = 0;

			for(int i = startLine; i >= 0 && i < 4; i += lineStep)
				for(int j = startColumn; j >= 0 && j < 4; j += columnStep){
					int nextI = i + dirLine[k], nextJ = j + dirColumn[k];
					//cout << i<<" "<<j<<" "<<nextI<<" "<<nextJ<<"\n";
					if(canDoMove(i, j, nextI, nextJ) && board[i][j]) {
						board[nextI][nextJ] += board[i][j];
						board[i][j] = 0;
						newPice = canDoMore = 1;
					}
				}
		
		} while(newPice);
		++k;
	}
	if(canDoMore){
		return true;
	}
	return false;
}

bool tryWin(){
	//bool ret [] = {false, false};
	for(int i = 0; i < 4; ++i)
		for(int j = 0; j < 4; ++j)
			if(board[i][j] == 2048){
				return true;
				//ret[0]=true;
				//ret[1]=false;
			}
	//ret[0] = ret[1] = tryNoPosibleMoves();
	return false;
}

int main(){

	srand(time(0));

	char commandToDir[128];
	commandToDir['s'] = 0;
	commandToDir['d'] = 1;
	commandToDir['w'] = 2;
	commandToDir['a'] = 3;
	
	//while(true){
		newgame();

		while(true){
			//bool ret [2] = {false, false};
			//ret[0], ret[1] = tryWin();
			if(tryWin()/*ret[0]*/)
			{
				/*if(ret[1])
				{
					cout<<"you lost :(\n";
					break;
				}*/
				cout<<"You have goten 2048 congratulation!!!\n";
				break;
			}
			printUi();
			char command;
			cin >> command;
			if(command == 'n')
				newgame();
			else if(command == 'q')
				break;
			else
			{
				int currentDirection = commandToDir[command];
				//cout << currentDirection<<"\n";
				applyMove(currentDirection);
			}
			
		}

	/*cout<<"Whana play agen?\n";
	char newGame;
	cin >> newGame;
	if(newGame == 'y' || newGame == 'Y'){}
	else
		break;
	

	}*/
	return 0;
}