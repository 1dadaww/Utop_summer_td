For the current sensoring task of the balancing robot, a few improvement can be made.

Firstly, the initial power PCB can be seen from the the picture below-[powerpcb](powerpcb.png). The track between Vb and the one motor driver share a the same track with part of the track between VM pin for current sensoring and the VB, the impedance of the track casue some voltage drop, which makes the detected voltage drop between the shunt resitor larger than the actual value. 

From estimation, and testing with constant supply, impedance of that part of the path is appromatly 0.003 Ohm,which cause around 1.1 mV of voltage drop when testing using a motor that drive 385mA of current at 15V. The values may varies slightly when using different stepper mottor settings and the temperature. 

To solve this problem, the first possible solution is to include the voltage drop while doing the calculation. The resistance of the path is 0.003 ohm , and that is only for 1 motor driver.

Secondly, difference shunt resistor values can be used. After testing with 3 different values of resistors, 10mohm, 50mOhm, and 100m ohm. The volage drop is relative constant. For testing with both motor driver, the percentage increase voltage difference are 16.5%, 3.3% and 1.4% respectively,(the total current for the drivers are difference in each testing condition possibly casued by the temperature of other components in the PCB ). 
Therefore a larger resistor could increase the accuracy,however for larger resistor value the voltage drop of the shunt resitor higher. 

###

Some current sensing circuit has potential risk of unstable performance and lead the current flowing from the current sesing circuit into the circuit. For example, the BJT current sensing circuit. the reason for that is because, when turn on the switch, there is a small current flowing from the Vout pin of the opamps, that potentially cause the BJT to become saturate,both junction forward biase, and that circuit is positive feedback circuit, that cause the output voltage continiously rising.  

To improve this spefic circuit, one solution is to using mosfet instead of BJT, because mosfet is a purely voltage drive circuit, and the current only flow in one direction of two junctions of the mosfet. And also, using a negative feedback circuit can avoid this problem, swap the V+ and V- input and using pnp trasnsitor instead.

To avoid this problem in general, can suggest people to use IM as power supply of the current sensing circuit for the motor. In that case the BJT only turn on when the second switch switch on.

However, directly there is only one IM pin on the power PCB, using one wire that connect from the pcb to the circuit may cause some voltage drop becasue the cable carry some current for the opamps supply. Testing with a jumper wire for the IM, the voltage drop across the wire is around 0.1 mV, after amplification, the difference may cause larger difference. Therefore, it may good to add an additional pin on the PCB board.

Other causes of unexpcted result. 
1. Grounding. If the opamp not coomon ground of the the input pints, the current will imediately flow into the PCB for any circuit including the resistor differential circuit.
2. Selecting correct opamp. The requiement for the opamps are 1.The supply voltage range need to cover at least 14V to 16.8V, which is the range of battery voltage that decay from 16.8v to around 13V. 2. The opamp for the motor current has to have rai to rail input since the supply voltage same as one of the input.And also it need to have differential coomon mode range acrross the supply range, for some opamps such as LT1637 labeled as rail to rail opamp but only have differential common mode range up to 15V. In testing, the ouput of the LT1637 model is lower than expected.3, it need to have low input offset voltage for accuracy.
### Thinngs to notice when using the microprocessors
The raspberry pi sometimes showing low voltage warning, after testing with power supply, the raspbery pi will show the low voltage warning very senstively when the voltage is less than 5V. That may casued by 1, the power source, some laptops have USB output less than 5V. 2, Using correct cable. using the AWG28 cable provided in the lab, the voltage drop is around 15mV,for the raspberry pi with no other sensors, which is very small.However, using other thin cable such as this cable below, the voltage drop is larger thatn 150mV which may effect the performance of some part the the board.

And also, for the ESp32 board, a diode is used to protect the board, it have a volage drop of 325mV. If using sensors run at 5V logic, need to check the spec to see if the supply voltage cover 4.6-4.7V.
In addition, both of the board run at 3.3V logic, when choosing compoent make sure it has 3.3V voltage output, other wise potential dividers needed.
