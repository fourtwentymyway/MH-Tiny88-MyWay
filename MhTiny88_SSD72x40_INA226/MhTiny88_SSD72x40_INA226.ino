
#include <Tiny4kOLED.h>
#include <INA226_WE.h>
#define I2C_ADDRESS 0x40
#include <Wire.h>
uint8_t width = 64;
uint8_t height = 32;
/* There are several ways to create your INA226 object:
 * INA226_WE ina226 = INA226_WE()              -> uses I2C Address = 0x40
 * INA226_WE ina226 = INA226_WE(ICM20948_ADDR) -> define I2C_ADDRESS
 */
INA226_WE ina226 = INA226_WE(I2C_ADDRESS);

void setup() {

  oled.begin(72, 40, sizeof(tiny4koled_init_72x40br), tiny4koled_init_72x40br);
  oled.setFont(FONT6X8);
  oled.clear();
  oled.on();
  
  oled.setCursor(0,0);
  if(!ina226.init()){
     oled.print("INA226 not  connected!");
     while(1){}
  }
  else{
    oled.print("INA226  connected");
    delay(1000);
    oled.clear();
  }

  /* Set ADC Mode for Bus and ShuntVoltage
  * Mode *            * Res / Samples *       * Conversion Time *
  BIT_MODE_9        9 Bit Resolution             84 µs
  BIT_MODE_10       10 Bit Resolution            148 µs  
  BIT_MODE_11       11 Bit Resolution            276 µs
  BIT_MODE_12       12 Bit Resolution            532 µs  (DEFAULT)
  SAMPLE_MODE_2     Mean Value 2 samples         1.06 ms
  SAMPLE_MODE_4     Mean Value 4 samples         2.13 ms
  SAMPLE_MODE_8     Mean Value 8 samples         4.26 ms
  SAMPLE_MODE_16    Mean Value 16 samples        8.51 ms     
  SAMPLE_MODE_32    Mean Value 32 samples        17.02 ms
  SAMPLE_MODE_64    Mean Value 64 samples        34.05 ms
  SAMPLE_MODE_128   Mean Value 128 samples       68.10 ms
  */
  //ina226.setADCMode(SAMPLE_MODE_128); // choose mode and uncomment for change of default
  
  /* Set measure mode
  POWER_DOWN - INA226 switched off
  TRIGGERED  - measurement on demand
  ADC_OFF    - Analog/Digital Converter switched off
  CONTINUOUS  - Continuous measurements (DEFAULT)
  */
  // ina226.setMeasureMode(CONTINUOUS); // choose mode and uncomment for change of default
  
  /* Set PGain
  * Gain *  * Shunt Voltage Range *   * Max Current (if shunt is 0.1 ohms) *
   PG_40       40 mV                    0.4 A
   PG_80       80 mV                    0.8 A
   PG_160      160 mV                   1.6 A
   PG_320      320 mV                   3.2 A (DEFAULT)
  */
  // ina226.setPGain(PG_320); // choose gain and uncomment for change of default
  
  /* Set Bus Voltage Range
   BRNG_16   -> 16 V
   BRNG_32   -> 32 V (DEFAULT)
  */
  // ina226.setBusRange(BRNG_32); // choose range and uncomment for change of default

  /* If the current values delivered by the INA226 differ by a constant factor
     from values obtained with calibrated equipment you can define a correction factor.
     Correction factor = current delivered from calibrated equipment / current delivered by INA226
  */
  // ina226.setCorrectionFactor(0.98); // insert your correction factor if necessary
  
  /* If you experience a shunt voltage offset, that means you detect a shunt voltage which is not 
     zero, although the current should be zero, you can apply a correction. For this, uncomment the 
     following function and apply the offset you have detected.   
  */
  // ina226.setShuntVoltOffset_mV(0.5); // insert the shunt voltage (millivolts) you detect at zero current 
}

void loop() {
  float shuntVoltage_mV = 0.0;
  float loadVoltage_V = 0.0;
  float busVoltage_V = 0.0;
  float current_mA = 0.0;
  float power_mW = 0.0; 
  bool ina226_overflow = false;
  
  shuntVoltage_mV = ina226.getShuntVoltage_mV();
  busVoltage_V = ina226.getBusVoltage_V();
  current_mA = ina226.getCurrent_mA();
  power_mW = ina226.getBusPower();
  //loadVoltage_V  = busVoltage_V + (shuntVoltage_mV/1000);
  //ina226_overflow = ina226.getOverflow();

  oled.setCursor(0,0);
  oled.print("[mA]:");
  oled.print(current_mA);
  oled.clearToEOL();
  
  oled.setCursor(0,1); //10
  oled.print("[mW]:");
  oled.print(power_mW);
  oled.clearToEOL();
  
  oled.setCursor(0,2); 
  oled.print("[V]:");
  oled.print(busVoltage_V);
  oled.clearToEOL();
  
  oled.setCursor(0,3); 
  oled.print("[mV]:");
  oled.print(shuntVoltage_mV);
  oled.clearToEOL();
  
  delay(3000);
}