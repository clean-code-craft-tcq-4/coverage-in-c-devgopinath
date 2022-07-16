#include <stdio.h>
#include "typewise-alert.h"

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

void checkAndAlert(AlertTarget alertTarget, BatteryCharacter batteryChar, double temperatureInC)
{
    BreachType breachType = classifyBreach(batteryChar.coolingType, temperatureInC);

    informBreachToTarget(alertTarget, breachType);
}

void informBreachToTarget(AlertTarget alertTarget, BreachType breachType)
{
    switch(alertTarget)
    {
        case TO_CONTROLLER:
        {
            sendToController(breachType);
        }
        break;
        case TO_EMAIL:
        {
            sendToEmail(breachType);
        }
        break;
        default:
        {
            /* no alert required */
        }
        break;
    }
}

void sendToController(BreachType breachType)
{
    const unsigned short header = 0xfeed;
    printf("%x : %x\n", header, breachType);
}

void sendToEmail(BreachType breachType)
{
    const char* recepient = "a.b@c.com";

    switch(breachType)
    {
        case TOO_LOW:
        {
            printf("To: %s\n", recepient);
            printf("Hi, the temperature is too low\n");
        }        
        break;
        case TOO_HIGH:
        {
            printf("To: %s\n", recepient);
            printf("Hi, the temperature is too high\n");
        }        
        break;
        default:
        {
            /* NORMAL - all okay. */
        }
        break;
    }
}
