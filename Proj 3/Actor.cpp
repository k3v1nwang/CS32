#include "Actor.h"
#include "Dungeon.h"
#include "utilities.h"
#include <iostream>

using namespace std;

///////////////////////////////
//Actor Class Implementations//
//////////////////////////////

//Actor constructor and destructor
Actor::Actor(Dungeon* dungeon, int r, int c)
{
	m_dungeon = dungeon;
	m_row = r;
	m_col = c;
}

Actor::Actor(Dungeon* dungeon, int HP, int maxHP, int arm, int str, int dex, int sleep, string name)
{
	m_dungeon = dungeon;
	m_HP = HP;
	m_max_HP = maxHP;
	m_arm = arm;
	m_str = str;
	m_dex = dex;
	m_sleep = sleep;
	m_death = false;
	m_name = name;
}

Actor::~Actor() { delete m_weapon; }

//Actor accessors
bool Actor::notAlive() const { return m_death; }
int Actor::getCol() const { return m_col; }
int Actor::getRow() const { return m_row; }
int Actor::getHP() const { return m_HP; }
int Actor::getArm() const { return m_arm; }
int Actor::getStr() const { return m_str; }
int Actor::getDex() const { return m_dex; }
Weapon* Actor::getWeapon() const { return m_weapon; }
string Actor::getName() const { return m_name; }
int Actor::getSleep() const { return m_sleep; }
Dungeon* Actor::getDungeon() const { return m_dungeon; }
int Actor::getMaxHp() const { return m_max_HP; }

//change member value functions

void Actor::decSleep(int a) { m_sleep = m_sleep - a; }
void Actor::incStr(int a) { m_str = m_str + a; }
void Actor::incHP(int a)
{
	if (m_HP <= m_max_HP - a)
		m_HP = m_HP + a;
	if (m_HP > m_max_HP - a && m_HP < m_max_HP)
		m_HP = m_max_HP;
	if (m_HP > m_max_HP)
		return;
}
void Actor::incDex(int a) { m_dex = m_dex + a; }
void Actor::incArm(int a) { m_arm = m_arm + a; }
void Actor::incSleep(int a) { m_sleep = m_sleep + a; }
void Actor::incMaxHP(int a) { m_max_HP = m_max_HP + a; }
bool Actor::setWeapon(Weapon* Weapon)
{
	m_weapon = Weapon;
	return true;
}

bool Actor::setPos(int r, int c)
{
	m_row = r;
	m_col = c;
	return true;
}

//attack function
void Actor::attack(Actor* attacker, Actor* target)
{
	int attackStat = attacker->m_dex + attacker->m_weapon->getDexBonus();
	int defenceStat = target->m_dex + target->m_arm;
	int a = randInt(attackStat);
	int b = randInt(defenceStat);
	if (a >= b)
		//whether it can attack or not
	{
		int damage = randInt(attacker->m_str + attacker->m_weapon->getStrAmt());
		target->m_HP = target->m_HP - damage;   //generate the damage amount
		if (target->m_HP > 0 && attacker->getWeapon()->getName() != "magic fangs of sleep")
			//if the target is still alive && attacker's Weapon is not magic fang
		{
			getDungeon()->actionStrings().push_back("the " + attacker->getName() + " " + attacker->getWeapon()->getAction() + " " + attacker->getWeapon()->getName() + " at " + target->getName() + " and hits.");
			//store the string value
		}
		else
		{
			if (target->m_HP <= 0)    //if the target is dead
			{
				target->m_death = true;
				Monster* ptr = dynamic_cast<Monster*>(target);
				if (ptr != nullptr)
				{
					ptr->monsterDrop(target->getDungeon(), ptr);
					getDungeon()->actionStrings().push_back("the " + attacker->getName() + " " + attacker->getWeapon()->getAction() + " " + attacker->getWeapon()->getName() + " at " + target->getName() + " dealing a final blow.");    //store the string value
				}
				else
				{
					Player* ptr = dynamic_cast<Player*>(target);
					if (ptr != nullptr)
					{
						getDungeon()->actionStrings().push_back("the " + attacker->getName() + " " + attacker->getWeapon()->getAction() + " " + attacker->getWeapon()->getName() + " at " + target->getName() + " dealing a final blow.");    //the Player is dead
						getDungeon()->actionStrings().push_back("Press q to exit game.");   //cout string
					}
				}
			}
			if (target->m_HP > 0 && attacker->getWeapon()->getName() == "magic fangs of sleep")
				//is the target is still alive and the attacker's Weapon is magic fang
			{
				bool sleep = trueWithProbability(1.0 / 5);
				if (sleep && target->getSleep() == 0)
				{
					target->incSleep(randInt(5) + 2);
					getDungeon()->actionStrings().push_back("the " + attacker->getName() + " " + attacker->getWeapon()->getAction() + " magic fangs at " + target->getName() + " and hits, putting " + target->getName() + " to sleep.");
					//store the value
				}
				else if (sleep && target->getSleep() > 0) //when the target is already asleep
				{
					int sleepTime = max(target->getSleep(), randInt(5) + 2);    //generate the sleeptime
					target->incSleep(sleepTime - target->getSleep());
					getDungeon()->actionStrings().push_back("the " + attacker->getName() + " " + attacker->getWeapon()->getAction() + " magic fangs at " + target->getName() + " and hits, putting " + target->getName() + " to sleep.");
					//store the string value
				}
				else if (!sleep)
				{
					getDungeon()->actionStrings().push_back("the " + attacker->getName() + " " + attacker->getWeapon()->getAction() + " magic fangs at " + target->getName() + " and hits.");
					//store the string value
				}
			}
		}
	}
	else if (a < b && attacker->getWeapon()->getName() != "magic fangs of sleep")
	{
		getDungeon()->actionStrings().push_back("the " + attacker->getName() + " " + attacker->getWeapon()->getAction() + " " + attacker->getWeapon()->getName() + " at " + target->getName() + " and misses.");
	}
	else if (a < b && attacker->getWeapon()->getName() == "magic fangs of sleep")
	{
		getDungeon()->actionStrings().push_back("the " + attacker->getName() + " " + attacker->getWeapon()->getAction() + " magic fangs at " + target->getName() + " and misses.");
	}
}
//setGrid after move
void setGrid(int r, int c, Actor* a)
{
	if (a->getName() == "Player")
		a->getDungeon()->setGrid(r, c, '@');
	else if (a->getName() == "Snakewoman")
		a->getDungeon()->setGrid(r, c, 'S');
	else if (a->getName() == "Bogeyman")
		a->getDungeon()->setGrid(r, c, 'B');
	else if (a->getName() == "Snakewoman")
		a->getDungeon()->setGrid(r, c, 'S');
	else if (a->getName() == "Dragon")
		a->getDungeon()->setGrid(r, c, 'D');
}
//move function

void Actor::move(char dir)
{
	switch (dir) {
	case ARROW_LEFT:
		if (m_dungeon->movable(m_row, m_col - 1))
		{
			m_dungeon->setGrid(m_row, m_col, ' ');
			m_col--;
			//setGrid(m_row, m_col-1, this);
		}
		break;
	case ARROW_RIGHT:
		if (m_dungeon->movable(m_row, m_col + 1))
		{
			m_dungeon->setGrid(m_row, m_col, ' ');
			m_col++;
			//setGrid(m_row, m_col+1, this);
		}
		break;
	case ARROW_DOWN:
		if (m_dungeon->movable(m_row + 1, m_col))
		{
			m_dungeon->setGrid(m_row, m_col, ' ');
			m_row++;
			//setGrid(m_row+1, m_col, this);
		}
		break;
	case ARROW_UP:
		if (m_dungeon->movable(m_row - 1, m_col))
		{
			m_dungeon->setGrid(m_row, m_col, ' ');
			m_row--;
			//setGrid(m_row-1, m_col, this);
		}
		break;
	default:
		break;
	}
	this->getDungeon()->display();
}

////////////////////////////////
//Player Class Implementations//
///////////////////////////////

//Player constructor and destructor

Player::Player(Dungeon* dungeon) :Actor(dungeon, 20, 20, 2, 2, 2, 0, "Player")
{
	Weapon* initialWeapon = new ShortSword();
	Actor::setWeapon(initialWeapon);
	inventory.push_back(initialWeapon);
	m_win = false;
}

Player::~Player()
{
	for (list<Object*>::iterator i = inventory.begin(); i != inventory.end(); i++)
		delete* i;
}

//Player accessors

bool Player::win() const { return m_win; }

list<Object*> Player::getInventory() const { return inventory; }

//Player move function
void Player::playerMove(char dir)
{
	if (notAlive()) //ptr if the Player is dead
		return;

	if (getSleep() > 0) //ptr if the Player is asleep
	{
		decSleep(1);
		return;
	}
	heal();      //random regainHp for the Player
	int row = getRow();
	int col = getCol();
	Dungeon* now = getDungeon();
	switch (dir) {
	case ARROW_LEFT:
		if (now->isMonster(getRow(), getCol() - 1))
		{
			Monster* a{};
			a = now->getMonster(getRow(), getCol() - 1, a);
			attack(this, a);    //attack if the Monster is attackable
		}
		else
			Actor::move(dir);   //otherwise just move
		break;
	case ARROW_RIGHT:
		if (now->isMonster(getRow(), getCol() + 1))
		{
			Monster* b{};
			b = now->getMonster(getRow(), getCol() + 1, b);
			attack(this, b);
		}
		else
			Actor::move(dir);
		break;
	case ARROW_UP:
		if (now->isMonster(getRow() - 1, getCol()))
		{
			Monster* c = nullptr;
			c = now->getMonster(getRow() - 1, getCol(), c);
			attack(this, c);
		}
		else
			Actor::move(dir);
		break;
	case ARROW_DOWN:
		if (now->isMonster(getRow() + 1, getCol()))
		{
			Monster* d = nullptr;
			d = now->getMonster(getRow() + 1, getCol(), d);
			attack(this, d);
		}
		else
			Actor::move(dir);
		break;
	default:
		break;
	}
}

//show inventory
void Player::openInventory()
{
	if (notAlive())
		return;
	if (getSleep() > 0)
	{
		decSleep(1);
		return;
	}
	clearScreen();
	cout << "Inventory:" << endl;
	char symbol = 'a';
	for (list<Object*>::iterator i = inventory.begin(); i != inventory.end(); i++, symbol++)
		cout << " " << symbol << ". " << (*i)->getName() << endl;   //display all objects in the inventory
}

//ptr objects
bool Player::checkObject()
{
	list<Object*> ptr = getDungeon()->getObjectList();
	for (list<Object*>::iterator i = ptr.begin(); i != ptr.end(); i++)
	{
		int r = (*i)->getRow();
		int c = (*i)->getCol();
		if (r == getRow() && c == getCol())
			return true;
	}
	return false;
}

//pickup objects
void Player::pickUp()
{
	if (getDungeon()->getGoldenIdol() != nullptr && getRow() == getDungeon()->getGoldenIdol()->getRow() && getCol() == getDungeon()->getGoldenIdol()->getCol())
	{
		m_win = true;
		cout << "You pick up the golden idol" << endl
			<< "Congratulations, you won!" << endl;
		return;
	}               //if the Object going to be picked up is golden idol, then win

	if (!checkObject())
	{
		return;
	}               //if there is no Object to be picked up
	else
	{
		if (inventory.size() > 25)   //if the bag is full
		{
			getDungeon()->actionStrings().push_back("Your knapsack is full; you can't pick that up.");
			return;
		}
		for (list<Object*>::iterator i = getDungeon()->getObjectList().begin(); i != getDungeon()->getObjectList().end(); i++)
		{
			if (getRow() == (*i)->getRow() && getCol() == (*i)->getCol())
			{
				inventory.push_back(*i);
				Weapon* ptr = dynamic_cast<Weapon*>(*i);
				if (ptr != nullptr)   //if the Object is a Weapon
				{
					if ((*i)->getName() == "short sword")
						getDungeon()->actionStrings().push_back("You pick up a short sword");
					else if ((*i)->getName() == "long sword")
						getDungeon()->actionStrings().push_back("You pick up a long sword");
					else if ((*i)->getName() == "Mace")
						getDungeon()->actionStrings().push_back("You pick up a Mace");
					else if ((*i)->getName() == "magic fangs of sleep")
						getDungeon()->actionStrings().push_back("You pick up a magic fang of sleep");
					else if ((*i)->getName() == "magic axe")
						getDungeon()->actionStrings().push_back("You pick up a magic axe");
					getDungeon()->getObjectList().erase(i);
					break;
				}

				Scroll* check2 = dynamic_cast<Scroll*>(*i);
				if (check2 != nullptr)  //if the Object is a Scroll
				{
					if ((*i)->getName() == "scroll of strength")
						getDungeon()->actionStrings().push_back("You pick up a Scroll called scroll of strength");
					else if ((*i)->getName() == "Scroll of enhance armor")
						getDungeon()->actionStrings().push_back("You pick up a Scroll called Scroll of enhance armor");
					else if ((*i)->getName() == "Scroll of enhance health")
						getDungeon()->actionStrings().push_back("You pick up a Scroll called Scroll of enhance health");
					else if ((*i)->getName() == "Scroll of enhance dexterity")
						getDungeon()->actionStrings().push_back("You pick up a Scroll called Scroll of enhance dexterity");
					else if ((*i)->getName() == "Scroll of teleportation")
						getDungeon()->actionStrings().push_back("You pick up a Scroll called Scroll of teleportation");
					getDungeon()->getObjectList().erase(i);
					break;
				}
			}
		}
	}
}

//read function
void Player::read(char a)
{
	int itemID = a - 'a';
	int w = 0;
	for (list<Object*>::iterator i = inventory.begin(); i != inventory.end(); i++)
	{
		if (w > itemID)
			break;
		if (w == itemID)
		{
			Scroll* ptr = dynamic_cast<Scroll*>(*i);//if the Object is a Scroll
			if (ptr != nullptr)
			{
				string s_name = (*i)->getName();
				if (s_name == "scroll of strength")
					Actor::incStr(randInt(3) + 1);
				else if (s_name == "Scroll of enhance armor")
					Actor::incArm(randInt(3) + 1);
				else if (s_name == "Scroll of enhance health")
					Actor::incHP(randInt(6) + 3);
				else if (s_name == "Scroll of enhance dexterity")
					Actor::incDex(1);
				else if (s_name == "Scroll of teleportation")
				{
					Dungeon* now = getDungeon();
					int t_r, t_c;
					do {
						t_r = randInt(18);
						t_c = randInt(70);  //teleportation of the Player
					} while (now->getGrid(t_r, t_c) == '@' || now->getGrid(t_r, t_c) == '#' || now->getGrid(t_r, t_c) == 'B' || now->getGrid(t_r, t_c) == 'S' || now->getGrid(t_r, t_c) == 'D' || now->getGrid(t_r, t_c) == 'G');
					this->getDungeon()->setGrid(this->getRow(), this->getCol(), ' ');
					this->setPos(t_r, t_c);
				}
				getDungeon()->actionStrings().push_back("You read the Scroll called " + (*i)->getName());
				getDungeon()->actionStrings().push_back((*i)->getAction());
				inventory.erase(i); //after reading, delete the Scroll
				break;
			}
			else    //if the Object is not a Scroll
			{
				getDungeon()->actionStrings().push_back("You can't read a " + (*i)->getName());
				break;
			}
		}
		else
			w++;
	}
}

//wield Weapon function
void Player::wieldWeapon(char a)
{
	int itemID = a - 'a';
	int w = 0;
	for (list<Object*>::iterator i = inventory.begin(); i != inventory.end(); i++)
	{
		if (w > itemID)
			break;
		if (w == itemID)
		{
			Weapon* ptr = dynamic_cast<Weapon*>(*i);
			if (ptr != nullptr) //if the Object is a Weapon
			{
				string w_name = (*i)->getName();
				if (w_name == "short sword")
					Actor::setWeapon(new ShortSword());
				else if (w_name == "long sword")
					Actor::setWeapon(new LongSword());
				else if (w_name == "Mace")
					Actor::setWeapon(new Mace());
				else if (w_name == "magic axe")
					Actor::setWeapon(new MagicAxe());
				else if (w_name == "magic fangs of sleep")
					Actor::setWeapon(new MagicFang());
				getDungeon()->actionStrings().push_back("You are wielding " + (*i)->getName());
				break;
			}
			else    //if the Object is not a Weapon
			{
				getDungeon()->actionStrings().push_back("You can't wield " + (*i)->getName());
				break;
			}
		}
		else
			w++;
	}
}

//cheat function
void Player::cheat()
{
	Actor::incHP(50 - getHP());
	Actor::incMaxHP(50 - getMaxHp());
	Actor::incStr(9 - getStr());
}

//regainHp function
void Player::heal()
{
	bool healChance = trueWithProbability(1.0 / 10);
	if (healChance && getHP() < getMaxHp())
	{
		Actor::incHP(1);
	}
}

/////////////////////////////////
//Monster Class Implementations//
////////////////////////////////

//Monster class constructor
Monster::Monster(Dungeon* m_dunge, int m_HP, int m_maxHP, int m_arm, int m_str, int m_dex, int m_sleep, string m_name) :Actor(m_dunge, m_HP, m_maxHP, m_arm, m_str, m_dex, m_sleep, m_name) {}

//Monster smell function
bool Monster::smell(Dungeon* dungeon, int r)
{
	int s_r = getRow();
	int s_c = getCol();
	int getRow = dungeon->getPlayer()->getRow();
	int getCol = dungeon->getPlayer()->getCol();
	int c_r = max(getRow, s_r);
	int d_r = min(getRow, s_r);
	int c_c = max(getCol, s_c);
	int d_c = min(getCol, s_c);
	int n_moves_to_player = c_r - d_r + (c_c - d_c);
	if (n_moves_to_player <= r)
		return true;
	return false;
}

//Monster dropItem function
void Monster::monsterDrop(Dungeon* dungeon, Monster* a)
{
	int r = a->getRow();
	int c = a->getCol();
	if (a->notAlive() == true && dungeon->getGrid(r, c) != '(' && dungeon->getGrid(r, c) != '?' && dungeon->getGrid(r, c) != '>' && dungeon->getGrid(r, c) != '@')
	{
		if (a->getName() == "Snakewoman")   //if it is a Snakewomen
		{
			bool dropFang = trueWithProbability(1.0 / 3);
			if (dropFang)
			{
				dungeon->getObjectList().push_back(new MagicFang(r, c));
			}
		}
		else if (a->getName() == "Bogeyman") //if it is a Bogeyman
		{
			bool dropMagicAxe = trueWithProbability(1.0 / 10);
			if (dropMagicAxe)
			{
				dungeon->getObjectList().push_back(new MagicAxe(r, c));
			}
		}
		else if (a->getName() == "Dragon")    //if it is a Dragon
		{
			int p_scroll = randInt(5);  //randomly generate a Scroll
			switch (p_scroll) {
			case 0:
				dungeon->getObjectList().push_back(new strScroll(r, c));
				break;
			case 1:
				dungeon->getObjectList().push_back(new armScroll(r, c));
				break;
			case 2:
				dungeon->getObjectList().push_back(new hpScroll(r, c));
				break;
			case 3:
				dungeon->getObjectList().push_back(new dexScroll(r, c));
				break;
			case 4:
				dungeon->getObjectList().push_back(new tpScroll(r, c));
				break;
			default:
				break;
			}
		}
		else if (a->getName() == "Goblin")  //if it is a Goblin
		{
			bool goblinDrop = trueWithProbability(1.0 / 3);
			if (goblinDrop)
			{
				bool dropAxe = trueWithProbability(0.5);
				if (dropAxe)
					dungeon->getObjectList().push_back(new MagicAxe(r, c));
				else
					dungeon->getObjectList().push_back(new MagicFang(r, c));
			}
		}
	}
}

char Monster::chooseDirection(Dungeon* dungeon, int r, int c)
{
	int getRow = r;
	int getCol = c;
	int d_row = dungeon->getPlayer()->getRow() - r;
	int d_col = dungeon->getPlayer()->getCol() - c;
	char dir = '\0';
	if (d_row > 0 && d_col >= 0)
	{
		if (d_row >= d_col && d_col != 0)
		{
			if (!dungeon->movable(getRow, getCol + 1))
				dir = ARROW_DOWN;
			else
				dir = ARROW_RIGHT;
		}
		else
		{
			if (!dungeon->movable(getRow + 1, getCol))
				dir = ARROW_RIGHT;
			else
				dir = ARROW_DOWN;
		}
	}
	else if (d_row >= 0 && d_col < 0)
	{
		if (d_row >= (-d_col) || d_row == 0)
		{
			if (!dungeon->movable(getRow, getCol - 1))
				dir = ARROW_DOWN;
			else
				dir = ARROW_LEFT;
		}
		else
		{
			if (!dungeon->movable(getRow + 1, getCol))
				dir = ARROW_LEFT;
			else
				dir = ARROW_DOWN;
		}
	}
	else if (d_row < 0 && d_col <= 0)
	{
		if ((-d_row) >= (-d_col) && d_col != 0)
		{
			if (!dungeon->movable(getRow, getCol - 1))
				dir = ARROW_UP;
			else
				dir = ARROW_LEFT;
		}
		else
		{
			if (!dungeon->movable(getRow - 1, getCol))
				dir = ARROW_LEFT;
			else
				dir = ARROW_UP;
		}
	}
	else if (d_row <= 0 && d_col > 0)
	{
		if ((-d_row) >= d_col || d_row == 0)
		{
			if (!dungeon->movable(getRow, getCol + 1))
				dir = ARROW_UP;
			else
				dir = ARROW_RIGHT;
		}
		else
		{
			if (!dungeon->movable(getRow - 1, getCol))
				dir = ARROW_RIGHT;
			else
				dir = ARROW_UP;
		}
	}
	return dir;
}

///////////////////////////////////
//Bogeyman Class Implementations//
//////////////////////////////////

//Bogeyman constructor
Bogeyman::Bogeyman(Dungeon* dungeon) :Monster(dungeon, randInt(6) + 5, randInt(6) + 5, 2, randInt(1) + 2, randInt(1) + 2, 0, "Bogeyman")
{
	Weapon* bogeyWep = new ShortSword();
	Actor::setWeapon(bogeyWep);
}

//Bogeyman doAction function
void Bogeyman::doAction(Dungeon* dungeon)
{
	if (getSleep() > 0) //if Bogeyman is asleep
	{
		decSleep(1);
		return;
	}

	if (notAlive() || dungeon->getPlayer()->notAlive())   //if Bogeyman is dead
	{
		return;
	}
	if (Monster::smell(dungeon, 5)) //ptr if the monser can move or not
	{
		int row = getRow();
		int col = getCol();
		char dir = Monster::chooseDirection(dungeon, row, col);
		//choose the direction to move
		switch (dir) {
		case ARROW_LEFT:
			if (dungeon->isPlayer(row, col - 1) || dungeon->isPlayer(row + 1, col) || dungeon->isPlayer(row - 1, col) || dungeon->isPlayer(row, col + 1))
			{
				attack(this, dungeon->getPlayer());   //attack
			}
			else
			{
				Actor::move(dir);   //move
			}
			break;
		case ARROW_RIGHT:
			if (dungeon->isPlayer(row, col - 1) || dungeon->isPlayer(row + 1, col) || dungeon->isPlayer(row - 1, col) || dungeon->isPlayer(row, col + 1))
			{
				attack(this, dungeon->getPlayer());
			}
			else
			{
				Actor::move(dir);
			}
			break;
		case ARROW_UP:
			if (dungeon->isPlayer(row, col - 1) || dungeon->isPlayer(row + 1, col) || dungeon->isPlayer(row - 1, col) || dungeon->isPlayer(row, col + 1))
			{
				attack(this, dungeon->getPlayer());
			}
			else
			{
				Actor::move(dir);
			}
			break;
		case ARROW_DOWN:
			if (dungeon->isPlayer(row, col - 1) || dungeon->isPlayer(row + 1, col) || dungeon->isPlayer(row - 1, col) || dungeon->isPlayer(row, col + 1))
			{
				attack(this, dungeon->getPlayer());
			}
			else
			{
				Actor::move(dir);
			}
			break;
		default:
			break;
		}
	}
}

////////////////////////////////////
//Snakewoman Class Implementations//
///////////////////////////////////

//Snakewomen constructor
Snakewomen::Snakewomen(Dungeon* dungeon) :Monster(dungeon, randInt(4) + 3, randInt(4) + 3, 3, 2, 3, 0, "Snakewoman")
{
	Weapon* snakeWep = new MagicFang();
	Actor::setWeapon(snakeWep);
}

//Snakewomen doAction function
void Snakewomen::doAction(Dungeon* dungeon)
{
	if (getSleep() > 0)
	{
		decSleep(1);
		return;
	}

	if (notAlive() || dungeon->getPlayer()->notAlive())
	{
		return;
	}
	if (Monster::smell(dungeon, 3)) //the only difference between this and Bogeyman doAction function
	{
		int row = getRow();
		int col = getCol();
		char dir = Monster::chooseDirection(dungeon, row, col);
		switch (dir) {
		case ARROW_LEFT:
			if (dungeon->isPlayer(row, col - 1) || dungeon->isPlayer(row + 1, col) || dungeon->isPlayer(row - 1, col) || dungeon->isPlayer(row, col + 1))
			{
				attack(this, dungeon->getPlayer());
			}
			else
			{
				Actor::move(dir);
			}
			break;
		case ARROW_RIGHT:
			if (dungeon->isPlayer(row, col - 1) || dungeon->isPlayer(row + 1, col) || dungeon->isPlayer(row - 1, col) || dungeon->isPlayer(row, col + 1))
			{
				attack(this, dungeon->getPlayer());
			}
			else
			{
				Actor::move(dir);
			}
			break;
		case ARROW_UP:
			if (dungeon->isPlayer(row, col - 1) || dungeon->isPlayer(row + 1, col) || dungeon->isPlayer(row - 1, col) || dungeon->isPlayer(row, col + 1))
			{
				attack(this, dungeon->getPlayer());
			}
			else
			{
				Actor::move(dir);
			}
			break;
		case ARROW_DOWN:
			if (dungeon->isPlayer(row, col - 1) || dungeon->isPlayer(row + 1, col) || dungeon->isPlayer(row - 1, col) || dungeon->isPlayer(row, col + 1))
			{
				attack(this, dungeon->getPlayer());
			}
			else
			{
				Actor::move(dir);
			}
			break;
		default:
			break;
		}
	}
}

/////////////////////////////////
//Dragon Class Implementations//
///////////////////////////////

//Dragon constructor
Dragon::Dragon(Dungeon* dungeon) :Monster(dungeon, randInt(6) + 20, randInt(6) + 20, 4, 4, 4, 0, "Dragon")
{
	Weapon* dragonWep = new LongSword();
	Actor::setWeapon(dragonWep);
}

//Dragon regainHp
void Dragon::regainHp()
{
	bool hpGain = trueWithProbability(1.0 / 10);   //random possibility
	if (getHP() < getMaxHp() && hpGain == true)
	{
		incHP(1);  //increase HP by 1
	}
}

//Dragon doAction function
void Dragon::doAction(Dungeon* dungeon)
{
	if (getSleep() > 0) //if it is asleep
	{
		decSleep(1);
		return;
	}

	if (notAlive() || dungeon->getPlayer()->notAlive())   //if it is dead
	{
		return;
	}
	regainHp();     //regainHp
	int row = getRow();
	int col = getCol();
	if (dungeon->isPlayer(row, col - 1))
		attack(this, dungeon->getPlayer());
	else if (dungeon->isPlayer(row, col + 1))
		attack(this, dungeon->getPlayer());
	else if (dungeon->isPlayer(row + 1, col))
		attack(this, dungeon->getPlayer());
	else if (dungeon->isPlayer(row - 1, col))
		attack(this, dungeon->getPlayer());   //Dragon can attack, but cannot move
}

/////////////////////////////////
//Goblin Class Implementations//
///////////////////////////////
Goblin::Goblin(Dungeon* dungeon) :Monster(dungeon, randInt(6) + 15, randInt(6) + 15, 1, 3, 1, 0, "Goblin")
{
	Weapon* golbinWep = new ShortSword();
	Actor::setWeapon(golbinWep);
	setDistance();
}

int Goblin::getDistance() const { return goblinsmelldistance; }

//Goblin smell distance set function
void Goblin::setDistance()
{
	goblinsmelldistance = getDungeon()->getGoblinSmell();
}

bool Goblin::goblinMovable(int r, int c)
{
	if (getDungeon()->getGrid(r, c) == ' ' || getDungeon()->getGrid(r, c) == ')' || getDungeon()->getGrid(r, c) == '>' || getDungeon()->getGrid(r, c) == '?' || getDungeon()->getGrid(r, c) == '&' || getDungeon()->getGrid(r, c) == '@')
		return true;
	else
		return false;
}

bool Goblin::goblinSmell(int r, int c, int d)
{
	int p_row = getDungeon()->getPlayer()->getRow();
	int p_col = getDungeon()->getPlayer()->getCol();
	if (d < 1)
		return false;
	if (r == p_row && c == p_col)
		return true;
	if (r < p_row)
	{
		if (goblinSmell(r + 1, c, d - 1) && goblinMovable(r + 1, c))
		{
			direction.push(ARROW_DOWN);
			return true;
		}
	}
	if (r > p_row)
	{
		if (goblinSmell(r - 1, c, d - 1) && goblinMovable(r - 1, c))
		{
			direction.push(ARROW_UP);
			return true;
		}
	}
	if (c > p_col)
	{
		if (goblinSmell(r, c - 1, d - 1) && goblinMovable(r, c - 1))
		{
			direction.push(ARROW_LEFT);
			return true;
		}
	}
	if (c < p_col)
	{
		if (goblinSmell(r, c + 1, d - 1) && goblinMovable(r, c + 1))
		{
			direction.push(ARROW_RIGHT);
			return true;
		}
	}
	return false;
}

void Goblin::doAction(Dungeon* dungeon)
{
	if (getSleep() > 0)
	{
		decSleep(1);
		return;
	}

	if (notAlive() || dungeon->getPlayer()->notAlive())
	{
		return;
	}

	if (goblinSmell(getRow(), getCol(), goblinsmelldistance))
	{
		int row = getRow();
		int col = getCol();
		char dir = direction.front();
		direction.pop();
		switch (dir) {
		case ARROW_LEFT:
			if (dungeon->isPlayer(row, col - 1) || dungeon->isPlayer(row + 1, col) || dungeon->isPlayer(row - 1, col) || dungeon->isPlayer(row, col + 1))
			{
				attack(this, dungeon->getPlayer());
			}
			else
			{
				Actor::move(dir);
			}
			break;
		case ARROW_RIGHT:
			if (dungeon->isPlayer(row, col - 1) || dungeon->isPlayer(row + 1, col) || dungeon->isPlayer(row - 1, col) || dungeon->isPlayer(row, col + 1))
			{
				attack(this, dungeon->getPlayer());
			}
			else
			{
				Actor::move(dir);
			}
			break;
		case ARROW_UP:
			if (dungeon->isPlayer(row, col - 1) || dungeon->isPlayer(row + 1, col) || dungeon->isPlayer(row - 1, col) || dungeon->isPlayer(row, col + 1))
			{
				attack(this, dungeon->getPlayer());
			}
			else
			{
				Actor::move(dir);
			}
			break;
		case ARROW_DOWN:
			if (dungeon->isPlayer(row, col - 1) || dungeon->isPlayer(row + 1, col) || dungeon->isPlayer(row - 1, col) || dungeon->isPlayer(row, col + 1))
			{
				attack(this, dungeon->getPlayer());
			}
			else
			{
				Actor::move(dir);
			}
			break;
		default:
			break;
		}
	}
	queue<char> empty;
	direction.swap(empty);
}