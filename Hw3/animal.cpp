
class Animal
{
public:
    Animal(string name);
    virtual ~Animal();
    virtual string moveAction() const { return m_move; };
    string name() const { return m_name; };
    virtual void speak() const = 0;
private:
    string m_name;
    string m_move;
};

Animal::Animal(string name)
{
    m_name = name;
    m_move = "walk";
}
Animal::~Animal()
{}

class Cat : public Animal
{
public:
    Cat(string name) : Animal(name)
    {};
  
    virtual void speak() const
    {
        cout << "Meow";
    }
    ~Cat()
    {
        cout << "Destroying " << name() << " the cat" << endl;
    };
};

class Pig : public Animal
{
public:
    Pig(string name, int weight);
    ~Pig()
    {
        cout << "Destroying " << name() << " the pig" << endl;
    };
    virtual void speak() const
    {
        if (m_weight >= 160)
            cout << "Grunt";
        else
            cout << "Oink";
    }
private:
    int m_weight;
};

Pig::Pig(string name, int weight)
    :Animal(name)
{
    m_weight = weight;
}

class Duck : public Animal
{
public:
    Duck(string name) : Animal(name)
    {};
    virtual string moveAction() const
    {
        return "swim";
    }
    ~Duck()
    {
        cout << "Destroying " << name() << " the duck" << endl;
    };
    virtual void speak() const
    {
        cout << "Quack";
    }
};

