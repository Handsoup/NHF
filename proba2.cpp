#include <iostream>
#include <thread>
#include <chrono>
#include <vector>

void printVector(const std::vector<int>& data)
{
    for (const auto& element : data)
    {
        std::cout << element << " ";
    }
    std::cout << std::endl;
}

int main()
{
    std::vector<int> data;
    std::chrono::steady_clock::time_point startTime = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsedSeconds;
	int i=0;
    while (elapsedSeconds.count() < 15.0)
    {
        // Push new elements into the vector
        data.push_back(0+i);

        // Check if five seconds have elapsed
        std::chrono::steady_clock::time_point currentTime = std::chrono::steady_clock::now();
        elapsedSeconds = currentTime - startTime;

        if (elapsedSeconds.count() >= 5.0)
        {
            printVector(data);
            startTime = currentTime;
        }
		i++;
        // Sleep for a short duration (e.g., 100 milliseconds) to avoid consuming excessive CPU
        std::this_thread::sleep_for(std::chrono::milliseconds(100));

    }
	

    return 0;
}

