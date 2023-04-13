mport numpy as np
import matplotlib.pyplot as plt

# Define the Higgs potential function
def higgs_potential(phi):
    return (phi**2 - 1)**2

# Define the range of phi values
phi_values = np.linspace(-2, 2, 100)

# Calculate the Higgs potential for each phi value
potential_values = higgs_potential(phi_values)

# Plot the Higgs potential
fig, ax = plt.subplots()
ax.plot(phi_values, potential_values)
ax.set_xlabel(r'$\phi$')
ax.set_ylabel(r'$V(\phi)$')
ax.set_xticks([])
ax.set_yticks([])
ax.set_title('Spontaneously broken symmetry')
plt.show()
