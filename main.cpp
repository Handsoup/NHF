#include <iostream>
#include <cstdlib>
#include <chrono>
#include <thread>
#include <vector>
#include <random>
#include <atomic>

std::atomic<bool> windowClosed(false);  // Atomic flag to track the status of the matplotlib window

// Function to check if the matplotlib window is closed
bool isWindowClosed() {
    return windowClosed.load();
}

int main() {
    // Execute the Python code using the system() function
    std::string pythonCode = R"(
import matplotlib.pyplot as plt
from matplotlib.widgets import Button

plt.ion()  # Turn on interactive mode for real-time plotting

# Create an empty plot with logarithmic y-axis
fig, ax = plt.subplots()
ax.set_yscale('log')
ax.set_xlabel('x')
ax.set_ylabel('y')
ax.set_title('Real-time Plot')

# Initialize plot state
is_log_scale = True

# Button callback function
def toggle_scale(event):
    global is_log_scale
    if is_log_scale:
        ax.set_yscale('linear')
        button.label.set_text('Log Scale')
        is_log_scale = False
    else:
        ax.set_yscale('log')
        button.label.set_text('Linear Scale')
        is_log_scale = True

# Create a button to toggle between logarithmic and linear scales
button_ax = plt.axes([0.7, 0.05, 0.2, 0.075])
button = Button(button_ax, 'Linear Scale' if is_log_scale else 'Log Scale')
button.on_clicked(toggle_scale)

# Plot random points in real-time
points = []

while True:
    random_number = float(input())
    points.append(random_number)
    ax.scatter(points, points, color='red')
    plt.pause(0.001)  # Pause briefly to update the plot
    if len(points) >= 10:
        break

# Check if the window is closed
if not plt.get_fignums():
    print("WindowClosed")

# Keep the matplotlib window open
while True:
    if not plt.get_fignums():
        print("WindowClosed")
        break
    plt.pause(5)
)";

    std::string pythonCommand = "python3 -c \"" + pythonCode + "\"";

    // Start the Python subprocess
    FILE* pipe = popen(pythonCommand.c_str(), "w");
    if (!pipe) {
        std::cerr << "Unable to open pipe to Python" << std::endl;
        return 1;
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0.0, 1.0);

    // Generate and send random numbers to Python in real-time
    while (!isWindowClosed()) {
        for (int i = 0; i < 10; ++i) {
            double random_number = dis(gen);
            fprintf(pipe, "%f\n", random_number);
            fflush(pipe);  // Flush the pipe to send the data immediately
        }
        std::this_thread::sleep_for(std::chrono::seconds(5));
    }

    pclose(pipe);

    return 0;
}

