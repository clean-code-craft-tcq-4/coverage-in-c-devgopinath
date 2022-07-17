#include <stdio.h>
#include "typewise-alert.h"

static void toConsole(const char * message);

static void toConsole(const char * message)
{
    printf("%s", message);
}

BreachType inferBreach(double value, double lowerLimit, double upperLimit)
{
    if(value < lowerLimit)
    {
        return TOO_LOW;
    }
    else if(value > upperLimit)
    {
        return TOO_HIGH;
    }
    else
    {
        return NORMAL;
    }
}

BreachType classifyBreach(CoolingType coolingType, double value)
{
    int lowerLimit = 0;
    int upperLimit = 0;

    if (coolingType < DEFAULT_COOLING)
    {
        upperLimit = BreachLimits[coolingType].upperLimit;
    }

    return inferBreach(value, lowerLimit, upperLimit);
}

void checkAndAlert(AlertTarget alertTarget, BatteryAttributes battAttribute, double temperatureInC)
{
    BreachType breachValue = classifyBreach(battAttribute.coolingType, temperatureInC);

    alertBreachToTarget(alertTarget, breachValue);
}

void alertBreachToTarget(AlertTarget alertTarget, BreachType breachValue)
{
    if (alertTarget < NO_ALERT)
    {
        TargetFunctions[alertTarget].report(breachValue);
    }
    else
    {
        /* no alert required */
    }
}

void sendToController(BreachType breachValue)
{
    const unsigned short header = 0xfeed;
    sprintf(SendMessage, "%x : %x\n", header, breachValue);
    toConsole(SendMessage);
}

void sendToEmail(BreachType breachValue)
{
    if (breachValue < NORMAL)
    {
        const char* recepient = "a.b@c.com";
        const char * parameterName = "temperature";

        sprintf(SendMessage, "To: %s\nHi, the %s is %s\n", recepient, parameterName, BreachTypeInString[breachValue]);
        toConsole(SendMessage);
    }
    else
    {
        /* NORMAL - all okay. */
    }
}
