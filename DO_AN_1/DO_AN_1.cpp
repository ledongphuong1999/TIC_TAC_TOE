#include <iostream>
#include <iomanip>
#include <algorithm>

using namespace std;
class Game
{
	enum class Player
	{
		none = '-',
		you = 'X',
		computer = 'O',
	};

	struct Move
	{
		int x = 0;
		int y = 0;
	};

	Player board[3][3];

public:
	Game()
	{
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				board[i][j] = Player::none;
			}
		}
	}

	void printBoard()
	{
		cout << "+-----------------+";
		for (int i = 0; i < 3; i++)
		{
			cout << "\n|";
			for (int j = 0; j < 3; j++)
			{
				cout << setw(3) << static_cast<char>(board[i][j]) << setw(3) << " |";
				
			}
		}
		cout << "\n+-----------------+\n";
	}

	bool isTie()
	{
		for (int i = 0; i < 3; i++)
		{
			if (board[i][0] == Player::none || board[i][1] == Player::none || board[i][2] == Player::none)
				return false;
		}
		return true;
	}

	bool checkWin(Player player)
	{
		for (int i = 0; i < 3; i++)
		{
			
			if (board[i][0] == player && board[i][1] == player && board[i][2] == player)
				return true;

			
			if (board[0][i] == player && board[1][i] == player && board[2][i] == player)
				return true;
		}

		
		if (board[0][0] == player && board[1][1] == player && board[2][2] == player)
			return true;

		if (board[0][2] == player && board[1][1] == player && board[2][0] == player)
			return true;

		return false;
	}

	Move minimax()
	{
	
		int score = INT_MAX;
		Move move;

		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				if (board[i][j] == Player::none)
				{
					board[i][j] = Player::computer;

					int temp = maxSearch();

					if (temp < score)
					{
						score = temp;
						move.x = i;
						move.y = j;
					}
					board[i][j] = Player::none;
				}
			}
		}

		return move;
	}

	int maxSearch()
	{
		if (checkWin(Player::you)) { return 10; }
		else if (checkWin(Player::computer)) { return -10; }
		else if (isTie()) { return 0; }

		
		int score = INT_MIN;
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				if (board[i][j] == Player::none)
				{
					board[i][j] = Player::you;
					score = max(score, minSearch());
					board[i][j] = Player::none;
				}
			}
		}

		return score;
	}

	int minSearch()
	{
		if (checkWin(Player::you)) { return 10; }
		else if (checkWin(Player::computer)) { return -10; }
		else if (isTie()) { return 0; }

		
		int score = INT_MAX;
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				if (board[i][j] == Player::none)
				{
					board[i][j] = Player::computer;
					score = min(score, maxSearch());
					board[i][j] = Player::none;
				}
			}
		}

		return score;
	}

	void getYouMove()
	{
		bool fail = true;
		int x = -1, y = -1;

		do
		{

			cout << "Buoc di cua ban : ";
			char c;
			cin >> c;
			x = c - '0';
			cin >> c;
			y = c - '0';
			if (x > 2 || y > 2)
			{
				return getYouMove();
			}

			fail = board[x][y] != Player::none;

			cin.clear();
			

		} while (fail);

		board[x][y] = Player::you;
	}

	void play()
	{
		int turn = 0;
		bool exit = false;

		printBoard();
		cout << "Nhap buoc di cua ban : [hang,cot]. vi du : 02\n";

		do
		{
			
			if (turn == 0)
			{
				getYouMove();

				if (checkWin(Player::you))
				{
					cout << "You Win!!\n";
					exit = true;
				}
			}
			else
			{
				cout << "\nBuoc di cua may : ";

				Move computermove = minimax();
				cout << computermove.x << computermove.y << "\n";
				board[computermove.x][computermove.y] = Player::computer;

				if (checkWin(Player::computer))
				{
					cout << "You Lose!!\n";
					exit = true;
				}
			}

			if (isTie())
			{
				cout << "\n*** Tie!! ***\n";
				exit = true;
			}

			turn ^= 1;
			printBoard();

		} while (!exit);
	}
};

int main()
{
	cout << "* | Tic-tac-toe | *\n";
	Game tictactoe;
	tictactoe.play();

}