#include <iostream>
#include <map>
#include <string>

using namespace std;

class House
{
    public:
        virtual string get_name() const { return name; }
        virtual House* clone() const = 0;
        virtual ~House() {}
    protected:
        House( string s ) : name( s ) {}
        string name;
};

class Front_door
 : public House
{
    public:
        Front_door() : House( "Drzwi frontowe" ) {}
        virtual House* clone() const { return new Front_door( *this ); }
};

class Back_door
 : public House
{
    public:
        Back_door() : House( "Drzwi tylne" ) {}
        virtual House* clone() const { return new Back_door( *this ); }
};

class High_wall
 : public House
{
    public:
        High_wall() : House( "Wysoka sciana" ) {}
        virtual House* clone() const { return new High_wall( *this ); }
};

class Short_wall
 : public House
{
    public:
        Short_wall() : House( "Niska sciana" ) {}
        virtual House* clone() const { return new Short_wall( *this ); }
};

class Big_window
 : public House
{
    public:
        Big_window() : House( "Duze okno" ) {}
        virtual House* clone() const { return new Big_window( *this ); }
};

class Small_window
 : public House
{
    public:
        Small_window() : House( "Male okno" ) {}
        virtual House* clone() const { return new Small_window( *this ); }
};

class Creator
{
    public:
        Creator()
        {
            p_list[ Door ] = 0;
            p_list[ Window ] = 0;
            p_list[ Wall ] = 0;
        }
        enum Typ{ Door, Window, Wall };
        void add_prototype( Typ t, House* p )
        {
            if( p_list[ t ] )
                delete p_list[ t ];
            p_list[ t ] = p;
        }

        House* make_door() { return p_list[ Door ]->clone(); }
        House* make_window() { return p_list[ Window ]->clone(); }
        House* make_wall() { return p_list[ Wall ]->clone(); }

        ~Creator()
        {
            for( map< Typ, House* >::iterator iter = p_list.begin();
                 iter != p_list.end(); ++iter )
                delete iter->second;
        }
    private:
        map< Typ, House* > p_list;
};

void room_creator( Creator& f )
{
    cout << "Wchodzimy przez " << f.make_door()->get_name() << " widzimy " 
         << f.make_wall()->get_name() << " i " << f.make_window()->get_name() << endl;
}

int main()
{
    House* win_ptr = new Big_window;
    House* wall_ptr = new High_wall;
    House* door_ptr = new Front_door;    
    Creator c;

    c.add_prototype( Creator::Window, win_ptr );
    c.add_prototype( Creator::Wall, wall_ptr );
    c.add_prototype( Creator::Door, door_ptr );

    room_creator( c );
}
