/*
 *-----------------------------------------------------------------------------
 *  Filename:    DataProcessingInterface.h
 *  Implementação da interface para algum modulo especifico.
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

/*** Renomear .cpp e o .h com o nome do módulo + "Interface" (ex. DataProcessingInterface) ***/

#ifndef DATA_PROCESSING_INTERFACE_H
#define DATA_PROCESSING_INTERFACE_H

//Father
#include "AbstractMessageInterface.h"

#include "proVantTypes.h"

/*! \brief Implementação da interface entre os modulos.
 *
 *  A interface contem um MessageQueue para cada inbox que possuir (q_in, no caso),
 *  e ponteiros para o inbox da interface com o qual ela se conecta (q_out).
 */
class DataProcessingInterface : public AbstractMessageInterface
{
public:
    DataProcessingInterface(std::string name) :

        name_(name) { }

    ~DataProcessingInterface();

    // Inboxes
    MsgQueue<proVant::atitude> q_atitude_in;
    MsgQueue<proVant::position> q_position_in;
    MsgQueue<proVant::servos_state> q_servos_in;
    MsgQueue<proVant::controlOutput> q_actuation_in;
    MsgQueue<proVant::debug> q_debug_in;
    MsgQueue<proVant::rcNormalize> q_rc_in;
    MsgQueue<proVant::status> q_status_in;


    // Outboxes (ponteiros para inboxes alheios)


private:
    std::string name_;

};

#endif // DATA_PROCESSING_INTERFACE_H
