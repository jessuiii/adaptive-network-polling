import pandas as pd
import matplotlib.pyplot as plt

df = pd.read_csv('results.csv')

plt.figure(figsize=(10, 6))
plt.plot(df['event_rate'], df['energy_saved'], 'bo-', label='Energy Saved (%)', linewidth=2, markersize=6)
plt.plot(df['event_rate'], df['latency_increase'], 'ro-', label='Latency Increase (%)', linewidth=2, markersize=6)

plt.title('Adaptive Polling Energy vs Latency Trade-off', fontsize=14, fontweight='bold')
plt.xlabel('Event Rate (events/sec)', fontsize=12)
plt.ylabel('Percentage', fontsize=12)
plt.grid(True, alpha=0.3)
plt.legend()

plt.tight_layout()

plt.savefig('adaptive_polling_plot.png', dpi=300, bbox_inches='tight')
plt.show()

print("✅ Plot saved as adaptive_polling_plot.png")