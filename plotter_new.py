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
    E = 1.6617
    xAxis = [i * (E * 1.2 / 1024) for i in range(1024)]

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

# Set y-axis scale to logarithmic
ax.set_yscale('log')

ax.set_xlabel('x')
ax.set_ylabel('y')
ax.set_title('Plot')

plt.show(block=True)

