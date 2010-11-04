#ifndef SATMDE
#define SATMDE

/* * File name		 : satMDE.hpp
 *
 * Abstract          : This file contains definitions of structures and Global classes
 *                     Struchers  used in the Gpsgyan project.

 *
 * Compiler          : Visual C++ Version 9.0
 *
 * Compiler options  : Default
 *
 * Pragmas           : None used
 *
 * H/W Platform      : IBM PC
 *
 * Portability       : No Operating system call used.
 *                     No machine specific instruction used.
 *                     No compiler specific routines used.
 *                     Hence Portable.
 *
 * Authors			: Priyank Kumar
 *
 *
 * Version history	: Base version
 *	                   Priyank Kumar     November 2009
 *
 * References        : None
 *
 * Functions called  : None
 * Library Used 	 : GPStk
 *  				   Copyright 2009, The University of Texas at Austin
 *
 */
/* GPSTk Library*/


#include "SatMedtypes.hpp"
#include "DayTime.hpp"
#include "SatID.hpp"
#include "Position.hpp"
#include "SatMdeMac.hpp"
#include "Geodetic.hpp"
#include "WGS84Geoid.hpp"
#include "Modulator.hpp"

/*C++ Systems Include files*/
#include <iostream>
#include <string>
#include <map>
#include <vector>

/*GPSGyan Include files*/
#include "EngineFramework.hpp"


using namespace gpstk;

class SatMDE: public EngineFramework
{
public:


	 NEW_EXCEPTION_CLASS(ExcSatMDE , gpstk::Exception);


	SatMDE(const string& applName) throw()
   : EngineFramework(
      applName,
      "this computes satellite Position , Velocity and time for the specified receiever position and time")
   {};

	 // bool initialize(int argc, char *argv[]) throw();
	 // virtual void process();

void GetPassiveInput(satMDE_psvIstruct &ref_psv);
void GetActiveInput(satMDE_actIstruct &ref_act);
void GetPassiveParam();
void GetActiveParam();


void InputInfToEngine(Kind kind);  // think of argv and argc implementation
//virtual void runEngine();
void InputParamToEngine(Kind kind);// throw(InvalidParameter);
//bool runEngine() throw();
//void outputInfFromEngine(std::ostream & s ,const std::string & 	data);
void outputInfFromEngine(std::ostream & s, SatID& satid , int type);
//void OutputDumpOfEngine();

// Public Data memebers
engineHealth satMDE_probe;

map<SatID, satMDE_ostruct> satMDE_oData;
//std::vector<satMDE_ostruct> satMDE_oData;
std::vector<SatID> visibleSV;
bool visiblityComputed;

satMDE_actIstruct ref_act;
satMDE_psvIstruct ref_psv;
DayTime inp_time ;

std::vector<int> error_number;


//std::string op_inf;
protected :
			void EngineControl(Kind kind);
			void SetInitialStateofEngine();
			void SetActiveStateofEngine ();

            void VerifyIpToEngine() throw(ExcSatMDE);
			void MethodOfEngine() throw(ExcSatMDE);
			void SatMDE_ExpHandler(ExcSatMDE &e);

			// Fromatted File Printing
			std::string print_content(satMDE_ostruct &ostruct);
		    std::string print_header();
			void updateLocals(const Xvt& satXvt ,const Xvt& rxXvt);
			void ComputePhaseAndDoppler(const double &rangeRate,const double &clkCorrection);
			int findSvPrvRange(SatID vis_svid);
		



private :
// Private Data Members

/* Structures*/
/* All active and passive inputs are defined in structures in <class>types.hpp

satMDE_actIstruct satMDE_ai;
satMDE_psvIstruct satMDE_pi;
satMDE_clkFreq clkL1,clkL2c,clkL5;



/*STL Containers*/
//Maps are a kind of associative containers that stores elements formed by the combination of a key value and a mapped value
// We are using map as all of our data is unique to a particular transmitter i.e satellited ID
map<SatID, satMDE_prvMeas> prvMeas; // map 
map<SatID, satMDE_ostruct> satMDE_pData1;

//Vectors are a kind of sequence containers. As such, their elements are ordered following a strict linear sequence.
//Vector containers are implemented as dynamic arrays; Just as regular arrays, vector containers have their elements 
//stored in contiguous storage locations, which means that their elements can be 
//accessed not only using iterators but also using offsets on regular pointers to elements.
//But unlike regular arrays, storage in vectors is handled automatically, allowing it to be expanded and contracted as needed.
// We are using vectors instead of array in all the processed data structure of visible transmitter (SV) 
// as we can expand or delete the data as in when the SV is visible or go out of visiblity respectively

std::vector<satMDE_ostruct> satMDE_pData;
std::vector<SatID> rejectedSV;

//Global Variables
bool timeToCompute;
int visCounter;
int totalSat;
unsigned int visSV;
double minElev;
Position tempPos;

// Private Members Functions
 	  
bool getMeasurement(SatID &temp_satid,
							 Position &rxXvt,
							 DayTime  &measTime,
							 SatDb    *satDb,
							 SatDgen *satDgen,
							 double range,
							 bool firstMeas,
							 bool svRange);
							 
void ComputeVisibility();
void CodeGenerator(CodeGen   *codegen,
					SatID &satid ,
					double& codefrequency);
void CarrGenerator(CarrGen   *carrgen,
					SatID &satid ,
					double& carrfrequency);					
void LoadChannel(satMDE_actIstruct &p_activeData, SatID &satid);							  
};							  
#endif
