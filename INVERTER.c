#define S_FUNCTION_LEVEL 2 
#define S_FUNCTION_NAME INVERTER
#include "simstruc.h" 
#include <math.h> 

#define U(element) (*uPtrs[element]) /*Pointer to Input Port0*/ 


static void mdlInitializeSizes(SimStruct *S){ 
    if (!ssSetNumInputPorts(S, 1)) return; 
    ssSetInputPortWidth(S, 0, 2); 
    ssSetInputPortDirectFeedThrough(S, 0, 1); 
    ssSetInputPortOverWritable(S, 0, 1); 
    if (!ssSetNumOutputPorts(S, 1)) return; 
    ssSetOutputPortWidth(S, 0, 3); 
    ssSetNumSampleTimes(S, 1); 

    ssSetOptions(S, SS_OPTION_EXCEPTION_FREE_CODE); } 

static void mdlInitializeSampleTimes(SimStruct *S) { 
    ssSetSampleTime(S, 0, CONTINUOUS_SAMPLE_TIME); 
    ssSetOffsetTime(S, 0, 0.0); } 

static void mdlOutputs(SimStruct *S, int_T tid) { 
    real_T *Y = ssGetOutputPortRealSignal(S,0); 
    InputRealPtrsType uPtrs = ssGetInputPortRealSignalPtrs(S,0); 
    real_T t = ssGetT(S);
    
    real_T Vdc, frequency, Vmax, Vac_a, Vac_b, Vac_c, pi;

    Vdc = U(0);
    frequency = U(1);
    pi = 3.1415926536;
    
    Vmax = Vdc; 
    Vac_a = Vmax * sin(2 * pi * frequency * t);
    Vac_b = Vmax * sin(2 * pi * frequency * t - 2*pi/3);
    Vac_c = Vmax * sin(2 * pi * frequency * t - 4*pi/3);
    
    Y[0] = Vac_a;
    Y[1] = Vac_b;
    Y[2] = Vac_c;
}


static void mdlTerminate(SimStruct *S) 
{ } /*Keep this function empty since no memory is allocated*/ 

#ifdef MATLAB_MEX_FILE 
/* Is this file being compiled as a MEX-file? */ 
#include "simulink.c" /* MEX-file interface mechanism */ 
#else 
#include "cg_sfun.h" /*Code generation registration function*/ 
#endif