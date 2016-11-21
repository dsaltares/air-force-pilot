#ifndef __DPHASE_H__
#define __DPHASE_H__


/**  
	@brief Utilizado para asignarle un orden de destrucción a los Singleton.
*/

class DestructionPhase {
  int m_phase;  // the smaller the phase, 
                // the later the object should be destroyed
public:
  /**
  	Constructor
  	@param phase Orden de destrucción, a más pequeño, más tarde será destruido el Singleton
  	
  	Por ejemplo un Singleton Log deberá tener una fase más baja que un Singleton que se encargue de manejar recursos multimedia.
  	Quizás éste último necesite usar el Singleton Log durante su destrucción, si el Log se hubiera destruído, daría problemas graves.
  */
  explicit DestructionPhase (int phase) : m_phase(phase) {}
  
  /**
  	Utilizado para saber si un objeto se debe destruir antes o después.
  	@param dp Fase de destrucción a comparar.
  	@return Verdadero si el DestructionPhase a es mayor que el b, falso en caso contrario.
  */
  bool operator> (const DestructionPhase& dp) const 
  { return m_phase > dp.m_phase; }
};

#endif // __DPHASE_H__

