/**
@class JdPerformance JdPerformance.h "JdPerformance.h"

@brief
This class provides methods to test the performance of algorithms and code sections.\n
It can be usefull to find a performant solution for computationally intensive functions.

@version v0.0.3 22.05.2021
@copyright This project is released under the MIT License (MIT).
\n
\n Copyright (c) 2021 Jochen Detert. All rights reserved.
\n
\n Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
\n
\n The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
\n
\n THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

v0.0.1 20.03.2021
- initial documented release
- added static void performanceTest(void (*p_jdPerfTestAlgo1)(), void (*p_jdPerfTestAlgo2)())

v0.0.2 21.03.2021
- bugfix output is micro- not nanoseconds ;-)
- added functions for performance measurement
- some improvements to make the measurements more accurate

v0.0.3 22.05.2021
- using github now
- documentation
- changed some function names to correct english
*/

#ifndef JDPERFORMANCE_H
#define JDPERFORMANCE_H

#include <iostream>
#include <string>
#include <sstream>
#include <chrono>
#include "JdError.h"

class JdPerformance
{
    public:
        JdPerformance();
        JdPerformance(char* name);
        virtual ~JdPerformance();

        //void multiPerformanceMeasurement(char* name, JdPerformanceMeasurementInstruction instruction);
        //void multiPerformanceMeasurement(char* name, JdPerformanceMeasurementInstruction instruction, uint16_t numberOfMeasurements);
        //void multiPerformanceMeasurement(char* name, JdPerformanceMeasurementInstruction instruction, uint16_t numberOfMeasurements, uint16_t ignoreFirstNumber);
        //void multiPerformanceMeasurement(char* name, JdPerformanceMeasurementInstruction instruction, uint16_t numberOfMeasurements, uint16_t ignoreFirstNumber, bool exitAfter);
        //void multiPerformanceMeasurement(char* name, JdPerformanceMeasurementInstruction instruction, uint16_t numberOfMeasurements, uint16_t ignoreFirstNumber, bool exitAfter, bool loop);
        /// @brief Belongs to the group of functions to measure performance in the source code. Indicates the finishing point of the measurement.\n
        /// A description and example can be found below the function
        /// @link performanceMeasurementStart(uint16_t numberOfMeasurements, uint16_t ignoreFirstNumber, bool autoReport, bool exitAfter, bool loop) @endlink with all parameters.
        static bool performanceMeasurementFinish();
        /// @brief Belongs to the group of functions to measure performance in the source code. Indicates the starting point of the measurement.
        /// A description and example can be found below the function
        /// @link performanceMeasurementStart(uint16_t numberOfMeasurements, uint16_t ignoreFirstNumber, bool autoReport, bool exitAfter, bool loop) @endlink with all parameters.
        static bool performanceMeasurementStart();
        /// @brief Belongs to the group of functions to measure performance in the source code. Indicates the starting point of the measurement.
        /// A description and example can be found below the function
        /// @link performanceMeasurementStart(uint16_t numberOfMeasurements, uint16_t ignoreFirstNumber, bool autoReport, bool exitAfter, bool loop) @endlink with all parameters.
        static bool performanceMeasurementStart(uint16_t numberOfMeasurements);
        /// @brief Belongs to the group of functions to measure performance in the source code. Indicates the starting point of the measurement.
        /// A description and example can be found below the function
        /// @link performanceMeasurementStart(uint16_t numberOfMeasurements, uint16_t ignoreFirstNumber, bool autoReport, bool exitAfter, bool loop) @endlink with all parameters.
        static bool performanceMeasurementStart(uint16_t numberOfMeasurements, uint16_t ignoreFirstNumber);
        /// @brief Belongs to the group of functions to measure performance in the source code. Indicates the starting point of the measurement.
        /// A description and example can be found below the function
        /// @link performanceMeasurementStart(uint16_t numberOfMeasurements, uint16_t ignoreFirstNumber, bool autoReport, bool exitAfter, bool loop) @endlink with all parameters.
        static bool performanceMeasurementStart(uint16_t numberOfMeasurements, uint16_t ignoreFirstNumber, bool autoReport);
        /// @brief Belongs to the group of functions to measure performance in the source code. Indicates the starting point of the measurement.
        /// A description and example can be found below the function
        /// @link performanceMeasurementStart(uint16_t numberOfMeasurements, uint16_t ignoreFirstNumber, bool autoReport, bool exitAfter, bool loop) @endlink with all parameters.
        static bool performanceMeasurementStart(uint16_t numberOfMeasurements, uint16_t ignoreFirstNumber, bool autoReport, bool exitAfter);
        /// @brief Belongs to the group of functions to measure performance in the source code. Indicates the starting point of the measurement.
        /// A description and example can be found below the detailed description of this function.
        /**
        @param numberOfMeasurements The number of times performanceMeasurementStart() and performanceMeasurementFinish() have to be reached until the report is created.
        Default is 1.
        @param ignoreFirstNumber You can give a number of loops, not taken into account in the calculation. This is usefull, if there are some routines that initialise the first time they run.
        Default is 0.
        @param autoReport If autoReport is set TRUE, you don't need the function performanceMeasurementReport(). In this case the report is generated as soon as the given number of measurements is reached.
        Default is false.
        @param exitAfter If exitAfter is set TRUE, the exit(0) command is called after output of the report.
        Default is false.
        @param loop If loop is set TRUE, the measurement will start again after output of the report. From the second measurement the parameter ignoreFirstNumber is ignored.
        Default is false.
        @return Returns TRUE if the actual call is measured, FALSE if not.

        Instruction for use:

        To measure the performance of a source code part, you have to use at least three functions if you use default settings. performanceMeasurementStart() is the startingpoint of the measurement.
        At the end of the measured code you have to insert the function performanceMeasurementFinish().
        At a place of your choice in your code place the function performanceMeasurementReport() to get the output data.

        Here is an example using default settings to measure the time a function consumed.
        @verbatim
        int main()
        {
            // start the time measurement;
            performanceMeasurementStart();

            functionThatDoesBrilliantThings();

            // end the measurement
            performanceMeasurementFinish();

            // output report
            performanceMeasurementReport();
        }
        @endverbatim

        This is an example of the report for the above code.
        @verbatim
        Performance data:
        Ignored first:          0
        Number of measurements: 1
        Total time:   4.740 ms
        Minimal time: 4.740 ms
        Maximum time: 4.740 ms
        Average time: 4.740 ms
        @endverbatim

        Let's explain the output with changed settings.
        In this example glfwSwapBuffers(window) runs only every 1/60 second. To measure the time for the rest of the routines in the loop, the performanceMeasurementStart() function
        is called after, the performanceMeasurementFinish() function before the command with the delay.
        @verbatim
        while(!vu.getWindowShouldClose()){
            [...]
            functionThatDoesBrilliantThings();
            [...]
            JdPerformance::performanceMeasurementFinish();
            glfwSwapBuffers(window); // runs every 1/60 sec (erwin_hp with geforce on)
            JdPerformance::performanceMeasurementStart(150, 5, true, false, true);
        }
        @endverbatim

        This is an example of the output of the above code.\n
        A new report is generated every few seconds.
        @verbatim
        Performance data:
        Ignored first:          5
        Number of measurements: 150
        Total time:   319.642 ms
        Minimal time: 1.254 ms
        Maximum time: 7.662 ms
        Average time: 2.131 ms

        Performance data:
        Ignored first:          0
        Number of measurements: 150
        Total time:   814.483 ms
        Minimal time: 3.596 ms
        Maximum time: 6.514 ms
        Average time: 5.430 ms

        Performance data:
        Ignored first:          0
        Number of measurements: 150
        Total time:   577.056 ms
        Minimal time: 1.173 ms
        Maximum time: 8.559 ms
        Average time: 3.847 ms
        .
        .
        .
        @endverbatim
        */
        static bool performanceMeasurementStart(uint16_t numberOfMeasurements, uint16_t ignoreFirstNumber, bool autoReport, bool exitAfter, bool loop);
        /// @brief Belongs to the group of functions to measure performance in the source code. Stops the measurement. It will not start again if PMI_START is reached again.
        /// @link performanceMeasurementStart(uint16_t numberOfMeasurements, uint16_t ignoreFirstNumber, bool autoReport, bool exitAfter, bool loop) @endlink with all parameters.
        static void performanceMeasurementStop();
        /// @brief Belongs to the group of functions to measure performance in the source code. Output data measured.
        /// A description and example can be found below the function
        /// @link performanceMeasurementStart(uint16_t numberOfMeasurements, uint16_t ignoreFirstNumber, bool autoReport, bool exitAfter, bool loop) @endlink with all parameters.
        static bool performanceMeasurementReport();
        /// @brief Belongs to the group of functions to measure performance in the source code. Reset to starting values in order to make possible the start of a new measurement.
        /// @link performanceMeasurementStart(uint16_t numberOfMeasurements, uint16_t ignoreFirstNumber, bool autoReport, bool exitAfter, bool loop) @endlink with all parameters.
        static void performanceMeasurementReset();
        /// @brief Compares the running time of two algorithms, each in a loop for one second.
        /**
        Instructions for use:

        To compare to versions of an algorithm attach them to two functions. JdPerfomanceTest will compare them.
        Use the following templates:

        Declare the functions.
        @verbatim
        void jdPerfTestAlgo1();
        void jdPerfTestAlgo2();
        @endverbatim

        Define the functions.
        @verbatim
        void jdPerfTestAlgo1(){
            // *****************************************************************************
            // declare the variables your first algorithm (1) uses here

            // your declaration ends here
            // *****************************************************************************

            // *****************************************************************************
            // put in the first algorithm (1) here

            // your algorithm (1) ends here
            // *****************************************************************************
        }

        void jdPerfTestAlgo2(){
            // *****************************************************************************
            // declare the variables your second algorithm (2) uses here

            // your declaration ends here
            // *****************************************************************************

            // *****************************************************************************
            // put in the second algorithm (2) here

            // your algorithm (2) ends here
            // *****************************************************************************
        }
        @endverbatim

        In your main function declare the function pointers.
        @verbatim
        void (*p_jdPerfTestAlgo1)()=jdPerfTestAlgo1;
        void (*p_jdPerfTestAlgo2)()=jdPerfTestAlgo2;
        @endverbatim

        Now you can call the test and compare.
        @verbatim
        JdPerformance::performanceTest(p_jdPerfTestAlgo1, p_jdPerfTestAlgo2);
        @endverbatim

        Here is an example I used to optimize a simulation function.
        In this case I found a faster method to calculate the cosinus between to vectors.
        @verbatim
        #include <iostream>
        #include "glm/glm.hpp"
        #include "glm/gtc/matrix_transform.hpp"
        #include "glm/gtc/type_ptr.hpp"

        void jdPerfTestAlgo1();
        void jdPerfTestAlgo2();

        void jdPerfTestAlgo1(){
            // *****************************************************************************
            // declare the variables your first algorithm (1) uses here

            glm::vec3 v1, v2;
            v1 = glm::vec3(2.3f, 5.1f, 0.2f);
            v2 = glm::vec3(6.3f, 2.1f, 3.4f);

            // your declaration ends here
            // *****************************************************************************

            // *****************************************************************************
            // put in the first algorithm (1) here

            glm::dot(glm::normalize(v1), glm::normalize(v2));

            // your algorithm (1) ends here
            // *****************************************************************************
        }

        void jdPerfTestAlgo2(){
            // *****************************************************************************
            // declare the variables your second algorithm (2) uses here

            glm::vec3 v1, v2;
            v1 = glm::vec3(2.3f, 5.1f, 0.2f);
            v2 = glm::vec3(6.3f, 2.1f, 3.4f);

            // your declaration ends here
            // *****************************************************************************

            // *****************************************************************************
            // put in the second algorithm (2) here

            glm::dot(v1, v2)/(glm::length(v1) * glm::length(v2));

            // your algorithm (2) ends here
            // *****************************************************************************
        }
        @endverbatim

        This is the output.
        @verbatim
        Please wait a few seconds.

        Now checking performance of test loop.

        Now checking performance of your first algorithm.

        The algorithm (1) ran  6639.95k times in one second.
        One algorithm (1) took 0.121081 microseconds.

        Now checking performance of your second algorithm.

        The algorithm (2) ran  9183.11k times in one second.
        One algorithm (2) took 0.0793732 microseconds.

        Your second algorithm (2) ran 34.4463% faster than your first algorithm (1).
        @endverbatim
        */
        static bool performanceTest(void (*p_jdPerfTestAlgo1)(), void (*p_jdPerfTestAlgo2)());

    protected:

    private:
        //private variables
        enum PMState{
            PMS_NONE,
            PMS_IGNORE_FIRST,
            PMS_RUNNING,
            PMS_STOPPED,
            PMS_REPORTED,
        };
        /// @brief For error handling.
        static JdError e;
        static void nanosecondsToText(uint64_t ns, char* formatedTime);
        static bool performanceMeasurementAutoReport;
        static uint64_t performanceMeasurementCounter;
        static bool performanceMeasurementExitAfter;
        static uint16_t performanceMeasurementsIgnored;
        static uint16_t performanceMeasurementIgnoreFirstNumber;
        static bool performanceMeasurementLoop;
        char* performanceMeasurementName;
        static uint16_t performanceMeasurementNumberOfMeasurements;
        static uint64_t performanceMeasurementTimeAverage;
        static uint64_t performanceMeasurementTimeLast;
        static uint64_t performanceMeasurementTimeMax;
        static uint64_t performanceMeasurementTimeMin;
        static uint64_t performanceMeasurementTimeStart;
        static uint64_t performanceMeasurementTimeTotal;
        static PMState state;

        // private functions
        static void performanceMeasurementIgnoreFirst();
        static void performanceMeasurementInit();
};

#endif // JDPERFORMANCE_H
