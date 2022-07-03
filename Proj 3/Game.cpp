// Game.cpp

#include "Game.h"
#include "utilities.h"
#include "Dungeon.h"
#include <iostream>
using namespace std;

// Implement these and other Game member functions you may have added.

Game::Game(int goblinSmellDistance)
{
	n_goblinSmellDistance = goblinSmellDistance;
	mini = new Dungeon(goblinSmellDistance);        //create a new mini for the game
	mini->addObject();           //add objects to the mini
	mini->addMonster();          //add monsters to the mini
	rogue = new Player(mini);   //add Player to the mini
	mini->addPlayer(rogue);
}

Game::~Game()
{
	delete mini;
}

void Game::play()
{
	Player* p = mini->getPlayer();
	char input;         //get input
	do {
		mini->display();
		input = getCharacter();
		switch (input) {
		case 'q':       //quit the game
			return;
		case 'g':       //pick up the Object or golden idol
			p->pickUp();
			break;
		case 'i':       //show inventory
		{
			p->openInventory();
			getCharacter(); //back to the Dungeon interface
			break;
		}
		case 'w':      //show inventory & wield weapons
		{
			p->openInventory();
			char inputWeapon = getCharacter();
			p->wieldWeapon(inputWeapon);
			break;
		}
		case 'r':   //show inventory & read scrolls
		{
			p->openInventory();
			char read = getCharacter();
			p->read(read);
			break;
		}
		case 'c':   //cheat
			p->cheat();
			break;
		case '>':   //go to the next level
		{
			if (mini->isStair(mini->getPlayer()->getRow(), mini->getPlayer()->getCol()) && mini->getLevel() != 4)
			{
				mini->deleteDungeon(mini);
				break;
			}
		}
		case ARROW_DOWN:    //4 moves
		case ARROW_LEFT:
		case ARROW_RIGHT:
		case ARROW_UP:
			p->playerMove(input);
		default:
			break;
		}
		for (list<Monster*>::iterator i = mini->getMonsterList().begin(); i != mini->getMonsterList().end(); i++)
			(*i)->doAction(mini); //Monster moves
	} while (!(p->win()));
}
// You will presumably add to this project other .h/.cpp files for the
// various classes of objects you need to play the game:  Player, monsters,
// weapons, etc.  You might have a separate .h/.cpp pair for each class
// (e.g., Player.h, Boegeyman.h, etc.), or you might put the class
// declarations for all actors in Actor.h, all game objects in GameObject.h,
// etc.