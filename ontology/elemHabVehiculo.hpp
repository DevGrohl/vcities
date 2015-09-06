#include "elementoHabitante.hpp"

class elemHabVehiculo : public elementoHabitante
{
};

	class elemHabBicicleta : public elemHabVehiculo
	{
	};

	class elemHabCamion : public elemHabVehiculo
	{
	};

		class elemHabAutobus : public elemHabCamion
		{
		};

			class elemHabAutobusArticulado : public elemHabAutobus
			{
			};

			class elemHabAutobusDosPisos : public elemHabAutobus
			{
			};

			class elemHabAutocar : public elemHabAutobus
			{
			};

			class elemHabMidibus : public elemHabAutobus
			{
			};

			class elemHabMinibus : public elemHabAutobus
			{
			};

			class elemHabTrolebus : public elemHabAutobus
			{
			};

	class elemHabCamionCarga : public elemHabCamion
	{
	};

		class elemHabCamionCargaArticulado : public elemHabCamionCarga
		{
		};

			class elemHabCamionCargaArtUnRemolque : public elemHabCamionCargaArticulado
			{
			};

			class elemHabCamionCargaArtDosRemolques : public elemHabCamionCargaArticulado
			{
			};

			class elemHabCamionCargaArtTren : public elemHabCamionCargaArticulado
			{
			};

		class elemHabCamionCargaRigido : public elemHabCamionCarga
		{
		};

	class elemHabCoche : public elemHabVehiculo
	{
	};

		class elemHabCochePorSegmento : public elemHabCoche
		{
		};

			class elemHabCochePorSegA : public elemHabCochePorSegmento
			{
			};

			class elemHabCochePorSegB : public elemHabCochePorSegmento
			{
			};

			class elemHabCochePorSegC : public elemHabCochePorSegmento
			{
			};

			class elemHabCochePorSegD : public elemHabCochePorSegmento
			{
			};

			class elemHabCochePorSegE : public elemHabCochePorSegmento
			{
			};

			class elemHabCochePorSegF : public elemHabCochePorSegmento
			{
			};

		class elemHabCocheTaxi : public elemHabCoche
		{
		};

		class elemHabMicroCoche : public elemHabCoche
		{
		};

	class elemHabMotocicleta : public elemHabVehiculo
	{
	};

		class elemHabCiclomotor : public elemHabMotocicleta
		{
		};

		class elemHabMotoCamino : public elemHabMotocicleta
		{
		};

		class elemHabMotoCarga : public elemHabMotocicleta
		{
		};

		class elemHabMotoCompetencia : public elemHabMotocicleta
		{
		};

		class elemHabMotoMedia : public elemHabMotocicleta
		{
		};

		class elemHabMotoTaxi : public elemHabMotocicleta
		{
		};

		class elemHabScooter : public elemHabMotocicleta
		{
		};

	class elemHabTrenUrbano : public elemHabVehiculo
	{
	};

		class elemHabFerrobus : public elemHabTrenUrbano
		{
		};

		class elemHabFunicular : public elemHabTrenUrbano
		{
		};

		class elemHabLigero : public elemHabTrenUrbano
		{
		};

		class elemHabMetro : public elemHabTrenUrbano
		{
		};

		class elemHabMonoriel : public elemHabTrenUrbano
		{
		};

		class elemHabTranvia : public elemHabTrenUrbano
		{
		};

	class elemHabUtilitario : public elemHabVehiculo
	{
	};

		class elemHabCamioneta : public elemHabUtilitario
		{
		};

		class elemHabFurgoneta : public elemHabUtilitario
		{
		};

		class elemHabFurgonDeCarga : public elemHabUtilitario
		{
		};

		class elemHabSubUtilitario : public elemHabUtilitario
		{
		};

		class elemHabTaxiUtilitario : public elemHabUtilitario
		{
		};

		class elemHabTodoTerreno : public elemHabUtilitario
		{
		};