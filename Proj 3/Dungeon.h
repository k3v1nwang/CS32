#ifndef DUNGEON_H
#define DUNGEON_H

#include "Actor.h"
#include <list>
#include <vector>

struct rectangle
{
	int x_region;
	int y_region;
	int height;
	int width;
};

class Dungeon
{
public:
	//constructor and destructor
	Dungeon(int a);
	~Dungeon();

	//accessors
	char getGrid(int r, int c) const;
	int getLevel() const;
	Player* getPlayer() const;
	Object* getStair() const;
	Object* getGoldenIdol() const;
	Monster* getMonster(int r, int c, Monster* a);
	list<Object*>& getObjectList();
	list<Monster*>& getMonsterList();
	vector<string>& actionStrings();
	int getGoblinSmell() const;

	//mutators
	void setGrid(int r, int c, char symbol);
	void setLevel(int a);
	void addPlayer(Player* p);
	void setPlayer();
	void addObject();
	void setObject();
	void addMonster();
	void setMonster();
	void deleteDungeon(Dungeon* dungeon);
	void setDropItems(Dungeon* dungeon, Object* a);
	bool movable(int r, int c);
	bool isMonster(int r, int c) const;
	bool isPlayer(int r, int c) const;
	bool isStair(int r, int c) const;
	void killDead();
	void display();

private:
	void createMap(int n_regions);
	int level;
	int n_regions;
	int n_objs;
	char grid[18][70];
	Player* m_player;
	list<Object*> objectList;
	list<Monster*> monsterList;
	vector<string> m_actionStrings;
	Object* goldenIdol;
	Object* stair;
	int n_Goblin_smell_distance;
};

bool recCmp(rectangle r1, rectangle r2);

#endif
