#pragma once

#include <Arduino.h>
#include <vector>

class Logger {
public:

    const size_t MAX_LOGS = 100;
    //public log vector
    std::vector<String> logMessages;

    void log_debug(const String& message);
    void log_info(const String& message);
    void log_warn(const String& message);
    void log_error(const String& message);
    String getLogs() const {
        String allLogs;
        if(logMessages.empty()) {
            return "No logs available.";
        }
        for (const auto& log : logMessages) {
            allLogs += log + "\n";
        }
        return allLogs;
    }

};
