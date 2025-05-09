#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <chrono>
#include <thread>
#include <string>
#include <atomic>

// Simple struct to hold sensor data
struct SensorData {
    double temperature; // degC
    double pressure;    // bar
    double thrust;      // kN
};

// TestStand class to manage test automation
class TestStand {
private:
    std::vector<SensorData> data;
    std::ofstream logFile;
    const double TEMP_MAX = 100.0, TEMP_MIN = 0.0;
    const double PRESSURE_MAX = 5.0, PRESSURE_MIN = 0.0;
    const double THRUST_MAX = 2000.0, THRUST_MIN = 0.0;
    std::atomic<int> passCount{ 0 }; // Use atomic for thread safety
    std::atomic<int> failCount{ 0 };

public:
    TestStand() {
        logFile.open("test_report.csv", std::ios::app);
        if (!logFile.is_open()) {
            throw std::runtime_error("Failed to open test_report.csv");
        }
        logFile << "Timestamp,PassCount,FailCount,AvgTemp,AvgPressure,AvgThrust\n";
    }

    ~TestStand() {
        if (logFile.is_open()) logFile.close();
    }

    // Read sensor data from CSV file
    void generateData(const std::string& filename) {
        data.clear();
        std::ifstream file(filename);
        if (!file.is_open()) {
            throw std::runtime_error("Failed to open " + filename);
        }
        std::string line;
        std::getline(file, line); // Skip header (Temperature,Pressure,Thrust)
        while (std::getline(file, line)) {
            std::stringstream ss(line);
            double temp, pres, thrust;
            char comma;
            ss >> temp >> comma >> pres >> comma >> thrust;
            data.push_back({ temp, pres, thrust });
        }
        file.close();
        if (data.empty()) {
            throw std::runtime_error("No data read from " + filename);
        }
    }

    // Validate sensor data against thresholds
    void validateData() {
        passCount = 0;
        failCount = 0;

        // Parallel validation using threads
        auto validateChunk = [&](size_t start, size_t end) {
            for (size_t i = start; i < end; ++i) {
                bool valid = (data[i].temperature >= TEMP_MIN && data[i].temperature <= TEMP_MAX) &&
                    (data[i].pressure >= PRESSURE_MIN && data[i].pressure <= PRESSURE_MAX) &&
                    (data[i].thrust >= THRUST_MIN && data[i].thrust <= THRUST_MAX);
                valid ? ++passCount : ++failCount;
            }
            };

        size_t chunkSize = data.size() / 2;
        std::thread t1(validateChunk, 0, chunkSize);
        std::thread t2(validateChunk, chunkSize, data.size());
        t1.join();
        t2.join();
    }

    // Generate test report
    void generateReport() {
        double avgTemp = 0.0, avgPressure = 0.0, avgThrust = 0.0;
        for (const auto& d : data) {
            avgTemp += d.temperature;
            avgPressure += d.pressure;
            avgThrust += d.thrust;
        }
        avgTemp /= data.size();
        avgPressure /= data.size();
        avgThrust /= data.size();

        auto now = std::chrono::system_clock::now();
        auto now_c = std::chrono::system_clock::to_time_t(now);
        char timeBuffer[26]; // ctime_s requires a buffer of at least 26 chars
        ctime_s(timeBuffer, sizeof(timeBuffer), &now_c); // Secure timestamp
        std::string timestamp = timeBuffer;
        timestamp.pop_back(); // Remove trailing newline

        std::cout << "Test Report:\n"
            << passCount << "/" << data.size() << " sensors valid\n"
            << "Avg Temp: " << avgTemp << " degC\n"
            << "Avg Pressure: " << avgPressure << " bar\n"
            << "Avg Thrust: " << avgThrust << " kN\n"
            << "Anomalies: " << failCount << "\n";

        logFile << timestamp << "," << passCount << "," << failCount << ","
            << avgTemp << "," << avgPressure << "," << avgThrust << "\n";
    }

    // Reset test stand for new run
    void reset() {
        data.clear();
        passCount = 0;
        failCount = 0;
        std::cout << "Reset complete, ready for new test run.\n";
    }

    // Run full test cycle
    void runTest(const std::string& filename = "sensor_data.csv") {
        generateData(filename);
        validateData();
        generateReport();
    }
};

// Main function to demonstrate usage
int main() {
    try {
        TestStand stand;
        stand.runTest("sensor_data.csv");
        std::this_thread::sleep_for(std::chrono::seconds(1));
        stand.reset();
        stand.runTest("sensor_data.csv");
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}