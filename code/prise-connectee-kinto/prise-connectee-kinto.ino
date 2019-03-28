/* Prise connectée
 * 
 * Détournement d’une prise connectée Sonoff.
 * Munie d’un microcontrôleur de type ESP8266, cette prise peut
 * être reprogramméeà l’aide de l’IDE Arduino pour être pilotée en Wifi.
 * 
 * https://docs.humanlab.me/myhumankit/prise-connectee
 */

#include <ESP8266WiFi.h>
#include <WiFiManager.h>   //https://github.com/tzapu/WiFiManager

// Kinto library
#include <KintoForIoT.h>

#define SERVER "http://kinto.blink-studio.com/v1"
#define LOGIN  ""
#define PASS   ""

// led data object
Led led;
Led relay;

// button data object
Button button;

void setup() {
  // initializing the led
  led.begin(13, HIGH);
  relay.begin(12);

  // initializing the button
  button.begin(0, HIGH);

  // connecting the led to Kinto
  led.connect(SERVER, LOGIN, PASS, "led");
  relay.connect(SERVER, LOGIN, PASS, "relay");

  // connecting the button to Kinto
  button.connect(SERVER, LOGIN, PASS, "button");

  // connecting to a WiFi network
  WiFiManager wifiManager;
  wifiManager.autoConnect("sonoff");
}

void loop() {
  for (int i = 0; i < 100; i++) {
    // reading the button status
    button.read();

    // sending button status to Kinto only if
    // it has changed since last call of read()
    if (button.hasChanged()) {
      button.post();
    }

    // wait a little ...
    delay(10);
  }
  // retrieve led status from Kinto
  led.get();
  relay.get();
}
