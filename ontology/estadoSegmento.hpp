#include "metaObjeto.hpp"

class estadoSegmento : public metaObjeto
{
};
// totalmente transitable
class transTotal : public estadoSegmento 
{
};
// parcialmente transitable
class transParcial : public estadoSegmento
{
};
// cerrado temporalmente
class cerrTemporal : public estadoSegmento
{
};
// cerrado permanentemente
class cerrPermanen : public estadoSegmento
{
};

class enConstruccion : public estadoSegmento
{
};
// funcional Saturado
class funcSaturado : public estadoSegmento
{
};

// funcional Saturado y parcialmente transitable se diferencian por la logica que bloquea el transito.
// funcSaturado esta totalmente transitable pero bloqueado 
// transParcial esta bloqueado por cuestiones ajenas