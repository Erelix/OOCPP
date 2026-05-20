#ifndef STRENGTH_H_039394
#define STRENGTH_H_039394

#include "Exercise.h"

class Strength : public Exercise {
private:
    int sets;
    int reps; // reps per set
    double weight; // kg

public:
    Strength(const std::string& name, int duration, int sets, int reps, double weight);

    Strength(const Strength& other) = delete;
    Strength& operator=(const Strength& other) = delete;

    ~Strength() override;
    
    // Formula: sets * reps * (weight / 10) * 0.1 * duration
    double calculateCaloriesBurned(int duration) const override;

    Exercise* clone() const override;

    void display() const override;

    int getSets() const;
    int getReps() const;
    double getWeight() const;
};

#endif
