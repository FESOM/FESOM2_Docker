#include "attribute_map.hpp"
#include "indent.hpp"

namespace xios
{
      /// ////////////////////// Définitions ////////////////////// ///
      CAttributeMap* CAttributeMap::Current = NULL;

      CAttributeMap::CAttributeMap(void)
         : xios_map<StdString, CAttribute*>()
      { CAttributeMap::Current = this; }

      CAttributeMap::~CAttributeMap(void)
      { /* Ne rien faire de plus */ }

      ///--------------------------------------------------------------

      /*!
         Clear all attributes of an object and reset them to empty state
      */
      void CAttributeMap::clearAllAttributes(void)
      {
         typedef std::pair<StdString, CAttribute*> StdStrAttPair;
         SuperClassMap::const_iterator it = SuperClassMap::begin(), end = SuperClassMap::end();
         for (; it != end; it++)
         {
            const StdStrAttPair& att = *it;
            att.second->reset();
         }
      }

      ///--------------------------------------------------------------
      /*!
         Dump of all non-empty attributes of an object
      */
      StdString CAttributeMap::dumpXiosAttributes(void) const
      {
        int maxNbChar = 250;
        StdString str;
        typedef std::pair<StdString, CAttribute*> StdStrAttPair;
        auto it = SuperClassMap::begin(), end = SuperClassMap::end();
        for (; it != end; it++)
        {
          const StdStrAttPair& att = *it;
          if (!att.second->isEmpty())
          {
            if (str.length() < maxNbChar)
            {
              str.append(att.second->dump());
              str.append(" ");
            }
            else if (str.length() == maxNbChar)
            {
              str.append("...");
            }
          }
        }
        return str;
      }



      StdString CAttributeMap::record4graphXiosAttributes(void) const
      {
        int maxNbChar = 250;
        StdString str;
        typedef std::pair<StdString, CAttribute*> StdStrAttPair;
        auto it = SuperClassMap::begin(), end = SuperClassMap::end();
        for (; it != end; it++)
        {
          const StdStrAttPair& att = *it;
          if (!att.second->isEmpty())
          {
            if (str.length() < maxNbChar)
            {
              str.append(att.second->dump4graph());
              str.append(" ");
            }
            else if (str.length() == maxNbChar)
            {
              str.append("...");
            }
          }
        }
        return str;
      }

      //---------------------------------------------------------------

      /*
        Clear an attribute and reset its value
        \param[in] key id of attribute
      */
      void CAttributeMap::clearAttribute(const StdString& key)
      {
        if (hasAttribute(key)) this->find(key)->second->reset();
      }

      //---------------------------------------------------------------

      /*!
        Set an attribute of certain id with a value
        \param[in] key id of the attribute
        \param[in] attr value of attribute
      */
      void CAttributeMap::setAttribute(const StdString& key, CAttribute* const attr)
      {
         if (!this->hasAttribute(key))
            ERROR("CAttributeMap::setAttribute(key, attr)",
                   << "[ key = " << key << "] key not found !");
         if (attr == NULL)
            ERROR("CAttributeMap::setAttribute(key, attr)",
                   << "[ key = " << key << "] attr is null !");
         this->find(key)->second->set(*attr);
//       this->find(key)->second->setAnyValue(attr->getAnyValue());
      }

      //---------------------------------------------------------------

      /*!
        Subscript operator. Return attribute with a specific id
      */
      CAttribute* CAttributeMap::operator[](const StdString& key)
      {
         if (!this->hasAttribute(key))
            ERROR("CAttributeMap::operator[](const StdString& key)",
                  << "[ key = " << key << "] key not found !");
         return SuperClassMap::operator[](key);
      }

      //---------------------------------------------------------------

      StdString CAttributeMap::toString(void) const
      {
         typedef std::pair<StdString, CAttribute*> StdStrAttPair;
         StdOStringStream oss;

         SuperClassMap::const_iterator it = SuperClassMap::begin(), end = SuperClassMap::end();
         for (; it != end; it++)
         {
            const StdStrAttPair& att = *it;
            if (!att.second->isEmpty())
               oss << *att.second << " ";
         }
         return oss.str();
      }

      //---------------------------------------------------------------

      void CAttributeMap::fromString(const StdString& str)
      {
         ERROR("CAttributeMap::fromString(const StdString& str)",
               << "[ str = " << str << "] Not implemented yet !");
      }

      //---------------------------------------------------------------

      //StdOStream& operator << (StdOStream& os, const CAttributeMap& attributmap)
      //{ os << attributmap.toString(); return (os); }

      //---------------------------------------------------------------

      void CAttributeMap::setAttributes(const xml::THashAttributes& attributes)
      {
         for (xml::THashAttributes::const_iterator it  = attributes.begin();
                                                   it != attributes.end();
                                                   it++)
         {
            if ((*it).first.compare(StdString("id")) != 0 && (*it).first.compare(StdString("src")) != 0)
            {
               //if (CAttributeMap::operator[]((*it).first)->isEmpty())
               CAttributeMap::operator[]((*it).first)->fromString((*it).second);
            }
         }
      }

      /*!
         Compare two attribute maps
         \param [in] another attribute map to compare
         \param [in] excludedAttrs attribute to be excluded from comparasion
         \return true if these two maps have same attributes whose value are identical
      */
      bool CAttributeMap::isEqual(const CAttributeMap& another, const vector<StdString>& excludedAttrs)
      {
         SuperClassMap::const_iterator itb = another.begin(), ite = another.end(), it;
         for (it = itb; it !=ite; ++it)
         {
            bool excluded = false;
            for (int idx = 0; idx < excludedAttrs.size(); ++idx)
            {
               if (0 == (*it).first.compare(excludedAttrs[idx]))
               {
                 excluded = true;
                 break;
               } 
            }

            if (!excluded)
            {
              if ((*it).first.compare(StdString("id")) != 0 && (*it).first.compare(StdString("src")) != 0)
              {
                if (this->hasAttribute(it->first))
                { 
                  if (!((*it).second->isEqual(*(*this)[it->first])))
                  {
                    return false;
                  }
                }
                else
                  return false;
              }
            }
         }

         return true;
      }


      //---------------------------------------------------------------

      /*!
      \brief Set attributes from a specific attributemap, considered parent.
         The child attribute map will insert the attributes of its parent into its current attribute map.
      The existing attributes can be filled with the values of the parent map if they are empty or
      simply replaced by these values depending on choice of user.
      \param [in] _parent Attribute map from which the current map gets attributes.
      \param [in] apply Specify if current attribute map is replaced by the attributes of parent (false)
                    or filled in in case of emptyp (true)
      */
      void CAttributeMap::setAttributes(const CAttributeMap* const _parent, bool apply)
      {
         typedef std::pair<StdString, CAttribute*> StdStrAttPair;

         SuperClassMap::const_iterator it = _parent->begin(), end = _parent->end();
         for (; it != end; it++)
         {
            const StdStrAttPair& el = *it;
            if (this->hasAttribute(el.first))
            {
               CAttribute* currentAtt = CAttributeMap::operator[](el.first);
               CAttribute* parentAtt = el.second;
               if (apply)
               {
                 if (currentAtt->isEmpty() && currentAtt->canInherite() && !el.second->isEmpty())
                 {
                    this->setAttribute(el.first, el.second);
                 }
               }
               else currentAtt->setInheritedValue(*parentAtt);
            }
         }
      }

      /*!
        Duplicate attribute map with a specific attribute map.
        Copy all non-empty attribute of the current attribute map
        \param [in] srcAttr attribute map which is copied from.
      */
      void CAttributeMap::duplicateAttributes(const CAttributeMap* const srcAttr)
      {
         typedef std::pair<StdString, CAttribute*> StdStrAttPair;

         SuperClassMap::const_iterator it = srcAttr->begin(), end = srcAttr->end();
         for (; it != end; it++)
         {
            const StdStrAttPair& el = *it;
            if (this->hasAttribute(el.first))
            {
               if (!el.second->isEmpty())
               {
                 this->setAttribute(el.first, el.second);
               }
            }
         }
      }

      //---------------------------------------------------------------
/*
      void CAttributeMap::toBinary(StdOStream& os) const
      {
         typedef std::pair<StdString, CAttribute*> StdStrAttPair;
         SuperClassMap::const_iterator it = this->begin(), end = this->end();

         const StdSize nbatt = SuperClassMap::size();
         os.write (reinterpret_cast<const char*>(&nbatt) , sizeof(StdSize));

         for (; it != end; it++)
         {
            const StdString& key   = it->first;
            const CAttribute* value = it->second;
            const StdSize size = key.size();

            os.write (reinterpret_cast<const char*>(&size) , sizeof(StdSize));
            os.write (key.data(), size* sizeof(char));

            if (!value->isEmpty())
            {
               bool b = true;
               os.write (reinterpret_cast<const char*>(&b) , sizeof(bool));
               value->toBinary(os);
            }
            else
            {
               bool b = false;
               os.write (reinterpret_cast<const char*>(&b) , sizeof(bool));
            }
         }
      }

      //---------------------------------------------------------------

      void CAttributeMap::fromBinary(StdIStream& is)
      {
         StdSize nbatt = 0;
         is.read (reinterpret_cast<char*>(&nbatt), sizeof(StdSize));

         for (StdSize i = 0; i < nbatt; i++)
         {
            bool hasValue = false;
            StdSize size  = 0;
            is.read (reinterpret_cast<char*>(&size), sizeof(StdSize));
            StdString key(size, ' ');
            is.read (const_cast<char *>(key.data()), size* sizeof(char));

            if (!this->hasAttribute(key))
               ERROR("CAttributeMap::fromBinary(StdIStream& is)",
                     << "[ key = " << key << "] key not found !");

            is.read (reinterpret_cast<char*>(&hasValue), sizeof(bool));

            if (hasValue)
               this->operator[](key)->fromBinary(is);
         }
      }
 */
      
      void CAttributeMap::generateCInterface(ostream& oss, const string& className)
      {
         SuperClassMap::const_iterator it = SuperClassMap::begin(), end = SuperClassMap::end();
         for (; it != end; it++)
         {
           if (it->second->isPublic())
           {
             oss << std::endl << iendl;
             it->second->generateCInterface(oss, className);
             oss << iendl;
             it->second->generateCInterfaceIsDefined(oss, className);
           }
         }
      }

      void CAttributeMap::generateFortran2003Interface(ostream& oss, const string& className)
      {
         SuperClassMap::const_iterator it = SuperClassMap::begin(), end = SuperClassMap::end();
         for (; it != end; it++)
         {
           if (it->second->isPublic())
           {
             oss << std::endl << iendl;
             it->second->generateFortran2003Interface(oss, className);
             oss << iendl;
             it->second->generateFortran2003InterfaceIsDefined(oss, className);
           }
         }
      }

      ///--------------------------------------------------------------

      void CAttributeMap::generateFortranInterface_hdl_(ostream& oss, const string& className)
      {
         oss << "SUBROUTINE xios(set_" << className << "_attr_hdl_)   &" << iendl++;
         SuperClassMap::const_iterator it;
         SuperClassMap::const_iterator begin = SuperClassMap::begin(), end = SuperClassMap::end();

         long startPos = oss.tellp();

         oss << "( " << className << "_hdl";
         for (it = begin; it != end; it++)
         {
           if (it->second->isPublic())
           {
             oss << ", " << it->second->getName() << "_";
             if (oss.tellp() - startPos > 90)
             {
               oss << "  &" << iendl;
               startPos = oss.tellp();
             }
           }
         }
         oss << " )";
         oss << std::endl;
         oss << iendl;

         oss << "IMPLICIT NONE" << iendl++;
         oss << "TYPE(txios(" << className << ")) , INTENT(IN) :: " << className << "_hdl";

         for (it = begin; it != end; it++)
         {
           if (it->second->isPublic())
           {
             oss << iendl;
             it->second->generateFortranInterfaceDeclaration_(oss, className);
           }
         }

         for (it = begin; it != end; it++)
         {
           if (it->second->isPublic())
           {
             oss << std::endl << iendl;
             it->second->generateFortranInterfaceBody_(oss, className);
           }
         }

         oss << std::endl << (iendl -= 2);
         oss << "END SUBROUTINE xios(set_" << className << "_attr_hdl_)" << std::endl;
      }

      void CAttributeMap::generateFortranInterfaceGet_hdl_(ostream& oss, const string& className)
      {
         oss << "SUBROUTINE xios(get_" << className << "_attr_hdl_)   &" << iendl++;
         SuperClassMap::const_iterator it;
         SuperClassMap::const_iterator begin = SuperClassMap::begin(), end = SuperClassMap::end();

         long startPos = oss.tellp();

         oss << "( " << className << "_hdl";
         for (it = begin; it != end; it++)
         {
           if (it->second->isPublic())
           {
             oss << ", " << it->second->getName() << "_";
             if (oss.tellp() - startPos > 90)
             {
               oss << "  &" << iendl;
               startPos = oss.tellp();
             }
           }
         }
         oss << " )";
         oss << std::endl;
         oss << iendl;

         oss << "IMPLICIT NONE" << iendl++;
         oss << "TYPE(txios(" << className << ")) , INTENT(IN) :: " << className << "_hdl";

         for (it = begin; it != end; it++)
         {
           if (it->second->isPublic())
           {
             oss << iendl;
             it->second->generateFortranInterfaceGetDeclaration_(oss, className);
           }
         }

         for (it = begin; it != end; it++)
         {
           if (it->second->isPublic())
           {
             oss << std::endl << iendl;
             it->second->generateFortranInterfaceGetBody_(oss, className);
           }
         }

         oss << std::endl << (iendl -= 2);
         oss << "END SUBROUTINE xios(get_" << className << "_attr_hdl_)" << std::endl;
      }

      void CAttributeMap::generateFortranInterfaceIsDefined_hdl_(ostream& oss, const string& className)
      {
         oss << "SUBROUTINE xios(is_defined_" << className << "_attr_hdl_)   &" << iendl++;
         SuperClassMap::const_iterator it;
         SuperClassMap::const_iterator begin = SuperClassMap::begin(), end = SuperClassMap::end();

         long startPos = oss.tellp();

         oss << "( " << className << "_hdl";
         for (it = begin; it != end; it++)
         {
           if (it->second->isPublic())
           {
             oss << ", " << it->second->getName() << "_";
             if (oss.tellp() - startPos > 90)
             {
               oss << "  &" << iendl;
               startPos = oss.tellp();
             }
           }
         }
         oss << " )";
         oss << std::endl;
         oss << iendl;

         oss << "IMPLICIT NONE" << iendl++;
         oss << "TYPE(txios(" << className << ")) , INTENT(IN) :: " << className << "_hdl";

         for (it = begin; it != end; it++)
         {
           if (it->second->isPublic())
           {
             oss << iendl;
             it->second->generateFortranInterfaceIsDefinedDeclaration_(oss, className);
           }
         }

         for (it = begin; it != end; it++)
         {
           if (it->second->isPublic())
           {
             oss << std::endl << iendl;
             it->second->generateFortranInterfaceIsDefinedBody_(oss, className);
           }
         }

         oss << std::endl << (iendl -= 2);
         oss << "END SUBROUTINE xios(is_defined_" << className << "_attr_hdl_)" << std::endl;
      }

      void CAttributeMap::generateFortranInterface_hdl(ostream& oss, const string& className)
      {
         oss << "SUBROUTINE xios(set_" << className << "_attr_hdl)  &" << iendl++;
         SuperClassMap::const_iterator it;
         SuperClassMap::const_iterator begin = SuperClassMap::begin(), end = SuperClassMap::end();

         long startPos = oss.tellp();

         oss << "( " << className << "_hdl";
         for (it = begin; it != end; it++)
         {
           if (it->second->isPublic())
           {
             oss << ", " << it->second->getName();
             if (oss.tellp() - startPos > 90)
             {
               oss << "  &" << iendl;
               startPos = oss.tellp();
             }
           }
         }
         oss << " )";
         oss << std::endl;
         oss << iendl;

         oss << "IMPLICIT NONE" << iendl++;
         oss << "TYPE(txios(" << className << ")) , INTENT(IN) :: " << className << "_hdl";

         for (it = begin; it != end; it++)
         {
           if (it->second->isPublic())
           {
             oss << iendl;
             it->second->generateFortranInterfaceDeclaration(oss, className);
           }
         }

         oss << std::endl << iendl;

         oss << "CALL xios(set_" << className << "_attr_hdl_)  &" << iendl;

         startPos = oss.tellp();

         oss << "( " << className << "_hdl";
         for (it = begin; it != end; it++)
         {
           if (it->second->isPublic())
           {
             oss << ", " << it->second->getName();
             if (oss.tellp() - startPos > 90)
             {
               oss << "  &" << iendl;
               startPos = oss.tellp();
             }
           }
         }
         oss << " )";

         oss << std::endl << (iendl -= 2);
         oss << "END SUBROUTINE xios(set_" << className << "_attr_hdl)" << std::endl;
      }

      void CAttributeMap::generateFortranInterfaceGet_hdl(ostream& oss, const string& className)
      {
         oss << "SUBROUTINE xios(get_" << className << "_attr_hdl)  &" << iendl++;
         SuperClassMap::const_iterator it;
         SuperClassMap::const_iterator begin = SuperClassMap::begin(), end = SuperClassMap::end();

         long startPos = oss.tellp();

         oss << "( " << className << "_hdl";
         for (it = begin; it != end; it++)
         {
           if (it->second->isPublic())
           {
             oss << ", " << it->second->getName();
             if (oss.tellp() - startPos > 90)
             {
               oss << "  &" << iendl;
               startPos = oss.tellp();
             }
           }
         }
         oss << " )";
         oss << std::endl;
         oss << iendl;

         oss << "IMPLICIT NONE" << iendl++;
         oss << "TYPE(txios(" << className << ")) , INTENT(IN) :: " << className << "_hdl";

         for (it = begin; it != end; it++)
         {
           if (it->second->isPublic())
           {
             oss << iendl;
             it->second->generateFortranInterfaceGetDeclaration(oss, className);
           }
         }

         oss << std::endl << iendl;

         oss << "CALL xios(get_" << className << "_attr_hdl_)  &" << iendl;

         startPos = oss.tellp();

         oss << "( " << className << "_hdl";
         for (it = begin; it != end; it++)
         {
           if (it->second->isPublic())
           {
             oss << ", " << it->second->getName();
             if (oss.tellp() - startPos > 90)
             {
               oss << "  &" << iendl;
               startPos = oss.tellp();
             }
           }
         }
         oss << " )";

         oss << std::endl << (iendl -= 2);
         oss << "END SUBROUTINE xios(get_" << className << "_attr_hdl)" << std::endl;
      }

      void CAttributeMap::generateFortranInterfaceIsDefined_hdl(ostream& oss, const string& className)
      {
         oss << "SUBROUTINE xios(is_defined_" << className << "_attr_hdl)  &" << iendl++;
         SuperClassMap::const_iterator it;
         SuperClassMap::const_iterator begin = SuperClassMap::begin(), end = SuperClassMap::end();

         long startPos = oss.tellp();

         oss << "( " << className << "_hdl";
         for (it = begin; it != end; it++)
         {
           if (it->second->isPublic())
           {
             oss << ", " << it->second->getName();
             if (oss.tellp() - startPos > 90)
             {
               oss << "  &" << iendl;
               startPos = oss.tellp();
             }
           }
         }
         oss << " )";
         oss << std::endl;
         oss << iendl;

         oss << "IMPLICIT NONE" << iendl++;
         oss << "TYPE(txios(" << className << ")) , INTENT(IN) :: " << className << "_hdl";

         for (it = begin; it != end; it++)
         {
           if (it->second->isPublic())
           {
             oss << iendl;
             it->second->generateFortranInterfaceIsDefinedDeclaration(oss, className);
           }
         }

         oss << std::endl << iendl;

         oss << "CALL xios(is_defined_" << className << "_attr_hdl_)  &" << iendl;

         startPos = oss.tellp();

         oss << "( " << className << "_hdl";
         for (it = begin; it != end; it++)
         {
           if (it->second->isPublic())
           {
             oss << ", " << it->second->getName();
             if (oss.tellp() - startPos > 90)
             {
               oss << "  &" << iendl;
               startPos = oss.tellp();
             }
           }
         }
         oss << " )";

         oss << std::endl << (iendl -= 2);
         oss << "END SUBROUTINE xios(is_defined_" << className << "_attr_hdl)" << std::endl;
      }

      void CAttributeMap::generateFortranInterface_id(ostream& oss, const string& className)
      {
         oss << "SUBROUTINE xios(set_" << className << "_attr)  &" << iendl++;
         SuperClassMap::const_iterator it;
         SuperClassMap::const_iterator begin = SuperClassMap::begin(), end = SuperClassMap::end();

         long startPos = oss.tellp();

         oss << "( " << className << "_id";
         for (it = begin; it != end; it++)
         {
           if (it->second->isPublic())
           {
             oss << ", " << it->second->getName();
             if (oss.tellp() - startPos > 90)
             {
               oss << "  &" << iendl;
               startPos = oss.tellp();
             }
           }
         }
         oss << " )";
         oss << std::endl;
         oss << iendl;

         oss << "IMPLICIT NONE" << iendl++;

         oss << "TYPE(txios(" << className << "))  :: " << className << "_hdl" << iendl;
         oss << "CHARACTER(LEN=*), INTENT(IN) ::" << className << "_id";

         for (it = begin; it != end; it++)
         {
           if (it->second->isPublic())
           {
             oss << iendl;
             it->second->generateFortranInterfaceDeclaration(oss, className);
           }
         }

         oss << std::endl << iendl;
         oss << "CALL xios(get_" << className << "_handle) &" << iendl;
         oss << "(" << className << "_id," << className << "_hdl)" << iendl;
         oss << "CALL xios(set_" << className << "_attr_hdl_)   &" << iendl;

         startPos = oss.tellp();

         oss << "( " << className << "_hdl";
         for (it = begin; it != end; it++)
         {
           if (it->second->isPublic())
           {
             oss << ", " << it->second->getName();
             if (oss.tellp() - startPos > 90)
             {
               oss << "  &" << iendl;
               startPos = oss.tellp();
             }
           }
         }
         oss << " )";

         oss << std::endl << (iendl -= 2);
         oss << "END SUBROUTINE xios(set_" << className << "_attr)" << std::endl;
      }

      void CAttributeMap::generateFortranInterfaceGet_id(ostream& oss, const string& className)
      {
         oss << "SUBROUTINE xios(get_" << className << "_attr)  &" << iendl++;
         SuperClassMap::const_iterator it;
         SuperClassMap::const_iterator begin = SuperClassMap::begin(), end = SuperClassMap::end();

         long startPos = oss.tellp();

         oss << "( " << className << "_id";
         for (it = begin; it != end; it++)
         {
           if (it->second->isPublic())
           {
             oss << ", " << it->second->getName();
             if (oss.tellp() - startPos > 90)
             {
               oss << "  &" << iendl;
               startPos = oss.tellp();
             }
           }
         }
         oss << " )";
         oss << std::endl;
         oss << iendl;

         oss << "IMPLICIT NONE" << iendl++;

         oss << "TYPE(txios(" << className << "))  :: " << className << "_hdl" << iendl;
         oss << "CHARACTER(LEN=*), INTENT(IN) ::" << className << "_id";

         for (it = begin; it != end; it++)
         {
           if (it->second->isPublic())
           {
             oss << iendl;
             it->second->generateFortranInterfaceGetDeclaration(oss, className);
           }
         }

         oss << std::endl << iendl;
         oss << "CALL xios(get_" << className << "_handle) &" << iendl;
         oss << "(" << className << "_id," << className << "_hdl)" << iendl;
         oss << "CALL xios(get_" << className << "_attr_hdl_)   &" << iendl;

         startPos = oss.tellp();

         oss << "( " << className << "_hdl";
         for (it = begin; it != end; it++)
         {
           if (it->second->isPublic())
           {
             oss << ", " << it->second->getName();
             if (oss.tellp() - startPos > 90)
             {
               oss << "  &" << iendl;
               startPos = oss.tellp();
             }
           }
         }
         oss << " )";

         oss << std::endl << (iendl -= 2);
         oss << "END SUBROUTINE xios(get_" << className << "_attr)" << std::endl;
      }

      void CAttributeMap::generateFortranInterfaceIsDefined_id(ostream& oss, const string& className)
      {
         oss << "SUBROUTINE xios(is_defined_" << className << "_attr)  &" << iendl++;
         SuperClassMap::const_iterator it;
         SuperClassMap::const_iterator begin = SuperClassMap::begin(), end = SuperClassMap::end();

         long startPos = oss.tellp();

         oss << "( " << className << "_id";
         for (it = begin; it != end; it++)
         {
           if (it->second->isPublic())
           {
             oss << ", " << it->second->getName();
             if (oss.tellp() - startPos > 90)
             {
               oss << "  &" << iendl;
               startPos = oss.tellp();
             }
           }
         }
         oss << " )";
         oss << std::endl;
         oss << iendl;

         oss << "IMPLICIT NONE" << iendl++;

         oss << "TYPE(txios(" << className << "))  :: " << className << "_hdl" << iendl;
         oss << "CHARACTER(LEN=*), INTENT(IN) ::" << className << "_id";

         for (it = begin; it != end; it++)
         {
           if (it->second->isPublic())
           {
             oss << iendl;
             it->second->generateFortranInterfaceIsDefinedDeclaration(oss, className);
           }
         }

         oss << std::endl << iendl;
         oss << "CALL xios(get_" << className << "_handle) &" << iendl;
         oss << "(" << className << "_id," << className << "_hdl)" << iendl;
         oss << "CALL xios(is_defined_" << className << "_attr_hdl_)   &" << iendl;

         startPos = oss.tellp();

         oss << "( " << className << "_hdl";
         for (it = begin; it != end; it++)
         {
           if (it->second->isPublic())
           {
             oss << ", " << it->second->getName();
             if (oss.tellp() - startPos > 90)
             {
               oss << "  &" << iendl;
               startPos = oss.tellp();
             }
           }
         }
         oss << " )";

         oss << std::endl << (iendl -= 2);
         oss << "END SUBROUTINE xios(is_defined_" << className << "_attr)" << std::endl;
      }
} // namespace xios
