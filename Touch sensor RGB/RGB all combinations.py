import machine
import utime
import neopixel

# Initialize the pins
pins = [14,15,16,17]  
pins_objects = [machine.Pin(pin, machine.Pin.IN) for pin in pins]

num_pixels = 2 
np = neopixel.NeoPixel(machine.Pin(18), num_pixels)

measurement_interval = 20  # Measurement interval in milliseconds

edge_count = 0

# Adjustable threshold frequencies for each channel
threshold_frequencies = [7900, 7900, 8500, 8000]

colors = [
    (255, 0, 0),      # Red
    (0, 255, 0),      # Green
    (0, 0, 255),      # Blue
    (255, 255, 0),    # Yellow
    (255, 0, 255),    # Magenta
    (0, 255, 255),    # Cyan
    (255, 255, 255),  # White
    
]

# Boolean constants for each pad
pad1 = False
pad2 = False
pad3 = False
pad4 = False

def count_edges(pin):
    global edge_count
    edge_count += 1

# Attach interrupt to a single pin
def attach_interrupt(pin):
    pin.irq(trigger=machine.Pin.IRQ_RISING, handler=count_edges)

# Function to measure frequency for a given pin
def measure_frequency_for_pin(pin_object):
    global edge_count
    edge_count = 0

    attach_interrupt(pin_object)
    utime.sleep_ms(measurement_interval)  # Measure for the interval

    pin_object.irq(handler=None)  # Disable interrupt after measurement

    frequency = edge_count * (1000 / measurement_interval)
    return frequency

while True:
    for i, pin_object in enumerate(pins_objects):
        freq = measure_frequency_for_pin(pin_object)
        print(f"Frequency on pin {pins[i]}: {freq:.2f} Hz")

        # Check if the frequency is below the threshold and set the boolean constant
        if freq < threshold_frequencies[i]:
            if i == 0:
                pad1 = True
            elif i == 1:
                pad2 = True
            elif i == 2:
                pad3 = True
            elif i == 3:
                pad4 = True
        else:
            if i == 0:
                pad1 = False
            elif i == 1:
                pad2 = False
            elif i == 2:
                pad3 = False
            elif i == 3:
                pad4 = False

    if pad1 and pad2 and pad3 and pad4:
        np[0] = colors[6]
        np[1] = colors[6]

    elif pad1 and pad2 and pad3:       
        np[0] = colors[4]
        np[1] = colors[4]

    elif pad1 and pad2 and pad4:      
        np[0] = colors[5]
        np[1] = colors[5]

    elif pad1 and pad3 and pad4:   
        np[0] = colors[4]
        np[1] = colors[5]

    elif pad2 and pad3 and pad4:
        np[0] = colors[4]
        np[1] = colors[6]

    elif pad1 and pad2:
        np[0] = colors[0]
        np[1] = colors[1]

    elif pad1 and pad3:
        np[0] = colors[0]
        np[1] = colors[2]

    elif pad1 and pad4:
        np[0] = colors[0]
        np[1] = colors[3]

    elif pad2 and pad3:
        np[0] = colors[1]
        np[1] = colors[2]

    elif pad2 and pad4:
        np[0] = colors[1]
        np[1] = colors[3]

    elif pad3 and pad4:
        np[0] = colors[2]
        np[1] = colors[3]

    elif pad1:
        np[0] = colors[0]
        np[1] = colors[0]

    elif pad2:
        np[0] = colors[1]
        np[1] = colors[1]

    elif pad3:
        np[0] = colors[2]
        np[1] = colors[2]

    elif pad4:
        np[0] = colors[3]
        np[1] = colors[3]

    else:
        np[0] = (0, 0, 0)
        np[1] = (0, 0, 0)

    np.write()
    utime.sleep(0.1)
