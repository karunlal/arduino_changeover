const int relayPinA = 2;         // Digital output pin for relay
const int relayPinB = 3;

double sensorValue1 = 0;
int val[100];
int max_v = 0;
double Veff = 0;

void setup() {
  Serial.begin(9600);
  pinMode(relayPinA, OUTPUT);
  pinMode(relayPinB, OUTPUT);
  digitalWrite(relayPinA, HIGH); // Initialize relays in OFF state
  digitalWrite(relayPinB, HIGH);
}

void loop() {
  float volt = voltage();
  if (volt > 200) {
    digitalWrite(relayPinA, LOW); // Turn ON relay A
    digitalWrite(relayPinB, HIGH);  // Turn OFF relay B
    Serial.println("Activating Relay A");
  } else {
    
    
    digitalWrite(relayPinB, LOW); // Turn ON relay B
    digitalWrite(relayPinA, HIGH);  // Turn OFF relay A
    Serial.println("Activating Relay B");
  }
}

float voltage() {
  for (int i = 0; i < 100; i++) {
    sensorValue1 = analogRead(A0);
    if (sensorValue1 > 511) {
      val[i] = sensorValue1;
    } else {
      val[i] = 0;
    }
    delay(1);
  }

  max_v = 0;

  for (int i = 0; i < 100; i++) {
    if (val[i] > max_v) {
      max_v = val[i];
    }
    val[i] = 0;
  }

  if (max_v != 0) {
    Veff = (((max_v / sqrt(2)) - 420.76) / -90.24) * -210.2 + 210.2;
  } else {
    Veff = 0;
  }

  Serial.print("Voltage: ");
  Serial.println(Veff);
  return Veff;
  delay (1000);

}
