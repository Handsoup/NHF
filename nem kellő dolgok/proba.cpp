#include <iostream>
#include <cstdlib>
#include <chrono>
#include <thread>
#include <vector>
#include <random>

int main() {
    // Execute the Python code using the system() function
    std::string pythonCode = R"(
import matplotlib.pyplot as plt

plt.ion()  # Turn on interactive mode for real-time plotting

# Create an empty plot with logarithmic y-axis
fig, ax = plt.subplots()
ax.set_yscale('log')
ax.set_xlabel('x')
ax.set_ylabel('y')
ax.set_title('Real-time Plot')

# Plot random points in real-time
while True:
    random_number = float(input())
    ax.scatter(random_number, random_number, color='red')
    plt.pause(1)  # Pause for 1 second to see the point
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
    while (true) {
        double random_number = dis(gen);
        fprintf(pipe, "%f\n", random_number);
        fflush(pipe);  // Flush the pipe to send the data immediately
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    pclose(pipe);

    return 0;
}

