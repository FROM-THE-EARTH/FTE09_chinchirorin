#include "Datas.h"
#include <chrono>
#include <string>


class AircraftBase {

protected:
  enum class Scene { Waiting, ReadyToLaunch, InFlight, Landing };

  enum class Commands {
    None,
    ResetMbed,
    EscapePreparing,
    CheckSensors,
    ClosingServo
  };

  const float launchThreshold;
  const float landingTime;
  const float basePressure;

  Datas datas;
  Scene scene = Scene::Waiting;

  bool recording = false;

public:
  // main loop
  void begin();

protected:
  AircraftBase(float launchThreshold, float landingTime, float basePressure)
      : launchThreshold(launchThreshold), landingTime(landingTime),
        basePressure(basePressure) {}

  // whether to show debug
  virtual void setDebugMode(bool mode) = 0;

  // initialize modules
  virtual bool initialize() = 0;

  // is all modules available
  virtual bool isReady(bool showDetail = false) = 0;

  // end processing
  virtual void end() = 0;

  // wait for preparing
  virtual void waiting() = 0;

  // wait for launch
  virtual void waitingLaunch() = 0;

  // in flight
  virtual bool detachAircraft() = 0;
  virtual bool openParachute() = 0;
  virtual void inFlight() = 0;

  // landing
  virtual void landing() = 0;

  // get datas
  virtual void getDatas() = 0;

  // write datas
  virtual void writeDatas() = 0;

  // Receiver
  virtual void onReceive() = 0;
  virtual Commands checkCommand(std::string recv) = 0;

  void beginRecord() { recording = true; }

  void endRecord() { recording = false; }
};