#include <string>
#include <map>

using namespace std;

class thing
{
public:

	string entraDesde; //*thing
	string estaConectadoA; //*thing
	string saleHacia; //*thing
	map <string, bool> estaFuncionando = {{"esOperante",0}, {"estaAbierto",0}};
	map <string, bool> tieneLogicaOperacion = {{"tieneLogPorCarril",0}, {"tieneLogPorSentido", 0}};
	bool puedeContener;
	bool tieneAmplitud;
	bool tieneOrientacion;
	bool tieneSentido;
	
};