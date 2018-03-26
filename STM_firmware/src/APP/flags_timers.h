#ifndef FLAGS_TIMERS_H_
#define FLAGS_TIMERS_H_

#include "config.h"
#include "data_types.h"

extern uint8_t flagPowerUp;
extern uint8_t flagProfileTranstionFunction;
extern uint8_t profileNumberPrevious;

extern CYCL_STATE flagCurrentCycle;

extern uint8_t flagCycleFlipToLightCycle;
extern uint8_t flagCycleFlipToDarkCycle;

extern CYCL_STATE flagAd1PreviousCycle;

extern TIME_M timePreviousLightOn;
extern TIME_M timePreviousLightOff;

extern uint8_t flagPreviousLightStatus;
extern uint8_t flagPreviousHdVStatus;

extern uint8_t flagPreviousCirStatus;
extern uint8_t flagPreviousVenStatus;
extern uint8_t flagPreviousFXP1OutletStatus;
extern uint8_t flagPreviousFXP2OutletStatus;
extern uint8_t flagPreviousLightSuspend;
extern uint8_t flagPreviousHdVSuspend;
extern uint8_t flagPreviousCirSuspend;
extern uint8_t flagPreviousVenSuspend;
extern uint8_t flagPreviousFXP1Suspend;
extern uint8_t flagPreviousFXP2Suspend;

extern uint8_t flagCriticalOverTempFault;
extern uint8_t flagPreviousCriticalOverTempFault;
extern uint8_t flagPreviousSensorComFault;
extern uint8_t flagPreviousWiFiComFault;
extern uint8_t flagWiFiComDTS;
extern uint8_t flagPreviousRS485FuseFault;
extern uint8_t flagPreviousEMRFuseFault;
extern uint8_t flagPreviousBackUpBattFault;
extern uint8_t flagAd1ReStrikeFault;

extern TIMER timerReStrikeFault;	

extern float tempVenDCTempThresholdOff;
extern float tempVenLCTempThresholdOff;
extern float humVenDCHumThresholdOff;
extern float humVenLCHumThresholdOff;

extern uint8_t flagHdVLCSrtDly;
extern uint8_t flgHdVDCSrtDly;
extern uint8_t flagCirLCSrtDly;

extern uint8_t flagCirDCSrtDly;
extern uint8_t flagVenLCSrtDly;
extern uint8_t flagVenDCSrtDly;
extern uint8_t flagFXP1LCSrtDly;
extern uint8_t flagFXP1DCSrtDly;
extern uint8_t flagFXP2LCSrtDly;
extern uint8_t flagFXP2DCSrtDly;
extern uint8_t flagPreviousHdVLCSrtDly;
extern uint8_t flagPreviousHdVDCSrtDly;
extern uint8_t flagPreviousCirLCSrtDly;
extern uint8_t flagPreviousCirDCSrtDly;
extern uint8_t flagPreviousVenLCSrtDly;
extern uint8_t flagPreviousVenDCSrtDly;
extern uint8_t flagPreviousFXP1LCSrtDly;
extern uint8_t flagPreviousFXP1DCSrtDly;
extern uint8_t flagPreviousFXP2LCSrtDly;
extern uint8_t flagPreviousFXP2DCSrtDly;
	
extern TIME_M tmrHdVLCSrtDly;
extern TIME_M tmrHdVDCSrtDly;
extern TIME_M tmrCirLCSrtDly;
extern TIME_M tmrCirDCSrtDly;	
extern TIME_M tmrVenLCSrtDly;
extern TIME_M tmrVenDCSrtDly;
extern TIME_M tmrFXP1LCSrtDly;
extern TIME_M tmrFXP1DCSrtDly;
extern TIME_M tmrFXP2LCSrtDly;
extern TIME_M tmrFXP2DCSrtDly;

extern uint8_t flagHdVLCRptTmrCclTime;
extern uint8_t flagHdVDCRptTmrCclTime;
extern uint8_t flagCirLCRptTmrCclTime;
extern uint8_t flagCirDCRptTmrCclTime;
extern uint8_t flagVenLCRptTmrCclTime;
extern uint8_t flagVenDCRptTmrCclTime;
extern uint8_t flagFXP1LCRptTmrCclTime;
extern uint8_t flagFXP1DCRptTmrCclTime;
extern uint8_t flagFXP2LCRptTmrCclTime;
extern uint8_t flagFXP2DCRptTmrCclTime;

extern TIME_M tmrHdVLCRptTmrCclTime;
extern TIME_M tmrHdVDCRptTmrCclTime;
extern TIME_M tmrCirLCRptTmrCclTime;
extern TIME_M tmrCirDCRptTmrCclTime;
extern TIME_M tmrVenLCRptTmrCclTime;
extern TIME_M tmrVenDCRptTmrCclTime;
extern TIME_M tmrFXP1LCRptTmrCclTime;
extern TIME_M tmrFXP1DCRptTmrCclTime;
extern TIME_M tmrFXP2LCRptTmrCclTime;
extern TIME_M tmrFXP2DCRptTmrCclTime;

extern uint8_t flagPreviousHdVLCRptTmrCclTime;
extern uint8_t flagPreviousHdVDCRptTmrCclTime;
extern uint8_t flagPreviousCirLCRptTmrCclTime;
extern uint8_t flagPreviousCirDCRptTmrCclTime;
extern uint8_t flagPreviousVenLCRptTmrCclTime;
extern uint8_t flagPreviousVenDCRptTmrCclTime;
extern uint8_t flagPreviousFXP1LCRptTmrCclTime;
extern uint8_t flagPreviousFXP1DCRptTmrCclTime;
extern uint8_t flagPreviousFXP2LCRptTmrCclTime;
extern uint8_t flagPreviousFXP2DCRptTmrCclTime;

extern uint8_t flagHdVLCRptTmrRptAfter;
extern uint8_t flagHdVDCRptTmrRptAfter;
extern uint8_t flagCirLCRptTmrRptAfter;
extern uint8_t flagCirDCRptTmrRptAfter;
extern uint8_t flagVenLCRptTmrRptAfter;
extern uint8_t flagVenDCRptTmrRptAfter;
extern uint8_t flagFXP1LCRptTmrRptAfter;
extern uint8_t flagFXP1DCRptTmrRptAfter;
extern uint8_t flagFXP2LCRptTmrRptAfter;
extern uint8_t flagFXP2DCRptTmrRptAfter;

extern TIME_M tmrHdVLCRptTmrRptAfter;
extern TIME_M tmrHdVDCRptTmrRptAfter;
extern TIME_M tmrCirLCRptTmrRptAfter;
extern TIME_M tmrCirDCRptTmrRptAfter;
extern TIME_M tmrVenLCRptTmrRptAfter;
extern TIME_M tmrVenDCRptTmrRptAfter;
extern TIME_M tmrFXP1LCRptTmrRptAfter;
extern TIME_M tmrFXP1DCRptTmrRptAfter;
extern TIME_M tmrFXP2LCRptTmrRptAfter;
extern TIME_M tmrFXP2DCRptTmrRptAfter;

extern uint8_t flagMasterSuspOnVent;
extern uint8_t flagHdVSuspOnVent;
extern uint8_t flagCirSuspOnVent;
extern uint8_t flagVenSuspOnVent;
extern uint8_t flagFXP1SuspOnVent;
extern uint8_t flagFXP2SuspOnVent;
extern uint8_t flagPreviousHdVSuspOnVent;
extern uint8_t flagPreviousCirSuspOnVent;
extern uint8_t flagPreviousVenSuspOnVent;
extern uint8_t flagPreviousFXP1SuspOnVent;
extern uint8_t flagPreviousFXP2SuspOnVent;
extern uint8_t flagPreviousLightForceOn;
extern uint8_t flagPreviousHdVForceOn;
extern uint8_t flagPreviousCirForceOn;
extern uint8_t flagPreviousVen;
extern uint8_t flagPreviousFXP1ForceOn;
extern uint8_t flagPreviousFXP2ForceOn;

const extern TIMER tmrHdVDCDeActDelayFactSet;
	
extern uint8_t flagHdVDCDeActDelay;

extern TIME_M tmrHdVDCDeActDelay;

const extern TIMER tmrCO2PostVenActDelayFactSet;

extern TIME_M tmrCO2PostVenActDelay;

extern uint8_t flagCO2PostVenActDelay;

extern uint8_t flagPreviousCO2PostVenActDelay;

extern uint8_t flagAd1CO2Inj;

extern TIME_M tmrHdVCO2Inj;

extern TIME_M tmrCirCO2Inj;
extern TIME_M tmrFXP1CO2Inj;
extern TIME_M tmrFXP2CO2Inj;

extern uint8_t flagPreviousHdVMode;
extern uint8_t flagPreviousCirMode;
extern uint8_t flagPreviousVenMode;
extern uint8_t flagPreviousFXP1Mode;
extern uint8_t flagPreviousFXP2Mode;

extern uint8_t ONOFFPreviousHdVLCUsrProg;
extern uint8_t ONOFFPreviousHdVDCUsrProg;
extern uint8_t ONOFFPreviousCirLCUsrProg;
extern uint8_t ONOFFPreviousCirDCUsrProg;
extern uint8_t ONOFFPreviousVenLCUsrProg;
extern uint8_t ONOFFPreviousVenDCUsrProg;
extern uint8_t ONOFFPreviousFXP1LCUsrProg;
extern uint8_t ONOFFPreviousFXP1DCUsrProg;
extern uint8_t ONOFFPreviousFXP2LCUsrProg;
extern uint8_t ONOFFPreviousFXP2DCUsrProg;

#endif // FLAGS_TIMERS_H_
