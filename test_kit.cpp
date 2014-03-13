#include <iostream>
#include <string>

using namespace std;

class Door
{
    public:
        virtual string get_name() const { return name; }
    protected:
        Door( string s ) : name( s ) {}
        string name;
};

class Front_door
 : public Door
{
    public:
        Front_door() : Door( "Drzwi frontowe" ) {}
};

class Back_door
 : public Door
{
    public:
        Back_door() : Door( "Drzwi tylne" ) {}
};

class Wall
{
    public:
        virtual string get_name() const { return name; }
    protected:
        Wall( string s ) : name( s ) {}
        string name;
};

class High_wall
 : public Wall
{
    public:
        High_wall() : Wall( "Wysoka sciana" ) {}
};

class Short_wall
 : public Wall
{
    public:
        Short_wall() : Wall( "Niska sciana" ) {}
};

class Window
{
    public:
        virtual string get_name() const { return name; }
    protected:
        Window( string s ) : name( s ) {}
        string name;
};

class Big_window
 : public Window
{
    public:
        Big_window() : Window( "Duze okno" ) {}
};

class Small_window
 : public Window
{
    public:
        Small_window() : Window( "Male okno" ) {}
};

class Factory
{
    public:
        virtual Door* make_door() = 0;
        virtual Wall* make_wall() = 0;
        virtual Window* make_window() = 0;
};

class Rich_Factory
 : public Factory
{
    public:
        virtual Door* make_door() { return new Front_door(); }
        virtual Wall* make_wall() { return new High_wall(); }
        virtual Window* make_window() { return new Big_window(); }
};

class Poor_Factory
 : public Factory
{
    public:
        virtual Door* make_door() { return new Back_door(); }
        virtual Wall* make_wall() { return new Short_wall(); }
        virtual Window* make_window() { return new Small_window(); }
};

void room_creator( Factory& f )
{
    cout << "Wchodzimy przez " << f.make_door()->get_name() << " widzimy " 
         << f.make_wall()->get_name() << " i " << f.make_window()->get_name() << endl;
}

int main()
{
    Rich_Factory rich;
    room_creator( rich );

    Poor_Factory poor;
    room_creator( poor );
}
