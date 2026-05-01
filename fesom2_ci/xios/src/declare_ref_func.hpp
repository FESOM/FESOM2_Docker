/*!
   \file declare_ref_func.hpp
   \author Ha NGUYEN
   \date 02 Dec 2014
   \since 02 Dec 2014

   \brief Macros to add functions used to solve references in class CDomain, CAxis and CField
 */
#ifndef __XIOS_DECLARE_REF_FUNC_HPP__
#define __XIOS_DECLARE_REF_FUNC_HPP__

// Declarations

#define DECLARE_REF_FUNC(type, name_)                       \
public:                                                     \
  void solveRefInheritance(bool apply = true);              \
  void removeRefInheritance();                              \
  bool hasDirect##type##Reference(void) const;              \
  C##type* getDirect##type##Reference(void) const;          \
  const StdString get##type##OutputName(void) const;        \
  void setAttributesReference(bool apply = true);           \
  bool hasRefTo(C##type* ref) const;                        \
                                                                       \
private:                                                               \
  std::vector<C##type*> refObjects;

// Definitions

#define DEFINE_REF_FUNC(type, name_)                                   \
void C##type::solveRefInheritance(bool apply)                          \
{                                                                      \
  std::set<C##type*> tmpRefObjects;                                    \
  C##type* refer_ptr = this;                                           \
  std::vector<C##type*>().swap(refObjects);                            \
  refObjects.push_back(this);                                          \
                                                                       \
  while (refer_ptr->hasDirect##type##Reference())                      \
  {                                                                    \
    tmpRefObjects.insert(refer_ptr);                                   \
                                                                       \
    refer_ptr = refer_ptr->getDirect##type##Reference();               \
                                                                       \
    if (tmpRefObjects.end() != tmpRefObjects.find(refer_ptr))          \
    {                                                                  \
      ERROR("void C" #type "::solveRefInheritance(bool apply)",        \
            << "Circular dependency stopped for " #name_ " object "    \
            << "with id = \"" << refer_ptr->getId() << "\".");         \
    }                                                                  \
                                                                       \
    refObjects.push_back(refer_ptr);                                   \
    SuperClassAttribute::setAttributes(refer_ptr, apply);              \
  }                                                                    \
  if (this->hasAttribute("name") && this->name.isEmpty())              \
    this->name.setValue(this->get##type##OutputName());                \
}                                                                      \
                                                                       \
void C##type::setAttributesReference(bool apply)                       \
{                                                                      \
  for (int i = 1; i < refObjects.size(); ++i)                          \
    refObjects[i]->setAttributes(refObjects[i-1], apply);              \
  if (refObjects.size() > 1)                                           \
    refObjects[refObjects.size()-1]->removeRefInheritance();           \
}                                                                      \
                                                                       \
void C##type::removeRefInheritance()                                   \
{                                                                      \
  if (!this->name_##_ref.isEmpty())                                    \
    this->name_##_ref.reset();                                         \
}                                                                      \
                                                                       \
bool C##type::hasDirect##type##Reference(void) const                   \
{                                                                      \
  return (!this->name_##_ref.isEmpty() &&                              \
          C##type::has(this->name_##_ref));                            \
}                                                                      \
                                                                       \
C##type* C##type::getDirect##type##Reference(void) const               \
{                                                                      \
  if (this->name_##_ref.isEmpty())                                     \
    ERROR("C" #type "* C" #type "::getDirect" #type "Reference(void)", \
          << "The " #name_ " with id = '" << getId() << "'"            \
          << " has no " #name_ "_ref.");                               \
                                                                       \
  if (!C##type::has(this->name_##_ref))                                \
    ERROR("C" #type "* C" #type "::getDirect" #type "Reference(void)", \
          << this->name_##_ref                                         \
          << " refers to an unknown " #name_ " id.");                  \
                                                                       \
  return C##type::get(this->name_##_ref);                              \
}                                                                      \
                                                                       \
const StdString C##type::get##type##OutputName(void) const             \
{                                                                      \
  if (!this->name.isEmpty())  return this->name;                       \
  else if (this->hasAutoGeneratedId() && hasDirect##type##Reference()) \
  {                                                                    \
    const C##type* refer_ptr = this, *tmp_ptr;                         \
    StdString nameRef = this->name_##_ref;                             \
    std::set<const C##type*> tmpRefObjects;                            \
    while (refer_ptr->hasAutoGeneratedId() &&                          \
          (C##type::has(nameRef)))                                     \
    {                                                                  \
      tmpRefObjects.insert(refer_ptr);                                 \
      tmp_ptr = refer_ptr;                                             \
      refer_ptr = tmp_ptr->getDirect##type##Reference();               \
      if (refer_ptr->hasAutoGeneratedId() &&                           \
          refer_ptr->hasDirect##type##Reference())                     \
        nameRef = refer_ptr->name_##_ref;                              \
      else {                                                           \
        nameRef = refer_ptr->getId(); break;                           \
      }                                                                \
      if (tmpRefObjects.end() != tmpRefObjects.find(refer_ptr))        \
      {                                                                \
        ERROR("const StdString& C" #type "::get" #type "OutputName(void) const ",      \
              << "Circular dependency stopped for " #name_ " object "  \
              << "with id = \"" << refer_ptr->getId() << "\".");       \
      }                                                                \
    }                                                                  \
    return nameRef;                                                    \
  }                                                                    \
  else                                                                 \
    return getId();                                                    \
}                                                                      \
                                                                       \
bool C##type::hasRefTo(C##type* ref) const                             \
{                                                                      \
  bool found = false;                                                  \
  for (int idx = 0; idx < refObjects.size(); ++idx)                    \
    if (ref == refObjects[idx]) { found = true; break; }                \
  return found;                                                        \
}

#endif // __XIOS_DECLARE_REF_FUNC_HPP__
