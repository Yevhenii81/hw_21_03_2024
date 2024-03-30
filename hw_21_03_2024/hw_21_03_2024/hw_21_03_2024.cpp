#include <iostream>
using namespace std;

class Base {
public:
    static int people_on_base;
    static int vehicles_on_base;
    static double petrol_on_base;
    static double goods_on_base;
};

int Base::people_on_base = 200;
int Base::vehicles_on_base = 20;
double Base::petrol_on_base = 97986;
double Base::goods_on_base = 45;

class Vehicle {
protected:
    double petrol_amount;
    double tank_volume;

public:
    Vehicle(double petrol_amount, double tank_volume) : petrol_amount(petrol_amount), tank_volume(tank_volume) {}

    void SetTankVolume(double tank_volume) {
        this->tank_volume = tank_volume;
    }

    void SetPetrolAmount(double petrol_amount) {
        this->petrol_amount = petrol_amount;
    }

    double GetTankVolume() const {
        return tank_volume;
    }

    double GetPetrolAmount() const {
        return petrol_amount;
    }

    void Arrive() {
        Base::vehicles_on_base++;
        Base::people_on_base += 4;
        cout << "Welcome...\n";
    }

    bool Leave() {
        if (petrol_amount < tank_volume) {
            double lacking_petrol = tank_volume - petrol_amount;
            if (Base::petrol_on_base >= lacking_petrol) {
                Base::petrol_on_base -= lacking_petrol;
                petrol_amount += lacking_petrol;
                Base::people_on_base -= 4;
                Base::vehicles_on_base--;
                cout << "Goodbye!!!\n";
                return true;
            }
            else {
                cout << "Insufficient petrol on base. Unable to leave.\n";
                return false;
            }
        }
        else {
            Base::vehicles_on_base--;
            cout << "Goodbye!!!\n";
            return true;
        }
    }
};

class Bus : public Vehicle {
private:
    int people;
    int max_people;
    double petrol;
    double max_petrol;

public:
    Bus(int people, int max_people, double petrol, double max_petrol)
        : Vehicle(petrol, max_petrol), people(people), max_people(max_people), petrol(petrol), max_petrol(max_petrol) {}

    void SetPeople(int people) {
        this->people = people;
    }

    int GetPeople() const {
        return people;
    }

    void SetMaxPeople(int max_people) {
        this->max_people = max_people;
    }

    int GetMaxPeople() const {
        return max_people;
    }

    void SetPetrol(double petrol) {
        this->petrol = petrol;
    }

    double GetPetrol() const {
        return petrol;
    }

    void SetMaxPetrol(double max_petrol) {
        this->max_petrol = max_petrol;
    }

    double GetMaxPetrol() const {
        return max_petrol;
    }

    void Arrive() {
        Vehicle::Arrive();
        Base::people_on_base += people;
    }

    bool Leave() {
        if (Base::people_on_base >= people && Vehicle::Leave()) {
            Base::people_on_base -= people;
            return true;
        }
        else {
            return false;
        }
    }
};

class Truck : public Vehicle {
private:
    double load;
    double max_load;
    double petrol;
    double max_petrol;

public:
    Truck(double load, double max_load, double petrol, double max_petrol)
        : Vehicle(petrol, max_petrol), load(load), max_load(max_load), petrol(petrol), max_petrol(max_petrol) {}

    void SetCurrentLoad(double load) {
        this->load = load;
    }

    double GetCurrentLoad() const {
        return load;
    }

    void SetMaxLoad(double max_load) {
        this->max_load = max_load;
    }

    double GetMaxLoad() const {
        return max_load;
    }

    void SetPetrol(double petrol) {
        this->petrol = petrol;
    }

    double GetPetrol() const {
        return petrol;
    }

    void SetMaxPetrol(double max_petrol) {
        this->max_petrol = max_petrol;
    }

    double GetMaxPetrol() const {
        return max_petrol;
    }

    void Arrive() {
        Vehicle::Arrive();
        Base::goods_on_base += load;
    }

    bool Leave() {
        if (Base::goods_on_base >= load && Vehicle::Leave()) {
            Base::goods_on_base -= load;
            return true;
        }
        else {
            return false;
        }
    }
};

int main() {
    Base one;
    Truck truck(10.0, 30.0, 100.0, 150.0);
    Bus bus(20, 50, 200.0, 300.0);
    Vehicle vehicle(50.0, 100.0);

    truck.Leave();
    vehicle.Leave();
    bus.Leave();

    cout << "People on base: " << Base::people_on_base << "\n";
    cout << "Vehicles on base: " << Base::vehicles_on_base << "\n";
    cout << "Petrol on base: " << Base::petrol_on_base << "\n";
    cout << "Goods on base: " << Base::goods_on_base << "\n";
}