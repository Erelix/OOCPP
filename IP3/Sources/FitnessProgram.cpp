#include "../Headers/FitnessProgram.h"
#include <iostream>
#include <algorithm>

FitnessProgram::FitnessProgram() : currentStrategy(nullptr) {}

FitnessProgram::FitnessProgram(const FitnessProgram& other) : currentStrategy(nullptr) {
    for (const auto& exercise : other.exercises) {
        exercises.push_back(exercise->clone());
    }
}

FitnessProgram& FitnessProgram::operator=(const FitnessProgram& other) {
    if (this != &other) {
        clear();
        delete currentStrategy;
        currentStrategy = nullptr;

        for (const auto& exercise : other.exercises) {
            exercises.push_back(exercise->clone());
        }
    }
    return *this;
}

FitnessProgram::~FitnessProgram() {
    clear();
    delete currentStrategy;
}

void FitnessProgram::addExercise(const Exercise* exercise) {
    if (exercise != nullptr) {
        exercises.push_back(exercise->clone());
    }
}

void FitnessProgram::removeExercise(int index) {
    if (index >= 0 && index < static_cast<int>(exercises.size())) {
        delete exercises[index];
        exercises.erase(exercises.begin() + index);
    }
}

Exercise* FitnessProgram::getExercise(int index) const {
    if (index >= 0 && index < static_cast<int>(exercises.size())) {
        return exercises[index];
    }
    return nullptr;
}

int FitnessProgram::size() const {
    return exercises.size();
}

void FitnessProgram::clear() {
    for (auto& exercise : exercises) {
        delete exercise;
    }
    exercises.clear();
}

FitnessProgram::Iterator FitnessProgram::begin() const {
    return Iterator(const_cast<std::vector<Exercise*>*>(&exercises), 0);
}

FitnessProgram::Iterator FitnessProgram::end() const {
    return Iterator(const_cast<std::vector<Exercise*>*>(&exercises), exercises.size());
}

void FitnessProgram::setComputeStrategy(ComputeStrategy* strategy) {
    delete currentStrategy;
    currentStrategy = strategy;
}

double FitnessProgram::compute() const {
    if (currentStrategy == nullptr) {
        throw StrategyNotSetException("No computation strategy has been set. Use setComputeStrategy() first.");
    }
    return currentStrategy->compute(exercises);
}

std::string FitnessProgram::getCurrentStrategyName() const {
    if (currentStrategy == nullptr) {
        return "No strategy set";
    }
    return currentStrategy->getName();
}

std::vector<Exercise*> FitnessProgram::filter(std::function<bool(const Exercise*)> predicate) const {
    std::vector<Exercise*> result;
    for (const auto& exercise : exercises) {
        if (predicate(exercise)) {
            result.push_back(exercise);
        }
    }
    return result;
}

void FitnessProgram::displayAll() const {
    std::cout << "\nFitness Program Exercises" << std::endl;
    for (size_t i = 0; i < exercises.size(); ++i) {
        std::cout << (i + 1) << ". ";
        exercises[i]->display();
    }
}

// Iterator implementation
FitnessProgram::Iterator::Iterator(std::vector<Exercise*>* data, size_t pos)
    : data(data), pos(pos) {}

Exercise*& FitnessProgram::Iterator::operator*() const {
    return (*data)[pos];
}

Exercise** FitnessProgram::Iterator::operator->() const {
    return &(*data)[pos];
}

FitnessProgram::Iterator& FitnessProgram::Iterator::operator++() {
    ++pos;
    return *this;
}

FitnessProgram::Iterator FitnessProgram::Iterator::operator++(int) {
    Iterator tmp = *this;
    ++pos;
    return tmp;
}

FitnessProgram::Iterator& FitnessProgram::Iterator::operator--() {
    --pos;
    return *this;
}

FitnessProgram::Iterator FitnessProgram::Iterator::operator--(int) {
    Iterator tmp = *this;
    --pos;
    return tmp;
}

FitnessProgram::Iterator& FitnessProgram::Iterator::operator+=(difference_type n) {
    pos += n;
    return *this;
}

FitnessProgram::Iterator& FitnessProgram::Iterator::operator-=(difference_type n) {
    pos -= n;
    return *this;
}

FitnessProgram::Iterator FitnessProgram::Iterator::operator+(difference_type n) const {
    return Iterator(data, pos + n);
}

FitnessProgram::Iterator FitnessProgram::Iterator::operator-(difference_type n) const {
    return Iterator(data, pos - n);
}

FitnessProgram::Iterator::difference_type FitnessProgram::Iterator::operator-(const Iterator& other) const {
    return static_cast<difference_type>(pos) - static_cast<difference_type>(other.pos);
}

bool FitnessProgram::Iterator::operator==(const Iterator& other) const {
    return pos == other.pos && data == other.data;
}

bool FitnessProgram::Iterator::operator!=(const Iterator& other) const {
    return !(*this == other);
}

bool FitnessProgram::Iterator::operator<(const Iterator& other) const {
    return pos < other.pos;
}

bool FitnessProgram::Iterator::operator<=(const Iterator& other) const {
    return pos <= other.pos;
}

bool FitnessProgram::Iterator::operator>(const Iterator& other) const {
    return pos > other.pos;
}

bool FitnessProgram::Iterator::operator>=(const Iterator& other) const {
    return pos >= other.pos;
}

Exercise*& FitnessProgram::Iterator::operator[](difference_type n) const {
    return (*data)[pos + n];
}
