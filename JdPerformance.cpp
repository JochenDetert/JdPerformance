#include "JdPerformance.h"

JdError JdPerformance::e;
bool JdPerformance::performanceMeasurementAutoReport = false;
uint64_t JdPerformance::performanceMeasurementCounter = 0;
bool JdPerformance::performanceMeasurementExitAfter = false;
uint16_t JdPerformance::performanceMeasurementsIgnored = 0;
uint16_t JdPerformance::performanceMeasurementIgnoreFirstNumber = 0;
bool JdPerformance::performanceMeasurementLoop = false;
uint16_t JdPerformance::performanceMeasurementNumberOfMeasurements = 1;
uint64_t JdPerformance::performanceMeasurementTimeAverage = 0;
uint64_t JdPerformance::performanceMeasurementTimeLast = 0;
uint64_t JdPerformance::performanceMeasurementTimeMax = 0;
uint64_t JdPerformance::performanceMeasurementTimeMin = 0;
uint64_t JdPerformance::performanceMeasurementTimeStart = 0;
uint64_t JdPerformance::performanceMeasurementTimeTotal = 0;
JdPerformance::PMState JdPerformance::state = PMS_NONE;

JdPerformance::JdPerformance()
{
    //ctor
    //performanceMeasurementName = "";
}

JdPerformance::JdPerformance(char* name)
{
    //ctor
    //performanceMeasurementName = name;
}

JdPerformance::~JdPerformance()
{
    //dtor
}

void JdPerformance::nanosecondsToText(uint64_t ns, char* formatedTime){
    float time;
    if(ns >= 1000000000){
        time = (float)ns / 1000000000;
        sprintf(formatedTime, "%.3f s", time);
    }
    if(ns < 999){
        sprintf(formatedTime, "%u ns", ns);
    }
    if(ns < 999999 && ns >=1000){
        time = (float)ns / 1000;
        sprintf(formatedTime, "%.3f µs", time);
    }
    if(ns < 999999999 && ns >= 1000000){
        time = (float)ns / 1000000;
        sprintf(formatedTime, "%.3f ms", time);
    }
}

bool JdPerformance::performanceMeasurementFinish(){
    if(state != PMS_RUNNING) return false;
    performanceMeasurementTimeLast = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()).count() - performanceMeasurementTimeStart;
    if(performanceMeasurementTimeLast > performanceMeasurementTimeMax) performanceMeasurementTimeMax = performanceMeasurementTimeLast;
    if(performanceMeasurementTimeMin == 0) performanceMeasurementTimeMin = performanceMeasurementTimeLast;
    if(performanceMeasurementTimeLast < performanceMeasurementTimeMin) performanceMeasurementTimeMin = performanceMeasurementTimeLast;
    performanceMeasurementTimeTotal += performanceMeasurementTimeLast;
    performanceMeasurementTimeAverage = performanceMeasurementTimeTotal / performanceMeasurementCounter;
    if(performanceMeasurementNumberOfMeasurements > 0 && performanceMeasurementCounter >= performanceMeasurementNumberOfMeasurements) performanceMeasurementStop();
    return true;
}

void JdPerformance::performanceMeasurementIgnoreFirst(){
    if(performanceMeasurementIgnoreFirstNumber > 0){
        performanceMeasurementIgnoreFirstNumber--;
    } else {
        performanceMeasurementInit();
    }
}

void JdPerformance::performanceMeasurementInit(){
    performanceMeasurementCounter = 0;
    performanceMeasurementTimeAverage = 0;
    performanceMeasurementTimeLast = 0;
    performanceMeasurementTimeMax = 0;
    performanceMeasurementTimeMin = 0;
    performanceMeasurementTimeStart = 0;
    performanceMeasurementTimeTotal = 0;

    performanceMeasurementCounter++;
    state = PMS_RUNNING;
    performanceMeasurementTimeStart = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
}

bool JdPerformance::performanceMeasurementReport(){
    if(state != PMS_STOPPED) return false;

    char formatedTime[12];
    nanosecondsToText(performanceMeasurementTimeAverage, formatedTime);

    std::cout << "Performance data: " << std::endl;
    std::cout << "Ignored first:          " << performanceMeasurementsIgnored << std::endl;
    std::cout << "Number of measurements: " << performanceMeasurementCounter << std::endl;
    nanosecondsToText(performanceMeasurementTimeTotal, formatedTime);
    std::cout << "Total time:   " << formatedTime << std::endl;
    nanosecondsToText(performanceMeasurementTimeMin, formatedTime);
    std::cout << "Minimal time: " << formatedTime << std::endl;
    nanosecondsToText(performanceMeasurementTimeMax, formatedTime);
    std::cout << "Maximum time: " << formatedTime << std::endl;
    nanosecondsToText(performanceMeasurementTimeAverage, formatedTime);
    std::cout << "Average time: " << formatedTime << std::endl << std::endl;
    state = PMS_REPORTED;
    if(performanceMeasurementExitAfter) exit(0);
    if(performanceMeasurementLoop){
        performanceMeasurementsIgnored = 0;
        performanceMeasurementInit();
    }
    return true;
}

void JdPerformance::performanceMeasurementReset(){
    performanceMeasurementAutoReport = false;
    performanceMeasurementCounter = 0;
    performanceMeasurementExitAfter = false;
    performanceMeasurementsIgnored = 0;
    performanceMeasurementIgnoreFirstNumber = 0;
    performanceMeasurementLoop = false;
    performanceMeasurementNumberOfMeasurements = 1;
    performanceMeasurementTimeAverage = 0;
    performanceMeasurementTimeLast = 0;
    performanceMeasurementTimeMax = 0;
    performanceMeasurementTimeMin = 0;
    performanceMeasurementTimeStart = 0;
    performanceMeasurementTimeTotal = 0;
    state = PMS_NONE;
}

bool JdPerformance::performanceMeasurementStart(){
    return performanceMeasurementStart(1, 0, false, false, false);
}

bool JdPerformance::performanceMeasurementStart(uint16_t numberOfMeasurements){
    return performanceMeasurementStart(numberOfMeasurements, 0, false, false, false);
}

bool JdPerformance::performanceMeasurementStart(uint16_t numberOfMeasurements, uint16_t ignoreFirstNumber){
    return performanceMeasurementStart(numberOfMeasurements, ignoreFirstNumber, false, false, false);
}

bool JdPerformance::performanceMeasurementStart(uint16_t numberOfMeasurements, uint16_t ignoreFirstNumber, bool autoReport){
    return performanceMeasurementStart(numberOfMeasurements, ignoreFirstNumber, autoReport, false, false);
}

bool JdPerformance::performanceMeasurementStart(uint16_t numberOfMeasurements, uint16_t ignoreFirstNumber, bool autoReport, bool exitAfter){
    return performanceMeasurementStart(numberOfMeasurements, ignoreFirstNumber, autoReport, exitAfter, false);
}

bool JdPerformance::performanceMeasurementStart(uint16_t numberOfMeasurements, uint16_t ignoreFirstNumber, bool autoReport, bool exitAfter, bool loop){
    uint64_t start, current;
    float timeLoop, timeAlgorithm1, timeAlgorithm2;

    switch(state){
        case PMS_RUNNING:
            performanceMeasurementCounter++;
            performanceMeasurementTimeStart = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
            return true;
            break;
        case PMS_IGNORE_FIRST:
            performanceMeasurementIgnoreFirst();
            break;
        case PMS_NONE:
            performanceMeasurementLoop = loop;
            performanceMeasurementExitAfter = exitAfter;
            performanceMeasurementAutoReport = autoReport;
            performanceMeasurementNumberOfMeasurements = numberOfMeasurements;
            if(ignoreFirstNumber > 0){
                performanceMeasurementsIgnored = ignoreFirstNumber;
                performanceMeasurementIgnoreFirstNumber = ignoreFirstNumber;
                state = PMS_IGNORE_FIRST;
                return false;
            }
            performanceMeasurementInit();
            return true;
            break;
    }
    return false;
}

void JdPerformance::performanceMeasurementStop(){
    if(state == PMS_RUNNING) state = PMS_STOPPED;
    if(performanceMeasurementAutoReport) performanceMeasurementReport();
}

bool JdPerformance::performanceTest(void (*p_jdPerfTestAlgo1)(), void (*p_jdPerfTestAlgo2)()){
    uint64_t counter;

    uint64_t start, current;
    float timeLoop, timeAlgorithm1, timeAlgorithm2;

    // do something for one second after program starts
    std::cout << "Please wait a few seconds." << std::endl << std::endl;
    counter = 0;
    start = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    while(std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now().time_since_epoch()).count() < start + 1000000){
    counter++;
    }

    // check performance of loop
    std::cout << "Now checking performance of test loop." << std::endl << std::endl;
    counter = 0;
    start = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    while(std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now().time_since_epoch()).count() < start + 1000000){
    counter++;
    }
    if(counter == 0) return e.error("JdPerformance::performanceTest(void (*p_jdPerfTestAlgo1)(), void (*p_jdPerfTestAlgo2)()) | counter == 0");
    timeLoop = 1000000.0f/counter;

    // check performance of algorithm 1
    std::cout << "Now checking performance of your first algorithm." << std::endl << std::endl;
    counter = 0;
    start = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    while(std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now().time_since_epoch()).count() < start + 1000000){
    // *****************************************************************************
    // put in the algorithm 1 here

    p_jdPerfTestAlgo1();

    // your algorithm 1 ends here
    // *****************************************************************************
    counter++;
    }
    if(counter == 0) return e.error("JdPerformance::performanceTest(void (*p_jdPerfTestAlgo1)(), void (*p_jdPerfTestAlgo2)()) | counter == 0");
    timeAlgorithm1  = 1000000.0f/counter;
    timeAlgorithm1 -= timeLoop;
    std::cout << "The algorithm (1) ran  " << (float)counter/1000 << "k times in one second." << std::endl;
    std::cout << "One algorithm (1) took " << timeAlgorithm1 << " microseconds." << std::endl << std::endl;

    // check performance of algorithm 2
    std::cout << "Now checking performance of your second algorithm." << std::endl << std::endl;
    counter = 0;
    start = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    while(std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now().time_since_epoch()).count() < start + 1000000){
    // *****************************************************************************
    // put in the algorithm 2 here

    p_jdPerfTestAlgo2();

    // your algorithm ends 2 here
    // *****************************************************************************
    counter++;
    }
    if(counter == 0) return e.error("JdPerformance::performanceTest(void (*p_jdPerfTestAlgo1)(), void (*p_jdPerfTestAlgo2)()) | counter == 0");
    timeAlgorithm2  = 1000000.0f/counter;
    timeAlgorithm2 -= timeLoop;
    std::cout << "The algorithm (2) ran  " << (float)counter/1000 << "k times in one second." << std::endl;
    std::cout << "One algorithm (2) took " << timeAlgorithm2 << " microseconds." << std::endl << std::endl;

    // rating
    if(timeAlgorithm1 < timeAlgorithm2){
        std::cout << "Your first algorithm (1) ran " << (1.0f-(timeAlgorithm1/timeAlgorithm2))*100 << "% faster than your second algorithm (2)." << std::endl;
    } else {
        std::cout << "Your second algorithm (2) ran " << (1.0f-(timeAlgorithm2/timeAlgorithm1))*100 << "% faster than your first algorithm (1)." << std::endl;
    }
}


