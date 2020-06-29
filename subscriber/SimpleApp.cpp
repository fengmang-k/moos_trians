#include "SimpleApp.h"

CSimpleApp::CSimpleApp(){

}
//destructor
CSimpleApp::~CSimpleApp(){

}

bool CSimpleApp::OnNewMail(MOOSMSG_LIST &NewMail){
    MOOSMSG_LIST::iterator p;
    for(p = NewMail.begin(); p != NewMail.end(); p++){
        CMOOSMsg & rMsg = *p;
        if(MOOSStrCmp(rMsg.GetKey(), "VehicleStatus")){
            OnVehicleStatus(rMsg);
        }
        else if(MOOSStrCmp(rMsg.GetKey(), "Heading")){

            OnHeading(rMsg);
        }
    }

    return true;
}

bool CSimpleApp::OnConnectToServer(){

    DoRegistrations();
    return true;
}
bool CSimpleApp::Iterate(){
    return true;
}

bool CSimpleApp::OnStartUp(){

    DoRegistrations();
    return true;
}

//
bool CSimpleApp::OnVehicleStatus(CMOOSMsg &Msg){
    MOOSTrace("I (%s) received a notifocation about \"%s\"the detail are :\n", \
    GetAppName().c_str(), Msg.GetKey().c_str());

    if(!Msg.IsString()){
        return MOOSFail("I was promised \" VehicleStatus\"would be a string!");

    }

    std::string sStatus = "Unknown";
    if(!MOOSValFromString(sStatus, Msg.GetString(),"Status")){
        MOOSTrace("warning fied \"Status \"not found in VehicleStatus String %s", \
        MOOSHERE);
    }

    double dfBatteryVoltage = -1;
    if(!MOOSValFromString(dfBatteryVoltage, Msg.GetString(),"BatteryVoltage")){
        MOOSTrace("warning fied \"BatteryVoltage\"not found in VehicleStatus String %s", \
        MOOSHERE);
    }
    //print findings ..
    MOOSTrace("Status is \"%s\"battery voltage is %.2f V\n", sStatus.c_str(),dfBatteryVoltage);
    return true;
}

bool CSimpleApp::OnHeading(CMOOSMsg & Msg){
    MOOSTrace("I (%s) received a notifocation about \"%s\"the detail are :\n", \
    GetAppName().c_str(), Msg.GetKey().c_str());

    if(!Msg.IsDouble()){
        return MOOSFail("I was promised \" Heading\"would be a double %s",MOOSHERE);

    }

    double dfHeading = Msg.GetDouble();
    double dfTime = Msg.GetTime();
    MOOSTrace("The heading (according to process %s), at time %f (%f since appstart) is %f\n", \
    Msg.GetSource().c_str(),dfTime, dfTime - GetAppStartTime(),dfHeading);
    return true;
}

void CSimpleApp::DoRegistrations(){
    m_Comms.Register("VehicleStatus", 0.0);
    m_Comms.Register("Heading", 0.25);

    return ;


}

