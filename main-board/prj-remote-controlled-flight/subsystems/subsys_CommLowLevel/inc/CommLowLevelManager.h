/*
 *-----------------------------------------------------------------------------
 *  Filename:    CommLowLevelManager.h
 *  Implementação do gerenciador e instanciador de submodulos.
 *-----------------------------------------------------------------------------
 *     ___                           _
 *    / _ \_ __ ___/\   /\__ _ _ __ | |_
 *   / /_)/ '__/ _ \ \ / / _` | '_ \| __|
 *  / ___/| | | (_) \ V / (_| | | | | |_
 *  \/    |_|  \___/ \_/ \__,_|_| |_|\__|
 *
 *-----------------------------------------------------------------------------
 *
 */


/*** Renomear .cpp e o .h com o nome do módulo + "Module" (ex. ContinuousControlModule) ***/

#ifndef COMMUNICATION_LOW_LEVEL_MANAGER_H
#define COMMUNICATION_LOW_LEVEL_MANAGER_H

//Common Father
#include "AbstractModuleManager.h"

//Interface
#include "CommLowLevelInterface.h"

//Modulos (nao precisa, mas pode incluir todos os headers dos submodulos)
//#include "uart.h"
#include "proVantProtocol.h"
#include <fstream>

class ContinuousControlManager;

/*! \brief Gerenciador padrão para módulos.
 *
 */
class CommLowLevelManager : public AbstractModuleManager
{
public:
	CommLowLevelManager();
    CommLowLevelManager(std::string name);
    ~CommLowLevelManager();

    // Interface do modulo
    //CommLowLevelInterface * interface;
    ContinuousControlManager * continuousControlManager;

    /*! \brief Implementação do ponto de entrada do modulo.
     *
     *  Equivalente à uma \em main para cada módulo. A implementação deste método é altamente
     *  dependente da estrutura e funcionamento deste módulo.
     */
    void Run();

	void setRcNormalize(proVant::rcNormalize message);
	void setServos(proVant::servos_state message);
	void setPosition(proVant::position message);
	void setAttitude(proVant::atitude message);
	void setStatus(proVant::status message);
	void setDebug(proVant::debug message);
	proVant::rcNormalize getRcNormalize();
	proVant::servos_state getServos();
    proVant::position getPosition();
    proVant::atitude getAttitude();
    proVant::status get_status();
	proVant::debug get_debug();
private:
    /*! \brief Implementação da inicializacao de cada módulo.
     *
     */
    void Init();
    void Log();
    proVantProtocol PROVANT;
    FILE * LOWLEVEL;
    char file[20];

    boost::mutex q_mutex;

    //Class Data
    proVant::atitude cll_atitude;
    proVant::position cll_position;
    proVant::servos_state cll_servos;
    proVant::debug cll_debug;
    proVant::rcNormalize cll_rc;
    proVant::status cll_status;

    //    uart UART;

    /***** Atributos e metodos especificos da topologia do modulo *****/

    // Tempo de amostragem para loop principal
    int ms_sample_time;
    boost::chrono::system_clock::time_point start;
    boost::chrono::system_clock::time_point last_start;

    // Nome do modulo
    std::string name_;

    /*! \brief Callback de recebimento de mensagem
     *
     *  Poderia ser definido em algum submodulo - depende da caracteristica desejada.
     *  Neste exempolo, o funcionamento geral apenas é disparado com a chegada de alguma mensagem.
     */
    void inboxCallback();

 };

#endif // COMMUNICATION_LOW_LEVEL_MANAGER_H
