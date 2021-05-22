 #include "JdError.h"

JdError::JdError()
{
    //ctor
    bufferSize = 5;
    reportError = true;
    init();
}

JdError::JdError(uint8_t newBufferSize, bool valueReportError)
{
    //ctor
    bufferSize = newBufferSize;
    reportError = valueReportError;
    init();
}

JdError::~JdError()
{
    //dtor
}

void JdError::addErrorData(int16_t code, char* message, uint8_t type){
    if(numberOfErrors == bufferSize) { // shift
        for(uint8_t i = 0; i < bufferSize - 1; i++){
            errorData[i] = errorData[i+1];
        }
        numberOfErrors--;
        overflow = true;
    }
    errorData[numberOfErrors].code = code;
    errorData[numberOfErrors].message = message;
    errorData[numberOfErrors].type = type;
    numberOfErrors++;
}

// static call, no buffer
bool JdError::error(char* message){
    std::cout << "error: " << message << std::endl;
    return false;
}

bool JdError::error(int16_t code, char* message){
    addErrorData(code, message, 1);
    if(!reportError) return false;
    return error(message);
}

// static call, no buffer
void JdError::fatalError(char* message){
    std::cout << "fatal error: " << message << std::endl;
    exit(1);
}

JdError::ErrorData JdError::getErrorData(){
    JdError::ErrorData retval;

    retval = peekErrorData();
    numberOfErrors--;

    return retval;
}

bool JdError::init(){
    hasError = false;
    numberOfErrors = 0;
    overflow = false;

    v = JdVersionControl({JDERROR_VERSION_MAJOR, JDERROR_VERSION_MINOR, JDERROR_VERSION_PATCH});

	errorData = (ErrorData*) malloc (sizeof (ErrorData) * bufferSize);
	if (errorData == NULL) return JdError::error("JdError::init() | Could not allocate memory.");
	return true;
}

JdError::ErrorData JdError::peekErrorData(){
    JdError::ErrorData retval;

    if(numberOfErrors == 0){
        if(overflow){ // discarded
            retval.code = 0;
            retval.message = "overflow | message discarded";
            retval.type = 3; // discarded
            retval.more = false;
            overflow = false;
            return retval;
        }
        retval.code = 0;
        retval.message = "nothing to report";
        retval.type = 0;
        retval.more = false;
        return retval;
    }

    retval = errorData[numberOfErrors - 1];
    if(numberOfErrors > 1 || overflow){
        retval.more = true;
    } else {
        retval.more = false;
    }

    return retval;
}

// static call, no buffer
bool JdError::warning(char* message){
    std::cout << "warning: " << message << std::endl;
    return true;
}

bool JdError::warning(int16_t code, char* message){
    addErrorData(code, message, 2);
    if(!reportError) return true;
    return warning(message);
}
