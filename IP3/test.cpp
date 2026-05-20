#include <iostream>
#include <cassert>
#include "Headers/Exercise.h"
#include "Headers/Exercises/Cardio.h"
#include "Headers/Exercises/Strength.h"
#include "Headers/exceptions.h"
#include "Headers/FitnessProgram.h"
#include "Headers/ComputeStrategy.h"

// Test counters
int testsRun = 0;
int testsPassed = 0;

void test(const std::string& name, bool condition) {
    testsRun++;
    if (condition) {
        testsPassed++;
        std::cout << "[PASS] " << name << std::endl;
    } else {
        std::cout << "[FAIL] " << name << std::endl;
    }
}

int main() {
    std::cout << "Fitness Program Test Suite" << std::endl << std::endl;

    std::cout << "--- Cardio Exercise Tests ---" << std::endl;
    Cardio running("Morning Run", 30, 150);
    test("Cardio name", running.getName() == "Morning Run");
    test("Cardio duration", running.getDuration() == 30);
    test("Cardio heart rate getter", running.getHeartRate() == 150);
    
    double runningCalories = running.calculateCaloriesBurned(30);
    test("Cardio calories calculation", runningCalories > 0);
    std::cout << "   Calories burned: " << runningCalories << std::endl;

    // Test Prototype for Cardio
    Exercise* runningCopy = running.clone();
    test("Cardio clone type", dynamic_cast<Cardio*>(runningCopy) != nullptr);
    test("Cardio clone equality", runningCopy->getName() == running.getName());
    delete runningCopy;


    std::cout << "\n--- Strength Exercise Tests ---" << std::endl;
    Strength deadlifts("Deadlifts", 20, 4, 8, 100);
    test("Strength name", deadlifts.getName() == "Deadlifts");
    test("Strength duration", deadlifts.getDuration() == 20);
    test("Strength sets getter", deadlifts.getSets() == 4);
    test("Strength reps getter", deadlifts.getReps() == 8);
    test("Strength weight getter", deadlifts.getWeight() == 100.0);

    double deadliftCalories = deadlifts.calculateCaloriesBurned(20);
    test("Strength calories calculation", deadliftCalories > 0);
    std::cout << "   Calories burned: " << deadliftCalories << std::endl;


    // Test Prototype for Strength
    Exercise* deadliftCopy = deadlifts.clone();
    test("Strength clone type", dynamic_cast<Strength*>(deadliftCopy) != nullptr);
    delete deadliftCopy;


    
    std::cout << "\n--- FitnessProgram Container Tests ---" << std::endl;
    FitnessProgram program;
    test("Empty program size", program.size() == 0);

    Cardio cycling("Cycling", 45, 140);
    Strength squats("Squats", 25, 5, 10, 80);

    program.addExercise(&running);
    program.addExercise(&cycling);
    program.addExercise(&deadlifts);
    program.addExercise(&squats);

    test("Program size after additions", program.size() == 4);
    test("Get exercise", program.getExercise(0) != nullptr);
    test("Get exercise name", program.getExercise(0)->getName() == "Morning Run");

    // TestRemove
    program.removeExercise(0);
    test("Program size after removal", program.size() == 3);

    // Add it back
    program.addExercise(&running);
    test("Program size after re-adding", program.size() == 4);


    std::cout << "\n--- Iterator Tests ---" << std::endl;
    int count = 0;
    for (auto it = program.begin(); it != program.end(); ++it) {
        count++;
    }
    test("Iterator count", count == 4);

    // Test iterator comparison
    auto it1 = program.begin();
    auto it2 = program.begin();
    test("Iterator equality", it1 == it2);
    ++it1;
    test("Iterator inequality after increment", it1 != it2);

    // Test iterator random access
    auto begin = program.begin();
    auto end = program.end();
    test("Iterator less than", begin < end);
    test("Iterator greater than", end > begin);


    std::cout << "\n--- Operator Tests ---" << std::endl;
    test("Exercise operator< (deadlifts < running)", deadlifts < running);

    auto it_op = program.begin();
    test("Iterator operator->", (*it_op)->getName() == "Cycling");

    auto it_plus = program.begin() + 2;
    test("Iterator operator+ and deref", (*it_plus)->getName() == "Squats");

    test("Iterator operator[]", (program.begin()[2])->getName() == "Squats");

    auto it3 = program.begin();
    it3 += 2;
    test("Iterator operator+=", (*it3)->getName() == "Squats");
    it3 -= 1;
    test("Iterator operator-=", (*it3)->getName() == "Deadlifts");

    auto it_post = program.begin();
    auto it_old = it_post++;
    test("Iterator post-increment returns old", (*it_old)->getName() == "Cycling");
    test("Iterator post-increment advanced", (*it_post)->getName() == "Deadlifts");

    auto it_last = program.end();
    --it_last;
    test("Iterator pre-decrement from end", (*it_last)->getName() == "Morning Run");

    auto dist = program.end() - program.begin();
    test("Iterator distance equals size", dist == program.size());

    auto dist2 = it_plus - program.begin();
    test("Iterator subtraction yields correct distance", dist2 == 2);


    std::cout << "\n--- Deep Copy (Prototype Pattern) Tests ---" << std::endl;
    FitnessProgram originalProgram;
    originalProgram.addExercise(&running);
    originalProgram.addExercise(&cycling);

    // Deep copy test
    FitnessProgram copiedProgram = originalProgram;
    test("Deep copy size matches", copiedProgram.size() == originalProgram.size());
    test("Deep copy creates different instances", 
         copiedProgram.getExercise(0) != originalProgram.getExercise(0));

    // Assignment operator (deep copy) tests
    FitnessProgram assignedProgram;
    assignedProgram = originalProgram;
    test("Assignment deep copy size matches", assignedProgram.size() == originalProgram.size());
    test("Assignment deep copy creates different instances", 
        assignedProgram.getExercise(0) != originalProgram.getExercise(0));


    std::cout << "\n--- Strategy Pattern Tests ---" << std::endl;
    FitnessProgram strategyProgram;
    strategyProgram.addExercise(&running);
    strategyProgram.addExercise(&cycling);
    strategyProgram.addExercise(&deadlifts);
    strategyProgram.addExercise(&squats);

    // Test strategy not set exception
    try {
        strategyProgram.compute();
        test("StrategyNotSet exception", false);
    } catch (const StrategyNotSetException&) {
        test("StrategyNotSet exception", true);
    }

    // Test Total strategy
    strategyProgram.setComputeStrategy(new TotalCaloriesStrategy());
    double total = strategyProgram.compute();
    test("Total calories strategy", total > 0);
    std::cout << "   Total calories: " << total << std::endl;

    // Test Max strategy
    strategyProgram.setComputeStrategy(new MaxCaloriesStrategy());
    double maxCal = strategyProgram.compute();
    test("Max calories strategy", maxCal > 0);
    std::cout << "   Max calories: " << maxCal << std::endl;

    // Test Average strategy
    strategyProgram.setComputeStrategy(new AverageCaloriesStrategy());
    double avgCal = strategyProgram.compute();
    test("Average calories strategy", avgCal > 0);
    std::cout << "   Average calories: " << avgCal << std::endl;


    std::cout << "\n--- Callback (Filter) Tests ---" << std::endl;
    std::vector<Exercise*> filtered1 = strategyProgram.filter(
        [](const Exercise* ex) { return ex->getDuration() >= 25; }
    );
    test("Filter by duration >= 25", filtered1.size() >= 2);
    std::cout << "   Filtered exercises: " << filtered1.size() << std::endl;

    std::vector<Exercise*> filtered2 = strategyProgram.filter(
        [](const Exercise* ex) { return dynamic_cast<const Cardio*>(ex) != nullptr; }
    );
    test("Filter by Cardio type", filtered2.size() == 2);
    std::cout << "   Cardio exercises: " << filtered2.size() << std::endl;


    std::cout << "\n--- Polymorphism Tests ---" << std::endl;
    Exercise* cardioPtr = &running;
    Exercise* strengthPtr = &deadlifts;
    
    double cardioResult = cardioPtr->calculateCaloriesBurned(30);
    double strengthResult = strengthPtr->calculateCaloriesBurned(20);
    
    test("Polymorphic calculation differs by type", cardioResult != strengthResult);
    std::cout << "   Cardio: " << cardioResult << " | Strength: " << strengthResult << std::endl;


    // Stretch Tests - not implemented
    std::cout << "\n--- Stretch Class Tests (Not Yet Implemented) ---" << std::endl;
    std::cout << "The Stretch class will be implemented with the following specifications:" << std::endl;
    std::cout << "1. Constructor: Stretch(name, duration, flexibilityLevel, targetArea)" << std::endl;
    std::cout << "2. calculateCaloriesBurned() throws NotImplementedException" << std::endl;
    std::cout << "3. clone() method for Prototype pattern" << std::endl;
    std::cout << "4. display() method showing all Stretch properties" << std::endl;
    std::cout << "5. getFlexibilityLevel() and getTargetArea() accessors" << std::endl;



    std::cout << "\n=== Test Summary ===" << std::endl;
    std::cout << "Tests run: " << testsRun << std::endl;
    std::cout << "Tests passed: " << testsPassed << std::endl;
    std::cout << "Tests failed: " << (testsRun - testsPassed) << std::endl;
    std::cout << "Success rate: " << (100.0 * testsPassed / testsRun) << "%" << std::endl;

    return (testsRun == testsPassed) ? 0 : 1;
}
