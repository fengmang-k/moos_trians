#include "Simulator.h"

int main(int argc, char *argv[]){
    MOOS::CommandLineParser P(argc, argv);

    std::string mission_file = P.GetFreeParameter(0, "ex40.moos");
    std::string app_name = P.GetFreeParameter(1, "Simulator");


    CSimulator TheApp;
    TheApp.Run(app_name, mission_file, argc, argv);

    return 0;

}