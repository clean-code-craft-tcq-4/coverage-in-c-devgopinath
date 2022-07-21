#ifndef TYPEWISE_ALERT_H
#define TYPEWISE_ALERT_H

#define IS_COOLING_VALID(COOL_TYPE) (COOL_TYPE < DEFAULT_COOLING)
#define IS_ALERT_VALID(ALERT_VALUE) (ALERT_VALUE < NO_ALERT)
#define IS_BREACH_VALID_AND_REQ_TOBE_REPORTED(BREACH_VALUE) (BREACH_VALUE < NORMAL)

typedef enum
{
    PASSIVE_COOLING = 0,
    HI_ACTIVE_COOLING,
    MED_ACTIVE_COOLING,
    DEFAULT_COOLING
} CoolingType;

typedef enum
{
    TOO_LOW = 0,
    TOO_HIGH,
    NORMAL
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
} BatteryAttributes;

typedef struct
{
    int upperLimit;
} BreachLimitsType;

typedef struct
{
    void (*report)(BreachType breachValue);
} TargetFunctionType;

BreachType inferBreach(double value, double lowerLimit, double upperLimit);
BreachType classifyBreach(CoolingType coolingType, double temperatureInC);
void checkAndAlert(AlertTarget alertTarget, BatteryAttributes battAttribute, double temperatureInC);
void sendToController(BreachType breachValue);
void sendToEmail(BreachType breachValue);
void alertBreachToTarget(AlertTarget alertTarget, BreachType breachValue);

extern const BreachLimitsType BreachLimits[];
extern const char * BreachTypeInString[];
extern char SendMessage[];
extern const TargetFunctionType TargetFunctions[];

#endif
