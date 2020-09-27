#include "Datas.h"
#include <string>

class AircraftBase
{

protected:
  enum class Scene
  {
    Waiting,
    ReadyToLaunch,
    InFlight,
    Landing
  };

  enum class Commands
  {
    None,
    ResetMbed,
    EscapePreparing,
    CheckSensors,
    ClosingServo
  };

  Datas datas;
  Scene scene = Scene::Waiting;

  bool recording = false;

public:
  // main loop
  void begin();

protected:
  AircraftBase() {}

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
  virtual void inFlight() = 0;

  // landing
  virtual void landing() = 0;

  // get datas
  virtual void getDatas() = 0;

  // write datas
  virtual void writeDatas() = 0;

  // on receive command
  virtual void onReceive() = 0;

  // check received command
  virtual Commands checkCommand(const std::string &recv) = 0;

  // start recording datas
  void beginRecord() { recording = true; }

  // end recording datas
  void endRecord() { recording = false; }
};