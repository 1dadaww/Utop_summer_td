## Common Issues and Solutions

### 1.

Some people have encountered problems when using large current sensors, such as a 12V, 1.1A rated camera. They have asked if a higher current-rated fuse is needed.

**Solution and Suggestions:**

- A 2A fuse would not blow immediately at 3A current. 
- The battery and PCB would support 3A, but the connectors and wires might not. 
- The connectors may not be ideal for large power output, and it's essential to choose a suitable rated wire. 
- The jumper wires provided have a maximum current rating of 1A, which is not suitable for large current applications.

### 2.

Some people noticed an error in the instructions for current sensing. The initial instruction calculation was based on a 50mΩ shunt resistor.

**Solution and Suggestions:**

- Most of the instructions have been corrected, but one sentence needs editing:
  - Original: "For example, the case above with a differential gain of 10 and a 1.25V reference would give an output of 1.75V, which is a convenient voltage for measuring with an ADC on a 3.3V microcontroller."
  - Correction: The output should be 1.35V instead of 1.75V.

### 3. 

People have asked whether it is safe to change the code to adjust acceleration using the `.setAccelerationRad` function, and if there is a safety range.

**Solution and Suggestions:**

- Answer from the forum:"If you set acceleration too high there won't be damage, the motors just won't keep up and stutter."

### 4.
Asking about the extent to which it is permitted to modify the chassis, specifically whether it could be redesigned to give it a lower centre of mass.

**Solution and Suggestions:**

- Answer from the forum:
  "You'd need a good reason to modify the chassis instead of working on other things. A lower centre of mass does not automatically make balancing easier. It would make it possible to recover from a larger tilt angle, but it would also increase the resonant frequency of the robot, so you would need higher bandwidth for your sensing and control algorithm."

### 5.
Some people asking about teams that buying more advanced sensors using their own budget.

**Solution and Suggestions:**

- Answer from the forum:
  "The policy is that no-one can get an advantage by buying their own parts. For example, if someone uses an expensive sensor to get better results then they get the same mark as a group who bought a sensor with their project budget and got less good results."


