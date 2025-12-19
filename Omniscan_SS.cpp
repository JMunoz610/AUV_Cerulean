/************************************************************/
/*    NAME: Jacob Munoz                                              */
/*    ORGN: MIT, Cambridge MA                               */
/*    FILE: Omniscan_SS.cpp                                        */
/*    DATE: October 24th, 2025                             */
/************************************************************/

#include <iterator>
#include "MBUtils.h"
#include "ACTable.h"
#include <string>
#include <sstream>
#include <iostream>
#include "Omniscan_SS.h"

using namespace std;

//---------------------------------------------------------
// Constructor()

Omniscan_SS::Omniscan_SS()
{
  // initialize variables
  m_raw_gps = "";
  m_raw_imu = "";
  m_raw_depth = "";
  depth_value = "";
}

//---------------------------------------------------------
// Destructor

Omniscan_SS::~Omniscan_SS()
{
}

//---------------------------------------------------------
// Procedure: OnNewMail()

bool Omniscan_SS::OnNewMail(MOOSMSG_LIST &NewMail)
{

AppCastingMOOSApp::OnNewMail(NewMail);

  MOOSMSG_LIST::iterator p;
  for(p=NewMail.begin(); p!=NewMail.end(); p++) {
    CMOOSMsg &msg = *p;
    string key    = msg.GetKey();

    if(key == "RAW_GPS"){
      m_raw_gps = msg.GetString();
      //need to write some function to extract this data
    }
    else if(key == "RAW_IMU"){
      m_raw_imu = msg.GetString();
      //same as above
    }
    else if(key == "RAW_DEPTH"){
      m_raw_depth = msg.GetString();
      remove_important_information(m_raw_depth);
      m_Comms.Notify("DEPTH_VALUE", depth_value);
    }
    else if(key != "APPCASE_REQ"){
      reportRunWarning("Unhandled Mail: " + key);
    }

#if 0 // Keep these around just for template
    string comm  = msg.GetCommunity();
    double dval  = msg.GetDouble();
    string sval  = msg.GetString();
    string msrc  = msg.GetSource();
    double mtime = msg.GetTime();
    bool   mdbl  = msg.IsDouble();
    bool   mstr  = msg.IsString();
#endif
  }

    return(true);
}

//---------------------------------------------------------
// Procedure: OnConnectToServer()

bool Omniscan_SS::OnConnectToServer()
{
   registerVariables();
   return(true);
}

//---------------------------------------------------------
// Procedure: Iterate()
//            happens AppTick times per second

bool Omniscan_SS::Iterate()
{
  AppCastingMOOSApp::Iterate();
  // Do your thing here!

  AppCastingMOOSApp::PostReport();
  return(true);
}

//---------------------------------------------------------
// Procedure: OnStartUp()
//            happens before connection is open

bool Omniscan_SS::OnStartUp()
{
  AppCastingMOOSApp::OnStartUp();

  STRING_LIST sParams;
  m_MissionReader.EnableVerbatimQuoting(false);
  if(!m_MissionReader.GetConfiguration(GetAppName(), sParams))
    reportConfigWarning("No config block found for " + GetAppName());

  STRING_LIST::iterator p;
  for(p=sParams.begin(); p!=sParams.end(); p++) {
    string orig  = *p;
    string line  = *p;
    string param = tolower(biteStringX(line, '='));
    string value = line;

    bool handled = false;
    if(param == "foo") {
      handled = true;
    }
    else if(param == "bar") {
      handled = true;
    }

    if(!handled)
      reportUnhandledConfigWarning(orig);

  }
  
  registerVariables();  
  return(true);
}

//---------------------------------------------------------
// Procedure: registerVariables()

void Omniscan_SS::registerVariables()
{
  AppCastingMOOSApp::RegisterVariables();
  // Register("FOOBAR", 0);
  Register("RAW_GPS",0);
  Register("RAW_IMU",0);
  Register("RAW_DEPTH",0);
}

//------------------------------------------------------------
// Procedure: buildReport()

bool Omniscan_SS::buildReport() 
{
  m_msgs << "============================================" << endl;
  m_msgs << "Omniscan_SS Status Report                   " << endl;
  m_msgs << "============================================" << endl;

  // m_msgs << "Latest Raw_Depth: " << m_raw_depth << endl;
  // m_msgs << "Latest RAW_IMU:   " << m_raw_imu << endl;
  // m_msgs << "Latest RAW_GPS:   " << m_raw_gps << endl;

#if 0
  ACTable actab(4);
  actab << "Alpha | Bravo | Charlie | Delta";
  actab.addHeaderLines();
  actab << "one" << "two" << "three" << "four";
  m_msgs << actab.getFormattedString();
# endif
  return(true);
}

void Omniscan_SS::remove_important_information(const std::string& long_message){
  std::istringstream iss(long_message);
  std::string msg;

  while (iss >> msg){

        if (msg == "depth:"){
            iss >> depth_value;
        }
    }
}
