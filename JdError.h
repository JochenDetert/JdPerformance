/**
@class JdError JdError.h "JdError.h"

@brief
Intended to output errormessages and warnings and handle errors.

@version v0.0.4 22.05.2021
@copyright This project is released under the MIT License (MIT).
\n
\n Copyright (c) 2021 Jochen Detert. All rights reserved.
\n
\n Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
\n
\n The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
\n
\n THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

v0.0.1 15.03.2021
- initial release

v0.0.2 04.04.2021
- made error(char* message), fatalError(char* message) and warning(char* message) static

v0.0.3 10.04.2021
- added support for buffered errormessages for JdError objects
- added reportError switch for silent mode
- added first tries with versionControl

v0.0.4 22.05.2021
- added peekErrorData()
- use github now


Example object integration:
@verbatim
#include "JdError.h"

class JdRating
{
    public:
        [...]
        /// @brief Error handling.
        JdError::ErrorData getErrorData();
    protected:
        JdError* e;
}
@endverbatim
@verbatim
JdError::ErrorData ClassName::getErrorData(){
    return e->getErrorData();
}

e = new JdError(2, false);

e->error(42, "ClassName::FunctionName() | something == false");
@endverbatim

*/
#ifndef JDERROR_H
#define JDERROR_H

#define JDERROR_VERSION_MAJOR  0
#define JDERROR_VERSION_MINOR  0
#define JDERROR_VERSION_PATCH  4

#include <iostream>
#include "JdVersionControl.h"

class JdError
{
    public:
        // public types
        /// @brief Structure with data of a buffered error.
        struct ErrorData{
            /// @brief The errorcode.
            int16_t code;
            /// @brief The error message.
            char* message;
            /// @brief 0 -> nothing to report
            /// \n 1 -> error
            /// \n 2 -> warning
            /// \n 3 -> discarded
            uint8_t type; // 0 -> nothing to report, 1 -> error, 2 -> warning, 3 -> discarded
            /// @brief True if there are more errors buffered.
            bool more;
        };

        //public objects
        /// @brief Object for version control.
        JdVersionControl v;

        // public variables

        // public functions
        JdError();
        JdError(uint8_t newBufferSize, bool report);
        virtual ~JdError();

        /// @brief Outputs the message and returns false.
        static bool error(char* message);
        bool error(int16_t code, char* message);
        /// @brief Outputs the message and exits program.
        static void fatalError(char* message);
        /// @brief Get the Data of a buffered error and delete it from buffer.
        ErrorData getErrorData();
        /// @brief Get the Data of a buffered error and keep it in the buffer.
        ErrorData peekErrorData();
        /// @brief Outputs the message and returns true.
        static bool warning(char* message);
        bool warning(int16_t code, char* message);

    protected:
        // protected variables
        uint8_t bufferSize;
        ErrorData* errorData;
        bool hasError;
        bool reportError;
        uint8_t numberOfErrors;
        bool overflow;

        // protected functions
        void addErrorData(int16_t code, char* message, uint8_t type);
        bool init();

    private:
};

#endif // JDERROR_H
