#ifndef __XMLIO_DECLARE_VIRTUAL_NODE__
#define __XMLIO_DECLARE_VIRTUAL_NODE__

/// ///////////////////////////// Macros ///////////////////////////// ///

#define DECLARE_VIRTUAL_NODE(type)                                    \
   class CVirtual##type                                               \
      : public CVirtualNode<C##type>                                     \
   {                                                                  \
      public:                                                         \
         typedef C##type           RelType;                           \
                                                                      \
         CVirtual##type() : CVirtualNode<RelType> ()                  \
         { /* Ne rien faire de plus */ }                              \
                                                                      \
         void setVirtual##type(RelType* newRelTypePtr)                \
         { CVirtualNode<C##type>::setVirtualNode(newRelTypePtr); }                     \
                                                                      \
         void setVirtual##type()                                      \
         { CVirtualNode<C##type>::setVirtualNode(); }                     \
                                                                      \
         RelType* getVirtual##type() const                            \
         { return CVirtualNode<C##type>::getVirtualNode(); }                           \
                                                                      \
         virtual ~CVirtual##type()                                    \
         { /* Ne rien faire de plus */ }                              \
   };                                                                 \
   typedef CVirtual##type CVirtual##type##Definition


#endif // __XMLIO_DECLARE_VIRTUAL_NODE__
