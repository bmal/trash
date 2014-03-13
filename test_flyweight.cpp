#include <iostream>
#include <algorithm>
#include <functional>
#include <vector>
#include <string>
#include <stdexcept>

using namespace std;

enum Types { type_go, type_stop, type_select, type_undo };

class Icon
{
  public:
    Icon( Types t ) : icon_type( t )
    {
        switch ( icon_type )
        {
            case type_go:
                _width = 20;
                _height = 20;
                break;
            case type_stop:
                _width = 40;
                _height = 40;
                break;
            case type_select:
                _width = 60;
                _height = 60;
                break;
            case type_undo:
                _width = 30;
                _height = 30;
                break;
            default:
                throw runtime_error( "Zly typ" );
        }
    }

    string getName()
    {
        switch ( icon_type )
        {
            case type_go:
                return string( "go" );
            case type_stop:
                return string( "stop" );
            case type_select:
                return string( "select" );
            case type_undo:
                return string( "undo" );
        }
        return string( '\0' );
    }

    void draw( int x, int y )
    {
        cout << "   drawing " << getName() << ": upper left (" << x << "," << y << 
          ") - lower right (" << x + _width << "," << y + _height << ")" <<
          endl;
    }


  private:
    Types icon_type;
    int _width;
    int _height;
};

class Flyweight_Factory
{
    public:
        Icon* make_icon( Types t )
        {
            if( icon_list[ t ] )
                return icon_list[ t ];
            return icon_list[ t ] = new Icon( t );
        }
        
        void print_icons() const
        {
            for( vector< Icon* >::const_iterator iter = icon_list.begin();
                 iter < icon_list.end();
                 ++iter )
                cout << ( *iter )->getName() << ", ";
        }

        static Flyweight_Factory* instant()
        {
            if( _factory == 0 )
                _factory = new Flyweight_Factory();
            return _factory;
        }

        ~Flyweight_Factory()
        {
            for( vector< Icon* >::size_type iter = 0;
                 iter < icon_list.size();
                 ++iter )
                delete icon_list[ iter ];
        }

    protected:
        Flyweight_Factory() : icon_list( type_undo + 1 ) {}

    private:
        vector< Icon* > icon_list;
        static Flyweight_Factory* _factory;
};

Flyweight_Factory* Flyweight_Factory::_factory = 0;

class DialogBox
{
  public:
    DialogBox(int x, int y, int incr): _iconsOriginX(x), _iconsOriginY(y),
      _iconsXIncrement(incr){}
    virtual void draw() = 0;

  protected:
    Icon *_icons[ 3 ];
    int _iconsOriginX;
    int _iconsOriginY;
    int _iconsXIncrement;
};

class FileSelection: public DialogBox
{
  public:
    FileSelection(Icon *first, Icon *second, Icon *third): DialogBox(100, 100,
      100)
    {
        _icons[0] = first;
        _icons[1] = second;
        _icons[2] = third;
    }
    void draw()
    {
        cout << "drawing FileSelection:" << endl;
        for (int i = 0; i < 3; i++)
          _icons[i]->draw(_iconsOriginX + (i *_iconsXIncrement), _iconsOriginY);
    }
};

class CommitTransaction: public DialogBox
{
  public:
    CommitTransaction(Icon *first, Icon *second, Icon *third): DialogBox(150,
      150, 150)
    {
        _icons[0] = first;
        _icons[1] = second;
        _icons[2] = third;
    }
    void draw()
    {
        cout << "drawing CommitTransaction:" << endl;
        for (int i = 0; i < 3; i++)
          _icons[i]->draw(_iconsOriginX + (i *_iconsXIncrement), _iconsOriginY);
    }
};

int main()
{
    Flyweight_Factory* ptr = Flyweight_Factory::instant();
    DialogBox* dialogs[2];
    dialogs[0] = new FileSelection( ptr->make_icon( type_go ),
                                    ptr->make_icon( type_stop ),
                                    ptr->make_icon( type_select ));
    dialogs[1] = new CommitTransaction( ptr->make_icon( type_select ),
                                        ptr->make_icon( type_stop ),
                                        ptr->make_icon( type_undo ));

    for (int i = 0; i < 2; i++)
        dialogs[i]->draw();

    ptr->print_icons();
}
