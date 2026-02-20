/**
 * @file main.cpp
 * @brief Embedded Temperature and Humidity Monitor using a DHT11 sensor.
 * @details
 * This sketch reads temperature and relative humidity from a DHT11 sensor
 * and prints human-readable measurements to the serial monitor. The code
 * performs a read every 2000 ms (required by the DHT11 timing) and prints
 * an error message when the library returns NaN for a measurement.
 *
 * Hardware assumptions:
 *  - A DHT11 data line is connected to the Arduino digital pin defined by
 *    `DHTPIN`.
 *  - The DHT library (https://github.com/adafruit/DHT-sensor-library or
 *    equivalent) is available to the build environment.
 *
 * Usage:
 *  - Open the Serial Monitor at 9600 baud to observe measurements.
 *
 * @author Akshat Lakhotiya
 * @date 2026-02-20
 */

#include <Arduino.h>
#include <DHT.h>

/** @brief Digital pin connected to the DHT data line. */
#define DHTPIN 2

/** @brief Type/model of the DHT sensor in use. */
#define DHTTYPE DHT11

/**
 * @brief DHT sensor instance used to read humidity and temperature.
 * @details Constructed with the pin and sensor type defined above. Use
 *          the methods readHumidity() and readTemperature() to obtain
 *          measurements. Returned temperature is in degrees Celsius and
 *          humidity is in percent (%RH) as provided by the DHT library.
 * @see DHT
 */
DHT dht(DHTPIN, DHTTYPE);

/**
 * @brief Arduino setup function.
 * @details Initializes serial communication at 9600 baud and starts the
 *          DHT sensor. Prints a startup confirmation message to the
 *          serial monitor.
 * @return void
 */
void setup() {
    Serial.begin(9600);
    dht.begin();
    Serial.println("DHT11 OK");
}

/**
 * @brief Main Arduino loop: read sensor and print values.
 * @details
 * Reads humidity and temperature (Celsius) from the DHT sensor. The code
 * checks for invalid readings (NaN) which indicate a failed read and prints
 * an error message before delaying 2000 ms and trying again. On success the
 * measurements are printed in a single line with units.
 *
 * Timing and failure modes:
 *  - DHT11 requires about 2 seconds between reads; the sketch delays 2000
 *    ms between iterations to satisfy that requirement.
 *  - The DHT library returns NaN when a read fails (CRC, timing or wiring
 *    issues); this is handled explicitly by detecting isnan() and returning
 *    early to the next loop iteration.
 *
 * @note This function never returns; it's the primary runtime loop for the
 *       Arduino sketch.
 * @see DHT::readHumidity(), DHT::readTemperature()
 * @return void
 */
void loop() {
    float humidity = dht.readHumidity();
    float temperature = dht.readTemperature();
    if (isnan(humidity) || isnan(temperature)) {
        Serial.println("Humidity or temperature read error");
        delay(2000);
        return;
    }
    Serial.print("Humidity: ");
    Serial.print(humidity);
    Serial.print(" %\t");
    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.println(" *C");
    delay(2000);


}
