int S=16;


void setup() {
  // put your setup code here, to run once:
pinMode(S, OUTPUT);
Serial.begin(9600);
Serial.println("Hello.....Initiaized");

}

void loop() {
  // put your main code here, to run repeatedly:
digitalWrite(S, 1);
Serial.print("ON");
delay(5000);
digitalWrite(S,0);
Serial.print("OFF");
delay(5000);
}
