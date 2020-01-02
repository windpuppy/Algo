#pragma once

#include <string>
#include <vector>

using namespace std;

// Vehicle base
class IVehicle {
  virtual int getSize() const = 0;
};

class Vehicle : public IVehicle{
  string plate;
  int size;

public:
  Vehicle() : plate(""), size(0) {}
  Vehicle(string p, int s) {
    plate = p;
    size = s;
  }

  int getSize() const { return size; }
};


// Vehicle classes
class Car : Vehicle {
public:
  Car(string p, int s) : Vehicle(p, s) {}
};

class Truck : Vehicle {
public:
  Truck(string p, int s) : Vehicle(p, s) {}
};



// Handicap spots, that takes all S, M, L sizes?
class ParkingSpot {
private:
  int size;
  Vehicle* currentVehicle;

public:
  ParkingSpot(int s) : size(s), currentVehicle(NULL) {}

  bool fit(Vehicle* v) {
    if (currentVehicle != NULL) return false;
    return v->getSize() <= size;
  }

  bool park(Vehicle* v) {
    if (!fit(v)) return false;
    currentVehicle = v;
  }

  void leave() {
    currentVehicle = NULL;
  }

  Vehicle* getVehicle() {
    return currentVehicle;
  }
};



// Preiume levels?
class Level {
  vector<ParkingSpot> spots;
  int numCars;
  double filledRatio;

public:
  Level(int capacity) {
    spots.resize(capacity);
    numCars = 0;
    filledRatio = 0;
  }

  bool hasSpot(Vehicle* v) {
    int size = v->getSize();
    return true;
  }

  double getFilledRatio() {
    return filledRatio;
  }

  void park(Vehicle *v) {
    auto spot = spots.front(); // add business logic here, hashmap?
    if (spot.park(v)) {
      numCars++;
      filledRatio = numCars / spots.size();
    }
  }


  void leave(Vehicle *v) {
    auto spot = spots.front(); // add business logic here, hashmap?
    numCars--;
    filledRatio = numCars / spots.size();
  }
};


