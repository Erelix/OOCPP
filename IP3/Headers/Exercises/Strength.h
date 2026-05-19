#ifndef STRENGTH_H_039394
#define STRENGTH_H_039394

#include "Exercise.h"

/// Formula: sets * reps * (weight / 10) * 0.1 * duration
class Strength : public Exercise {
private:
    int sets;
    int reps; // reps per set
    double weight; // kg

public:
    Strength(const std::string& name, int duration, int sets, int reps, double weight);
    
    double calculateCaloriesBurned(int duration) const override;

    Exercise* clone() const override;

    void display() const override;

    int getSets() const;
    int getReps() const;
    double getWeight() const;
};

#endif
