#include "GameObject.h"

////////////////////////////////
//Object Class Implementations//
///////////////////////////////

//Object class constructors

Object::Object(string name, string action)
{
	m_name = name;
	m_action = action;
}

Object::Object(string name, string action, int r, int c)
{
	m_name = name;
	m_action = action;
	m_row = r;
	m_col = c;
}

Object::Object(string name, int r, int c)
{
	m_name = name;
	m_row = r;
	m_col = c;
}

//Object class accessors

int Object::getCol() const { return m_col; }

int Object::getRow() const { return m_row; }

string Object::getAction() const { return m_action; }

string Object::getName() const { return m_name; }

int Weapon::getDexBonus() const { return dexBonus; }

int Weapon::getStrAmt() const { return StrAmt; }

//Object setPos function
void Object::setPos(int r, int c)
{
	m_row = r;
	m_col = c;
}

////////////////////////////////
//Weapon Class Implementations//
///////////////////////////////

//Weapon class constructors
Weapon::Weapon(string name, string action, int dex, int str) :Object(name, action)
{
	dexBonus = dex;
	StrAmt = str;
}

Weapon::Weapon(string name, string action, int dex, int str, int r, int c) :Object(name, action, r, c)
{
	dexBonus = dex;
	StrAmt = str;
}

ShortSword::ShortSword() :Weapon("short sword", "slashes", 0, 2) {}

Mace::Mace() : Weapon("Mace", "swings", 0, 2) {}

LongSword::LongSword() : Weapon("long sword", "swings", 2, 4) {}

MagicAxe::MagicAxe() : Weapon("magic axe", "chops", 5, 5) {};

MagicFang::MagicFang() :Weapon("magic fangs of sleep", "strikes", 3, 2) {};

MagicFang::MagicFang(int r, int c) :Weapon("magic fangs of sleep", "strikes", 3, 2, r, c) {};
MagicAxe::MagicAxe(int r, int c) :Weapon("magic axe", "chops", 5, 5, r, c) {};

////////////////////////////////
//Scroll Class Implementations//
///////////////////////////////

Scroll::Scroll(string name, string effect, int r, int c) :Object(name, effect, r, c) {}
Scroll::Scroll(string name, string effect) : Object(name, effect)
{}
strScroll::strScroll() : Scroll("scroll of strength", "Your muscles bulge.") {};

armScroll::armScroll() :Scroll("Scroll of enhance armor", "Your armor glows blue.") {};

hpScroll::hpScroll() :Scroll("Scroll of enhance health", "You feel your heart beating stronger.") {};

dexScroll::dexScroll() :Scroll("Scroll of enhance dexterity", "You feel like less of a klutz.") {};

tpScroll::tpScroll() :Scroll("Scroll of teleportation", "You feel your body wrenched in space and time.") {};

strScroll::strScroll(int r, int c) :Scroll("scroll of strength", "Your muscles bulge.", r, c) {};

armScroll::armScroll(int r, int c) :Scroll("Scroll of enhance armor", "Your armor glows blue.", r, c) {};

hpScroll::hpScroll(int r, int c) :Scroll("Scroll of enhance health", "You feel your heart beating stronger.", r, c) {};

dexScroll::dexScroll(int r, int c) :Scroll("Scroll of enhance dexterity", "You feel like less of a klutz.", r, c) {};

tpScroll::tpScroll(int r, int c) :Scroll("Scroll of teleportation", "You feel your body wrenched in space and time.", r, c) {};