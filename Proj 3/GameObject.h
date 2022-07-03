#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <string>
using namespace std;

class Dungeon;
class Player;

class Object
{
public:
	//constructor & destructor
	Object();
	Object(string name, string action);
	Object(string name, string action, int r, int c);
	Object(string name, int r, int c);
	virtual ~Object() {};

	//accessor
	string getName() const;
	string getAction() const;
	int getRow() const;
	int getCol() const;

	//mutator
	void setPos(int r, int c);
private:
	string m_name;
	string m_action;
	int m_row;
	int m_col;
};

class Weapon :public Object
{
public:
	//constructor & destructor
	Weapon(string name, string action, int dex, int str);
	Weapon(string name, string action, int dex, int str, int r, int c);
	virtual ~Weapon() {};

	//accessor
	int getDexBonus() const;
	int getStrAmt() const;
private:
	int dexBonus;
	int StrAmt;
};

class ShortSword : public Weapon
{
public:
	//constructor & destructor
	ShortSword();
	virtual ~ShortSword() {};
};

class Mace : public Weapon
{
public:
	//constructor & destructor
	Mace();
	virtual ~Mace() {};
};

class LongSword :public Weapon
{
public:
	//constructor & destructor
	LongSword();
	virtual ~LongSword() {};
};

class MagicAxe :public Weapon
{
public:
	//constructor & destructor
	MagicAxe();
	MagicAxe(int r, int c);
	virtual ~MagicAxe() {};
};

class MagicFang :public Weapon
{
public:
	//constructor & destructor
	MagicFang();
	MagicFang(int r, int c);
	virtual ~MagicFang() {};
};

class Scroll :public Object
{
public:
	//constructor & destructor
	Scroll(string name, string effect);
	Scroll(string name, string effect, int r, int c);
	virtual ~Scroll() {};
};

class strScroll : public Scroll
{
public:
	//constructor & destructor
	strScroll();
	strScroll(int r, int c);
	virtual ~strScroll() {};
};

class armScroll : public Scroll
{
public:
	//constructor & destructor
	armScroll();
	armScroll(int r, int c);
	virtual ~armScroll() {};
};

class hpScroll :public Scroll
{
public:
	//constructor & destructor
	hpScroll();
	hpScroll(int r, int c);
	virtual ~hpScroll() {};
};

class dexScroll :public Scroll
{
public:
	//constructor & destructor
	dexScroll();
	dexScroll(int r, int c);
	virtual ~dexScroll() {};
};

class tpScroll : public Scroll
{
public:
	//constructor & destructor
	tpScroll();
	tpScroll(int r, int c);
	virtual ~tpScroll() {};
};

#endif
