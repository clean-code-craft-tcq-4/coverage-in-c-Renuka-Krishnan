#include "typewise-alert.h"
#include <stdio.h>

AlertStatus classifyBreachAndAlert(AlertTarget alertTarget, BatteryCharacter batteryChar, double temperatureInC) 
{

  BreachType BreachTypeData;
  AlertStatus alertStatus;
  
  if((batteryChar.coolingType >= 0) && (batteryChar.coolingType <= 2))
  {
    BreachTypeData = classifyTemperatureBreach(batteryChar.coolingType, temperatureInC);
    alertStatus = checkAndAlert(alertTarget, BreachTypeData);
  }
  else
  {
    BreachTypeData = UNKNOWN_BREACH;
    alertStatus = UNKNOWN_BREACH_ALERT_FAILURE;
  }
  return(alertStatus);
 
 }
  
BreachType classifyTemperatureBreach(
    CoolingType coolingType, double temperatureInC) 
{
  int lowerLimit = 0;
  int upperLimit = 0;
  switch(coolingType) 
  {
    case PASSIVE_COOLING:
      lowerLimit = 0;
      upperLimit = 35;
      break;
    case HI_ACTIVE_COOLING:
      lowerLimit = 0;
      upperLimit = 45;
      break;
    default:
      lowerLimit = 0;
      upperLimit = 40;
      break;
  }
  return inferBreach(temperatureInC, lowerLimit, upperLimit);
}

BreachType inferBreach(double value, double lowerLimit, double upperLimit) 
{
  if(value < lowerLimit) 
  {
    return TOO_LOW;
  }
  if(value > upperLimit) 
  {
    return TOO_HIGH;
  }
  return NORMAL;
}

AlertStatus checkAndAlert(AlertTarget alertTarget, BreachType typeOfBreach) 
{
  AlertStatus alertRet;
  
  switch(alertTarget) 
  {
    case TO_CONTROLLER:
      sendToController(typeOfBreach);
      alertRet = ALERT_SUCCESS;
      break;
    case TO_EMAIL:
      sendToEmail(typeOfBreach);
      alertRet = ALERT_SUCCESS;
      break;
    default:
      alertRet = ALERT_FAILURE;
      break;
  }
  return alertRet;
}

void sendToController(BreachType BreachTypeData) 
{
  const unsigned short header = 0xfeed;
  printf("%x : %x\n", header, BreachTypeData);
}

void sendToEmail(BreachType BreachTypeData) 
{
  const char* recepient = "a.b@c.com";
  switch(BreachTypeData) {
    case TOO_LOW:
      printf("To: %s\n", recepient);
      printf("Hi, the temperature is too low\n");
      break;
    case TOO_HIGH:
      printf("To: %s\n", recepient);
      printf("Hi, the temperature is too high\n");
      break;
    default:
      printf("To: %s\n", recepient);
      printf("Hi, the temperature is Normal\n");	
      break;
  }
}
