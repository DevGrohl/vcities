#include "elementoHabitante.hpp"

class elemHabOtro : public elementoHabitante
{
};

class elemHabGas : public elemHabOtro
{
};

class elemHabAire : public elemHabGas
{
};

class elemHabGasContaminante : public elemHabGas
{
};

class elemHabLiquido : public elemHabOtro
{
};

class elemHabAguasNegras : public elemHabLiquido
{
};

class elemHabLluvia : public elemHabLiquido
{
};

class elemHabOtrosDerrames : public elemHabLiquido
{
};