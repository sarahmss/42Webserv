
#include "global.hpp"

std::ofstream logFile;
clock_t start;
clock_t end;

void sendMessageToLogFile(std::string message, bool errorOrNot, double duration)
{
    time_t now = time(0);
    char *dt = ctime(&now);
    if ((errorOrNot == true || errorOrNot == false) && duration == 0)
        logFile << message << " | " << dt << std::endl;
    else
    {
        logFile << message << " | " << dt << " | Duration: " << duration;
        logFile << std::endl;
    }

}

std::string		concatenate_string(std::string s1, std::string s2)
{
	std::string ret = s1 + s2;
	return ret;
}

std::string		concatenate_int(std::string s1, int n2)
{
	std::ostringstream oss;
    oss << n2;

    std::string resultado = s1 + oss.str();
    return resultado;
}
