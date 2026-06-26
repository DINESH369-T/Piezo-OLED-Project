#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

int sensorPin = A0;
int buzzerPin = 8;
int buttonPin = 2;
int threshold = 150;
float voltageLimit = 1.0;
int count = 0;
bool pressed = false;
int page = 0;
float heldEnergy = 0;
float heldForce = 0;
float heldPressure = 0;
unsigned long lastHoldTime = 0;

// store last 10 readings above 1V
float lastReadings[10];
int readingIndex = 0;

int readPiezo() {
  long sum = 0;
  for (int i = 0; i < 10; i++) {
    sum += analogRead(sensorPin);
    delay(2);
  }
  return sum / 10;
}

void setup() {
  Serial.begin(9600);
  pinMode(buzzerPin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);

  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3D)) {
      while(1);
    }
  }
  display.clearDisplay();
  display.setTextColor(WHITE);
}

void loop() {
  int value = readPiezo();
  if (value < threshold) value = 0;

  if (value > threshold && !pressed) {
    count++;
    pressed = true;
    delay(200);
  }
  if (value == 0) pressed = false;

  float voltage = value * (5.0 / 1023.0);

  // buzzer logic
  bool buzzerOn = false;
  if (voltage > voltageLimit) {
    digitalWrite(buzzerPin, HIGH);
    buzzerOn = true;
  } else {
    digitalWrite(buzzerPin, LOW);
    buzzerOn = false;
  }

  // store readings above 1V
  if (voltage > 1.0) {
    lastReadings[readingIndex] = voltage;
    readingIndex = (readingIndex + 1) % 10;
  }

  // button cycles pages
  if (digitalRead(buttonPin) == LOW) {
    page++;
    if (page > 3) page = 0;
    delay(300);
  }

  // display
  display.clearDisplay();

  if (page == 0) {
    // Page 1: Piezo Energy + progress bar
    display.setTextSize(1);
    display.setCursor(0,0);
    display.println("Piezo Energy");

    display.setCursor(0,15);
    display.print("Count: ");
    display.println(count);

    display.setCursor(0,30);
    display.print("Volt: ");
    display.println(voltage);

    // progress bar (scale voltage to 0-100 pixels)
    int barLength = (int)(voltage * 20); // adjust scaling
    if (barLength > 100) barLength = 100;
    display.drawRect(0,50,100,10,WHITE);
    display.fillRect(0,50,barLength,10,WHITE);
  }
else if (page == 1) {
  // Page 2: Energy and Force/Pressure
  float energy = voltage * count; // demo formula
  float force = voltage * 10;     // demo constant k=10
  float pressure = force / 10;    // demo formula

  // Freeze all three values for 2 seconds
  if (voltage > 0) {
    heldEnergy = energy;
    heldForce = force;
    heldPressure = pressure;
    lastHoldTime = millis();
  }

  // After 2 seconds, reset to 0
  if (millis() - lastHoldTime > 2000) {
    heldEnergy = 0;
    heldForce = 0;
    heldPressure = 0;
  }

  display.setTextSize(1);
  display.setCursor(0,0);
  display.println("Energy & Force");

  display.setCursor(0,15);
  display.print("Energy: ");
  display.println(heldEnergy);

  display.setCursor(0,30);
  display.print("Force: ");
  display.println(heldForce);

  display.setCursor(0,45);
  display.print("Pressure: ");
  display.println(heldPressure);
}

  else if (page == 2) {
    // Page 3: Buzzer status
    display.setTextSize(2);
    display.setCursor(20,25);
    display.println(buzzerOn ? "BUZZER ON" : "BUZZER OFF");
  }
  else if (page == 3) {
    // Page 4: Last 10 readings above 1V
    display.setTextSize(1);
    display.setCursor(0,0);
    display.println("Last 10 Volt >1V");

    for (int i = 0; i < 5; i++) {
  display.setCursor(0, 12 + i*10);
  display.println(lastReadings[i]);
  display.setCursor(64, 12 + i*10);
  display.println(lastReadings[i+5]);
}
  }

  display.display();
  delay(100);
}