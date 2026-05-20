#ifndef EXERCISE_H_281192
#define EXERCISE_H_281192

#include <string>
#include <memory>

/// Defines the interface for calculating calories burned during exercises.
class Exercise {

protected:
    std::string name;
    int duration; // min

public:

    Exercise(const std::string& name, int duration);

    Exercise(const Exercise& other) = delete;
    Exercise& operator=(const Exercise& other) = delete;

    virtual ~Exercise();

    // duration(min)
    // returns calories burned(approximately)
    virtual double calculateCaloriesBurned(int duration) const = 0;

    std::string getName() const;

    int getDuration() const;

    /// olymorphic copy (Prototype pattern)
    virtual Exercise* clone() const = 0;

    virtual void display() const;

    /// Less-than operator for sorting
    bool operator<(const Exercise& other) const;
};

#endif