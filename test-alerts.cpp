#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

#include "test/catch.hpp"
#include "typewise-alert.h"

TEST_CASE("infers the breach according to lower limit crossed") 
{
  REQUIRE(inferBreach(12, 20, 30) == TOO_LOW);
}

TEST_CASE("infers the breach is normal") 
{
  REQUIRE(inferBreach(40, 6, 40) == NORMAL);
}

TEST_CASE("infers the breach according to higher limit crossed") 
{
  REQUIRE(inferBreach(44, 10, 40) == TOO_HIGH);
}

TEST_CASE("infers the no breach according to the cooling limits and notify it via e-mail")
{
  BatteryCharacter BatteryAttribute = {HI_ACTIVE_COOLING, "Hi_Active_Cooling"};
  REQUIRE(classifyBreachAndAlert(TO_EMAIL, BatteryAttribute, 45) == ALERT_SUCCESS);
}

TEST_CASE("infers the breach according to the Hi Active cooling limits and send it to controller") 
{
  BatteryCharacter BatteryAttribute = {HI_ACTIVE_COOLING, "Hi_Active_Cooling_High_Breach"};
  REQUIRE(classifyBreachAndAlert(TO_CONTROLLER, BatteryAttribute, 49) == ALERT_SUCCESS);
}

TEST_CASE("infers the breach according to the Med Active cooling limits and notify it via e-mail") 
{
  BatteryCharacter BatteryAttribute = {MED_ACTIVE_COOLING, "Med_Active_Cooling_High_Breach"};
  REQUIRE(classifyBreachAndAlert(TO_EMAIL, BatteryAttribute, 43) == ALERT_SUCCESS);
}

TEST_CASE("infers the breach according to the Med Active cooling limits and send it to controller") 
{
  BatteryCharacter BatteryAttribute = {MED_ACTIVE_COOLING, "Med_Active_Cooling_Low_Breach"};
  REQUIRE(classifyBreachAndAlert(TO_CONTROLLER, BatteryAttribute, -5) == ALERT_SUCCESS);
}

TEST_CASE("infers the breach according to the Passive cooling limits and send it to controller") 
{
  BatteryCharacter BatteryAttribute = {PASSIVE_COOLING, "Low_Breach"};
  REQUIRE(classifyBreachAndAlert(TO_CONTROLLER, BatteryAttribute, -4) == ALERT_SUCCESS);
}

TEST_CASE("Infers the breach according to the Passive cooling limits and notify it via e-mail") 
{
  BatteryCharacter BatteryAttribute = {PASSIVE_COOLING, "High_Breach"};
  REQUIRE(classifyBreachAndAlert(TO_EMAIL, BatteryAttribute, 37) == ALERT_SUCCESS);
}

TEST_CASE("Negative test case for unknown cooling type") 
{
  BatteryCharacter BatteryAttribute = {(CoolingType)4, "Med_Active_Cooling_Low_Breach"};
  REQUIRE(classifyBreachAndAlert(TO_EMAIL, BatteryAttribute, 40) == UNKNOWN_BREACH_ALERT_FAILURE);
}
