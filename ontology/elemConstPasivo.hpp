#include "elemConstructivo.hpp"

class elemConstPasivo : public elemConstructivo
{
};

class elemConstBloque : public elemConstPasivo
{
};

	class elemPasivoBloqueCondominio : public elemConstBloque
	{
	};

	class elemPasivoBloqueCoto : public elemConstBloque
	{
	};

	class elemPasivoBloqueManzana : public elemConstBloque
	{
	};

	class elemPasivoBloqueModulo : public elemConstBloque
	{
	};

	class elemPasivoBloquePlaza : public elemConstBloque
	{
	};

	class elemPasivoBloqueGlorieta : public elemConstBloque
	{
	};

		class elemPasivoBloqueCamellon : public elemConstBloqueGlorieta
		{
		};

		class elemPasivoBloqueCuchilla : public elemConstBloqueGlorieta
		{
		};

		class elemPasivoBloqueGlorieta : public elemConstBloqueGlorieta
		{
		};

class elemConstCrucero : public elemConstPasivo
{
};

class elemConstSegmento : public elemConstPasivo
{
};

	class elemPasivoSegmentoAndador : public elemConstSegmento
	{
	};

	class elemPasivoSegmentoAutopista : public elemConstSegmento
	{
	};

	class elemPasivoSegmentoAvenida : public elemConstSegmento
	{
	};

	class elemPasivoSegmentoCalle : public elemConstSegmento
	{
	};

	class elemPasivoSegmentoCiclovia : public elemConstSegmento
	{
	};

	class elemPasivoSegmentoSendero : public elemConstSegmento
	{
	};

	class elemPasivoSegmentoPaso : public elemConstSegmento
	{
	};

		class elemPasivoSegmentoCambioVia : public elemPasivoSegmentoPaso
		{
		};

		class elemPasivoSegmentoEntradaVia : public elemPasivoSegmentoPaso
		{
		};

		class elemPasivoSegmentoPuente : public elemPasivoSegmentoPaso
		{
		};

		class elemPasivoSegmentoPuentePeatonal : public elemPasivoSegmentoPaso
		{
		};

		class elemPasivoSegmentoSalidaVia : public elemPasivoSegmentoPaso
		{
		};

		class elemPasivoSegmentoTunel : public elemPasivoSegmentoPaso
		{
		};