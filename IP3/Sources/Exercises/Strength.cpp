#include "../Headers/Exercises/Strength.h"
#include <iostream>

Strength::Strength(const std::string& name, int duration, int sets, int reps, double weight)
    : Exercise(name, duration), sets(sets), reps(reps), weight(weight) {}

double Strength::calculateCaloriesBurned(int duration) const {
    return sets * reps * (weight / 10.0) * 0.1 * duration;
}

Exercise* Strength::clone() const {
    return new Strength(*this);
}

void Strength::display() const {
    std::cout << "Strength: " << name << " | Duration: " << duration << " min | Sets: " 
              << sets << " | Reps: " << reps << " | Weight: " << weight << " kg | Calories: " 
              << calculateCaloriesBurned(duration) << std::endl;
}

int Strength::getSets() const {
    return sets;
}

int Strength::getReps() const {
    return reps;
}

double Strength::getWeight() const {
    return weight;
}
