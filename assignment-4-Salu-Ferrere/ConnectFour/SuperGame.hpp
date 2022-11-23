#ifndef SUPERGAME_HPP
#define SUPERGAME_HPP

#include "Game.hpp"

class SuperGame : public Game {

public:


    virtual bool playNextTurn(unsigned int column);

    virtual void checkWinner();


};

#endif /* end of include guard: SUPERGAME_HPP */
