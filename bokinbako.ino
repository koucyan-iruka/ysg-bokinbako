// LED bokinbako V3
#include <Servo.h>
Servo servo;
int coin = 0;  
int TRIG = 5;
int ECHO = 2;

double duration = 0;
double distance = 0;
double speed_of_sound = 331.5 + 0.6 * 25; // 25℃の気温の想定


void setup() {
  // initialize the LED pin as an output:
  Serial.begin( 9600 );
  pinMode(5, INPUT); //sensor
  pinMode(4, OUTPUT);//buzzer
  pinMode(3, OUTPUT);//relay
  pinMode(11,OUTPUT);//servo
  pinMode(ECHO, INPUT );
  pinMode(TRIG, OUTPUT );
  digitalWrite(3,HIGH);
  servo.attach(11);
  servo.write(90);
  
}

void loop() {
  // read the state of the pushbutton value:
  digitalWrite(TRIG, LOW); 
  delayMicroseconds(2); 
  digitalWrite( TRIG, HIGH );
  delayMicroseconds( 10 ); 
  digitalWrite( TRIG, LOW );
  duration = pulseIn( ECHO, HIGH ); // 往復にかかった時間が返却される[マイクロ秒]

  if (duration > 0) {
    duration = duration / 2; // 往路にかかった時間
    distance = duration * speed_of_sound * 100 / 1000000;
    Serial.print("Distance:");
    Serial.print(distance);
    Serial.println(" cm");
    delay(10);
  }

  if (distance < 6.5) {
    // turn LED on:
    Serial.println("Thanks!");
    tone(4,523.251);
    delay(100);
    tone(4,659.255);
    delay(100);
    tone(4,1046.502);
    delay(300);
    noTone(4);
    digitalWrite(3, LOW);
    servo.write(70);
    delay(15500);
    digitalWrite(3, HIGH);
    servo.write(90);
    Serial.println("See you again :)");
    
  } else {
    // turn LED off:
    digitalWrite(3, HIGH);
  }
}
