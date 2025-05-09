import random
import csv

# Define realistic ranges and anomaly probabilities
TEMP_MEAN, TEMP_STD = 50.0, 15.0  # Temperature: center at 50°C, std dev 15°C
PRESSURE_MEAN, PRESSURE_STD = 3.0, 1.0  # Pressure: center at 3 bar, std dev 1 bar
THRUST_MEAN, THRUST_STD = 1000.0, 200.0  # Thrust: center at 1000 kN, std dev 200 kN
ANOMALY_PROB = 0.05  # 5% chance of anomaly per value
TEMP_MAX, PRESSURE_MAX, THRUST_MAX = 100.0, 5.0, 2000.0

# Generate synthetic data
data = []
for _ in range(100):
    # Temperature
    if random.random() < ANOMALY_PROB:
        temp = random.uniform(TEMP_MAX + 10, TEMP_MAX + 50)  # Anomalous: 110–150°C
    else:
        temp = max(0, min(TEMP_MAX, random.gauss(TEMP_MEAN, TEMP_STD)))  # Normal distribution
    
    # Pressure
    if random.random() < ANOMALY_PROB:
        pressure = random.uniform(PRESSURE_MAX + 1, PRESSURE_MAX + 3)  # Anomalous: 6–8 bar
    else:
        pressure = max(0, min(PRESSURE_MAX, random.gauss(PRESSURE_MEAN, PRESSURE_STD)))  # Normal distribution
    
    # Thrust
    if random.random() < ANOMALY_PROB:
        thrust = random.uniform(THRUST_MAX + 100, THRUST_MAX + 500)  # Anomalous: 2100–2500 kN
    else:
        thrust = max(0, min(THRUST_MAX, random.gauss(THRUST_MEAN, THRUST_STD)))  # Normal distribution
    
    data.append([temp, pressure, thrust])

# Write to CSV
with open('sensor_data.csv', 'w', newline='') as csvfile:
    writer = csv.writer(csvfile)
    writer.writerow(['Temperature', 'Pressure', 'Thrust'])  # Header
    for row in data:
        writer.writerow([f"{row[0]:.1f}", f"{row[1]:.1f}", f"{row[2]:.1f}"])  # 1 decimal place