#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define SIM_TIME 3600.0
#define RAND_SEED 42

// Random exponential generator
double exp_rand(double lambda) {
    double u = ((double)rand() + 1.0) / ((double)RAND_MAX + 1.0);
    return -log(u) / lambda;
}

// Generate events using Poisson process
int generate_events(double *events, double lambda) {
    double t = 0.0;
    int count = 0;
    while (t < SIM_TIME && count < 10000) {
        t += exp_rand(lambda);
        if (t < SIM_TIME)
            events[count++] = t;
    }
    return count;
}

// Fixed interval polling simulation
void simulate_fixed(double interval, double *events, int n_events,
                    double *mean_latency, int *polls) {
    double latency_sum = 0.0;
    *polls = ceil(SIM_TIME / interval);

    for (int i = 0; i < n_events; i++) {
        double next_poll = ceil(events[i] / interval) * interval;
        latency_sum += (next_poll - events[i]);
    }
    *mean_latency = (n_events > 0) ? latency_sum / n_events : 0.0;
}

// Adaptive polling simulation
void simulate_adaptive(double base, double min, double max, double *events,
                       int n_events, double *mean_latency, int *polls) {
    double current = base, t = 0.0, latency_sum = 0.0;
    int e_idx = 0, total_polls = 0, consecutive_empty = 0;

    while (t < SIM_TIME) {
        total_polls++;
        int found = 0;

        // Process events at current time
        while (e_idx < n_events && events[e_idx] <= t) {
            latency_sum += (t - events[e_idx]);
            e_idx++;
            found = 1;
        }

        // Adapt polling interval
        if (found) {
            consecutive_empty = 0;
            current = fmax(min, base / 2.0);
        } else {
            consecutive_empty++;
            if (consecutive_empty >= 3)
                current = fmin(current * 2.0, max);
        }
        t += current;
    }

    *mean_latency = (n_events > 0) ? latency_sum / n_events : 0.0;
    *polls = total_polls;
}

int main() {
    srand(RAND_SEED);
    
    // Open output file
    FILE *fp = fopen("results.csv", "w");
    if (!fp) {
        perror("results.csv");
        return 1;
    }
    fprintf(fp, "event_rate,fixed_latency,adaptive_latency,fixed_polls,adaptive_polls,energy_saved,latency_increase\n");

    double rates[] = {0.005, 0.01, 0.02, 0.03, 0.04, 0.05};
    int n_rates = sizeof(rates) / sizeof(rates[0]);

    // Run simulation for each event rate
    for (int r = 0; r < n_rates; r++) {
        double lambda = rates[r];
        double events[10000];
        int n = generate_events(events, lambda);

        double fixed_lat, adaptive_lat;
        int fixed_polls, adaptive_polls;

        simulate_fixed(15.0, events, n, &fixed_lat, &fixed_polls);
        simulate_adaptive(15.0, 5.0, 300.0, events, n, &adaptive_lat, &adaptive_polls);

        double energy_saved = 100.0 * (1.0 - (double)adaptive_polls / fixed_polls);
        double latency_increase = (fixed_lat > 0) ? 100.0 * ((adaptive_lat / fixed_lat) - 1.0) : 0.0;

        printf("Rate=%.3f -> Energy saved=%.1f%%, Latency +%.1f%%\n",
               lambda, energy_saved, latency_increase);

        fprintf(fp, "%.3f,%.3f,%.3f,%d,%d,%.2f,%.2f\n",
                lambda, fixed_lat, adaptive_lat, fixed_polls, adaptive_polls,
                energy_saved, latency_increase);
    }
    
    fclose(fp);
    printf("\nResults written to results.csv\n");
    return 0;
}
