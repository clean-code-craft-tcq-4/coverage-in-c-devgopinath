#ifndef TYPEWISE_ALERT_H
#define TYPEWISE_ALERT_H

typedef enum
{
    PASSIVE_COOLING = 0,
    HI_ACTIVE_COOLING,
    MED_ACTIVE_COOLING,
    DEFAULT_COOLING
} CoolingType;

typedef enum
{
    NORMAL = 0,
    TOO_LOW,
    TOO_HIGH
} BreachType;

typedef enum
{
    TO_CONTROLLER = 0,
    TO_EMAIL,
    NO_ALERT
} AlertTarget;

typedef struct
{
    CoolingType coolingType;
    char brand[48];
} BatteryCharacter;

typedef struct
{
    int upperLimit;
} BreachLimitsType;

BreachType inferBreach(double value, double lowerLimit, double upperLimit);
BreachType classifyBreach(CoolingType coolingType, double temperatureInC);
void checkAndAlert(AlertTarget alertTarget, BatteryCharacter batteryChar, double temperatureInC);
void sendToController(BreachType breachType);
void sendToEmail(BreachType breachType);
void alertBreachToTarget(AlertTarget alertTarget, BreachType breachType);

extern const BreachLimitsType BreachLimits[];

#endif
