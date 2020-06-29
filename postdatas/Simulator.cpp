#include "Simulator.h"
#include <math.h>

CSimulator::CSimulator(){
    
}

CSimulator::~CSimulator(){

}

bool CSimulator::OnNewMail(MOOSMSG_LIST &newmail){
    return true;
}

bool CSimulator::OnConnectToServer(){
    return true;
}

bool CSimulator::Iterate(){
    static int k = 0;
    if(k++ % 10 == 0){
        static double dfHeading = 0;
        dfHeading += MOOSWhiteNoise(0.1);

        m_Comms.Notify("Heading", dfHeading,MOOSTime());

    }
    if(k %35 == 0){
        static double dfVolts = 100;
        dfVolts -= fabs(MOOSWhiteNoise(0.1));
        std::string Status = MOOSFormat("Status = %s, BatteryVoltage = %.2f, Bilge \
        = %s", dfVolts > 50.0 ? "Good":"Bad", dfVolts,k % 100 > 50 ? "On":"Off");

        m_Comms.Notify("VehicleStatus",Status,MOOSTime());

    }
    return true;

}

bool CSimulator::OnStartUp(){

    std::string m_sVehicleName = "UnNamed";
    if(!m_MissionReader.GetConfigurationParam("VehicleName", m_sVehicleName)){
        MOOSTrace("VehicleName not specified\n");
    }

    std::vector<double> vInitialLocation(3, 0.0);
    int nRows = vInitialLocation.size();
    int nCols = 1;
    if(!m_MissionReader.GetConfigurationParam("InitialLocation", vInitialLocation,nRows,nCols)){
        MOOSTrace("initiallocation not specified\n");

    }

    std::string sComplex;
    std::string m_sBilge = "Off";
    double m_dfBatteryVolage = 100.0;
    double m_dfHeading = 0;

    if(m_MissionReader.GetConfigurationParam("InitialConditions",sComplex)){

        MOOSValFromString(m_sBilge, sComplex, "Bilge");

        MOOSValFromString(m_dfBatteryVolage, sComplex, "BatteryVoltage");

        MOOSValFromString(m_dfHeading, sComplex, "Heading");

    }
    else
    {
        return MOOSFail("no InitialCondition specified\n");

    }

    MOOSTrace("Verbose Summary:\n");
    MOOSTrace("\tVehicle is called : %s\n", m_sVehicleName.c_str());
    MOOSTrace("\tInitialLocation : %s \n", DoubleVector2String(vInitialLocation).c_str());
    MOOSTrace("\tHeading : %f\n", m_dfHeading);
    MOOSTrace("\tBatteryVoltage : %s \n", m_sBilge.c_str());
    
    return true;
}