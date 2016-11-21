#include <algorithm>   // for 'sort'

#include "dmanager.h"
#include "destructor.h"

using namespace std;

DestructionManager::DestructionManagerPtr& DestructionManager::get_instance() 
{
  static DestructionManagerPtr the_destruction_manager(new DestructionManager);

  return the_destruction_manager;
}

DestructionManager::~DestructionManager()
{
  // the Destruction Manager is responsible for managing
  // the memory occupied by Destructor objects
  for (unsigned i = 0; i < m_destructors.size(); ++i)
    delete m_destructors[i];
}

/**
	@brief Clase auxiliar para el DestructionManager
*/
template <class T> class greater_ptr {
public:
  typedef T* T_ptr;
  
  bool operator()(const T_ptr& lhs, const T_ptr& rhs) const 
  { return *lhs > *rhs; }
};

void DestructionManager::destroy_objects()
{
  // sort the destructors in decreasing order
  sort( m_destructors.begin(), 
        m_destructors.end(), 
        greater_ptr<Destructor>() );
  
  // destroy the objects
  for (unsigned i = 0; i < m_destructors.size(); ++i)
    m_destructors[i]->destroy();
}

