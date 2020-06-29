#ifndef SIMPLEAPPH
#define SIMPLEAPPH

#include "MOOS/libMOOS/App/MOOSApp.h"

class CSimpleApp : public CMOOSApp{
    public :
        CSimpleApp();
        virtual ~CSimpleApp();

    public :
        bool OnNewMail(MOOSMSG_LIST &NewMail);

        bool Iterate();

        bool OnConnectToServer();

        bool OnStartUp();

        //our code
        void DoRegistrations();

        bool OnVehicleStatus(CMOOSMsg &Msg);

        bool OnHeading(CMOOSMsg &Msg);

};

#endif