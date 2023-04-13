import matplotlib.pyplot as plt
import numpy as np

# Define the x range
x = np.linspace(-5, 5, 100)

# Define the y values for the parabola
y = x**2

# Create the plot
plt.plot(x, y)

# Add axis labels and title
#plt.xlabel('x')
#plt.ylabel('y')
plt.xlabel(r'$\phi$')
plt.ylabel(r'$V(\phi)$')
plt.xticks([])
plt.yticks([])
plt.title('Unbroken symmetry')

# Show the plot
plt.show()
