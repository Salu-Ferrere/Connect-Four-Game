#include "SuperGame.hpp"
#include <vector>
using namespace std;


//same logic as Game::playNextTurn except gane is only finished if entire grid is filled up,
//winner is based on most connect 4's won in the game
bool SuperGame::playNextTurn(unsigned int column){
	if(gameStatus == GS_INVALID || gameStatus == GS_COMPLETE){
		return false;
	}
	bool result;
	Grid::Cell cell;
	if(nextPlayer() == player1){
		cell = Grid::GC_PLAYER_ONE;
	}
	if(nextPlayer() == player2){
		cell = Grid::GC_PLAYER_TWO;
	}
	result = this->grid->insertDisc(column, cell);
	if(result == true){
		if(NextPlayer == player1){
			this->NextPlayer = player2;
		}else if (NextPlayer == player2){
			this->NextPlayer = player1;
	}
	}
	//keep checking to see if more connect 4's are made after previous game pieces fall down
	checkWinner();
	while(connectFour == true){
		checkWinner();
	}

	//check for tie game, other wise award player with most points as the winner
	if(checkTie() == true){
		if(this->player1->getScore() == this->player2->getScore()){
			gameWinner = NULL;

		}
		if(this->player1->getScore() < this->player2->getScore()){
			this->gameWinner = this->player2;
		} else{
			this->gameWinner = this->player1;
		}
		if(gameWinner != NULL){
			gameWinner->increaseWins();
		}
		this->gameStatus = GS_COMPLETE;
	}
	return result;
}


//for(int i = 0; i < this->grid->rowCount(); i++){
//	for(int j = 0; j < this->grid->columnCount(); j++){
//		cout<<this->grid->cellAt(i,j);
//
//	}
//	cout<<" "<<endl;
//}
//cout<<" "<<endl;



//after each turn is played, checkWinner is called to see if a connect 4 has been made, and a player has won a point
void SuperGame::checkWinner(){

	connectFour = false;
	horizontal = false;
	vertical = false;
	diagonal = false;
	diagonalop = false;
	Player* player;
	int Hi, Hj, Vi, Vj, Di, Dj, DOi, DOj;


	//check for all possible connect 4's keeping track of their position
	for(unsigned int i = 0; i < this->grid->rowCount(); i++){
		for(unsigned int j = 0; j < this->grid->columnCount(); j++){
			if(checkHorizontal(i,j) != NULL && horizontal == false){
				player = checkHorizontal(i,j);
				Hi = i;
				Hj = j;
				horizontal = true;
				connectFour = true;

			}
			if(checkVertical(i,j) != NULL && vertical == false){
				player = checkVertical(i,j);
				vertical = true;
				Vi = i;
				Vj = j;
				connectFour = true;

			}
			if(checkDiagonal(i,j) != NULL && diagonal == false){
				player = checkDiagonal(i,j);
				diagonal = true;
			    Di = i;
			    Dj = j;
			    connectFour = true;

		    }
			if(checkDiagonalOp(i,j) != NULL && diagonalop == false){
				player = checkDiagonalOp(i,j);
				diagonalop = true;
				DOi = i;
				DOj = j;
				connectFour = true;


		}
		}
	}
	//remove all tiles that are part of connect 4's
	if(horizontal == true){
		grid->removeHorizontal(Hi,Hj);
	}
	if(vertical == true){
		grid->removeVertical(Vi,Vj);
	}
	if(diagonal == true){
		grid->removeDiagonal(Di,Dj);
	}
	if(diagonalop == true){
		grid->removeDiagonalOp(DOi,DOj);
	}


	//drop all above tiles down into holes created by removed connect 4's
	if (connectFour == true){
		grid->cleanGrid();
		player->increaseScore();
	}

	return;
}

