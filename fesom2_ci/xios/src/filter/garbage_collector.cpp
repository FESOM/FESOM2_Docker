#include "garbage_collector.hpp"

namespace xios
{
  int InvalidableObject::filterIdGenerator = 0;

  int InvalidableObject::edgeIdGenerator = 0;

  int InvalidableObject::clusterIdGenerator = 0;
  
  void CGarbageCollector::registerObject(InvalidableObject* Object, Time timestamp)
  {
    registeredObjects[timestamp].insert(Object);
  }

  void CGarbageCollector::unregisterObject(InvalidableObject* Object, Time timestamp)
  {
    std::map<Time, std::set<InvalidableObject*> >::iterator it = registeredObjects.find(timestamp);
    if (it != registeredObjects.end())
      it->second.erase(Object);
  }

  void CGarbageCollector::invalidate(Time timestamp)
  {
    std::map<Time, std::set<InvalidableObject*> >::iterator it    = registeredObjects.begin(),
                                                            itEnd = registeredObjects.lower_bound(timestamp);
    for (; it != itEnd; ++it)
    {
      std::set<InvalidableObject*>::iterator itObject    = it->second.begin(),
                                             itObjectEnd = it->second.end();
      for (; itObject != itObjectEnd; ++itObject)
        (*itObject)->invalidate(timestamp);
    }
    registeredObjects.erase(registeredObjects.begin(), itEnd);
  }
} // namespace xios
