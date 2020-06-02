#ifndef Language_h
#define Language_h

#include "Arduino.h"

const char CURSOR = '|';
const char SPACE = ' ';
const char DOUBLEPOINT = ':';
const char EQUALS = '=';
const char HASHSIGN = '#';
const char ASTERIX = '*';
const char PERCENT = '%';
const char DASH = '-';
const char QUESTIONMARK = '?';
const char ZERO = '0';
const char S = 's';
const char M = 'm';
const char D = 'd';
const char DOUBLEQUOTES = '\"';
const char SLASH = '/';
const char NEWLINE = '\n';
const char CARRIAGERETURN = '\r';
const char SEMICOLON = ';';
const char BACKSLASH = '\\';
const char POINT = '.';
const char VERTICALBAR = '|';
const char COMMA = ',';
const char ENDOFLINE = '\0';
const char OPEN_BRACKET = '[';
const char CLOSE_BRACKET = ']';
const char OPEN_CURLY_BRACKET = '{';
const char CLOSE_CURLY_BRACKET = '}';

const char STR_TRUE[] PROGMEM = "true";
const char STR_FALSE[] PROGMEM = "false";
const char STR_MIN[] PROGMEM = "min";

const char F_ERROR_MAC[] PROGMEM = "ERROR: MAC address invalid";
const char F_COLOR_INVALID[] PROGMEM = "ERROR: Color code invalid";
const char F_ERROR_READING_FILE[] PROGMEM = "ERROR: reading file ";
const char F_LINE[] PROGMEM = "[%d] ";
const char F_ERROR_FILE[] PROGMEM = "ERROR: File doesn't exist ";
const char F_ERROR_OPEN[] PROGMEM = "ERROR couldn't open ";
const char F_ERROR_PARSING_JSON[] PROGMEM = "ERROR parsing JSON ";
const char F_ERROR_TO_BIG[] PROGMEM = "ERROR file too big ";
const char F_TMP[] PROGMEM = "/tmp";
const char F_COPY[] PROGMEM = "_copy";
const char F_ERROR_SAVING[] PROGMEM =
    "ERROR: saving file. Try 'format' and restart - ";

const char SETUP_OK[] PROGMEM = "OK";
const char SETUP_ERROR[] PROGMEM = "ERROR";
const char SETUP_MOUNT_SPIFFS[] PROGMEM = "Mounting SPIFFS...";
const char SETUP_FORMAT_SPIFFS[] PROGMEM = "Formatting SPIFFS...";
const char SETUP_SERIAL_WARNING[] PROGMEM = "Warning: Serial deactivated";
const char SETUP_STARTED[] PROGMEM = "STARTED! \\o/";
const char SETUP_COPYING[] PROGMEM = "Copying ";
const char SETUP_PROGMEM_TO_SPIFFS[] PROGMEM = " from PROGMEM to SPIFFS...";

const char D_BACK[] PROGMEM = "[BACK]";

#endif