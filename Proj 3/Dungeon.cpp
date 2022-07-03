#include "Dungeon.h"
#include <iostream>
#include <algorithm>
#include <string>
#include "utilities.h"
#include "GameObject.h"
#include "Actor.h"

using namespace std;

Dungeon::Dungeon(int a)  //Dungeon constructor
{
	n_regions = randInt(3) + 3;     //set number of regions
	createMap(n_regions);           //create mini
	n_objs = randInt(2) + 2;        //set number of objects
	level = 0;                      //set the initial level
	n_Goblin_smell_distance = a;
}

Dungeon::~Dungeon() //Dungeon destructor
{
	if (level == 4)
		delete goldenIdol;
	else
		delete stair;
	for (list<Object*>::iterator i = objectList.begin(); i != objectList.end(); i++)
		delete* i;
	for (list<Monster*>::iterator q = monsterList.begin(); q != monsterList.end(); q++)
		delete* q;  //delete monsters & objects
}

//Dungeon accessors

int Dungeon::getGoblinSmell() const { return n_Goblin_smell_distance; }

vector<string>& Dungeon::actionStrings() { return m_actionStrings; }

Player* Dungeon::getPlayer() const { return m_player; }

Object* Dungeon::getStair() const { return stair; }

Object* Dungeon::getGoldenIdol() const { return goldenIdol; }

list<Object*>& Dungeon::getObjectList() { return objectList; }

list<Monster*>& Dungeon::getMonsterList() { return monsterList; }

char Dungeon::getGrid(int r, int c) const { return grid[r][c]; }

int Dungeon::getLevel() const { return level; }

Monster* Dungeon::getMonster(int r, int c, Monster* a)
{
	//tranverse the Monster list
	for (list<Monster*>::iterator i = monsterList.begin(); i != monsterList.end(); i++)
	{
		if ((*(*i)).getRow() == r && (*(*i)).getCol() == c)
		{
			a = *i;
			return a;
		}
	}
	return a;
}

//Dungeon mutators

// 4 checks for the mini actors
bool Dungeon::movable(int r, int c)
{
	if (grid[r][c] == ' ' || grid[r][c] == ')' || grid[r][c] == '>' || grid[r][c] == '?' || grid[r][c] == '&')
		return true;
	else
		return false;
}

bool Dungeon::isMonster(int r, int c) const
{
	if (grid[r][c] == 'B' || grid[r][c] == 'S' || grid[r][c] == 'D' || grid[r][c] == 'G')
	{
		return true;
	}
	else
		return false;
}

bool Dungeon::isPlayer(int r, int c) const
{
	if (grid[r][c] == '@' || (r == m_player->getRow() && c == m_player->getCol()))
		return true;
	else
		return false;
}

bool Dungeon::isStair(int r, int c) const
{
	int row = getStair()->getRow();
	int col = getStair()->getCol();
	if (r == row && c == col)
		return true;
	else
		return false;
}

//set functions

void Dungeon::setGrid(int r, int c, char symbol)
{
	grid[r][c] = symbol;
}

void Dungeon::setLevel(int a)
{
	level = a;
}

void Dungeon::setPlayer()
{
	int n_r, n_c;
	do {
		n_r = randInt(18);
		n_c = randInt(70);
	} while (getGrid(n_r, n_c) == '#' || getGrid(n_r, n_c) == 'S' || getGrid(n_r, n_c) == 'G' || getGrid(n_r, n_c) == 'D' || getGrid(n_r, n_c) == 'B');
	m_player->setPos(n_r, n_c);
}

void Dungeon::setDropItems(Dungeon* dungeon, Object* a)
{
	dungeon->getObjectList().push_back(a);
}

void Dungeon::setObject()
{
	//tranverse the Object list
	for (list<Object*>::iterator i = objectList.begin(); i != objectList.end(); i++)
	{
		int m_row, m_col;
		do {
			m_row = randInt(18);
			m_col = randInt(70);      //initialize the position of the Object
		} while (getGrid(m_row, m_col) == '#' || getGrid(m_row, m_col) == '>' || getGrid(m_row, m_col) == '?' || getGrid(m_row, m_col) == '&' || getGrid(m_row, m_col) == ')');
		(*(*i)).setPos(m_row, m_col);
		Weapon* ptr = dynamic_cast<Weapon*>(*i);  //ptr the Object type
		if (ptr != nullptr)
			grid[m_row][m_col] = ')';
		else
			grid[m_row][m_col] = '?';   //set grids of Weapon and Scroll respectively
	}
	int n_r, n_c;
	do {
		n_r = randInt(18);
		n_c = randInt(70);
	} while (getGrid(n_r, n_c) == '#' || getGrid(n_r, n_c) == ')' || getGrid(n_r, n_c) == '?');

	if (level != 4)
	{
		stair = new Object("stair", n_r, n_c);      ///set the stair
		grid[n_r][n_c] = '>';
	}
	else
	{
		goldenIdol = new Object("golden idol", n_r, n_c);   //set the golden idol
		grid[n_r][n_c] = '&';
	}
}

void Dungeon::setMonster()
{
	//tranverse the Monster list
	for (list<Monster*>::iterator i = monsterList.begin(); i != monsterList.end(); i++)
	{
		int m_row, m_col;
		do {
			m_row = randInt(18);
			m_col = randInt(70);
		} while (getGrid(m_row, m_col) == 'B' || getGrid(m_row, m_col) == 'D' || getGrid(m_row, m_col) == 'S' || getGrid(m_row, m_col) == 'G' || getGrid(m_row, m_col) == '@' || getGrid(m_row, m_col) == '#');
		(*(*i)).setPos(m_row, m_col);
		if ((*(*i)).getName() == "Goblin")
			grid[m_row][m_col] = 'G';
		else if ((*(*i)).getName() == "Snakewoman")
			grid[m_row][m_col] = 'S';
		else if ((*(*i)).getName() == "Bogeyman")
			grid[m_row][m_col] = 'B';
		else if ((*(*i)).getName() == "Dragon")     //set the four kinds of monsters respectively
			grid[m_row][m_col] = 'D';
	}
}

//add functions

void Dungeon::addPlayer(Player* p)
{
	m_player = p;
	setPlayer();
}

void Dungeon::addObject()
{
	for (int i = 0; i < n_objs; i++)    //choose random numbers to generate random objects
	{
		int objectKey = randInt(8);
		switch (objectKey) {
		case 0:
			objectList.push_back(new strScroll());
			break;
		case 1:
			objectList.push_back(new armScroll());
			break;
		case 2:
			objectList.push_back(new hpScroll());
			break;
		case 3:
			objectList.push_back(new dexScroll());
			break;
		case 4:
			objectList.push_back(new ShortSword());
			break;
		case 5:
			objectList.push_back(new LongSword());
			break;
		case 6:
			objectList.push_back(new Mace());
			break;
		case 7:
			objectList.push_back(new tpScroll());
			break;
		default:
			break;
		}
	}
	setObject();
}

void Dungeon::addMonster()
{
	int n_monsters = 2 + randInt(5 * (level + 1));
	for (int i = 0; i < n_monsters; i++)     //generate random numbers to generate random monsters
	{
		if (level == 0 || level == 1)       //generate Snakewomen and Goblin in level 0 and level 1
		{
			int monster_index = randInt(2);
			switch (monster_index) {
			case 0:
				monsterList.push_back(new Goblin(this));
				break;
			case 1:
				monsterList.push_back(new Snakewomen(this));
				break;
			default:
				break;
			}
		}
		if (level == 2)     //generate Snakewomen, Goblin, Bogeyman in level 2
		{
			int monster_index_2 = randInt(3);
			switch (monster_index_2) {
			case 0:
				monsterList.push_back(new Goblin(this));
				break;
			case 1:
				monsterList.push_back(new Snakewomen(this));
				break;
			case 2:
				monsterList.push_back(new Bogeyman(this));
				break;
			default:
				break;
			}
		}
		if (level == 3 || level == 4)   //generate all monsters in level 3 and 4
		{
			int monster_index_3 = randInt(4);
			switch (monster_index_3) {
			case 0:
				monsterList.push_back(new Goblin(this));
				break;
			case 1:
				monsterList.push_back(new Snakewomen(this));
				break;
			case 2:
				monsterList.push_back(new Bogeyman(this));
				break;
			case 3:
				monsterList.push_back(new Dragon(this));
				break;
			default:
				break;
			}
		}
	}
	setMonster();
}

//clean monsters' corpse
void Dungeon::killDead()
{
	for (list<Monster*>::iterator i = monsterList.begin(); i != monsterList.end();)
	{
		if ((*i)->notAlive() == true)
		{
			grid[(*i)->getRow()][(*i)->getCol()] = ' ';
			i = monsterList.erase(i);
		}
		else
			i++;
	}
}

//delete the old Dungeon and set the new Dungeon in the new level
void Dungeon::deleteDungeon(Dungeon* dungeon)
{
	level++;

	n_regions = randInt(3) + 3;

	createMap(n_regions);
	addPlayer(dungeon->m_player);
	n_objs = randInt(2) + 2;
	monsterList.clear();
	objectList.clear();
	addMonster();
	addObject();
}

//display function
void Dungeon::display()
{
	clearScreen();
	killDead();

	if (level != 4)
		grid[stair->getRow()][stair->getCol()] = '>';
	else
		grid[goldenIdol->getRow()][goldenIdol->getCol()] = '&'; //display the golden idol or the stair

	for (list<Object*>::iterator i = objectList.begin(); i != objectList.end(); i++)
	{
		int n_r = (*i)->getRow();
		int n_c = (*i)->getCol();
		Weapon* ptr = dynamic_cast<Weapon*>(*i);
		if (ptr != nullptr)
			grid[n_r][n_c] = ')';
		else
			grid[n_r][n_c] = '?';
	}                               //display the objects

	for (list<Monster*>::iterator i = monsterList.begin(); i != monsterList.end(); i++)
	{
		int m_row = (*i)->getRow();
		int m_col = (*i)->getCol();
		if ((*(*i)).getName() == "Goblin")
			grid[m_row][m_col] = 'G';
		else if ((*(*i)).getName() == "Snakewoman")
			grid[m_row][m_col] = 'S';
		else if ((*(*i)).getName() == "Bogeyman")
			grid[m_row][m_col] = 'B';
		else if ((*(*i)).getName() == "Dragon")
			grid[m_row][m_col] = 'D';
	}                               //display the mosnters

	if (getPlayer() != nullptr)
		grid[getPlayer()->getRow()][getPlayer()->getCol()] = '@'; //display the Player

	for (int i = 0; i < 18; i++)
	{
		for (int j = 0; j < 70; j++)
		{
			cout << grid[i][j];
		}
		cout << endl;   //display the mini
	}

	cout << "Dungeon Level: " << level << ", Hit Points: ";
	cout << getPlayer()->getHP() << ", Armor: " << getPlayer()->getArm() << ", Strength: " << getPlayer()->getStr() << ", Dexterity: " << getPlayer()->getDex() << endl;   //the Player information
	cout << endl;
	for (unsigned long i = 0; i < actionStrings().size(); i++)
	{
		cout << actionStrings()[i] << endl;  //display the strings
	}

	if (getPlayer()->notAlive())    //see if the Player is dead
		return;
	actionStrings().clear();
}

//create mini functions
bool recCmp(rectangle r1, rectangle r2)
{
	return r1.x_region > r2.x_region;   //compare rectangles to sort the regions
}

void Dungeon::createMap(int n_regions)
{
	for (int r = 0; r < 18; r++)
		for (int w = 0; w < 70; w++)
			grid[r][w] = '#';

	rectangle* regions = new rectangle[n_regions];  //create new rectangle list
	for (int k = 0; k < n_regions; k++)
	{
		regions[k].width = randInt(9) + 5;
		regions[k].height = randInt(6) + 5;
		regions[k].x_region = randInt(64 - regions[k].width) + 3;
		regions[k].y_region = randInt(12 - regions[k].height) + 3;  //set the coords and width and length
		bool ptr = false;
		for (int w = 0; w < k; w++)
		{
			int x_max = regions[w].x_region + regions[w].width;
			int y_max = regions[w].y_region + regions[w].height;
			if (regions[k].x_region > x_max + 1 || regions[k].x_region + regions[k].width < regions[w].x_region - 1 || regions[k].y_region > y_max + 1 || regions[k].y_region + regions[k].height < regions[w].y_region - 1)
			{
				ptr = true;
				if (w == k - 1)
					break;
			}
			else                            //to ptr the regions are not overlapping
			{
				ptr = false;
			}
			if (ptr == false && k > 0)
				k--;
			else
				continue;
		}
	}

	for (int k = 0; k < n_regions; k++)
	{
		for (int h = 0; h < regions[k].height; h++)
			for (int w = 0; w < regions[k].width; w++)
				grid[regions[k].y_region + h][regions[k].x_region + w] = ' ';   //set the regions as ' '
	}

	sort(regions, regions + n_regions, recCmp); //sort the regions in order

	for (int i = 0; i < n_regions - 1; i++)  //create corridors between regions
	{
		int x_1 = randInt(regions[i].width) + regions[i].x_region;
		int y_1 = randInt(regions[i].height) + regions[i].y_region;
		int x_2 = randInt(regions[i + 1].width) + regions[i + 1].x_region;
		int y_2 = randInt(regions[i + 1].height) + regions[i + 1].y_region;
		if (x_1 <= x_2 && y_1 <= y_2)
		{
			for (int i = x_1; i <= x_2; i++)
				grid[y_1][i] = ' ';
			for (int i = y_1; i <= y_2; i++)
				grid[i][x_2] = ' ';
		}
		if (x_1 > x_2 && y_1 > y_2)
		{
			for (int i = x_2; i <= x_1; i++)
				grid[y_2][i] = ' ';
			for (int i = y_2; i <= y_1; i++)
				grid[i][x_1] = ' ';
		}
		if (x_1 <= x_2 && y_1 > y_2)
		{
			for (int i = x_1; i <= x_2; i++)
				grid[y_1][i] = ' ';
			for (int i = y_2; i <= y_1; i++)
				grid[i][x_2] = ' ';
		}
		if (x_1 > x_2 && y_1 <= y_2)
		{
			for (int i = x_2; i <= x_1; i++)
				grid[y_2][i] = ' ';
			for (int i = y_1; i <= y_2; i++)
				grid[i][x_1] = ' ';
		}
	}
	delete[] regions;
}