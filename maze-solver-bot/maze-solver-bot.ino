#define trigPin A0
#define echoPin 10
#define trigPin1 A1
#define echoPin1 11
#define trigPin2 A2 
#define echoPin2 12


#define in1 4
#define in2 5
#define in3 6
#define in4 7

#define ena 3
#define enb 9

#define RIGHT_distance distance2
#define LEFT_distance distance1
#define FRONT_distance distance


void setup(){

    Serial.begin(9600);
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
    pinMode(trigPin1, OUTPUT);
    pinMode(echoPin1, INPUT);
    pinMode(trigPin2, OUTPUT);
    pinMode(echoPin2, INPUT);


    pinMode(in1, OUTPUT);
    pinMode(in2, OUTPUT);
    pinMode(in3, OUTPUT);
    pinMode(in4, OUTPUT);
    pinMode(ena, OUTPUT);
    pinMode(enb, OUTPUT);

    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    digitalWrite(in3, LOW);
    digitalWrite(in4, LOW);

    analogWrite(ena, 255);
    analogWrite(enb, 255);

    delay(1000);
}

void FORWARD(int Speed){

  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);

  analogWrite(ena, 255);
  analogWrite(enb, 255);
}

void RIGHT(int Speed, int Time){
 
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);

  analogWrite(ena, Speed);
  analogWrite(enb, Speed);

  delay(Time);
}

void LEFT(int Speed, int Time){
 
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);

  analogWrite(ena, Speed);
  analogWrite(enb, Speed);

  delay(Time);
}

void loop() 
{
  
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin,LOW);
    long duration = pulseIn(echoPin, HIGH); 
    long distance = duration*0.017;

    delayMicroseconds(20);
    digitalWrite(trigPin1, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin1, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin1,LOW);
    long duration1 = pulseIn(echoPin1, HIGH); 
    long distance1 = duration1*0.017;

    delayMicroseconds(20);
    digitalWrite(trigPin2, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin2, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin2,LOW);
    long duration2 = pulseIn(echoPin2, HIGH); 
    long distance2 = duration2*0.017;

    Serial.println(FRONT_distance);
    Serial.println(LEFT_distance);
    Serial.println(RIGHT_distance);

    if(LEFT_distance > 10 && LEFT_distance < 15){
      //too far from left wall, move slightly towards the left
      Serial.println("too far");

      LEFT(255, 100);
      FORWARD(255);
      delay(100);
      RIGHT(255, 50);

    }
    if(LEFT_distance < 5){
      //too close to left wall, move slightly toward the right
      Serial.println("too close");

      RIGHT(255, 100);
      FORWARD(255);
      delay(100);
      LEFT(255, 50);

    }


    if(LEFT_distance < 15){
      if(FRONT_distance < 15){
        if(RIGHT_distance < 15){
          //deadend, so turn 180 degrees and continue forward
          Serial.println("U-turn");
          RIGHT(255, 1300);
          FORWARD(255);
        }
        else{
          //right turn as there are walls in front and on the left
          Serial.println("right turn");
          RIGHT(255, 615);
          FORWARD(255);
        }
      }

      else{
        //left wall present and nothing in front, right doesnt matter, move forward
        FORWARD(255);
      }

    }

    else{
      //left wall ended, turn left
      Serial.println("left turn");
      delay(330);
      LEFT(255, 615);
      FORWARD(255);
      delay(900);
    }
}