
// SETTING NECESSARY CONSTANTS FOR THERMISTOR READING
// resistance at 25 degrees C
#define THERMISTORNOMINAL 10000      
// temp. for nominal resistance (almost always 25 C)
#define TEMPERATURENOMINAL 25   
// The beta coefficient of the thermistor (usually 3000-4000)
#define BCOEFFICIENT 3950
// the value of the 'other' resistor
#define SERIESRESISTOR 10000    

// VARIABLES FOR READING DATA FROM ANALOG PINS
int RespiPadPin = 0;                 // Pressure Sensor SIGNAL WIRE connected to ANALOG PIN 0
int PulseSensorPurplePin = 1;        // Pulse Sensor PURPLE WIRE connected to ANALOG PIN 1
int LED13 = 10;                      //  The on-board Arduion LED or external LED


int Signal;                // holds the incoming raw data. Signal value can range from 0-1024
int RSignal;                // holds the incoming raw data. Signal value can range from 0-1024
int TempSignal;                // holds the incoming raw data. Signal value can range from 0-1024
int Threshold = 550;            // Determine which Signal to "count as a beat", and which to ingore. 
float average;

// The SetUp Function:
void setup() {
  pinMode(LED13,OUTPUT);         // pin that will blink to your heartbeat!
  Serial.begin(9600);         // Set's up Serial Communication at certain speed. 
}

// The Main Loop Function
void loop() {

  Signal = analogRead(PulseSensorPurplePin);  // Read the PulseSensor's value. 
                                              // Assign this value to the "Signal" variable.
  RSignal = analogRead(RespiPadPin);          // Read the Respiration Sensor's value. 
                                              // Assign this value to the "RSignal" variable.
  TempSignal = analogRead(2);                 // Read the Respiration Sensor's value. 
                                              // Assign this value to the "RSignal" variable.
  average = 1023 / TempSignal - 1;
  average = SERIESRESISTOR / average;
  float steinhart;
  steinhart = average / THERMISTORNOMINAL;     // (R/Ro)
  steinhart = log(steinhart);                  // ln(R/Ro)
  steinhart /= BCOEFFICIENT;                   // 1/B * ln(R/Ro)
  steinhart += 1.0 / (TEMPERATURENOMINAL + 273.15); // + (1/To)
  steinhart = 1.0 / steinhart;                 // Invert
  steinhart -= 273.15;                         // convert to C

   Serial.print(Signal);
   Serial.print("\t");
   Serial.print(TempSignal);
   Serial.print("\t");
   Serial.println(RSignal);

   if(Signal > Threshold){                          // If the signal is above "550", then "turn-on" Arduino's on-Board LED.  
     digitalWrite(LED13,HIGH);          
   } else {
     digitalWrite(LED13,LOW);                //  Else, the sigal must be below "550", so "turn-off" this LED.
   }

   if(RSignal < 450){                          // If the signal is above "550", then "turn-on" Arduino's on-Board LED.  
     digitalWrite(11,HIGH);          
   } else {
     digitalWrite(11,LOW);                //  Else, the sigal must be below "550", so "turn-off" this LED.
   }
   delay(10);   
}




