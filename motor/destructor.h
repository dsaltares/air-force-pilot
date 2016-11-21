#ifndef __DESTRUCTOR_H__
#define __DESTRUCTOR_H__

#include "dphase.h"
#include "dmanager.h"

/**  
	@brief Clase base del destructor genérico para destuir Singleton
*/
class Destructor {
  DestructionPhase m_dphase;
public:
  
  /**
  	Constructor
  	
  	Establece la fase de destrucción y registra el Singleton en la lista de los Singleton a destruir.
  	@param dphase Objeto DestructionPhase que indica el orden.
  */
  Destructor(DestructionPhase dphase) : m_dphase(dphase)
  { DestructionManager::instance().register_destructor(this); }
  
  /**
  	Compara dos destructores en función de su fase de destrucción (DestructionPhase)
  	@param destructor Destructor con el que comparar
  	@return Verdadero si el destructor a debe eliminarse después que el destructor b
  */
  bool operator>(const Destructor& destructor) const
  { return m_dphase > destructor.m_dphase; }

  /**
  	Función virtual pura, utilizada para elegir el destructor apropiado en tiempo de ejecución
  */
  virtual void destroy() = 0;
};


/**  
	@brief Clase paramétrica derivada de Destructor encargada de destruir objetos Singleton
*/
template <class T> class TDestructor : public Destructor {
  T* m_object;
public:
  
  /**
  	Constructor.
  	
  	Establece la fase de destrucción y registra el Singleton en la lista de los Singleton a destruir.
  	
  	@param object Puntero al objeto a destruir
  	@param dphase Orden de destrucción
  */
  TDestructor(T* object, DestructionPhase dphase)
    : Destructor(dphase), m_object(object) {}

  /**
  	Destruye el Singleton apuntado por object
  */
  void destroy() { m_object->destroy_instance(); }
};

#endif // __DESTRUCTOR_H__

