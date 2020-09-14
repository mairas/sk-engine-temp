#include <Arduino.h>

//#define SERIAL_DEBUG_DISABLED

#define USE_LIB_WEBSOCKET true

#include "sensesp_app.h"
#include "sensors/onewire_temperature.h"
#include "signalk/signalk_output.h"
#include "wiring_helpers.h"

ReactESP app([] () {
  #ifndef SERIAL_DEBUG_DISABLED
  Serial.begin(115200);

  // A small arbitrary delay is required to let the
  // serial port catch up

  delay(100);
  Debug.setSerialEnabled(true);
  #endif

  sensesp_app = new SensESPApp("engine-temp");

  DallasTemperatureSensors* dts = new DallasTemperatureSensors(D5);

  (new OneWireTemperature(dts, 1000, "/devices/temperature"))
    -> connectTo(new SKOutput<float>("propulsion.main.temperature", "/sensors/temperature"));

  (new OneWireTemperature(dts, 1000, "/devices/coolantTemperature"))
    -> connectTo(new SKOutput<float>("propulsion.main.coolantTemperature", "/sensors/coolantTemperature"));

  (new OneWireTemperature(dts, 1000, "/devices/exhaustTemperature"))
    ->connectTo(new SKOutput<float>("propulsion.main.exhaustTemperature", "/sensors/exhaustTemperature"));

  sensesp_app->enable();
});
