
#include "global.hpp"

std::ofstream logFile;

void sendMessageToLogFile(std::string message, bool errorOrNot, double duration)
{
    time_t now = time(0);
    char *dt = ctime(&now);
    if ((errorOrNot == true || errorOrNot == false) && duration == 0)
        logFile << message << " | " << dt << std::endl;
    else
    {
        logFile << message << " | " << dt << " | Duration: " << duration << std::endl;
        logFile << std::endl;
    }

}

