# Main
Library = ProjectSAM Organ Mystique - Large Organ # For which library algorithm is optimized
Type = 0 # Instrument type

# Instrument parameters
n_min = C2 # Lowest note
n_max = F6 # Highest note
t_min = 20 # Shortest note in ms
t_max = 0 # Longest melody withot pauses in ms (0 = no limit). Decreases with dynamics
poly = 100 # Maximum number of simultaneous voices
#leap_t_min = 1 # Shortest note after leap
#dying = 5 # Seconds to fade out at mf

# Controls
Volume_default = 100 # default 127 (direct CC volume, should not be changed by user)
CC_Name = 2: "Filter cutoff" # Decreasing this value will decrease higher frequencies
CC_Name = 3: "Filter resonance"
CC_Name = 4: "Attack"
CC_Name = 5: "Decay"
CC_Name = 6: "Sustain"
CC_Name = 8: "Release"

# Initial setup
InitCommand = "Filter cutoff: 127" # default 127
InitCommand = "Filter resonance: 0" # default 0
InitCommand = "Attack: 7" # default 7
InitCommand = "Decay: 0" # default 0
InitCommand = "Sustain: 127" # default 127
InitCommand = "Release: 21" # default 0
Pan = 50 # default 50 (maximum left, 50 - default position, 100 - maximum right)
Volume = 100 # default 100 (relative volume from 0 to 100)

# Lengroup adaptor
lengroup2 = 30 # Percent of grouping notes into groups of 2
lengroup3 = 30 # Percent of grouping notes into groups of 3
lengroup4 = 30 # Percent of grouping notes into groups of 4
lengroup_edt1 = 70 # delta to alter note ending time of all notes in group except for the last (ms)
lengroup_edt2 = -100 # delta to alter note ending time of last note in group (ms)

# Randomization
rand_pos = 8-8 # Randomize note starts-ends not greater than percent of note length 
rand_pos_max = 70-70 # Maximum shift in ms (start-end)
rnd_vel = 8 # Randomize note velocity not greater than this percent

# Delay adaptor
all_ahead = 70 # Time in ms to stretch sutain notes (not legato) back to cope with slow attack
