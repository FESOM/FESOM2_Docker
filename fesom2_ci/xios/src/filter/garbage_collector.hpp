#ifndef __XIOS_CGarbageCollector__
#define __XIOS_CGarbageCollector__

#include <map>
#include <set>

#include "date.hpp"

namespace xios
{
  /*!
   * Interface shared by all objects that might need to invalidate packets.
   */
  struct InvalidableObject
  {
    /*!
     * Removes all pending packets which are older than the specified timestamp.
     *
     * \param timestamp the timestamp used for invalidation
     */
    void virtual invalidate(Time timestamp) = 0;
  
    

    static int filterIdGenerator;

    static int edgeIdGenerator;

    static int clusterIdGenerator;

    
    
  }; // struct InvalidableObject

  /*!
   * A basic garbage collector which ensures no old packets linger in the filter graph.
   */
  class CGarbageCollector
  {
    public:
      /*!
       * Constructs a garbage collector.
       */
      CGarbageCollector()
      { /* Nothing to do */ };

      /*!
       * Registers an object for a specified timestamp.
       *
       * \param object the object to register
       * \param timestamp the timestamp for which the object is registered
       */
      void registerObject(InvalidableObject* object, Time timestamp);

      /*!
       * Removes a object previously registered for a specified timestamp.
       *
       * \param object the object to unregister
       * \param timestamp the timestamp for which the object is unregistered
       */
      void unregisterObject(InvalidableObject* object, Time timestamp);

      /*!
       * Ensures all registered objects invalidate packets older than the specified timestamp.
       *
       * \param timestamp the timestamp used for invalidation
       */
      void invalidate(Time timestamp);

    private:
      CGarbageCollector(const CGarbageCollector&);
      CGarbageCollector& operator=(const CGarbageCollector&);

      std::map<Time, std::set<InvalidableObject*> > registeredObjects; //!< Currently registered objects
  }; // class CGarbageCollector
} // namespace xios

#endif //__XIOS_CGarbageCollector__
