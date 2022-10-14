#include "HX711.h"

//Define Loop Counter
int loop_counter = 0;

//Define LED Pin 
const int LED = 47;

//Define Load Cell Pins 
const int DOUT = 3; 
const int CLK = 2; 

//Initialize Load Cell
HX711 load_cell; 

//Define Unit Variable
String unit = "lbf"; // "lbf" 

//Define Calibration Factor
int calibration_factor; 

//Define Offset Variable
float offset; 

//Define Sample Rate
const int sampleRate = 10; //20 for 50 samples/sec; 10 for 100 samples/sec
 
//Define Number of Raw Readings per Sample 
const int numRaws = 1; //!!Note!! play around with this val

//Create Arrays to Store Data 
float thrust_samples[100]; 
float times[100]; 

void setup() {
  
  //Set LED Pin 
  pinMode(LED, OUTPUT);

  calibration_factor = 6060;
  


  //Begin Serial Monitor
  Serial.begin(9600); 

  //Begin Load Cell
  load_cell.begin(DOUT, CLK);

  //Calibrate Load Cell w/ Calibration Factor 
  load_cell.set_scale(calibration_factor); 

  //Tare the Load Cell
  Serial.println("Tared the Load Cell!"); 
  load_cell.tare(); 

  //Delay 30 Seconds before collecting data 
  delay(10000); 

}

void loop() {
  
  //Sample data on first Loop
  if(loop_counter == 0){

    sample();
    
  }
  
  for (int i = 0; i < 100; i++){
    Serial.print(String(thrust_samples[i]) + ", ");
  }
  Serial.println();
  for (int i = 0; i < 100; i++){
    Serial.print(String(times[i]) + ", ");
  }
  Serial.println();
  Serial.println();

  loop_counter++;
}

void sample() {
  digitalWrite(LED, HIGH);
  //Collect Data
  for(int idx = 0; idx < 100; idx++){
    thrust_samples[idx] = load_cell.get_units(numRaws);
    times[idx] = millis();   
  }
  //Record Final Value
  offset = load_cell.get_units(numRaws);
  digitalWrite(LED, LOW);
}
