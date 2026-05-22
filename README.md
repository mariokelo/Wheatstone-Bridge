# Wheatstone Bridge Resistance Meter

An implementation of a Wheatstone bridge circuit that measures an
unknown resistance (Rx) using a calibrated potentiometer, with results
shown on a 128x32 OLED display and a balance indicator LED.

## How it works

A Wheatstone bridge works by balancing two voltage dividers against
each other. When the bridge is balanced (both midpoints at equal
voltage), the unknown resistance can be directly calculated from the
known resistors and the potentiometer setting.

The Arduino reads both bridge midpoint voltages via ADC, then:

1. Calculates the potentiometer's resistance from its measured voltage
2. Checks whether the bridge is balanced (|ΔV| < 20mV threshold)
3. If balanced, computes Rx using the bridge equation:

**Rx = (R1 × Rpot) / R2**

The LED lights up when balance is achieved, and the OLED shows either
the measured resistance or a "Bridge not balanced" prompt.

## Hardware

- Arduino (Uno or compatible)
- 2× 1kΩ fixed resistors (R1, R2)
- 1× potentiometer (used as the adjustable bridge arm)
- 1× unknown resistor (Rx) to measure
- LED + 220Ω resistor
- Adafruit SSD1306 128×32 OLED display (I2C)
- Connecting wires / breadboard

The potentiometer must be adjusted until the LED turns on, then read Rx from
the display.

## Wiring

| Component         | Arduino Pin |
|-------------------|-------------|
| Bridge midpoint A | A1          |
| Bridge midpoint B | A2          |
| Balance LED       | D10         |
| OLED SDA          | A4          |
| OLED SCL          | A5          |

## Balance indicator

| State               | LED  | OLED                  |
|---------------------|------|-----------------------|
| ΔV < 20 mV (balanced) | ON | Displays Rx in Ohms  |
| ΔV ≥ 20 mV          | OFF  | "Bridge not balanced" |

The 20 mV threshold can be adjusted in the code:
```cpp
if (abs(Adelta) < 0.02)  // change 0.02 to widen or narrow the window
```

## Serial output

With Serial Monitor open at **9600 baud**:

```
A0: 2.4980 V   A1: 2.4920 V   Rpot: 998.72 Ohm   Rx: 998.72 Ohm
```

## Dependencies

Must install via the Arduino Library Manager:

- [Adafruit SSD1306](https://github.com/adafruit/Adafruit_SSD1306)
- [Adafruit GFX](https://github.com/adafruit/Adafruit-GFX-Library)
