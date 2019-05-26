#include <Arduino.h>

//#define SERIAL_DEBUG_DISABLED

#define USE_LIB_WEBSOCKET true

#include "sensesp_app.h"
#include "devices/onewire_temperature.h"
#include "transforms/passthrough.h"
#include "wiring_helpers.h"

ReactESP app([] () {
  #ifndef SERIAL_DEBUG_DISABLED
  Serial.begin(115200);

  // A small arbitrary delay is required to let the
  // serial port catch up

  delay(100);
  Debug.setSerialEnabled(true);
  #endif

  sensesp_app = new SensESPApp();

  DallasTemperatureSensors* dts = new DallasTemperatureSensors(D5);

  (new OneWireTemperature(dts, "/devices/temperature"))
    -> connectTo(new Passthrough<float>("propulsion.0.temperature"));

  (new OneWireTemperature(dts, "/devices/coolantTemperature"))
    -> connectTo(new Passthrough<float>("propulsion.0.coolantTemperature"));

  (new OneWireTemperature(dts, "/devices/exhaustTemperature"))
    ->connectTo(new Passthrough<float>("propulsion.0.exhaustTemperature"));

  sensesp_app->enable();
});
