#ifndef FITNESS_PROGRAM_H_738445
#define FITNESS_PROGRAM_H_738445

#include <vector>
#include <memory>
#include <functional>
#include "Exercise.h"
#include "ComputeStrategy.h"
#include "exceptions.h"

/**
 * This container holds pointers to exercises and provides:
 * - CRUD operations
 * - Strategy pattern for different computations
 * - Callback support for filtering exercises
 * - Iterator implementation
 * - Deep copy capability(Prototype pattern)
 */
class FitnessProgram {
public:
    class Iterator;

    FitnessProgram();

    /// Copy constructor and assignment (deep copy)
    FitnessProgram(const FitnessProgram& other);
    FitnessProgram& operator=(const FitnessProgram& other);

    ~FitnessProgram();

    /// CRUD operations
    void addExercise(const Exercise* exercise);
    void removeExercise(int index);
    Exercise* getExercise(int index) const;

    /// Get total number of exercises
    int size() const;

    /// Clear all exercises
    void clear();

    Iterator begin() const;
    Iterator end() const;

    void setComputeStrategy(ComputeStrategy* strategy);

    /// Compute using the current strategy
    /// StrategyNotSetException if no strategy is set
    double compute() const;

    std::string getCurrentStrategyName() const;

    /// Callback support
    std::vector<Exercise*> filter(std::function<bool(const Exercise*)> predicate) const;

    void displayAll() const;

public:
    class Iterator {
    public:
        using iterator_category = std::random_access_iterator_tag;
        using value_type = Exercise*;
        using difference_type = std::ptrdiff_t;
        using pointer = Exercise**;
        using reference = Exercise*&;

        Iterator(std::vector<Exercise*>* data, size_t pos);

        /// Dereference operator
        Exercise*& operator*() const;
        Exercise** operator->() const;

        /// Increment/Decrement
        Iterator& operator++();    // Pre-increment
        Iterator operator++(int);  // Post-increment
        Iterator& operator--();    // Pre-decrement
        Iterator operator--(int);  // Post-decrement

        /// Random access
        Iterator& operator+=(difference_type n);
        Iterator& operator-=(difference_type n);
        Iterator operator+(difference_type n) const;
        Iterator operator-(difference_type n) const;
        difference_type operator-(const Iterator& other) const;

        /// Comparison
        bool operator==(const Iterator& other) const;
        bool operator!=(const Iterator& other) const;
        bool operator<(const Iterator& other) const;
        bool operator<=(const Iterator& other) const;
        bool operator>(const Iterator& other) const;
        bool operator>=(const Iterator& other) const;

        /// Subscript
        Exercise*& operator[](difference_type n) const;

    private:
        std::vector<Exercise*>* data;
        size_t pos;
    };

private:
    std::vector<Exercise*> exercises;
    ComputeStrategy* currentStrategy;
};

#endif
