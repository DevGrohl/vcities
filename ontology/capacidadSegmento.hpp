#include "thing.hpp"

class capacidadSegmento : public thing
{	
};

class capSegContenido : public capacidadSegmento
{
};

class capSegPromedioVehiculosPorParte : public capSegContenido
{
};

class capSegPromedioVehiculosTotal : public capSegContenido
{
};

class capSegPeso : public capacidadSegmento
{
};

class capSegPesoAlto : public capSegPeso
{
};

class capSegPesoBajo : public capSegPeso
{
};

class capSegPesoMedio : public capSegPeso
{
};

class capSegVelocidad : public capacidadSegmento
{
};