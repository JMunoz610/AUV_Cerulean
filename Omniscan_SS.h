/************************************************************/
/*    NAME: Jacob Munoz                                              */
/*    ORGN: MIT, Cambridge MA                               */
/*    FILE: Omniscan_SS.h                                          */
/*    DATE: December 29th, 1963                             */
/************************************************************/

#ifndef Omniscan_SS_HEADER
#define Omniscan_SS_HEADER

#include "MOOS/libMOOS/Thirdparty/AppCasting/AppCastingMOOSApp.h"

class Omniscan_SS : public AppCastingMOOSApp
{
 public:
   Omniscan_SS();
   ~Omniscan_SS();

 protected: // Standard MOOSApp functions to overload  
   bool OnNewMail(MOOSMSG_LIST &NewMail);
   bool Iterate();
   bool OnConnectToServer();
   bool OnStartUp();

   //added function
   void remove_important_information(const std::string& long_message);

 protected: // Standard AppCastingMOOSApp function to overload 
   bool buildReport();

 protected:
   void registerVariables();

 private: // Configuration variables

 private: // State variables

  // full message strings
  std::string m_raw_gps;
  std::string m_raw_imu;
  std::string m_raw_depth;

  // variables parsed out of full messages
  std::string depth_value;
};

#endif 
