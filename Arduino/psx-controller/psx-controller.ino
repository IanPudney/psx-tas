#define UP 25
#define DOWN 27
#define LEFT 29
#define RIGHT 31
#define TRIANGLE 33
#define X 35
#define SQUARE 37
#define CIRCLE 39
#define L1 41
#define L2 43
#define R1 45
#define R2 47
#define SELECT 49
#define START 51
#define ANALOG_MODE 53

#define LED 13

void setup() {
  Serial.begin(2000000);
  pinMode(UP, OUTPUT);
  pinMode(DOWN, OUTPUT);
  pinMode(LEFT, OUTPUT);
  pinMode(RIGHT, OUTPUT);
  pinMode(TRIANGLE, OUTPUT);
  pinMode(X, OUTPUT);
  pinMode(SQUARE, OUTPUT);
  pinMode(CIRCLE, OUTPUT);
  pinMode(START, OUTPUT);
  pinMode(LED, OUTPUT);
  digitalWrite(UP, HIGH);
  digitalWrite(DOWN, HIGH);
  digitalWrite(LEFT, HIGH);
  digitalWrite(RIGHT, HIGH);
  digitalWrite(TRIANGLE, HIGH);
  digitalWrite(X, HIGH);
  digitalWrite(SQUARE, HIGH);
  digitalWrite(CIRCLE, HIGH);
  digitalWrite(START, HIGH);
  digitalWrite(LED, LOW);
}

void loop() {
  if (Serial.available() > 0) {
    digitalWrite(LED, HIGH);
    byte c = Serial.read();
    if (c == 'u') {
      digitalWrite(UP, LOW);
    } else if (c == 'd') {
      digitalWrite(DOWN, LOW);
    } else if (c == 'l') {
      digitalWrite(LEFT, LOW);
    } else if (c == 'r') {
      digitalWrite(RIGHT, LOW);
    } else if (c == 't') {
      digitalWrite(TRIANGLE, LOW);
    } else if (c == 'x') {
      digitalWrite(X, LOW);
    } else if (c == 's') {
      digitalWrite(SQUARE, LOW);
    } else if (c == 'c') {
      digitalWrite(CIRCLE, LOW);
    } else if (c == '+') {
      digitalWrite(START, LOW);
    } else if (c == '0' || c == '\0') {
      digitalWrite(UP, HIGH);
      digitalWrite(DOWN, HIGH);
      digitalWrite(LEFT, HIGH);
      digitalWrite(RIGHT, HIGH);
      digitalWrite(TRIANGLE, HIGH);
      digitalWrite(X, HIGH);
      digitalWrite(SQUARE, HIGH);
      digitalWrite(CIRCLE, HIGH);
      digitalWrite(START, HIGH);
      digitalWrite(LED, LOW);
    } else {
      Serial.println("Unknown command");
    }
    Serial.println("0");
  }
}
