#include "Player.hpp"

Player::Player(const std::string& name){
	this->name = name;
	this->score = 0;
	this->wins = 0;

}

//returns players name as a string
std::string Player::getName() const{
	return this->name;
}

//returns players current score as a positive integer
unsigned int Player::getScore() const{
	return this->score;
}

//resets players score to 0
void Player::resetScore(){
	this->score = 0;
}

//increases players score by 1 point
void Player::increaseScore(){
	this->score++;
}

//returns number of wins player has
unsigned int Player::getWins() const{
	return this->wins;
}

//increases number of wins by 1
void Player::increaseWins(){
	this->wins++;
}


