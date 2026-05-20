/*
 * Stretch.cpp - Implementation Specification
 * 
 * The Stretch class represents flexibility and stretching exercises in a fitness program.
 * 
 * Private fields:
 * - int flexibilityLevel;  // 0-10 scale: 0 (beginner) to 10 (advanced)
 * - std::string targetArea; // Body region: "hamstrings", "shoulders", "back", "full_body", etc.
 * 
 * Public methods:
 * 
 * 1. Constructor:
 *    Stretch(const std::string& name, int duration, int flexibilityLevel, const std::string& targetArea)
 *    - Initialize base class with name and duration
 *    - Set flexibility level (validate 0-10 range)
 *    - Set target area
 * 
 * 2. calculateCaloriesBurned(int duration) - override:
 *    - MUST throw NotImplementedException
 *    - Reasoning: Stretching burns minimal calories; this demonstrates exception handling
 *    - Message: "Stretch exercises calorie calculation not yet supported"
 * 
 * 3. clone() - override:
 *    - Return a deep copy of the current Stretch object
 *    - Use: return new Stretch(*this);
 *    - Purpose: Implements Prototype pattern for polymorphic copying
 * 
 * 4. display() - override:
 *    - Print: "Stretch: [name] | Duration: [duration] min | Target: [targetArea] | Flexibility: [level]"
 *    - So, output: "Stretch: Yoga Session | Duration: 30 min | Target: full_body | Flexibility: 7"
 * 
 * 5. Getter methods:
 *    - int getFlexibilityLevel() const
 *    - std::string getTargetArea() const
 * 
 * Testing:
 * - Test construction with various flexibility levels
 * - Test that calculateCaloriesBurned properly throws NotImplementedException
 * - Test clone() creates independent copy
 * - Test display() outputs correct format
 * - Use with FitnessProgram container to verify polymorphic behavior
 */
