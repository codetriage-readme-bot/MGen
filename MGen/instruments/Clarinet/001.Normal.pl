include "..\include\SM Woodwinds.pl"

# Main
library = "Samplemodeling Clarinet 2.8.0" # For which library algorithm is optimized

# Instrument parameters
n_min = "C#3" # Lowest note
n_max = "A#6" # Highest note
t_min = 20 # Shortest note in ms
t_max = 8000 # Longest note without pauses in ms (0 = no limit). Decreases with dynamics
#leap_t_min = 100 # Shortest note after leap in ms

# Transition types
vel_harsh = 50 # Velocity equal or above this value triggers harsh sustain
vel_immediate = 38 # Velocity equal or above this value triggers immediate sustain
#vel_gliss = 33 # Velocity below this value triggers glissando transition
vel_normal = 11 # Velocity equal or above this value triggers normal sustain
vel_normal_minlen = 400 # Minimum note length (ms) that can have a normal or lower sustain
harsh_freq = 0 # Frequency of harsh sustain articulation in percent of all possible situations
