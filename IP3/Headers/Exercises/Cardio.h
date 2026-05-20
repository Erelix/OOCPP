#ifndef CARDIO_H_092923
#define CARDIO_H_092923

#include "Exercise.h"

/// Formula: (heart_rate - 60) * 0.5 * duration
class Cardio : public Exercise {
private:
    int heartRate; // beats per minute

public:
    Cardio(const std::string& name, int duration, int heartRate);

    Cardio(const Cardio& other) = delete;
    Cardio& operator=(const Cardio& other) = delete;

    ~Cardio() override;
    
    double calculateCaloriesBurned(int duration) const override;

    Exercise* clone() const override;

    void display() const override;

    int getHeartRate() const;
};

#endif
