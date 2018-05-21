#include "flags_timers.h"

uint8_t flagPowerUp = NO;
uint8_t flagProfileTranstionFunction = NO;
uint8_t profileNumberPrevious = 1;

CYCL_STATE flagCurrentCycle = (CYCL_STATE)UNKNOWN;

uint8_t flagCycleFlipToLightCycle = NO;
uint8_t flagCycleFlipToDarkCycle = NO;

CYCL_STATE flagAd1PreviousCycle = DARK;

TIME_M timePreviousLightOn = {6, 0, 0};
TIME_M timePreviousLightOff = {18, 0, 0};

uint8_t flagPreviousLightStatus = OFF;
uint8_t flagPreviousHdVStatus = OFF;

uint8_t flagPreviousCirStatus = OFF;
uint8_t flagPreviousVenStatus  = OFF;
uint8_t flagPreviousFXP1OutletStatus = OFF;
uint8_t flagPreviousFXP2OutletStatus = OFF;
uint8_t flagPreviousLightSuspend = NO;
uint8_t flagPreviousHdVSuspend = NO;
uint8_t flagPreviousCirSuspend = NO;
uint8_t flagPreviousVenSuspend = NO;
uint8_t flagPreviousFXP1Suspend = NO;
uint8_t flagPreviousFXP2Suspend = NO;

uint8_t flagCriticalOverTempFault = NO;
uint8_t flagPreviousCriticalOverTempFault = NO;
uint8_t flagPreviousSensorComFault = NO;
uint8_t flagPreviousWiFiComFault = NO;

uint8_t flagWiFiComDTS = NO; 

uint8_t flagPreviousRS485FuseFault = NO;
uint8_t flagPreviousEMRFuseFault = NO;
uint8_t flagPreviousBackUpBattFault = NO;
uint8_t flagAd1ReStrikeFault = NO;

TIMER timerReStrikeFault = {15, 0};

#ifdef TMP_FAHRENHEIT
	float tempVenDCTempThresholdOff = 65.0;
	float tempVenLCTempThresholdOff = 65.0;
#endif

#ifdef TMP_CELCIUS
	float tempVenDCTempThresholdOff = 18.3333;
	float tempVenLCTempThresholdOff = 18.3333;
#endif

float humVenDCHumThresholdOff = 0.5;
float humVenLCHumThresholdOff = 0.5;

uint8_t flagHdVLCSrtDly = NO;
uint8_t flgHdVDCSrtDly = NO;
uint8_t flagCirLCSrtDly = NO;
uint8_t flagCirDCSrtDly = NO;
uint8_t flagVenLCSrtDly = NO;
uint8_t flagVenDCSrtDly = NO;
uint8_t flagFXP1LCSrtDly = NO;
uint8_t flagFXP1DCSrtDly = NO;
uint8_t flagFXP2LCSrtDly = NO;
uint8_t flagFXP2DCSrtDly = NO;

uint8_t flagPreviousHdVLCSrtDly = NO;
uint8_t flagPreviousHdVDCSrtDly = NO;
uint8_t flagPreviousCirLCSrtDly = NO;
uint8_t flagPreviousCirDCSrtDly = NO;
uint8_t flagPreviousVenLCSrtDly = NO;
uint8_t flagPreviousVenDCSrtDly = NO;
uint8_t flagPreviousFXP1LCSrtDly = NO;
uint8_t flagPreviousFXP1DCSrtDly = NO;
uint8_t flagPreviousFXP2LCSrtDly = NO;
uint8_t flagPreviousFXP2DCSrtDly = NO;

TIME_M tmrHdVLCSrtDly = {0, 0, 0};
TIME_M tmrHdVDCSrtDly = {0, 0, 0};
TIME_M tmrCirLCSrtDly = {0, 0, 0};
TIME_M tmrCirDCSrtDly = {0, 0, 0};	
TIME_M tmrVenLCSrtDly = {0, 0, 0};
TIME_M tmrVenDCSrtDly = {0, 0, 0};
TIME_M tmrFXP1LCSrtDly = {0, 0, 0};
TIME_M tmrFXP1DCSrtDly = {0, 0, 0};
TIME_M tmrFXP2LCSrtDly = {0, 0, 0};
TIME_M tmrFXP2DCSrtDly = {0, 0, 0};

uint8_t flagHdVLCRptTmrCclTime = NO;
uint8_t flagHdVDCRptTmrCclTime = NO;
uint8_t flagCirLCRptTmrCclTime = NO;
uint8_t flagCirDCRptTmrCclTime = NO;
uint8_t flagVenLCRptTmrCclTime = NO;
uint8_t flagVenDCRptTmrCclTime = NO;
uint8_t flagFXP1LCRptTmrCclTime = NO;
uint8_t flagFXP1DCRptTmrCclTime = NO;
uint8_t flagFXP2LCRptTmrCclTime = NO;
uint8_t flagFXP2DCRptTmrCclTime = NO;

TIME_M tmrHdVLCRptTmrCclTime = {0, 5, 0};
TIME_M tmrHdVDCRptTmrCclTime = {0, 5, 0};
TIME_M tmrCirLCRptTmrCclTime = {0, 5, 0};
TIME_M tmrCirDCRptTmrCclTime = {0, 5, 0};
TIME_M tmrVenLCRptTmrCclTime = {0, 5, 0};
TIME_M tmrVenDCRptTmrCclTime = {0, 5, 0};
TIME_M tmrFXP1LCRptTmrCclTime = {0, 5, 0};
TIME_M tmrFXP1DCRptTmrCclTime = {0, 5, 0};
TIME_M tmrFXP2LCRptTmrCclTime = {0, 5, 0};
TIME_M tmrFXP2DCRptTmrCclTime = {0, 5, 0};

uint8_t flagPreviousHdVLCRptTmrCclTime = NO;
uint8_t flagPreviousHdVDCRptTmrCclTime = NO;
uint8_t flagPreviousCirLCRptTmrCclTime = NO;
uint8_t flagPreviousCirDCRptTmrCclTime = NO;
uint8_t flagPreviousVenLCRptTmrCclTime = NO;
uint8_t flagPreviousVenDCRptTmrCclTime = NO;
uint8_t flagPreviousFXP1LCRptTmrCclTime = NO;
uint8_t flagPreviousFXP1DCRptTmrCclTime = NO;
uint8_t flagPreviousFXP2LCRptTmrCclTime = NO;
uint8_t flagPreviousFXP2DCRptTmrCclTime = NO;

uint8_t flagHdVLCRptTmrRptAfter = NO;
uint8_t flagHdVDCRptTmrRptAfter = NO;
uint8_t flagCirLCRptTmrRptAfter = NO;
uint8_t flagCirDCRptTmrRptAfter = NO;
uint8_t flagVenLCRptTmrRptAfter = NO;
uint8_t flagVenDCRptTmrRptAfter = NO;
uint8_t flagFXP1LCRptTmrRptAfter = NO;
uint8_t flagFXP1DCRptTmrRptAfter = NO;
uint8_t flagFXP2LCRptTmrRptAfter = NO;
uint8_t flagFXP2DCRptTmrRptAfter = NO;

TIME_M tmrHdVLCRptTmrRptAfter  = {1, 30, 0};
TIME_M tmrHdVDCRptTmrRptAfter  = {1, 30, 0};
TIME_M tmrCirLCRptTmrRptAfter  = {1, 30, 0};
TIME_M tmrCirDCRptTmrRptAfter  = {1, 30, 0};
TIME_M tmrVenLCRptTmrRptAfter  = {1, 30, 0};
TIME_M tmrVenDCRptTmrRptAfter  = {1, 30, 0};
TIME_M tmrFXP1LCRptTmrRptAfter  = {1, 30, 0};
TIME_M tmrFXP1DCRptTmrRptAfter  = {1, 30, 0};
TIME_M tmrFXP2LCRptTmrRptAfter  = {1, 30, 0};
TIME_M tmrFXP2DCRptTmrRptAfter  = {1, 30, 0};

uint8_t flagMasterSuspOnVent = NO;

uint8_t flagHdVSuspOnVent = NO;
uint8_t flagCirSuspOnVent = NO;
uint8_t flagVenSuspOnVent = NO;
uint8_t flagFXP1SuspOnVent = NO;
uint8_t flagFXP2SuspOnVent = NO;

uint8_t flagPreviousHdVSuspOnVent = NO;
uint8_t flagPreviousCirSuspOnVent = NO;
uint8_t flagPreviousVenSuspOnVent = NO;
uint8_t flagPreviousFXP1SuspOnVent = NO;
uint8_t flagPreviousFXP2SuspOnVent = NO;

uint8_t flagPreviousLightForceOn = NO;

uint8_t flagPreviousHdVForceOn = NO;
uint8_t flagPreviousCirForceOn = NO;
uint8_t flagPreviousVenForceOn = NO; // Added ForceOn not mentioned in excel file
uint8_t flagPreviousFXP1ForceOn = NO;
uint8_t flagPreviousFXP2ForceOn = NO;

const TIMER tmrHdVDCDeActDelayFactSet = {5, 0};
	
uint8_t flagHdVDCDeActDelay = NO;

TIME_M tmrHdVDCDeActDelay = {0, 0, 0};

const TIMER tmrCO2PostVenActDelayFactSet = {5, 0};

TIME_M tmrCO2PostVenActDelay = {0, 0, 0};

uint8_t flagCO2PostVenActDelay = NO;

uint8_t flagPreviousCO2PostVenActDelay = NO;

uint8_t flagAd1CO2Inj = NO;

TIME_M tmrHdVCO2Inj = {0 , 5, 0};
TIME_M tmrCirCO2Inj = {0 , 5, 0};
TIME_M tmrFXP1CO2Inj = {0 , 5, 0};
TIME_M tmrFXP2CO2Inj = {0 , 5, 0};

uint8_t flagPreviousHdVMode = NO;
uint8_t flagPreviousCirMode = NO;
uint8_t flagPreviousVenMode = NO;
uint8_t flagPreviousFXP1Mode = NO;
uint8_t flagPreviousFXP2Mode = NO;

uint8_t ONOFFPreviousHdVLCUsrProg = OFF;
uint8_t ONOFFPreviousHdVDCUsrProg = OFF;
uint8_t ONOFFPreviousCirLCUsrProg = OFF;
uint8_t ONOFFPreviousCirDCUsrProg = OFF;
uint8_t ONOFFPreviousVenLCUsrProg = OFF;
uint8_t ONOFFPreviousVenDCUsrProg = OFF;
uint8_t ONOFFPreviousFXP1LCUsrProg = OFF;
uint8_t ONOFFPreviousFXP1DCUsrProg = OFF;
uint8_t ONOFFPreviousFXP2LCUsrProg = OFF;
uint8_t ONOFFPreviousFXP2DCUsrProg = OFF;
