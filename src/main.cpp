#include "../lib/ToFSensor/ToFSensor.hpp"
#include "../lib/Motors/Motors.hpp"

// TB6612FNG Motor Drivers
#define IN4 4
#define IN3 3
#define IN2 7
#define IN1 8
#define ENA 5
#define ENB 6
#define SPEED 150

Motors motors(IN1, IN2, IN4, IN3, ENA, ENB);

// VL53L0X ToF Sensors
#define LOX1_ADDRESS 0x30
#define LOX2_ADDRESS 0x31

#define SHT_LOX1 A2
#define SHT_LOX2 A3

ToFSensor sensor1(SHT_LOX1);
ToFSensor sensor2(SHT_LOX2);

// TRP-105F Sensors
#define IR1_THRESHOLD 855
#define IR2_THRESHOLD 855

// Dip Switch & Push Button
#define BIT0_PIN 9 // LSB
#define BIT1_PIN 10
#define BIT2_PIN 11 // MSB
#define START_BUTTON 12

void executeStrategy(int strategy, int ir1, int ir2, int distance1, int distance2, int diff);

void setup()
{
  Serial.begin(115200);

  pinMode(BIT0_PIN, INPUT_PULLUP);
  pinMode(BIT1_PIN, INPUT_PULLUP);
  pinMode(BIT2_PIN, INPUT_PULLUP);
  pinMode(START_BUTTON, INPUT_PULLUP);
  pinMode(A1, OUTPUT);
  pinMode(A6, INPUT);
  pinMode(A7, INPUT);
  digitalWrite(A1, HIGH);

  motors.begin();

  Serial.println(("Initializing ToF Sensors..."));

  if (!sensor1.begin(LOX1_ADDRESS))
  {
    Serial.println(F("Failed to initialize Sensor 1"));
    while (1)
      ;
  }

  if (!sensor2.begin(LOX2_ADDRESS))
  {
    Serial.println(F("Failed to initialize Sensor 2"));
    while (1)
      ;
  }
}

void loop()
{
  bool start_button = digitalRead(START_BUTTON);

  while (start_button == LOW)
  {
    int bit0 = !digitalRead(BIT0_PIN);
    int bit1 = !digitalRead(BIT1_PIN);
    int bit2 = !digitalRead(BIT2_PIN);

    int strategy = bit2 << 2 | bit1 << 1 | bit0;

    int ir1 = analogRead(A6);
    int ir2 = analogRead(A7);
    int distance1 = sensor1.readDistance();
    int distance2 = sensor2.readDistance();
    delay(10);

    int diff = distance1 - distance2;

    Serial.print("Distance1: ");
    Serial.print(distance1);
    Serial.print(" Distance2: ");
    Serial.println(distance2);

    executeStrategy(strategy, ir1, ir2, distance1, distance2, diff);
  }
}

void executeStrategy(int strategy, int ir1, int ir2, int distance1, int distance2, int diff)
{
  static bool executed = false;

  // if (distance1 < 150 || distance2 < 250)
  // {
  //   motors.forward(SPEED * 0.6);
  //   return;
  // }

  switch (strategy)
  {
  case 0: // Default
    if (ir1 < IR1_THRESHOLD || ir2 < IR2_THRESHOLD)
    {
      motors.forward(SPEED * 0.1);
    }
    else
    {
      motors.backward(SPEED * .4);
      delay(800);
      motors.right(SPEED * .8);
      delay(300);
    }
    break;

  case 1: // Bait and Switch BETA
    if (!executed)
    {
      motors.right(SPEED);
      delay(500);
      motors.left(SPEED);
      delay(500);
      executed = true;
    }

    if (ir1 < IR1_THRESHOLD || ir2 < IR2_THRESHOLD)
    {
      motors.forward(SPEED * 0.1);
    }
    else
    {
      motors.backward(SPEED * .4);
      delay(1000);
      motors.right(SPEED);
      delay(500);
    }
    break;

  case 2: // WOODPECKER BETA
    if (!executed)
    {
      motors.forward(SPEED);
      delay(250);
      motors.backward(SPEED * 0.1);
      delay(150);
      motors.forward(SPEED);
      delay(250);
      motors.backward(SPEED * 0.1);
      delay(150);
      motors.forward(SPEED);
      delay(250);
      motors.backward(SPEED * 0.1);
      delay(150);
      executed = true;
    }

    if (ir1 < IR1_THRESHOLD || ir2 < IR2_THRESHOLD)
    {
      motors.forward(SPEED * 0.1);
    }
    else
    {
      motors.backward(SPEED * .4);
      delay(1000);
      motors.right(SPEED);
      delay(500);
    }

    break;

    // case 3: // SEARCH N DESTROY BETA
    //   if (!executed)
    //   {
    //     motors.right(SPEED * 0.5);
    //     delay(3000);
    //     executed = true;
    //   }

    //   if (ir1 < IR1_THRESHOLD || ir2 < IR2_THRESHOLD)
    //   {
    //     motors.forward(SPEED * 0.1);
    //   }
    //   else
    //   {
    //     motors.backward(SPEED * .4);
    //     delay(1000);
    //     motors.right(SPEED);
    //     delay(1000);
    //   }
    //   break;

  case 4: // CALM BEFORE THE STORM
    if (!executed)
    {
      motors.forward(SPEED * 0.1);
      delay(1500);
      executed = true;
    }

    if (ir1 < IR1_THRESHOLD || ir2 < IR2_THRESHOLD)
    {
      motors.forward(SPEED * 0.1);
    }
    else
    {
      motors.backward(SPEED * .4);
      delay(1000);
      motors.right(SPEED);
      delay(500);
    }
    break;

  case 5: // HESIVON
    if (!executed)
    {
      delay(1500);
      motors.backward(SPEED * 0.3);
      delay(450);
      executed = true;
    }

    if (ir1 < IR1_THRESHOLD || ir2 < IR2_THRESHOLD)
    {
      motors.forward(SPEED * 0.1);
    }
    else
    {
      motors.backward(SPEED * .4);
      delay(1000);
      motors.right(SPEED);
      delay(500);
    }
    break;

  case 6: // REVERSE BAIT AND SWITCH
    if (!executed)
    {
      motors.left(SPEED);
      delay(500);
      motors.right(SPEED);
      delay(500);
      executed = true;
    }

    if (ir1 < IR1_THRESHOLD || ir2 < IR2_THRESHOLD)
    {
      motors.forward(SPEED * 0.1);
    }
    else
    {
      motors.backward(SPEED * .4);
      delay(1000);
      motors.right(SPEED);
      delay(500);
    }
    break;

  case 7: // CATAPULT
    if (!executed)
    {
      motors.forward(SPEED);
      delay(250);
      motors.stop();
      executed = true;
    }

    if (ir1 < IR1_THRESHOLD || ir2 < IR2_THRESHOLD)
    {
      motors.forward(SPEED * 0.1);
    }
    else
    {
      motors.backward(SPEED * .4);
      delay(1000);
      motors.right(SPEED);
      delay(500);
    }
    break;

  default:
    motors.stop();
    break;
  }
}
