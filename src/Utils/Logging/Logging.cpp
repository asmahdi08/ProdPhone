#include "Logging.h"

void Logger::log_debug(const String& message) {
    Serial.println("[DEBUG] " + message);
    logMessages.push_back("[DEBUG] " + message);
}

void Logger::log_info(const String& message) {
    Serial.println("[INFO] " + message);
    logMessages.push_back("[INFO] " + message);
}

void Logger::log_warn(const String& message) {
    Serial.println("[WARN] " + message);
    logMessages.push_back("[WARN] " + message);
}

void Logger::log_error(const String& message) {
    Serial.println("[ERROR] " + message);
    logMessages.push_back("[ERROR] " + message);
}
