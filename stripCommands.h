#include "stripVariables.h"
#include "Constants.h"
namespace stripCommands {
    /**
     * @brief Runs the switch function handling timers. 
     * @note probably should be called instead of switchPixel() 
     * becuase it updates the timers and checks
    */
    void runSwitch();

    /**
     *@brief Moves the electron foward on all the strios
    */
    void moveElectronFoward();

    void updateBlinks();

    void blinkAll(int times);

    /**
     * @brief switches the electrons between the inner and outer strip
    */
    void switchPixel();

    bool shouldSwitch();

    unsigned long getLastSwitchTime();
}
