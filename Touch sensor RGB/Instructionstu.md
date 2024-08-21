#Touch Pad Oscillator Circuit with Raspberry Pi Control

## Overview

This circuit is an example of an oscillator that produces a square wave signal. The frequency of this signal changes when you touch a pad connected to the circuit. The signal is then fed into a Raspberry Pi running MicroPython, where the frequency is measured. Based on these measurements, the Raspberry Pi controls NeoPixel LEDs to change colors or perform other actions.

## Key Components

### Schmitt Trigger Inverter

- **Function**: Cleans up a signal, turning it into a sharp square wave.
- **Thresholds**:
  - **High Threshold (V_th+)**: The input voltage at which the output switches from low to high.
  - **Low Threshold (V_th-)**: The input voltage at which the output switches from high to low.

### Resistor (R) and Capacitor (C)

- **Function**: Together, they control how quickly the capacitor charges and discharges. This charging and discharging determines the frequency of the signal.

### Touch Pad

- **Function**: When you touch the pad, you add a small amount of extra capacitance to the circuit. This slows down the charging and discharging of the capacitor, lowering the frequency of the square wave.

### Raspberry Pi

- **Function**: Measures the frequency of the square wave signal using GPIO pins and uses this information to control NeoPixel LEDs.

## How the Circuit Works

### Oscillation Mechanism

1. **Charging**: The capacitor charges through the resistor, and the voltage across the capacitor increases.
2. **Thresholds**: When the voltage reaches a high threshold (V_th+), the Schmitt trigger inverter switches its output from low to high, causing the capacitor to discharge.
3. **Discharging**: The capacitor discharges until the voltage drops to a lower threshold (V_th-), at which point the Schmitt trigger switches the output back to low, and the capacitor starts charging again.
4. **Repetition**: This cycle repeats, creating a continuous square wave signal at the output.

### Waveforms on the Oscilloscope []

- **Sawtooth Wave (Bottom Waveform)**: Represents the voltage across the capacitor.
  - **Charging Phase**: The capacitor voltage rises as it charges.
  - **Discharging Phase**: The voltage suddenly drops when the capacitor discharges.
- **Square Wave (Top Waveform)**: Represents the output from the Schmitt trigger.
  - The square wave switches between high and low states based on the capacitor’s voltage reaching the high and low thresholds.

### Frequency Formula

The frequency of the square wave is given by:

\[
f = \frac{1}{2RC \cdot \ln\left(\frac{V_{th+}}{V_{th-}}\right)}
\]

Where:
- \(R\) is the resistance.
- \(C\) is the capacitance.
- The logarithm term relates to the Schmitt trigger’s thresholds.
