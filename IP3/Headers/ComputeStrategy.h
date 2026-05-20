#ifndef COMPUTE_STRATEGY_H_627621
#define COMPUTE_STRATEGY_H_627621

#include <vector>
#include <memory>
#include "Exercise.h"

class ComputeStrategy {
public:
    virtual ~ComputeStrategy() = default;

    /// exercises - Vector of pointers to exercises
    /// returns computed statistic value
    virtual double compute(const std::vector<Exercise*>& exercises) const = 0;

    virtual std::string getName() const = 0;
};

/// Strategy to compute total calories burned across all exercises
class TotalCaloriesStrategy : public ComputeStrategy {
public:
    double compute(const std::vector<Exercise*>& exercises) const override;
    std::string getName() const override { return "Total Calories"; }
};

/// Strategy to compute maximum calories burned in a single exercise
class MaxCaloriesStrategy : public ComputeStrategy {
public:
    double compute(const std::vector<Exercise*>& exercises) const override;
    std::string getName() const override { return "Maximum Calories"; }
};

/// Strategy to compute average calories burned per exercise
class AverageCaloriesStrategy : public ComputeStrategy {
public:
    double compute(const std::vector<Exercise*>& exercises) const override;
    std::string getName() const override { return "Average Calories"; }
};

#endif
