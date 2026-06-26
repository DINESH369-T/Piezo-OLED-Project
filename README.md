# Piezo-OLED-Project
---
## Project Goal
The main goal of this project is to build a **pressure/tap detection system** using piezoelectric discs , an Arduino, and an OLED display.  
It demonstrates how piezo sensors can detect taps or steps, how the energy can be stored in a capacitor, and how the data can be visualized in real time on an OLED screen.

---

## How It Works
- **Piezoelectric discs** generate voltage spikes when pressed, tapped, or stepped on.  
- These signals are rectified using a **DB107 bridge rectifier** to ensure a stable DC output.  
- The rectified energy is stored in a **capacitor**, which smooths the spikes and provides usable energy.  
- A **LED** connected to the capacitor glows briefly, showing the harvested energy.  
- The **Arduino** reads the piezo voltage and drives a **buzzer** when the threshold is exceeded.  
- An **OLED display** shows multiple pages of information, cycling with a button press.

---

## Hardware Used
- Arduino board (Uno/Nano)  
- Piezoelectric discs (wired in parallel under foam sheets)  
- **DB107 rectifier** → converts AC pulses from piezo into DC  
- **Capacitor (100µF–1000µF)** → stores piezo energy and smooths voltage  
- **LED** → glows when capacitor discharges, visual indicator of energy  
- OLED display (SSD1306, 128x64)  
- Buzzer  
- Push button for page navigation  
- Resistors and wires for stabilization  

---

## OLED Pages
The OLED display cycles through **four pages**:

1. **Piezo Energy + Progress Bar**  
   - Shows tap count, live voltage, and a bar graph.

2. **Energy, Force, Pressure**  
   - Displays calculated values (demo formulas).  
   - Freezes readings for 2 seconds after each tap.

3. **Buzzer Status**  
   - Shows whether the buzzer is ON or OFF depending on voltage threshold.

4. **Last 10 Voltage Readings (>1V)**  
   - Displays the last 10 voltage values above 1V.  
   - Organized in two columns for readability.

---

## Repository Structure
- `piezo_oled.ino` → Arduino sketch with OLED dashboard logic.  
- `README.md` → Project documentation.  
 
---

## Applications
- Step counter mats.  
- Pressure/tap detection pads.  
- Energy harvesting demos (piezo → rectifier → capacitor → LED).  
- Educational visualization of sensor signals.
