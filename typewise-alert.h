#pragma once

typedef enum {
  PASSIVE_COOLING,
  HI_ACTIVE_COOLING,
  MED_ACTIVE_COOLING
} CoolingType;

typedef enum {
  TOO_LOW,
  TOO_HIGH,
  NORMAL,
  UNKNOWN_BREACH
} BreachType;

BreachType inferBreach(double value, double lowerLimit, double upperLimit);
BreachType classifyTemperatureBreach(CoolingType coolingType, double temperatureInC);

typedef enum {
  TO_CONTROLLER,
  TO_EMAIL
} AlertTarget;

typedef struct {
  CoolingType coolingType;
  char brand[48];
} BatteryCharacter;

typedef enum
{
  ALERT_FAILURE,
  ALERT_SUCCESS,
  UNKNOWN_BREACH_ALERT_FAILURE
}AlertStatus;

void sendToController(BreachType BreachTypeData);
void sendToEmail(BreachType BreachTypeData);

AlertStatus classifyBreachAndAlert(AlertTarget alertTarget, BatteryCharacter BatteryAttribute, double temperatureInC);
AlertStatus checkAndAlert(AlertTarget alertTarget, BreachType typeOfBreach);
