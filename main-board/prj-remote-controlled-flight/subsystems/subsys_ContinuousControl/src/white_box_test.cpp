/*
 *-----------------------------------------------------------------------------
 *  Filename:    main.cpp
 *
 *-----------------------------------------------------------------------------
 *     ___                           _
 *    / _ \_ __ ___/\   /\__ _ _ __ | |_
 *   / /_)/ '__/ _ \ \ / / _` | '_ \| __|
 *  / ___/| | | (_) \ V / (_| | | | | |_
 *  \/    |_|  \___/ \_/ \__,_|_| |_|\__|
 *
 *-----------------------------------------------------------------------------
 *
 *  PROVANT - SUBSYS Template V1
 *
 *  Template C++ para projeto de um susbistema do VANT.
 *
 *  Implementa a classe abstrata de interface do módulo, a unidade de white-box
 *  e de black-box testing, além de algumas classes de teste do modulo.
 *
 *  provant_subsys_template_v1/             Pasta com subsistema
 *  |-  black_box_test.cpp                  Tem uma main para testes caixa preta
 *  |-  doc/
 *  |-  build/                              Modulo compilado.
 *  |-  module_template/
 *      |- src/
 *      |- inc/
 *      CMakeLists.txt
 */

/* TODO:
 *
 *      - Implementar container (queue de uma variavel so)
 *  - Implementar as perspectivas de teste
 *  - Chamar CMake recursivamente (para os varios modulos a partir de um central)
 *
 *  - Para o ARM, implementar o ARM_HAL como singleton também -> system init, not lazy
 */

// STL
#include <iostream>

// Boost
#include <boost/thread/thread.hpp>

// Test framework
// #include ...

// Project Includes
#include "ContinuousControlManager.h"
#include "debug.h"

// Module and test dummy interface
ContinuousControlManager *   module1;
ContinuousControlInterface * dummyIface;

void testThread() {
    std::string msg("Test message!");

    while(true) {
        //dummyIface->push(msg, dummyIface->q_atitude_out_);
        boost::this_thread::sleep(boost::posix_time::milliseconds(1000));
    }
}

int main()
{
    // Create module
    module1 = new ContinuousControlManager("ContinuousControl:Manager");

    //Dummy test interface
    dummyIface = new ContinuousControlInterface("DummyIface");

    // Debug
    DEBUG(LEVEL_INFO, "Created!");

    // Connect
    //dummyIface->q_out_ = &module1->interface->q_in;
    //module1->interface->q_out_ = &dummyIface->q_in;

    // Run module
    boost::thread th1( boost::bind( &ContinuousControlManager::Run, module1) );
    boost::thread th2( testThread ) ;

    // Wait for threads to end
    th1.join();
    th2.join();
    return 0;

}

