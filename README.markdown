# Test Stand Automation Tool

## Overview
The **Test Stand Automation Tool** is a C++ console application designed to simulate rocket engine test stand operations, automating the validation and reporting of sensor data (temperature, pressure, thrust). Built to showcase skills for SpaceX’s Software Engineer, Test Engineering and Operations role, it processes test data from CSV files, validates it against configurable thresholds, and generates detailed reports, mimicking real-world aerospace test workflows. The project leverages thread-safe parallel processing and secure coding practices to ensure reliability, aligning with SpaceX’s needs for automated checkout operations and streamlined test processes.

## Features
- **CSV Data Input**: Reads rocket engine sensor data (temperature in °C, pressure in bar, thrust in kN) from `sensor_data.csv`, simulating real test data processing.
- **Automated Validation**: Validates sensor data against thresholds (e.g., 0–100°C, 0–5 bar, 0–2000 kN) using parallel processing with `std::thread` and thread-safe `std::atomic` counters.
- **Reporting**: Generates console reports and logs results to `test_report.csv` with timestamps, summarizing valid sensors, averages, and anomalies.
- **Secure Coding**: Uses `ctime_s` for safe timestamp handling and includes robust error handling for file I/O.
- **Data Generation**: Includes a Python script (`generate_sensor_data.py`) to create synthetic, realistic test data with ~5% anomalies.
- **Reset Functionality**: Supports resetting the test stand for multiple runs, reflecting operational test cycles.

## Relevance to SpaceX
This project demonstrates skills critical for SpaceX’s test engineering:
- **Automation**: Streamlines sensor data validation and reporting, reducing manual effort in test workflows.
- **C++ Proficiency**: Utilizes `std::thread`, `std::atomic`, `std::chrono`, and `std::fstream` for real-time, reliable processing.
- **Aerospace Context**: Processes rocket engine sensor data, aligning with “vehicle test processes” and “aerospace instrumentation.”
- **Reliability**: Ensures thread-safe validation and robust error handling, vital for mission-critical systems.

## Prerequisites
- **C++ Compiler**: Visual Studio 2022 (or similar) with C++17 support.
- **Python**: Python 3.8+ (for generating `sensor_data.csv`).
- **Operating System**: Windows (tested), Linux/macOS (with minor adjustments for `ctime_s`).

## Setup and Running
1. **Clone the Repository**:
   ```bash
   git clone <repository-url>
   cd TestStandAutomationTool
   ```

2. **Generate Sensor Data**:
   - Run the Python script to create `sensor_data.csv`:
     ```bash
     python generate_sensor_data.py
     ```
   - Copy `sensor_data.csv` to the build output directory (e.g., `Debug` or `Release`).

3. **Build the C++ Program**:
   - Open `TestStandAutomationTool.sln` in Visual Studio.
   - Set the solution configuration to `Debug` or `Release`.
   - Build the solution (Ctrl+Shift+B).

4. **Run the Program**:
   - Run in Visual Studio (F5 for Debug or Ctrl+F5 for Release).
   - Alternatively, run the executable from the command line:
     ```bash
     ./Debug/TestStandAutomationTool.exe
     ```
   - Expected output:
     ```
     Test Report:
     78/100 sensors valid
     Avg Temp: 53.19 degC
     Avg Pressure: 3.264 bar
     Avg Thrust: 1122.94 kN
     Anomalies: 22
     Reset complete, ready for new test run.
     ...
     ```
   - Check `test_report.csv` in the output directory for logged results.

## Repository Contents
- `TestStandAutomationTool.cpp`: Main C++ source file implementing the test stand automation logic.
- `generate_sensor_data.py`: Python script to generate synthetic `sensor_data.csv` with realistic test data.
- `sensor_data.csv`: Sample CSV file with 100 rows of sensor data (generated or provided as an example).
- `TestStandAutomationTool.sln`: Visual Studio solution file.
- `README.md`: This file, describing the project and usage.

## Future Enhancements
- Add command-line arguments to configure sensor thresholds dynamically.
- Support multiple CSV inputs for varied test scenarios.
- Integrate unit tests with a framework like Catch2.

## Contact
For questions or feedback, reach out via [your-email@example.com] or [your-GitHub-profile].