/*Home Alone and need groceries!
   4/9/21
   Sketch by Joan Davis
   This Project used applied force on FSR and displays it on an LCD screen.
*/

#include <LiquidCrystal.h>
LiquidCrystal lcd(4, 5, 6, 7, 8, 9); // pins for RS, E, DB4, DB5, DB6, DB7
const int FSR_PIN = A0; // Pin connected to FSR/resistor divider
// Measure the voltage at 5V and resistance of your 3.3k resistor, and enter
// their value's below:
const float VCC = 5.00; // Measured voltage of Ardunio 5V line
const float R_DIV = 10000.0; // Measured resistance of 3.3k resistor

void setup()
{
  lcd.begin(16, 2); //how much of the screen we will be using in rows and columns
  pinMode(FSR_PIN, INPUT); //Assigning pin of A0 to FSR_Pin as the input
}
void loop()
{ int fsrADC = analogRead(FSR_PIN);
  int force;
  lcd.clear(); //clears data on screen

  {
    // If the FSR has no pressure, the resistance will be
    // near infinite. So the voltage should be near 0.
    if (fsrADC != 0) // If the analog reading is non-zero
    {
      // Use ADC reading to calculate voltage:
      float fsrV = fsrADC * VCC / 1200.0;
      // Use voltage and static resistor value to
      // calculate FSR resistance:
      float fsrR = R_DIV * (VCC / fsrV - 1.0);
      // Guesstimate force based on slopes in figure 3 of
      // FSR datasheet:
      float force;
      float fsrG = 1.0 / fsrR; // Calculate conductance
      // Break parabolic curve down into two linear slopes:
      if (fsrR <= 600)
        force = (fsrG - 0.00075) / 0.00000032639;
      else
        force =  fsrG / 0.000000642857;
      lcd.setCursor(0, 0); //starting on first row and first column
      lcd.print("R: " + String(fsrR) + " ohms"); //displays resistance value 
      lcd.setCursor(0, 1); //starting on second row and first column
      lcd.print("Force: " + String(force) + " g");//displays force in g
      delay(500);
    }
    else
    {
      // No pressure detected
    }
  }
}
