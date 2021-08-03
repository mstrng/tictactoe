# include <stdio.h>

#define EMPTY '-'
#define CROSS 'X'
#define CIRCLE 'O'

#define WIN_NO 0
#define WIN_CROSS 1
#define WIN_CIRCLE 2
#define WIN_TIE 3

#define MAX_TURNS 9

struct Game
{
	char tablero[3][3]; //Array Representing the 3x3 squares of the game
	int win_state; //For checking and setting if the game has ended and how
	int turns; //Number of turns played
};

/*Renders the state of the game with printf, checking the squares from the struct*/
void render_game(struct Game game)
{
	printf("----------------------------------\n");
	for(int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			printf("[%c] ", game.tablero[j][i]);
		}
		printf("\n");
	}
	printf("----------------------------------\n");
	printf("\n");
}
/*Function for checking if the game should end or not, returns type of Win*/
int compute_logic(struct Game game, char type, int x, int y)
{
	//Vertical
	int counter = 0;
	for(int i = 0; i < 3; i++) {
		if (game.tablero[x][i] == type) {
			counter++;
		}
	}
	if (counter == 3) {
		if (type == CROSS) return WIN_CROSS;
		else return WIN_CIRCLE;
	}

	//Horizontal
	counter = 0;
	for(int i = 0; i < 3; i++) {
		if (game.tablero[i][y] == type) {
		counter++;
		}
	}
	if (counter == 3) {
		if (type == CROSS) return WIN_CROSS;
		else return WIN_CIRCLE;
	}
    //Diagonal 1
    counter = 0;
    int x_ini = x;
    int y_ini = y;
    while(x_ini > 0 && y_ini > 0) {
        x_ini--;
        y_ini--;
    }
    while(x_ini < 3 && y_ini < 3) {
        if (game.tablero[x_ini++][y_ini++] == type) {
            counter++;
        }
    }
    if (counter == 3) {
		if (type == CROSS) return WIN_CROSS;
		else return WIN_CIRCLE;
	}

    //Diagonal 2
    counter = 0;
    x_ini = x;
    y_ini = y;
    while(x_ini < 2 && y_ini > 0) {
        x_ini++;
        y_ini--;
    }
    while(x_ini >= 0 && y_ini < 3) {
        if (game.tablero[x_ini--][y_ini++] == type) {
            counter++;
        }
    }
    if (counter == 3) {
		if (type == CROSS) return WIN_CROSS;
		else return WIN_CIRCLE;
	}
    //Check Tie
	if (game.turns == MAX_TURNS) {
		return WIN_TIE;
	}
    //Otherwise, WIN_NO
    return WIN_NO;
}

int main()
{
	struct Game Current;
	for(int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			Current.tablero[i][j] = EMPTY;
		}
	}

	Current.win_state = WIN_NO;
	char player_current = CROSS;
	Current.turns = 0;	
	
	while (Current.win_state == WIN_NO) {
		render_game(Current);
		int player_X, player_Y = -1;
		int valid_position = 0;
		while (!valid_position) {

			printf("Player %c, enter row between 0 i 2: ", player_current);
			scanf("%d", &player_Y);
			printf("\n");

			printf("player %c, enter column between 0 i 2: ", player_current);
			scanf("%d", &player_X);
			printf("\n");

			if ((player_X >= 0 && player_X < 4) && ((player_Y >= 0 && player_Y < 4))) {
				if (Current.tablero[player_X][player_Y] == EMPTY) {
					valid_position = 1;
				}
			}

			if (valid_position) {

				Current.tablero[player_X][player_Y] = player_current;
				Current.turns++;
				Current.win_state = compute_logic(Current, player_current,
                player_X, player_Y);

				if (player_current == CROSS) {
					player_current = CIRCLE;
				}
				else {
				 player_current = CROSS;
				}

				printf("Turns Played: %d\n",Current.turns);
				//printf("estat: %d\n",Current.win_state);

			}

			else {
				printf("Invalid Position\n");
			}
		}
	}
	render_game(Current);
	switch(Current.win_state) {
		case WIN_CROSS :
			printf("Winner: X\n");
			break;
		case WIN_CIRCLE :
			printf("Winner: O\n");
			break;
		case WIN_TIE :
			printf("Tie\n");
			break;
	}
}






