#ifndef ACTORS_INCLUDED
#define ACTORS_INCLUDED

#include <list>
#include <vector>
#include "GameObject.h"
#include <queue>

using namespace std;

class Dungeon;
class Actor
{
public:
	//constructor & destructor
	Actor(Dungeon* d, int r, int c);
	Actor(Dungeon* d, int HP, int maxHP, int arm, int str, int dex, int sleep, string name);
	virtual ~Actor();

	//accessor
	int getRow() const;
	int getCol() const;
	int getHP() const;
	int getArm() const;
	int getStr() const;
	int getDex() const;
	bool notAlive() const;
	int getSleep() const;
	int getMaxHp() const;
	string getName() const;
	Weapon* getWeapon() const;
	Dungeon* getDungeon() const;

	//mutators
	bool setWeapon(Weapon* Weapon);
	bool setPos(int r, int c);
	void attack(Actor* attaker, Actor* target);
	void move(char dir);
	void incStr(int a);
	void incHP(int a);
	void incDex(int a);
	void incArm(int a);
	void incSleep(int a);
	void decSleep(int a);
	bool isAsleep();
	void incMaxHP(int a);
	void setGrid(int r, int c, Actor* a);
	void monsterMove(char dir, Actor* a);

private:
	Dungeon* m_dungeon;
	int m_row;
	int m_col;
	int m_HP;
	int m_max_HP;
	Weapon* m_weapon;
	int m_arm;
	int m_str;
	int m_dex;
	int m_sleep;
	bool m_death;
	string m_name;
};

class Player : public Actor
{
public:
	//constructor and destructor
	Player(Dungeon* d);
	virtual ~Player();

	//accessors
	list<Object*> getInventory() const;
	bool win() const;

	//mutators
	void openInventory();
	void pickUp();
	/*void nextLevel();*/
	void cheat();
	void playerMove(char dir);
	//void useInventoryObjs(char a);
	void wieldWeapon(char a);
	void read(char a);
	/*void setEquip(Object* a);*/
	bool checkObject();
	void heal();

private:
	bool m_win;
	list<Object*> inventory;
};

class Monster : public Actor
{
public:
	//constructor and destructor
	Monster(Dungeon* m_dunge, int m_HP, int m_maxHP, int m_arm, int m_str, int m_dex, int m_sleep, string m_name);
	virtual ~Monster() {};

	//mutators
	virtual void doAction(Dungeon* d) = 0;
	bool smell(Dungeon* d, int r);
	void monsterDrop(Dungeon* d, Monster* a);
	char chooseDirection(Dungeon* d, int r, int c);
};

class Bogeyman : public Monster
{
public:
	//constructor and destructor
	Bogeyman(Dungeon* d);
	virtual ~Bogeyman() {};

	//mutators
	virtual void doAction(Dungeon* d);
	void dropItem(Dungeon* d);
};

class Snakewomen :public Monster
{
public:
	//constructor and destructor
	Snakewomen(Dungeon* d);
	virtual ~Snakewomen() {};

	//mutators
	virtual void doAction(Dungeon* d);
	void dropItem(Dungeon* d);
};

class Dragon :public Monster
{
public:
	//constructor and destructor
	Dragon(Dungeon* d);
	virtual ~Dragon() {};

	//mutators
	virtual void doAction(Dungeon* d);
	void regainHp();
};

class Goblin :public Monster
{
public:
	//constructor and destructor
	Goblin(Dungeon* d);
	virtual ~Goblin() {};

	//accessor
	int getDistance() const;
	void setDistance();

	//mutators
	virtual void doAction(Dungeon* d);
	bool goblinSmell(int r, int c, int d);

	bool goblinMovable(int r, int c);
private:
	int goblinsmelldistance;
	char goblinArray[18][70];
	struct coord {
		int r;
		int c;
		coord() { r = 0; c = 0; }
		coord(int r, int c) { this->r = r; this->c = c; }
	};
	coord pos;
	bool findPath;
	queue<char> direction;
};
#endif // defined ACTORS_INCLUDED