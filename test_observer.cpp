#include <iostream>
#include <string>
#include <list>
using namespace std;

class Observer {
public:
    virtual void update() = 0;
};

class Observable {
protected:
    list <Observer*> observers;
public:
    void attach (Observer *o) {
        observers.push_back (o);
    }
    void detach (Observer *o) {
        observers.remove (o);
    }
 
    void notify () {
        list<Observer *>::iterator it;
        for (it = observers.begin(); it != observers.end(); it++) {
            (*it)->update ();
        }
    }
};

class Honey {
protected:
    int quantity;
public:
    Honey (int q) {
        quantity = q;
    }
 
    int getQuantity () {
        return quantity;
    }
 
    void setQuantity (int q) {
        quantity = q;
    }
};
 
class ObservableHoney : public Observable, public Honey {
    string state;
public:
    ObservableHoney (int q) : Honey(q) {
    }
 
    string getState () {
        return state;
    }
 
    void setState (const string& s) {
        state = s;
        cout << "Stan: " << state << endl;
        notify();
    }
};

class ObserverBear : public Observer {
protected:
    int bearId;
    ObservableHoney *honey;
public:
    ObserverBear (ObservableHoney *h, int id) {
        honey = h;
        bearId = id;
    }
    void update () {
        string state = honey->getState();
        if (!state.compare ("Sa ludzie blisko miodu")) {
            cout << "Mis" << bearId << ": Czekam w ukryciu" << endl;
        } else if (!state.compare ("Nie ma ludzi blisko miodu")) {
            cout << "Mis" << bearId << ": Kradne miod" << endl;
            honey->setQuantity(honey->getQuantity()-1);
        } else if (!state.compare ("Ida ludzie")) {
            cout << "Mis" << bearId << ": Uciekam" << endl;
        }
    }
};

int main() {
    ObservableHoney honey (5);
    Observer *bear1 = new ObserverBear(&honey, 1);
    Observer *bear2 = new ObserverBear(&honey, 2);
 
    honey.attach(bear1);
    honey.attach(bear2);
 
    cout << "Ilosc miodu: " << honey.getQuantity() << endl;
 
    honey.setState("Sa ludzie blisko miodu");
    honey.setState("Nie ma ludzi blisko miodu");
    honey.setState("Ida ludzie");
    honey.setState("Nie ma ludzi blisko miodu");
 
    cout << "Ilosc miodu: " << honey.getQuantity() << endl;
    delete bear1;
    delete bear2;
    return 0;
}

