#ifndef OBSERVER_H
#define OBSERVER_H

#include <vector>
#include <algorithm>

class Observer {
public:
    virtual void update() = 0;
    virtual ~Observer() = default;
};

class Observable {
private:
    std::vector<Observer*> observers;
public:
    void addObserver(Observer* o) {
        observers.push_back(o);
    }

    void removeObserver(Observer* o) {
        observers.erase(std::remove(observers.begin(), observers.end(), o), observers.end());
    }

    void notifyObservers() {
        for (auto* o : observers)
            o->update();
    }
};

#endif