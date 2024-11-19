#include <iostream>
#include <vector>
#include <string>
#include <mutex>

class Logger
{
private:
    // Static instance for the singleton
    static Logger *instance;
    // Mutex for thread safety
    static std::mutex mtx;
    // Vector to store log entries
    std::vector<std::string> logs;

    // Private constructor to prevent direct instantiation
    Logger() {}

public:
    // Get the singleton instance
    static Logger *getInstance()
    {
        std::lock_guard<std::mutex> lock(mtx);
        if (!instance)
        {
            instance = new Logger();
        }
        return instance;
    }

    // Log a message with "info" level
    void logInfo(const std::string &message)
    {
        logs.push_back("[INFO]: " + message);
        std::cout << "[INFO]: " << message << std::endl;
    }

    // Log a message with "warning" level
    void logWarning(const std::string &message)
    {
        logs.push_back("[WARNING]: " + message);
        std::cout << "[WARNING]: " << message << std::endl;
    }

    // Log a message with "error" level
    void logError(const std::string &message)
    {
        logs.push_back("[ERROR]: " + message);
        std::cout << "[ERROR]: " << message << std::endl;
    }

    // Retrieve all logs
    void showLogs() const
    {
        std::cout << "All logs:" << std::endl;
        for (const auto &log : logs)
        {
            std::cout << log << std::endl;
        }
    }
};

// Initialize static members
Logger *Logger::instance = nullptr;
std::mutex Logger::mtx;

// Client Code
int main()
{
    // Get singleton logger instance
    Logger *logger = Logger::getInstance();

    // Log messages from different parts of the application
    logger->logInfo("Application started.");
    logger->logWarning("Low disk space warning.");
    logger->logError("Unable to connect to database.");

    // Get logger instance again (same instance)
    Logger *logger2 = Logger::getInstance();
    logger2->logInfo("Another part of the application is logging.");

    // Retrieve all logs
    logger->showLogs();

    return 0;
}
