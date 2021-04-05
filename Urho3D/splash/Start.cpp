#include "splash.h"



/**
 * Start function. Executes base class startup, calls Scene1 for welcome screen
 * expect and accept mouse input 
 * 
 */
void GameSys::Start()
{   
    // Execute base class startup
    Sample::Start();

    // Create "Hello World" Text
    CreateScene1();

    // Set the mouse mode to use in the sample
    Sample::InitMouseMode(MM_FREE);
    
return;
}
