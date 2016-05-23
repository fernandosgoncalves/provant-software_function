/*
 *-----------------------------------------------------------------------------
 *  Filename:    AbstractModuleInterface.h
 *  Interface padrao para modulos.
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

#ifndef ABSTRACT_MESSAGE_INTERFACE_H
#define ABSTRACT_MESSAGE_INTERFACE_H

// STL
#include <iostream>
#include <queue>
#include <memory>

//Boost
#include <boost/thread/mutex.hpp>
#include <boost/thread/thread.hpp>
#include <boost/signals2.hpp>
#include <boost/smart_ptr.hpp>


/*! \brief Interface padrão para módulos.
 *
 *  Implementa o sistema de mensagens entre módulos. Esta classe é abstrata, os métodos
 *  de envio de mensagens são privados (protegidos por acessores publicos).
 *  Sendo herdada como public, o metodo de troca de mensagens entre threads ficará
 *  definido internamente nesta classe, o que fará com que as implmentações dessa classe
 *  possam apenas alterar IDs, nomes e tamanhos de buffers de mensagens.
 */
class AbstractMessageInterface
{
public:
    AbstractMessageInterface();
    ~AbstractMessageInterface();


    /*! \brief Caixa de mensagens entre módulos.
     *
     *  Contem uma fila para mensagens do tipo declarado, um nome, uma mutex para proteção
     *  de acesso, e uma condição para a sinalização de chegada de mensagens.
     */
    template <typename T> struct MsgQueue {
        std::queue<T>                    queue;
        boost::mutex                     q_mutex;
        boost::signals2::signal<void ()> notification;
    };

    /*! \brief Insere um elemento em um outbox.
     */
    template <typename T> void push(T const & value, MsgQueue<T>* mq) {
        if(mq != NULL) { // ponteiro inicializado?
            mq->q_mutex.lock();
            mq->queue.push(value);
            //boost::lock_guard<boost::mutex> (mq->c_mutex);
            //mq->cond.notify_all();
            mq->notification();
            mq->q_mutex.unlock();
        }
    }


    /*! \brief Lê e remove um elemento de um inbox.
     */
    template <typename T> bool pop(T & value, MsgQueue<T>*  mq) {
        if(mq != NULL) { // ponteiro inicializado?
            mq->q_mutex.lock();
            if(mq->queue.empty()) { // algum elemento na fila?
                mq->q_mutex.unlock();
                return false;
            } else {
                //value = mq->queue.front();
            	value = mq->queue.back();
                mq->queue.pop();
                mq->q_mutex.unlock();
                return true;
            }
        } else {
            return false;
        }
    }


 };

#endif // ABSTRACT_MESSAGE_INTERFACE_H
