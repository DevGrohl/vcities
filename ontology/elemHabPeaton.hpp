#include "elementoHabitante.hpp"

class elemHabPeaton : public elementoHabitante
{
};

class elemHabPedestre : public elemHabPeaton
{
};

class elemHabNoPedestre : public elemHabPeaton
{
};

class elemHabPatines : public elemHabNoPedestre
{
};

class elemHabSillaRuedas : public elemHabNoPedestre
{
};

class elemHabPatin : public elemHabNoPedestre
{
};

class elemHabMotorizado : public elemHabPatin
{
};

class elemHabNoMotorizado : public elemHabPatin
{
};