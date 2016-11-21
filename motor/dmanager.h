#ifndef __DMANAGER_H__
#define __DMANAGER_H__

#include <memory>
#include <vector>

using namespace std;

class Destructor; // forward declaration

/**  @brief Singleton utilizado para controlar la ordenada destrucción de los demás Singletons
	
	Lo único que hay que hacer es crear nuestros Singleton de la misma manera que Galeria, por ejemplo.
	Sólo hay que preocuparse que, cuando vayan a destruirse todos los Singleton se haga la siguiente llamada:
	
	\code
	DestructionManager::instance().destroy_objects();
	\endcode
	
	De esta manera los todos Singleton del sistema se destruyen de manera perfectamente ordenada.
	
	Si se sigue el esquema de Galeria para los Singleton no hay que preocuparse por esta clase
*/
class DestructionManager {
  typedef auto_ptr<DestructionManager> DestructionManagerPtr;

  vector<Destructor*> m_destructors;

  static DestructionManagerPtr& get_instance();
  
  DestructionManager() {} 
  ~DestructionManager();
  
  friend class auto_ptr<DestructionManager>;
  
  DestructionManager(const DestructionManager&);
  DestructionManager& operator=(const DestructionManager&);

public:
  // singleton interface
  
  /**
  	Obtiene la única instancia del DestructionManager del sistema
  	@return instancia del manejador de destrucción del sistema
  */
  static DestructionManager& instance() { return *get_instance(); }
  
  /**
  	Obtiene la única instancia del DestructionManager del sistema
  	@return instancia constante del manejador de destrucción del sistema
  */
  static const DestructionManager& const_instance() { return instance(); }

  /**
  	Registra un objeto del tipo Singleton a través de un puntero a Destructor relacionado con él
  	@param destructor Puntero al objeto de la clase Destructor relacionado con el objeto Singleton a destruir
  */
  void register_destructor(Destructor* destructor)
  { m_destructors.push_back(destructor); }
  
  /**
  	Se encarga de destruir todos los objetos Singleton de manera ordenada.
  */
  void destroy_objects(); // destroy the objects
};

#endif // __DMANAGER_H__

