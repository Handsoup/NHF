import time
import matplotlib.pyplot as plt


def process_file(filename):
    def read_file(filename):
        with open(filename, 'r') as file:
            line = file.readline().strip()
            values = line.split(',')
            return values

    # Convert values to numbers
    values_list = read_file(filename)

    # Create yAxis with 1024 zeros
    yAxis = [0] * 1024

    # Create xAxis
    xAxis = [i * (2 / 1024) for i in range(1024)]

    # Find closest xAxis values and update yAxis accordingly
    for value in values_list:
        if value:
            y_value = float(value)
            closest_index = min(range(len(xAxis)), key=lambda i: abs(xAxis[i] - y_value))
            yAxis[closest_index] += 1

    return xAxis, yAxis


# Set up the initial plot
filename = 'output.txt'  # Replace with the location of your file
xAxis, yAxis = process_file(filename)

fig, ax = plt.subplots()
line, = ax.plot(xAxis, yAxis)

# Create a button for toggling the y-axis scale
log_scale = False

def toggle_log_scale(event):
    global log_scale
    log_scale = not log_scale
    if log_scale:
        ax.set_yscale('log')
    else:
        ax.set_yscale('linear')
    plt.draw()

axtoggle = plt.axes([0.7, 0.05, 0.15, 0.075])
button = plt.Button(axtoggle, 'Toggle Log Scale')
button.on_clicked(toggle_log_scale)

ax.set_yscale('log')
ax.set_xlabel('x')
ax.set_ylabel('y')
ax.set_title('Real-time Plot')

# Set the y-axis range to 0-40000
ax.set_ylim(0, 40000)

plt.ion()  # Turn on interactive mode

while True:
    # Read values from the file and update the plot every five seconds
    xAxis, yAxis = process_file(filename)
    line.set_ydata(yAxis)
    plt.pause(5)  # Pause for five seconds

plt.ioff()  # Turn off interactive mode
plt.show()

