#include "../Headers/ComputeStrategy.h"
#include <algorithm>

double TotalCaloriesStrategy::compute(const std::vector<Exercise*>& exercises) const {
    double total = 0.0;
    for (const auto& exercise : exercises) {
        total += exercise->calculateCaloriesBurned(exercise->getDuration());
    }
    return total;
}

double MaxCaloriesStrategy::compute(const std::vector<Exercise*>& exercises) const {
    if (exercises.empty()) return 0.0;
    
    double maxCalories = 0.0;
    for (const auto& exercise : exercises) {
        double calories = exercise->calculateCaloriesBurned(exercise->getDuration());
        maxCalories = std::max(maxCalories, calories);
    }
    return maxCalories;
}

double AverageCaloriesStrategy::compute(const std::vector<Exercise*>& exercises) const {
    if (exercises.empty()) return 0.0;
    
    double total = 0.0;
    for (const auto& exercise : exercises) {
        total += exercise->calculateCaloriesBurned(exercise->getDuration());
    }
    return total / exercises.size();
}
