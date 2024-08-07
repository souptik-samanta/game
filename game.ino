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

void loop() {
  if (digitalRead(SEL_PIN) == LOW) {
    gameRunning = false;
    showScore();
    while (digitalRead(SEL_PIN) == LOW) {} // Wait for button release
    return; // Exit loop to prevent further movement
  }

  if (gameRunning) {
    int horz = analogRead(HORZ_PIN);
    int vert = analogRead(VERT_PIN);

    if (vert < 300) {
      y = min(y + 1, MAX_Y);
      tone(EFFECT_BUZZER_PIN, 500, 100); // Play sound effect
    }
    if (vert > 700) {
      y = max(y - 1, 0);
      tone(EFFECT_BUZZER_PIN, 500, 100); // Play sound effect
    }
    if (horz > 700) {
      x = min(x + 1, MAX_X);
      tone(EFFECT_BUZZER_PIN, 500, 100); // Play sound effect
    }
    if (horz < 300) {
      x = max(x - 1, 0);
      tone(EFFECT_BUZZER_PIN, 500, 100); // Play sound effect
    }

    mx.clear();
    mx.setPoint(y, x, true);
    mx.update();

    delay(100); // Small delay to slow down the movement
  }
}

void showScore() {
  for (int i = 0; i < 5; i++) {
    mx.clear();
    mx.update();
    delay(500);
    displayScore(score);
    delay(500);
  }
}

void displayScore(int score) {
  mx.clear();
  if (score < 10) {
    mx.setChar(4, '0' + score);
  } else {
    int tens = score / 10;
    int ones = score % 10;
    mx.setChar(3, '0' + tens);
    mx.setChar(4, '0' + ones);
  }
  mx.update();
}
