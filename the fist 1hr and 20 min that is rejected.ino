#include <MD_MAX72xx.h>

#define MAX_DEVICES 1 // Change to the number of devices you have
#define MAX_X (MAX_DEVICES * 8 - 1)
#define MAX_Y 7

#define CLK_PIN  13
#define DATA_PIN 11
#define CS_PIN   10

#define VERT_PIN A0
#define HORZ_PIN A1
#define SEL_PIN  2

#define POINT_BUZZER_PIN 3
#define EFFECT_BUZZER_PIN 4

MD_MAX72XX mx = MD_MAX72XX(MD_MAX72XX::FC16_HW, CS_PIN, MAX_DEVICES);

int x = 0;
int y = 0;
int score = 0;
bool gameRunning = true;

void setup() {
  mx.begin();
  mx.control(MD_MAX72XX::INTENSITY, MAX_INTENSITY / 2);
  mx.clear();

  pinMode(VERT_PIN, INPUT);
  pinMode(HORZ_PIN, INPUT);
  pinMode(SEL_PIN, INPUT_PULLUP);

  pinMode(POINT_BUZZER_PIN, OUTPUT);
  pinMode(EFFECT_BUZZER_PIN, OUTPUT);
}
