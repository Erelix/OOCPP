#include "../Headers/Exercise.h"
#include <iostream>

Exercise::Exercise(const std::string& name, int duration)
    : name(name), duration(duration) {}

std::string Exercise::getName() const {
    return name;
}

int Exercise::getDuration() const {
    return duration;
}

void Exercise::display() const {
    std::cout << "Exercise: " << name << " | Duration: " << duration << " min" << std::endl;
}

bool Exercise::operator<(const Exercise& other) const {
    return duration < other.duration;
}
