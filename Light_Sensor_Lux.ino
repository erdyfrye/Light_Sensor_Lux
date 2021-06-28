#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#define LDR_PIN             0
#define MAX_ADC_READING     1023
#define ADC_REF_VOLTAGE     5.0
#define REF_RESISTANCE      10000
#define LUX_CALC_SCALAR     123235178.3654270
#define LUX_CALC_EXPONENT   -1.604568157
LiquidCrystal_I2C lcd(0x3F,16,2);
void setup()
{

  lcd.backlight();
  Serial.begin(9600);
  lcd.setCursor(0,0);
  lcd.print("LuxMeter");
  lcd.setCursor(0,1);
  lcd.print("RTelleng'14");
  delay(2000);
  lcd.clear();
}
void loop()
{
  int ldrRawData;
  float resistorVoltage, ldrVoltage;
  float ldrResistance;
  float ldrLux;
  ldrRawData = analogRead(LDR_PIN);
  resistorVoltage = (float)ldrRawData / MAX_ADC_READING * ADC_REF_VOLTAGE;
  ldrVoltage = ADC_REF_VOLTAGE - resistorVoltage;
  ldrResistance = ldrVoltage/resistorVoltage * REF_RESISTANCE;
  ldrLux = LUX_CALC_SCALAR * pow(ldrResistance, LUX_CALC_EXPONENT);
  Serial.print("LDR Illuminance :"); Serial.print(ldrLux); Serial.println("lux");
  lcd.setCursor(0,1);
  lcd.print("kondisi :");
  lcd.setCursor(0,0);
  lcd.print(ldrLux);
  lcd.setCursor(7,0);
  lcd.print("Lux");
  if (ldrLux < 10){
    lcd.setCursor(9,1);
    lcd.print("Gelap");
  } else if (ldrLux < 30) {
    lcd.setCursor(9,1);
    lcd.print("Redup");
  } else if (ldrLux < 100) {
    lcd.setCursor(9,1);
    lcd.print("Sedang");
  } else if (ldrLux < 300){
    lcd.setCursor(9,1);
    lcd.print("Terang");
  } else if (ldrLux >= 500)
  {
    lcd.setCursor(9,1);
    lcd.print ("Tera++");
    }
    delay(200);
}
