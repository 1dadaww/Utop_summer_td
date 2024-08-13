For the current sensoring task of the balancing robot, a few improvement can be made.

Firstly, the initial power PCB can be seen from the the picture below-[powerpcb](powerpcb.png). The track between Vb and the one motor driver share a the same track with part of the track between VM pin for current sensoring and the VB, the impedance of the track casue some voltage drop, which makes the detected voltage drop between the shunt resitor larger than the actual value. 

From estimation, and testing with constant supply, impedance of that part of the path is appromatly 0.003 Ohm,which cause around 1.1 mV of voltage drop when testing using a motor that drive 385mA of current at 15V. The values may varies slightly when using different stepper mottor settings and the temperature. 
