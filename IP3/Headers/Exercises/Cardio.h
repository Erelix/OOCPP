#ifndef CARDIO_H_092923
#define CARDIO_H_092923

#include "Exercise.h"

/// Formula: (heart_rate - 60) * 0.5 * duration
class Cardio : public Exercise {
private:
    int heartRate; // beats per minute

public:
    Cardio(const std::string& name, int duration, int heartRate);
    
    /**
     * @brief Calculate calories burned during cardio exercise
     * @param duration Duration in minutes
     * @return Calories burned
     */
    double calculateCaloriesBurned(int duration) const override;

    /**
     * @brief Polymorphic copy (Prototype pattern)
     */
    Exercise* clone() const override;

    /**
     * @brief Display cardio exercise information
     */
    void display() const override;

    /**
     * @brief Get heart rate
     */
    int getHeartRate() const;
};

#endif
