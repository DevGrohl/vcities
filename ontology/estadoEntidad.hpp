#include "metaObjeto.hpp"

class estadoEntidad : public metaObjeto
{	
};

class edoEntApertura : public estadoEntidad
{	
};

class edoEntAbierto : public edoEntApertura
{	
};

class edoEntCerrado : public edoEntApertura
{	
};

class edoEntFuncionalidad : public estadoEntidad
{	
};

class edoEntEnFunciones : public edoEntFuncionalidad
{	
};

class edoEntNoAutorizado : public edoEntFuncionalidad
{	
};

class edoEntOperacion : public estadoEntidad
{	
};

class edoEntOperante : public edoEntOperacion
{	
};

class edoEntNoOperante : public edoEntOperacion
{	
};
