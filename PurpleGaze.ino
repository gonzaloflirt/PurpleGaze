#include <Bounce2.h>

#define CHANNEL 13
#define NUM_CONTROLS 8

struct Control {
  byte in;
  byte out;
  byte note;
  byte value = LOW;
  Bounce bounce = Bounce();

  void setup()
  {
    bounce.attach(in, INPUT_PULLUP);
    bounce.interval(25);
    pinMode(out, OUTPUT);
    digitalWrite(out, LOW);
  }

  void read() {
    bounce.update();
    if (bounce.fell()) {
      value = !value;
      digitalWrite(out, value);
      usbMIDI.sendControlChange(note, value == LOW ? 0 : 127, CHANNEL);
    }
  }

  void update(byte v)
  {
    value = v == 0 ? LOW : HIGH;
    digitalWrite(out, value);
  }
};

Control CONTROLS[NUM_CONTROLS] {{17, 16, 0}, {15, 14, 1}, {6, 7, 2}, {8, 9, 3}, {3, 2, 4}, {5, 4, 5}, {20, 21, 6}, {18, 19, 7}};

void controlChange(byte channel, byte control, byte value)
{
  for (int i = 0; i < NUM_CONTROLS; ++i)
  {
    if (control == CONTROLS[i].note && channel == CHANNEL)
    {
      CONTROLS[i].update(value);
    }
  }
}

void readIns()
{
  for (int i = 0; i < NUM_CONTROLS; ++i)
  {
    CONTROLS[i].read();
  }
}

void setup()
{
  for (int i = 0; i < NUM_CONTROLS; ++i)
  {
    CONTROLS[i].setup();
  }
  usbMIDI.setHandleControlChange(controlChange);
}

void loop()
{
  usbMIDI.read();
  readIns();
}
