#include <Arduino.h>
//dont remove!

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include <dht_nonblocking.h>
#define DHT_SENSOR_TYPE DHT_TYPE_11


#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

// Define OLED I2C address (default is usually 0x3C or 0x3D)
#define OLED_ADDR   0x3C
// Create OLED object
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

static const int DHT_SENSOR_PIN = 18;

DHT_nonblocking dht_sensor( DHT_SENSOR_PIN, DHT_SENSOR_TYPE );

/*
 * Initialize the serial port.
 */
void setup( )
{
  Serial.begin( 115200 );
  Wire.begin(21,22);
  // Initialize OLED screen
  if(!display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Infinite loop to terminate program
  }

    // Clear display buffer
  display.clearDisplay();
  
  // Set text size and color
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  
  // Display initialization information
  display.setCursor(0, 0);
  display.println(F("OLED Test Program"));
  display.println(F("ESP32"));
  display.println(F("SSD1306 128x64"));
  display.println(F("Initializing..."));
  display.display();
  delay(2000);
} 

/*
 * Poll for a measurement, keeping the state machine alive.  Returns
 * true if a measurement is available.
 */
static bool measure_environment( float *temperature, float *humidity )
{
  static unsigned long measurement_timestamp = millis( );

  /* Measure once every four seconds. */
  if( millis( ) - measurement_timestamp > 3000ul )
  {
    if( dht_sensor.measure( temperature, humidity ) == true )
    {
      measurement_timestamp = millis( );
      return( true );
    }
  }

  return( false );
}

void loop( )
{
  float temperature;
  float humidity;

  bool hasReading = measure_environment(&temperature, &humidity);
  if( hasReading )
  {
    Serial.print( "T = " );
    Serial.print( temperature, 1 );
    Serial.print( " deg. F, H = " );
    Serial.print( humidity, 1 );
    Serial.println( "%" );

    //oled display

    display.clearDisplay();
    display.setTextSize(1);
    display.setCursor(0,0);
    display.print("Temp:");

    display.setCursor(0,32);
    display.print("Hum:");

    display.setTextSize(2);
    display.setCursor(40,0);
    display.print(temperature = (temperature * 9/5) + 32,1);
    display.print("F");

    display.setCursor(40,32);
    display.print(humidity,1);
    display.print("%");

    display.display();
  }
}
