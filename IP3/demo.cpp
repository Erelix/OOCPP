#include <iostream>
#include <algorithm>
#include "Headers/Exercise.h"
#include "Headers/Exercises/Cardio.h"
#include "Headers/Exercises/Strength.h"
#include "Headers/exceptions.h"
#include "Headers/FitnessProgram.h"
#include "Headers/ComputeStrategy.h"

int main() {
    std::cout << "=========== Demo ==============" << std::endl;

    FitnessProgram program;

    Cardio running("Morning Run", 30, 150);
    Cardio cycling("Cycling", 45, 140);
    Strength deadlifts("Deadlifts", 20, 4, 8, 100);
    Strength squats("Squats", 25, 5, 10, 80);

    program.addExercise(&running);
    program.addExercise(&cycling);
    program.addExercise(&deadlifts);
    program.addExercise(&squats);

    program.displayAll();

    std::cout << std::endl;
    int i = 1;
    // polymorphism
    for (auto it = program.begin(); it != program.end(); ++it) {
        std::cout << i++ << ". "<<"Calories burned: " << (*it)->calculateCaloriesBurned((*it)->getDuration()) << " cal" << std::endl;
    }
    
    // iterator
    std::cout << "\nUsing Iterator with std::sort" << std::endl;
    std::sort(program.begin(), program.end(), 
              [](const Exercise* a, const Exercise* b) { 
                  return *a < *b; 
              });
    
    program.displayAll();

    // deep copy
    std::cout << "\nDeep Copy" << std::endl;
    FitnessProgram programCopy = program;
    std::cout << "Original program size: " << program.size() << std::endl;
    std::cout << "Copied program size: " << programCopy.size() << std::endl;

    // strategy
    std::cout << "\nStrategy Pattern" << std::endl;
    program.setComputeStrategy(new TotalCaloriesStrategy());
    std::cout << "Strategy: " << program.getCurrentStrategyName() << std::endl;
    std::cout << "Result: " << program.compute() << " cal" << std::endl;

    program.setComputeStrategy(new MaxCaloriesStrategy());
    std::cout << "Strategy: " << program.getCurrentStrategyName() << std::endl;
    std::cout << "Result: " << program.compute() << " cal" << std::endl;

    program.setComputeStrategy(new AverageCaloriesStrategy());
    std::cout << "Strategy: " << program.getCurrentStrategyName() << std::endl;
    std::cout << "Result: " << program.compute() << " calories" << std::endl;

    // callback
    std::cout << "\nCallback Filter Demo" << std::endl;
    std::vector<Exercise*> filtered = program.filter(
        [](const Exercise* ex) { return ex->getDuration() >= 25; }
    );
    
    // "one method in the container that passes through all the objects in the container"
    std::cout << "Exercises with duration >= 25 minutes:" << std::endl;
    for (const auto& ex : filtered) {
        ex->display();
    }

    std::cout << "\nDemo Completed" << std::endl;

    return 0;
}
