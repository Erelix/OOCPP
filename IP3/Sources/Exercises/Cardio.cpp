#include "../Headers/Exercises/Cardio.h"
#include <iostream>

Cardio::Cardio(const std::string& name, int duration, int heartRate)
    : Exercise(name, duration), heartRate(heartRate) {}

double Cardio::calculateCaloriesBurned(int duration) const {
    return (heartRate - 60) * 0.5 * duration;
}

Exercise* Cardio::clone() const {
    return new Cardio(*this);
}

void Cardio::display() const {
    std::cout << "Cardio: " << name << " | Duration: " << duration << " min | Heart Rate: " 
              << heartRate << " bpm | Calories: " << calculateCaloriesBurned(duration) << std::endl;
}

int Cardio::getHeartRate() const {
    return heartRate;
}
