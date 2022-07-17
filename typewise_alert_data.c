#include "typewise-alert.h"

char SendMessage[100];

const BreachLimitsType BreachLimits[] =
{
    {
        // CoolingType : PASSIVE_COOLING
        35
    },
    {
        // CoolingType : HI_ACTIVE_COOLING
        45
    },
    {
        // CoolingType : MED_ACTIVE_COOLING
        40
    }
};

/* inline with BreachType */
const char * BreachTypeInString[] =
{
    "TOO LOW",
    "TOO HIGH",
    "NORMAL"
};

const TargetFunctionType TargetFunctions[] =
{
    {&sendToController},
    {&sendToEmail}
};
