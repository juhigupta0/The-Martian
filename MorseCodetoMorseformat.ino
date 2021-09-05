/*
>> The present code belongs to the alternative decoding pipeline of Morse Code using LEDs
>> In this implementation, the message encrypted in Morse code is perceived in the output using LEDs
>> The encoded message conveyed using Red LED for dot and Green LED for dash
>> The LEDs turns on with respect to the entered Morse input by the user
*/
unsigned long signal_len,t1,t2;   // Time for which button is pressed
int inputPin = 5;                 // Input pin for push button
String code = "";                 // Stores morse code
int redLED=13;                    // LED for dot input
int greenLED=12;                  // LED for dash input

int unit_length = 200;            // Unit length for a dot

void setup() {
  Serial.begin(9600);
  pinMode(inputPin, INPUT_PULLUP); 
  pinMode(redLED,OUTPUT);
  pinMode(greenLED, OUTPUT);
}

void loop()
{
NextInput:

  while (digitalRead(inputPin) == HIGH) {
  yield();
  }

  t1 = millis();                            

  while (digitalRead(inputPin) == LOW) {
  yield();
  }

  t2 = millis();                            

  signal_len = t2 - t1;                     // Time for which button is pressed

  if (signal_len > 50)                      // To account for switch debouncing
  {
    code += readio();                       // Function to read dot or dash
  }

  while ((millis() - t2) < 1000)            // Decode the alphabet if the time between button is greater than 1sec
  {     
    if (digitalRead(inputPin) == LOW)
    {
      goto NextInput;
    }
  }
}
  
char readio()
{
  if (signal_len < (unit_length*3) && signal_len > 50)
  {
    digitalWrite(redLED, HIGH);
    Serial.print(".");
    delay(50);
    digitalWrite(redLED,LOW);
    return '.';                        //if button press less than 0.6sec, it is a dot
  }
  else if (signal_len > (unit_length*3))
  {
    digitalWrite(greenLED, HIGH);
    Serial.print("-");
    delay(100);
    digitalWrite(greenLED,LOW);
    return '-';                        //if button press more than 0.6sec, it is a dash
  }
}
