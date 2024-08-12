import machine
import utime
import neopixel

adc = machine.ADC(machine.Pin(27))

num_pixels = 2

np = neopixel.NeoPixel(machine.Pin(18), num_pixels)

ref_voltage = 3.3

initial_values = []

for _ in range(5):
    initial_values.append(adc.read_u16())
    utime.sleep(0.1)
#Read initial values, find an average and set it to 0 duty cycle
initial_average_analog_value = sum(initial_values) / len(initial_values)

initial_average_voltage = (initial_average_analog_value / 65535) * ref_voltage

voltage_drop_threshold = 0.01

initial_duty_cycle = 0

color = (255, 0, 0)


while True:
    
    analog_value = adc.read_u16()
    
    voltage = (analog_value / 65535) * ref_voltage
    print("Analog value:", analog_value, "Voltage:", voltage)
    
    thresholds_crossed = int((initial_average_voltage - voltage) / voltage_drop_threshold)
    duty_cycle = initial_duty_cycle + (thresholds_crossed * 0.1)
    duty_cycle = max(0, min(1, duty_cycle))
    
    adjusted_color = (int(color[0] * duty_cycle), int(color[1] * duty_cycle), int(color[2] * duty_cycle))
    
    for i in range(num_pixels):
        np[i] = adjusted_color
    
    np.write()
    utime.sleep(0.1)
