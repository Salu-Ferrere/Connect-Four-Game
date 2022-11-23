#include "Game.hpp"

    //initialise variables to NULL, and gamestatus to invalid
    Game::Game(){
    	this->gameStatus = GS_INVALID;
    	this->player1 = NULL;
    	this->player2 = NULL;
    	this->grid = NULL;
    	this->gameWinner = NULL;
    	this->NextPlayer = NULL;
    	this->connectFour = false;
        this->vertical = false;
        this->horizontal = false;
        this->diagonal = false;
        this->diagonalop = false;
 }

    //sets game grid, returns if grid is a null pointer, sets game status to in progress if players have been assigned
    void Game::setGrid(Grid* grid){
    	if(grid == NULL){
    		return;
    	}
    	delete this->grid;
    	this->grid = grid;
    	if(this->player1 != NULL && this->player2 != NULL){
    		this->gameStatus = GS_IN_PROGRESS;
    	}
    }

    //sets player 1, returns the function if player is a null pointer or is the same as player 2
    // if assigned changes game status to in progress if player 2 and grid have already been set
    void Game::setPlayerOne(Player* player){
    	if(player == NULL || player == player2){
    		return;
    	}
    	this->player1 = player;
    	this->NextPlayer = player;
    	if(player2 != NULL && grid != NULL){
    		this->gameStatus = GS_IN_PROGRESS;
    	}
    	return;
    }

    //sets player 2, returns the function if player is a null pointer or is the same as player 1
    // if assigned changes game status to in progress if player 1 and grid have already been set
    void Game::setPlayerTwo(Player* player){
    	if(player == NULL || player == player1){
    		return;
    	}
    	this->player2 = player;
    	if(player1 != NULL && grid != NULL){
    		this->gameStatus = GS_IN_PROGRESS;
    	}
    }

    //resets players scores, the grid and game status back to in progress, if game status is invalid, return
    void Game::restart(){
    	if(this->gameStatus == GS_INVALID){
    		return;
    	}
    	this->gameStatus = GS_IN_PROGRESS;
    	this->player1->resetScore();
    	this->player2->resetScore();
    	this->grid->reset();
    	this->NextPlayer = player1;
    	this->gameWinner = NULL;
    }

    //returns game status
    Game::Status Game::status() const{
    	return this->gameStatus;
    }

    //returns game winner, returns null if a draw or game still in progress
    const Player* Game::winner() const{
    	if(gameWinner == NULL || this->gameStatus == GS_IN_PROGRESS){
    		return NULL;
    	}
    	return gameWinner;
    }

    //returns a pointer to the player whose next turn it is only if game is in progress
    const Player* Game::nextPlayer() const{
    	if(gameStatus == GS_IN_PROGRESS){
    		return this->NextPlayer;
    	}
    	return NULL;
    }

    //makes the next turn by placing a piece in the entered column of whoever players turn it is next,
    //checks to see if there is a winner or a stale mate after turn has been made and assigns the next player
    bool Game::playNextTurn(unsigned int column){
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
    	checkWinner();
    		if(this->gameWinner != NULL){
    			this->gameStatus = GS_COMPLETE;
    			gameWinner->increaseScore();
    			gameWinner->increaseWins();
    		}

    	if(checkTie() == true){
    		this->gameStatus = GS_COMPLETE;
    	}
    	return result;
    }

    // checks to see if there is a horizontal connect 4
    Player* Game::checkHorizontal(unsigned int r, unsigned int c){
    	if(c+3 >= this->grid->columnCount()){
    		return NULL;
    	}
    	if(this->grid->cellAt(r,c) == Grid::GC_PLAYER_ONE && this->grid->cellAt(r,c+1) == Grid::GC_PLAYER_ONE &&
    			this->grid->cellAt(r,c+2) == Grid::GC_PLAYER_ONE && this->grid->cellAt(r,c+3) == Grid::GC_PLAYER_ONE){
    		return this->player1;
    	}
    	if(this->grid->cellAt(r,c) == Grid::GC_PLAYER_TWO && this->grid->cellAt(r,c+1) == Grid::GC_PLAYER_TWO &&
    			this->grid->cellAt(r,c+2) == Grid::GC_PLAYER_TWO && this->grid->cellAt(r,c+3) == Grid::GC_PLAYER_TWO){
    		return this->player2;
    	}
    	return NULL;
    }

    //checks to see if there is a vertical connect 4
    Player* Game::checkVertical(unsigned int r, unsigned int c){
    	if(r+3 >= this->grid->rowCount()){
    		return NULL;
    	}
    	if(this->grid->cellAt(r,c) == Grid::GC_PLAYER_ONE && this->grid->cellAt(r+1,c) == Grid::GC_PLAYER_ONE &&
    			this->grid->cellAt(r+2,c) == Grid::GC_PLAYER_ONE && this->grid->cellAt(r+3,c) == Grid::GC_PLAYER_ONE){
    		return this->player1;
    	}
    	if(this->grid->cellAt(r,c) == Grid::GC_PLAYER_TWO && this->grid->cellAt(r+1,c) == Grid::GC_PLAYER_TWO &&
    			this->grid->cellAt(r+2,c) == Grid::GC_PLAYER_TWO && this->grid->cellAt(r+3,c) == Grid::GC_PLAYER_TWO){
    		return this->player2;
    	}
    	return NULL;
    }


    //checks to see if there is a diagonal connect 4
    Player* Game::checkDiagonal(unsigned int r, unsigned int c){
    	if(r+3 >= this->grid->rowCount() || c+3 >= this->grid->columnCount()){
    		return NULL;
    	}
    	if(this->grid->cellAt(r,c) == Grid::GC_PLAYER_ONE && this->grid->cellAt(r+1,c+1) == Grid::GC_PLAYER_ONE &&
    			this->grid->cellAt(r+2,c+2) == Grid::GC_PLAYER_ONE && this->grid->cellAt(r+3,c+3) == Grid::GC_PLAYER_ONE){
    		return this->player1;
    	}
    	if(this->grid->cellAt(r,c) == Grid::GC_PLAYER_TWO && this->grid->cellAt(r+1,c+1) == Grid::GC_PLAYER_TWO &&
    			this->grid->cellAt(r+2,c+2) == Grid::GC_PLAYER_TWO && this->grid->cellAt(r+3,c+3) == Grid::GC_PLAYER_TWO){
    		return this->player2;
    	}
    	return NULL;
    }

    //checks to see if there is an opposite diagonal connect 4
    Player* Game::checkDiagonalOp(unsigned int r, unsigned int c){
    	if(r+3 >= this->grid->rowCount() || c-3 < 0){
    		return NULL;
    	}
    	if(this->grid->cellAt(r,c) == Grid::GC_PLAYER_ONE && this->grid->cellAt(r+1,c-1) == Grid::GC_PLAYER_ONE &&
    			this->grid->cellAt(r+2,c-2) == Grid::GC_PLAYER_ONE && this->grid->cellAt(r+3,c-3) == Grid::GC_PLAYER_ONE){
    		return this->player1;
    	}
    	if(this->grid->cellAt(r,c) == Grid::GC_PLAYER_TWO && this->grid->cellAt(r+1,c-1) == Grid::GC_PLAYER_TWO &&
    			this->grid->cellAt(r+2,c-2) == Grid::GC_PLAYER_TWO && this->grid->cellAt(r+3,c-3) == Grid::GC_PLAYER_TWO){
    		return this->player2;
    	}
    	return NULL;

    }

   // runs through grid checking to see if there is a connect 4 of any kind
    void Game::checkWinner(){
    	for(unsigned int i = 0; i < this->grid->rowCount(); i++){
    		for(unsigned int j = 0; j < this->grid->columnCount(); j++){
    			if(checkHorizontal(i,j) != NULL){
    				this->gameWinner = checkHorizontal(i,j);
    				return;
    			}
    			if(checkVertical(i,j) != NULL){
    				this->gameWinner = checkVertical(i,j);
    				return;
    			}
    			if(checkDiagonal(i,j) != NULL){
    				this->gameWinner = checkDiagonal(i,j);
    				return;
    			}
    			if(checkDiagonalOp(i,j) != NULL){
    				this->gameWinner = checkDiagonalOp(i,j);
    				return;
    			}

    		}
    	}
    	return;
    }

    //runs through top row of grid to see if there is a tie
   bool Game::checkTie(){
	   for(unsigned int i = 0; i < this->grid->columnCount(); i++){
		   if(this->grid->cellAt(0,i) == Grid::GC_EMPTY){
			   return false;
		   }
	   }
	   return true;
   }



   // destructor deletes game grid
    Game::~Game(){
    	delete this->grid;

    }
