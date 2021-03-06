/*! \file ModbusSensors.h
	\brief Library for managing the modbus sensors in Smart Water Xtreme.
	This library is not compatible con Smart water version.

	Copyright (C) 2018 Libelium Comunicaciones Distribuidas S.L.
	http://www.libelium.com

	This program is free software: you can redistribute it and/or modify
	it under the terms of the GNU Lesser General Public License as published by
	the Free Software Foundation, either version 2.1 of the License, or
	(at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU Lesser General Public License for more details.

	You should have received a copy of the GNU Lesser General Public License
	along with this program.  If not, see <http://www.gnu.org/licenses/>.

	Version:			3.0
	Design:				David Gascón
	Implementation:		Victor Boria
*/


#ifndef ModbusSensor_h
#define ModbusSensor_h

/*****************************************************************************
* Includes
******************************************************************************/
#include <inttypes.h>

/////////////////////////////////////////////////////////////////////////////
// Include the neccesary libraries.
/////////////////////////////////////////////////////////////////////////////

#include "ModbusMaster.h"
/******************************************************************************
 * Definitions & Declarations
 ******************************************************************************/

//! DEBUG MODE
/*! 0: No debug mode enabled
 * 	1: debug mode enabled for error output messages
 * 	2: debug mode enabled for both error and ok messages
 */
#define DEBUG_XTR_MODBUS		0

#define PRINT_XTR_MODBUS(str)		USB.print(F("[XTR-MODBUS] ")); USB.print(str);
#define PRINT_XTR_MODBUS_VAL(val)	USB.print(val, BIN);

#define PRINTLN_XTR_MODBUS(str)		USB.print(F("[XTR-MODBUS] ")); USB.println(str);
#define PRINTLN_XTR_MODBUS_VAL(val)	USB.println(val, BIN);


// Some sensor Registers
#define ADDRESS_REG			0xA3
#define WAITING_TIME_REG	0xA4
#define MEASUREMENTS_REG	0x53
#define RESET_REG			0x02
#define COMP_TEMP_REG		0x5D
#define TEMP_MEAS_STATUS	0x64
#define OPER_NAME_REG		0x027E
#define DATE_TEMP_REG		0x0286
#define SERIAL_NUMBER_REG	0x0D10
#define TEMP_TYPE_CON		0xA5
#define TURB_TYPE_CON		0xA6
#define AVRG_PARA_REG		0xAA
#define TURB_MEAS_STATUS	0x65
#define NEW_MEAS_REG		0x01
#define TEMP_COEF_LIST_REG	0x014C
#define RESTORE_CALIB_REG	0x0002


//NTU sensor standard calibration registers
#define CALIB_STANDARD_TEMP_1	0x0200 //Temp offset
#define CALIB_STANDARD_TEMP_2 	0x0202 //Temp slope
#define CALIB_STANDARD_1		0x0204
#define CALIB_STANDARD_2		0x0206
#define CALIB_STANDARD_3		0x0208
#define CALIB_STANDARD_4		0x020A
#define CALIB_STANDARD_5		0x020C
#define CALIB_STANDARD_6		0x020E
#define CALIB_STANDARD_7		0x0210
#define CALIB_STANDARD_8		0x0212
#define CALIB_STANDARD_9		0x0214
#define CALIB_STANDARD_10		0x0216

#define DONT_RETURN_AVG_TO_1	0
#define RETURN_AVG_TO_1			1
#define RETURN_AVG_TO_1_AND_STOP_ELECTRONIC_ZERO	2

//Parameters
#define TEMPERATURE		1
#define PARAMETER_1 	2
#define PARAMETER_2 	3
#define PARAMETER_3		4
#define PARAMETER_4		5

#define OXYGEN			2
#define PH				2
#define REDOX			3
#define CONDUCTIVITY	2
#define NTU_TURBIDITY	2
#define SLUDGE_BLANKET	2
#define FAU_TURBIDITY	4

//Ranges for some measures
#define RANGE_AUTOMATIC 0
#define RANGE_1 		1
#define RANGE_2 		2
#define RANGE_3 		3
#define RANGE_4 		4


#define STEP_1 		1
#define STEP_2 		2
#define STEP_3 		3
#define STEP_4 		4
#define STEP_3B		10

// This address will be configured as a first step
#define DEFAULT_ADDRESS			40
#define DEFAULT_WAITING_TIME	300 // in ms


// Supported sensors with Xtreme boards
#define _5TE				1
#define GS3					2
#define VP4					3
#define MPS6				4
#define SO411				5
#define SI411				6
#define _5TM				7
#define SF421				8
#define C4E					9
#define CTZN				10
#define MES5				11
#define OPTOD				12
#define PHEHT				13
#define NTU					14

/******************************************************************************
 * Class
 ******************************************************************************/

//! Turbidity Sensor Class
/*!
	This Class defines all the variables and functions used for
	managing the Turbidity Sensor
 */
class modbusSensorsClass
{
	public:

		// Public functions
		modbusSensorsClass();
		modbusSensorsClass(uint8_t);
		
		void initCommunication();
		
		uint8_t readWaitingTime();
		
		void clearBuffer();
		
		// Basic functions
		uint8_t initSensor(uint8_t range, uint8_t avg);
		uint8_t initSensor(uint8_t range);
		uint8_t initSensor();
		
		// Reading functions
		uint8_t readMeasures(float &parameter1, 
							float &parameter2, 
							float &parameter3, 
							float &parameter4);
						
		uint8_t readSerialNumber(char *sensorSerialNumber);
		
		
		// Sensor managemente functions
		uint8_t writeAverage(uint8_t average);
		uint16_t readAverage();
		uint8_t writeParamConfig(uint8_t paramNumber, uint8_t range);
		uint16_t readParamConfig(uint8_t paramNumber);
		
		// Sensor calibration functions
		uint8_t calibrate(uint8_t sensor, uint8_t parameter, uint8_t step, float value);
		uint8_t writeCalibrationStandard(uint16_t address, float value);
		float readCalibrationStandard(uint16_t address);
		uint8_t writeTemporaryCoefficientList(uint16_t coefficient);
		uint8_t readTemporaryCoefficientList();
		uint8_t writeCalibrationValidation(uint8_t value);
		uint8_t restoreToFactoryCalibration(uint8_t parameter);
		uint8_t resetTemporaryCalibrationData(uint8_t returnAvgTo1_stopElectronicZero);
		char calibrationOperatorsName[17];
		char calibrationDate[17];
		uint16_t address_offset;
		uint16_t address_slope;
		
		// For Mdobus management
		ModbusMaster sensor;
		
		//Calibration variables
		uint16_t temporaryCoefficientListBuffer;

		void setParametersBySensor(uint8_t sensorType);
		
		////////////////////////////////////////////////////////////////////
		// This declaration is used to generate a float from two integers
		// integer(16 bits) + integer (16 bits) => float (32bits)
		////////////////////////////////////////////////////////////////////
		union
		{
			uint16_t ints[2];
			float toFloat;
		}
		foo;
		
		////////////////////////////////////////////////////////////////////
		// This declaration is used to generate a float from two integers
		// integer(16 bits) + integer (16 bits) => float (32bits)
		////////////////////////////////////////////////////////////////////
		union
		{
			uint8_t uint8t[2];
			uint16_t uint16t;
		}
		foo2;
		
	private:
		


};


// object to manage Modbus sensors in Xtreme boards
extern modbusSensorsClass modbusSensorsXtr;



#endif
