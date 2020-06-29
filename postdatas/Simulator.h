#ifndef SIMULATOR
#define SIMULATOR

#include "MOOS/libMOOS/App/MOOSApp.h"

class CSimulator : public CMOOSApp{
    public :
        CSimulator();
        virtual ~CSimulator();

    public :
        bool OnNewMail(MOOSMSG_LIST &NewMail);

        bool Iterate();

        bool OnConnectToServer();

        bool OnStartUp();

};

#endif