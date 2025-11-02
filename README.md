# Adaptive Network Polling Simulation

A C-based simulation that compares fixed vs adaptive polling strategies for network event processing, demonstrating the trade-offs between energy efficiency and response latency.

## 📋 Overview

This project implements and analyzes two different polling strategies:
- **Fixed Polling**: Polls at regular intervals (every 15 seconds)
- **Adaptive Polling**: Dynamically adjusts polling frequency based on event activity

The simulation uses a Poisson process to generate network events and measures:
- Energy consumption (number of polls)
- Response latency (time between event occurrence and detection)

## 🚀 Features

- **Event Generation**: Uses exponential distribution to simulate realistic network events
- **Dual Simulation**: Compares fixed vs adaptive polling side-by-side
- **Performance Metrics**: Calculates energy savings and latency trade-offs
- **Data Export**: Outputs results to CSV for further analysis
- **Visualization**: Python script for plotting results

## 📁 Project Structure

```
adaptive-network-polling/
├── adaptive_network.c      # Main simulation program (C)
├── plot_results.py         # Visualization script (Python)
├── README.md              # Project documentation
├── results.csv            # Simulation output data
└── adaptive_polling_plot.png # Generated visualization
```

## 🛠️ Requirements

### For C Simulation:
- GCC compiler
- Math library support (`-lm`)

### For Visualization (Optional):
- Python 3.x
- matplotlib
- pandas

## 📦 Installation & Usage

### 1. Clone the Repository
```bash
git clone https://github.com/yourusername/adaptive-network-polling.git
cd adaptive-network-polling
```

### 2. Compile the C Program
```bash
gcc -o adaptive_network adaptive_network.c -lm
```

### 3. Run the Simulation
```bash
./adaptive_network
```

### 4. Generate Visualization (Optional)
```bash
pip install matplotlib pandas
python plot_results.py
```

## 📊 Sample Output

```
Rate=0.005 -> Energy saved=75.4%, Latency +1071.3%
Rate=0.010 -> Energy saved=33.3%, Latency +175.3%
Rate=0.020 -> Energy saved=27.1%, Latency +229.2%
Rate=0.030 -> Energy saved=-7.5%, Latency +93.4%
Rate=0.040 -> Energy saved=-31.7%, Latency +31.7%
Rate=0.050 -> Energy saved=-36.7%, Latency +21.4%

Results written to results.csv
```

## 📈 Key Findings

| Event Rate | Energy Savings | Latency Increase | Recommendation |
|-----------|---------------|------------------|----------------|
| **Low (≤0.02)** | **27-75%** | 175-1071% | ✅ **Use Adaptive** |
| **High (≥0.03)** | -8 to -37% | 21-93% | ❌ **Use Fixed** |

### Insights:
- **Adaptive polling excels at low event rates** where energy savings outweigh latency costs
- **Fixed polling is better for high event rates** due to adaptive overhead
- **Sweet spot**: Event rates around 0.005-0.02 events/second

## ⚙️ Configuration

Key parameters in `adaptive_network.c`:

```c
#define SIM_TIME 3600.0        // Simulation duration (seconds)
#define RAND_SEED 42           // Random seed for reproducibility

// Adaptive polling parameters
double base_interval = 15.0;    // Starting interval
double min_interval = 5.0;      // Minimum polling interval
double max_interval = 300.0;    // Maximum polling interval
```

## 📄 Output Files

- **`results.csv`**: Raw simulation data with columns:
  - `event_rate`: Events per second
  - `fixed_latency`: Average latency for fixed polling
  - `adaptive_latency`: Average latency for adaptive polling
  - `fixed_polls`: Total polls for fixed strategy
  - `adaptive_polls`: Total polls for adaptive strategy
  - `energy_saved`: Percentage energy savings
  - `latency_increase`: Percentage latency increase

## 🔬 Algorithm Details

### Fixed Polling
- Polls every 15 seconds regardless of activity
- Simple and predictable
- Energy usage: `ceil(SIM_TIME / interval)` polls

### Adaptive Polling
- Starts with base interval (15s)
- **Reduces** interval to `max(min, base/2)` when events found
- **Increases** interval to `min(current*2, max)` after 3 consecutive empty polls
- Dynamic adjustment based on recent activity

## 🤝 Contributing

1. Fork the repository
2. Create a feature branch (`git checkout -b feature/improvement`)
3. Commit your changes (`git commit -am 'Add improvement'`)
4. Push to the branch (`git push origin feature/improvement`)
5. Create a Pull Request

## 📝 License

This project is open source and available under the [MIT License](LICENSE).

## 👥 Authors
Jesu Joel George,
Harshit Gupta, 
Gaurav Soni 

## 🙏 Acknowledgments

- Inspired by real-world network polling challenges
- Built for educational and research purposes
- Demonstrates classic computer science trade-offs between performance and efficiency
