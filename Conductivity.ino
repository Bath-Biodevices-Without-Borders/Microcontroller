// Initialise Variables
int Cond_Pin1 = A1; 
int Cond_Temp_Pin1 = A2;
int Cond_Temp_Pin2 = A3;
int Cond_Pin2 = A4;

float Cond_Voltage1;                  // A1 - Output voltage 1.
float Cond_Current1;                  // A1 - Output current 1.
float Cond_Temp1;                     // A2 - Temperature 1.
float Cond_Temp2;                     // A3 - Temperature 2.
float Cond_Voltage2;                  // A4 - Output voltage 2.
float Cond_Current2;                  // A4 - Output current 2.

float Avg_Temp;                       // Average Temperature of the solution.
float Avg_Voltage;                    // Average Voltage.
float Avg_Current;                    // Average Current.
float Conductance;                    // Conductance of the solution.
float Conductivity;                   // Electrical Conductivity of the solution.

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(Cond_Pin1,INPUT);           // A1 - Output current 1.
  pinMode(Cond_Temp_Pin1,INPUT);      // A2 - Temperature 1.
  pinMode(Cond_Temp_Pin2,INPUT);      // A3 - Temperature 2.
  pinMode(Cond_Pin2,INPUT);           // A4 - Output current 2.
}

void loop() {
  // put your main code here, to run repeatedly:
  // Set all variables to zero.
  Cond_Voltage1 = 0;                  
  Cond_Temp1 = 0;
  Cond_Temp2 = 0;
  Cond_Voltage2 = 0;

  // Read values on input pins.
  Cond_Voltage1 += ((float)analogRead(Cond_Pin1)/1023)*5;
  Cond_Temp1 += ((float)analogRead(Cond_Temp_Pin1)/1023)*5;
  Cond_Temp2 += ((float)analogRead(Cond_Temp_Pin2)/1023)*5;
  Cond_Voltage2 += ((float)analogRead(Cond_Pin2)/1023)*5;

  // Calculate current and average variables.
  Cond_Current1 = (float)(Cond_Voltage1/1000);  // 1000 = Resistance (Ohms).
  Cond_Current2 = (float)(Cond_Voltage2/1000);
  Avg_Temp = (float)(Cond_Temp1 + Cond_Temp2)/2;
  Avg_Voltage = (float)(Cond_Voltage1 + Cond_Voltage2)/2;
  Avg_Current = (float)((Cond_Current1 + Cond_Current2)/2);

  // Calculate conductance and conductivity.
  Conductance = (float)(1/(Avg_Voltage/Avg_Current));
  Conductivity = (float)(Conductance*(Length/(Length + (Conductance*0.4) + (Avg_Temp - 25))));    // Define length.

  Serial.println("Conductivity");
  Serial.println(Conductivity);
}