/* ************************************************************************** *
 *      Copyright © IPSL/LSCE, xios, Avril 2010 - Octobre 2011         *
 * ************************************************************************** */

#include <boost/multi_array.hpp>
#include <memory>
#include <string>
#include <cstring>
#include <iostream>


#include "xios.hpp"
#include "oasis_cinterface.hpp"

#include "attribute_template.hpp"
#include "object_template.hpp"
#include "group_template.hpp"

#include "icutil.hpp"
#include "cxios.hpp"
#include "client.hpp"
#include "field.hpp"
#include "context.hpp"
#include "context_client.hpp"
#include "mpi.hpp"
#include "timer.hpp"
#include "array_new.hpp"


extern "C"
{
// /////////////////////////////// Définitions ////////////////////////////// //

   // ----------------------- Redéfinition de types ----------------------------

   typedef enum { NETCDF4 = 0 } XFileType;

   typedef xios::CContext* XContextPtr;

   // -------------------- Traitement des données ------------------------------

   // This function is not exported to the public Fortran interface,
   // it is only used from the parse_xml.exe standalone test tool.
   void cxios_init(void)
   TRY
   {
     CXios::initialize();
   }
   CATCH_DUMP_STACK

   void cxios_init_server(void)
   TRY
   {
     CXios::initServerSide();
   }
   CATCH_DUMP_STACK

   void cxios_init_client(const char* client_id , int len_client_id, MPI_Fint* f_local_comm, MPI_Fint* f_return_comm )
   TRY
   {
      std::string str;
      MPI_Comm local_comm;
      MPI_Comm return_comm;

      if (!cstr2string(client_id, len_client_id, str)) return;

      int initialized;
      MPI_Initialized(&initialized);
      if (initialized) local_comm=MPI_Comm_f2c(*f_local_comm);
      else local_comm=MPI_COMM_NULL;
      CXios::initClientSide(str, local_comm, return_comm);
      *f_return_comm=MPI_Comm_c2f(return_comm);
      CTimer::get("XIOS init").suspend();
      CTimer::get("XIOS").suspend();
   }
   CATCH_DUMP_STACK

   void cxios_context_initialize(const char* context_id , int len_context_id, MPI_Fint* f_comm)
   TRY
   {
     std::string str;
     MPI_Comm comm;

     if (!cstr2string(context_id, len_context_id, str)) return;
     CTimer::get("XIOS").resume();
     CTimer::get("XIOS init context").resume();
     comm=MPI_Comm_f2c(*f_comm);
     CClient::registerContext(str, comm);
     CTimer::get("XIOS init context").suspend();
     CTimer::get("XIOS").suspend();
   }
   CATCH_DUMP_STACK

   void cxios_oasis_enddef()
   TRY
   {
     CTimer::get("XIOS").resume();
     CClient::callOasisEnddef();
     CTimer::get("XIOS").suspend();
   }
   CATCH_DUMP_STACK

   void cxios_context_is_initialized(const char* context_id , int len_context_id, bool* initialized)
   TRY
   {
     std::string str;

     if (!cstr2string(context_id, len_context_id, str)) return;
     CTimer::get("XIOS").resume();
     CContext* context = CContext::get(str, str);
     *initialized=context->isInitialized();
     CTimer::get("XIOS").suspend();
   }
   CATCH_DUMP_STACK

   void cxios_context_close_definition()
   TRY
   {
     CTimer::get("XIOS").resume();
     CTimer::get("XIOS close definition").resume();
     CContext* context = CContext::getCurrent();
     context->closeDefinition();
     CTimer::get("XIOS close definition").suspend();
     CTimer::get("XIOS").suspend();
   }
   CATCH_DUMP_STACK

   void cxios_context_finalize()
   TRY
   {
     CTimer::get("XIOS").resume();
     CTimer::get("XIOS context finalize").resume();
     CContext* context = CContext::getCurrent();
     context->finalize();
     CTimer::get("XIOS context finalize").suspend();
     CTimer::get("XIOS").suspend();
   }
   CATCH_DUMP_STACK

   void cxios_finalize()
   TRY
   {
     CTimer::get("XIOS").resume();
     CTimer::get("XIOS finalize").resume();
     CXios::clientFinalize();
   }
   CATCH_DUMP_STACK

   void cxios_solve_inheritance()
   TRY
   {
     CTimer::get("XIOS").resume();
     CContext* context = CContext::getCurrent();
     context->solveAllInheritance(false);
     CTimer::get("XIOS").suspend();
   }
   CATCH_DUMP_STACK

   /*! \brief This group of functions retrieve variable information from the configuration file (.xml)
    *
    * These functions provide intermediate C interfaces to get variable information of the configuration file (e.x iodef.xml),
    * from a Fortran one, for example the value of a variable with id = "using_server".
    * Each function corresponds to each basic type.
    * \param varId        [in] id of the variable that we'd like to get
    * \param varIdSize    [in] size of the variable type (integer, float, double, string)
    * \param dataInt      [in/out] the retrieved data
    * \param isVarExisted [in/out] Verify whether variable with varId exists
   */
   void cxios_get_variable_data_k8(const char* varId, int varIdSize, double* data, bool* isVarExisted)
   TRY
   {
      std::string varIdStr;
      if (!cstr2string(varId, varIdSize, varIdStr)) return;

      CTimer::get("XIOS").resume();
      CTimer::get("XIOS get variable data").resume();

      CContext* context = CContext::getCurrent();
      *isVarExisted = CVariable::has(context->getId(), varIdStr);

      if (*isVarExisted)
      {
        *data = CVariable::get(context->getId(), varIdStr)->getData<double>();
      }

      CTimer::get("XIOS get variable data").suspend();
      CTimer::get("XIOS").suspend();
   }
   CATCH_DUMP_STACK

   void cxios_get_variable_data_k4(const char* varId, int varIdSize, float* data, bool* isVarExisted)
   TRY
   {
      std::string varIdStr;
      if (!cstr2string(varId, varIdSize, varIdStr)) return;

      CTimer::get("XIOS").resume();
      CTimer::get("XIOS get variable data").resume();

      CContext* context = CContext::getCurrent();
      *isVarExisted = CVariable::has(context->getId(), varIdStr);

      if (*isVarExisted)
      {
        *data = CVariable::get(context->getId(), varIdStr)->getData<float>();
      }

      CTimer::get("XIOS get variable data").suspend();
      CTimer::get("XIOS").suspend();
   }
   CATCH_DUMP_STACK

   void cxios_get_variable_data_int(const char* varId, int varIdSize, int* data, bool* isVarExisted)
   TRY
   {
      std::string varIdStr;
      if (!cstr2string(varId, varIdSize, varIdStr)) return;

      CTimer::get("XIOS").resume();
      CTimer::get("XIOS get variable data").resume();

      CContext* context = CContext::getCurrent();
      *isVarExisted = CVariable::has(context->getId(), varIdStr);

      if (*isVarExisted)
      {
        *data = CVariable::get(context->getId(), varIdStr)->getData<int>();
      }

      CTimer::get("XIOS get variable data").suspend();
      CTimer::get("XIOS").suspend();
   }
   CATCH_DUMP_STACK

   void cxios_get_variable_data_logic(const char* varId, int varIdSize, bool* data, bool* isVarExisted)
   TRY
   {
      std::string varIdStr;
      if (!cstr2string(varId, varIdSize, varIdStr)) return;

      CTimer::get("XIOS").resume();
      CTimer::get("XIOS get variable data").resume();

      CContext* context = CContext::getCurrent();
      *isVarExisted = CVariable::has(context->getId(), varIdStr);

      if (*isVarExisted)
      {
        *data = CVariable::get(context->getId(), varIdStr)->getData<bool>();
      }

      CTimer::get("XIOS get variable data").suspend();
      CTimer::get("XIOS").suspend();
   }
   CATCH_DUMP_STACK

   void cxios_get_variable_data_char(const char* varId, int varIdSize, char* data, int dataSizeIn, bool* isVarExisted)
   TRY
   {
      std::string varIdStr;
      if (!cstr2string(varId, varIdSize, varIdStr)) return;

      CTimer::get("XIOS").resume();
      CTimer::get("XIOS get variable data").resume();

      CContext* context = CContext::getCurrent();
      *isVarExisted = CVariable::has(context->getId(), varIdStr);

      if (*isVarExisted)
      {
        int dataSizeOut = CVariable::get(context->getId(), varIdStr)->getData<string>().length();
        strncpy(data, CVariable::get(context->getId(), varIdStr)->getData<string>().c_str(), std::min(dataSizeIn, dataSizeOut));
      }

      CTimer::get("XIOS get variable data").suspend();
      CTimer::get("XIOS").suspend();
   }
   CATCH_DUMP_STACK

   /*! \brief This group of functions write information into existing variable in the configuration file (.xml)
    *
    *  These functions provide intermediate C interfaces to get variable information of the configuration file (e.x iodef.xml),
    * from a Fortran one, for example the value of a variable with id = "using_server".
    * Each function corresponds to each basic type.
    * \param varId        [in] id of the variable that we'd like to get
    * \param varIdSize    [in] size of the variable type (integer, float, double, string)
    * \param data         [in] the input data
    * \param isVarExisted [in/out] Verify whether variable with varId exists
   */
   void cxios_set_variable_data_k8(const char* varId, int varIdSize, double data, bool* isVarExisted)
   TRY
  {
      std::string varIdStr;
      if (!cstr2string(varId, varIdSize, varIdStr)) return;

      CTimer::get("XIOS").resume();
      CTimer::get("XIOS set variable data").resume();

      CContext* context = CContext::getCurrent();
      *isVarExisted = CVariable::has(context->getId(), varIdStr);

      if (*isVarExisted)
      {
        CVariable::get(context->getId(), varIdStr)->setData<double>(data);
        //CVariable::get(context->getId(), varIdStr)->sendValue();
      }

      CTimer::get("XIOS set variable data").suspend();
      CTimer::get("XIOS").suspend();
   }
   CATCH_DUMP_STACK

   void cxios_set_variable_data_k4(const char* varId, int varIdSize, float data, bool* isVarExisted)
   TRY
   {
      std::string varIdStr;
      if (!cstr2string(varId, varIdSize, varIdStr)) return;

      CTimer::get("XIOS").resume();
      CTimer::get("XIOS set variable data").resume();

      CContext* context = CContext::getCurrent();
      *isVarExisted = CVariable::has(context->getId(), varIdStr);

      if (*isVarExisted)
      {
        CVariable::get(context->getId(), varIdStr)->setData<float>(data);
        //CVariable::get(context->getId(), varIdStr)->sendValue();
      }

      CTimer::get("XIOS set variable data").suspend();
      CTimer::get("XIOS").suspend();
   }
   CATCH_DUMP_STACK

   void cxios_set_variable_data_int(const char* varId, int varIdSize, int data, bool* isVarExisted)
   TRY
   {
      std::string varIdStr;
      if (!cstr2string(varId, varIdSize, varIdStr)) return;

      CTimer::get("XIOS").resume();
      CTimer::get("XIOS set variable data").resume();

      CContext* context = CContext::getCurrent();
      *isVarExisted = CVariable::has(context->getId(), varIdStr);

      if (*isVarExisted)
      {
        CVariable::get(context->getId(), varIdStr)->setData<int>(data);
        //CVariable::get(context->getId(), varIdStr)->sendValue();
      }


      CTimer::get("XIOS set variable data").suspend();
      CTimer::get("XIOS").suspend();
   }
   CATCH_DUMP_STACK

   void cxios_set_variable_data_logic(const char* varId, int varIdSize, bool data, bool* isVarExisted)
   TRY
   {
      std::string varIdStr;
      if (!cstr2string(varId, varIdSize, varIdStr)) return;

      CTimer::get("XIOS").resume();
      CTimer::get("XIOS set variable data").resume();

      CContext* context = CContext::getCurrent();
      *isVarExisted = CVariable::has(context->getId(), varIdStr);

      if (*isVarExisted)
      {
        CVariable::get(context->getId(), varIdStr)->setData<bool>(data);
        //CVariable::get(context->getId(), varIdStr)->sendValue();
      }

      CTimer::get("XIOS set variable data").suspend();
      CTimer::get("XIOS").suspend();
   }
   CATCH_DUMP_STACK

   void cxios_set_variable_data_char(const char* varId, int varIdSize, const char* data, int dataSizeIn, bool* isVarExisted)
   TRY
  {
      std::string varIdStr, dataStr;
      if (!cstr2string(varId, varIdSize, varIdStr)) return;
      if (!cstr2string(data, dataSizeIn, dataStr))
      {
        *isVarExisted = false;
        return;
      }

      CTimer::get("XIOS").resume();
      CTimer::get("XIOS set variable data").resume();

      CContext* context = CContext::getCurrent();
      *isVarExisted = CVariable::has(context->getId(), varIdStr);

      if (*isVarExisted)
      {
        CVariable::get(context->getId(), varIdStr)->setData<string>(dataStr);
        //CVariable::get(context->getId(), varIdStr)->sendValue();
      }

      CTimer::get("XIOS set variable data").suspend();
      CTimer::get("XIOS").suspend();
   }
   CATCH_DUMP_STACK

   // ---------------------- Ecriture des données ------------------------------
   
   void cxios_write_data_k80_hdl(CField* field, double* data_k8, int data_Xsize)
   TRY
   {
      CTimer::get("XIOS").resume();
      CTimer::get("XIOS send field").resume();
      CContext* context = CContext::getCurrent();
      if (!context->hasServer && !context->client->isAttachedModeEnabled())
        context->checkBuffersAndListen();
      CArray<double, 1> data(data_k8, shape(data_Xsize), neverDeleteData);
      field->setData(data);
      CTimer::get("XIOS send field").suspend();
      CTimer::get("XIOS").suspend();
   }
   CATCH_DUMP_STACK

   void cxios_write_data_k80(const char* fieldid, int fieldid_size, double* data_k8, int data_Xsize)
   TRY
   {
      std::string fieldid_str;
      if (!cstr2string(fieldid, fieldid_size, fieldid_str)) return;
      cxios_write_data_k80_hdl(CField::get(fieldid_str), data_k8, data_Xsize) ;
   }
   CATCH_DUMP_STACK



  
   void cxios_write_data_k81_hdl(CField* field, double* data_k8, int data_Xsize, int tileid)
   TRY
   {
      CTimer::get("XIOS").resume();
      CTimer::get("XIOS send field").resume();

      CContext* context = CContext::getCurrent();
      if (!context->hasServer && !context->client->isAttachedModeEnabled())
        context->checkBuffersAndListen();

      CArray<double, 1> data(data_k8, shape(data_Xsize), neverDeleteData);
      field->setData(data, tileid);

      CTimer::get("XIOS send field").suspend();
      CTimer::get("XIOS").suspend();
   }
   CATCH_DUMP_STACK
   
   void cxios_write_data_k81(const char* fieldid, int fieldid_size, double* data_k8, int data_Xsize, int tileid)
   TRY
   {
      std::string fieldid_str;
      if (!cstr2string(fieldid, fieldid_size, fieldid_str)) return;
      cxios_write_data_k81_hdl(CField::get(fieldid_str), data_k8, data_Xsize, tileid) ;
    
   }
   CATCH_DUMP_STACK



   void cxios_write_data_k82_hdl(CField* field, double* data_k8, int data_Xsize, int data_Ysize, int tileid)
   TRY
   {
      CTimer::get("XIOS").resume();
      CTimer::get("XIOS send field").resume();

      CContext* context = CContext::getCurrent();
      if (!context->hasServer && !context->client->isAttachedModeEnabled())
        context->checkBuffersAndListen();

      CArray<double, 2>data(data_k8, shape(data_Xsize, data_Ysize), neverDeleteData);
      field->setData(data, tileid);

      CTimer::get("XIOS send field").suspend();
      CTimer::get("XIOS").suspend();
   }
   CATCH_DUMP_STACK

   void cxios_write_data_k82(const char* fieldid, int fieldid_size, double* data_k8, int data_Xsize, int data_Ysize, int tileid)
   TRY
   {
      std::string fieldid_str;
      if (!cstr2string(fieldid, fieldid_size, fieldid_str)) return;
      cxios_write_data_k82_hdl(CField::get(fieldid_str), data_k8, data_Xsize, data_Ysize, tileid) ;
   }
   CATCH_DUMP_STACK






   void cxios_write_data_k83_hdl(CField* field, double* data_k8, int data_Xsize, int data_Ysize, int data_Zsize, int tileid)
   TRY
   {
      CTimer::get("XIOS").resume();
      CTimer::get("XIOS send field").resume();

      CContext* context = CContext::getCurrent();
      if (!context->hasServer && !context->client->isAttachedModeEnabled())
        context->checkBuffersAndListen();

      CArray<double, 3>data(data_k8, shape(data_Xsize, data_Ysize, data_Zsize), neverDeleteData);
      field->setData(data, tileid);

      CTimer::get("XIOS send field").suspend();
      CTimer::get("XIOS").suspend();
   }
   CATCH_DUMP_STACK
   
   void cxios_write_data_k83(const char* fieldid, int fieldid_size, double* data_k8, int data_Xsize, int data_Ysize, int data_Zsize, int tileid)
   TRY
   {
      std::string fieldid_str;
      if (!cstr2string(fieldid, fieldid_size, fieldid_str)) return;
      cxios_write_data_k83_hdl(CField::get(fieldid_str), data_k8, data_Xsize, data_Ysize, data_Zsize, tileid) ;


   }
   CATCH_DUMP_STACK






   void cxios_write_data_k84_hdl(CField* field, double* data_k8, int data_0size, int data_1size, int data_2size, int data_3size, int tileid)
   TRY
   {
      CTimer::get("XIOS").resume();
      CTimer::get("XIOS send field").resume();

      CContext* context = CContext::getCurrent();
      if (!context->hasServer && !context->client->isAttachedModeEnabled())
        context->checkBuffersAndListen();

      CArray<double, 4>data(data_k8, shape(data_0size, data_1size, data_2size, data_3size), neverDeleteData);
      field->setData(data, tileid);

      CTimer::get("XIOS send field").suspend();
      CTimer::get("XIOS").suspend();
   }
   CATCH_DUMP_STACK

   void cxios_write_data_k84(const char* fieldid, int fieldid_size, double* data_k8,
                             int data_0size, int data_1size, int data_2size,
                             int data_3size, int tileid)
   TRY
   {
      std::string fieldid_str;
      if (!cstr2string(fieldid, fieldid_size, fieldid_str)) return;

      CTimer::get("XIOS").resume();
      CTimer::get("XIOS send field").resume();
      cxios_write_data_k84_hdl(CField::get(fieldid_str), data_k8, data_0size, data_1size, data_2size, data_3size, tileid) ;
   }
   CATCH_DUMP_STACK



   

   void cxios_write_data_k85_hdl(CField* field, double* data_k8,
                             int data_0size, int data_1size, int data_2size,
                             int data_3size, int data_4size, int tileid)
   TRY
   {
      CTimer::get("XIOS").resume();
      CTimer::get("XIOS send field").resume();

      CContext* context = CContext::getCurrent();
      if (!context->hasServer && !context->client->isAttachedModeEnabled())
        context->checkBuffersAndListen();

      CArray<double, 5>data(data_k8, shape(data_0size, data_1size, data_2size, data_3size, data_4size), neverDeleteData);
      field->setData(data, tileid);

      CTimer::get("XIOS send field").suspend();
      CTimer::get("XIOS").suspend();
   }
   CATCH_DUMP_STACK

   void cxios_write_data_k85(const char* fieldid, int fieldid_size, double* data_k8,
                             int data_0size, int data_1size, int data_2size,
                             int data_3size, int data_4size, int tileid)
   TRY
   {
      std::string fieldid_str;
      if (!cstr2string(fieldid, fieldid_size, fieldid_str)) return;
      cxios_write_data_k85_hdl(CField::get(fieldid_str), data_k8, data_0size, data_1size, data_2size, data_3size, data_4size, tileid) ;

   }
   CATCH_DUMP_STACK



   void cxios_write_data_k86_hdl(CField* field, double* data_k8,
                             int data_0size, int data_1size, int data_2size,
                             int data_3size, int data_4size, int data_5size, int tileid)
   TRY
   {
 
      CTimer::get("XIOS").resume();
      CTimer::get("XIOS send field").resume();

      CContext* context = CContext::getCurrent();
      if (!context->hasServer && !context->client->isAttachedModeEnabled())
        context->checkBuffersAndListen();

      CArray<double, 6>data(data_k8, shape(data_0size, data_1size, data_2size, data_3size, data_4size, data_5size), neverDeleteData);
      field->setData(data, tileid);

      CTimer::get("XIOS send field").suspend();
      CTimer::get("XIOS").suspend();
   }
   CATCH_DUMP_STACK
   
   void cxios_write_data_k86(const char* fieldid, int fieldid_size, double* data_k8,
                             int data_0size, int data_1size, int data_2size,
                             int data_3size, int data_4size, int data_5size, int tileid)
   TRY
   {
      std::string fieldid_str;
      if (!cstr2string(fieldid, fieldid_size, fieldid_str)) return;
      cxios_write_data_k86_hdl(CField::get(fieldid_str), data_k8, data_0size, data_1size, data_2size, data_3size, data_4size, data_5size, tileid) ;

  }
   CATCH_DUMP_STACK
   



   void cxios_write_data_k87_hdl(CField* field, double* data_k8,
                             int data_0size, int data_1size, int data_2size,
                             int data_3size, int data_4size, int data_5size,
                             int data_6size, int tileid)
   TRY
   {
      CTimer::get("XIOS").resume();
      CTimer::get("XIOS send field").resume();

      CContext* context = CContext::getCurrent();
      if (!context->hasServer && !context->client->isAttachedModeEnabled())
        context->checkBuffersAndListen();

      CArray<double, 7>data(data_k8, shape(data_0size, data_1size, data_2size, data_3size, data_4size, data_5size, data_6size), neverDeleteData);
      field->setData(data, tileid);

      CTimer::get("XIOS send field").suspend();
      CTimer::get("XIOS").suspend();
   }
   CATCH_DUMP_STACK
   
   void cxios_write_data_k87(const char* fieldid, int fieldid_size, double* data_k8,
                             int data_0size, int data_1size, int data_2size,
                             int data_3size, int data_4size, int data_5size,
                             int data_6size, int tileid)
   TRY
   {
      std::string fieldid_str;
      if (!cstr2string(fieldid, fieldid_size, fieldid_str)) return;
      cxios_write_data_k87_hdl(CField::get(fieldid_str), data_k8, data_0size, data_1size, data_2size, data_3size, data_4size,
                               data_5size, data_6size, tileid) ;
   }
   CATCH_DUMP_STACK
   




   void cxios_write_data_k40_hdl(CField* field, float* data_k4, int data_Xsize)
   TRY
   {
      CTimer::get("XIOS").resume();
      CTimer::get("XIOS send field").resume();
      CContext* context = CContext::getCurrent();
      if (!context->hasServer && !context->client->isAttachedModeEnabled())
        context->checkBuffersAndListen();

      CArray<float, 1> data_tmp(data_k4, shape(data_Xsize), neverDeleteData);
      CArray<double, 1> data(data_Xsize) ;
      data = data_tmp;
      field->setData(data);
      CTimer::get("XIOS send field").suspend();
      CTimer::get("XIOS").suspend();
   }
   CATCH_DUMP_STACK

   void cxios_write_data_k40(const char* fieldid, int fieldid_size, float* data_k4, int data_Xsize)
   TRY
   {
      std::string fieldid_str;
      if (!cstr2string(fieldid, fieldid_size, fieldid_str)) return;
      cxios_write_data_k40_hdl(CField::get(fieldid_str), data_k4, data_Xsize);

   }
   CATCH_DUMP_STACK
   
   
   void cxios_write_data_k41_hdl(CField* field, float* data_k4, int data_Xsize, int tileid)
   TRY
   {
      CTimer::get("XIOS").resume();
      CTimer::get("XIOS send field").resume();

      CContext* context = CContext::getCurrent();
      if (!context->hasServer && !context->client->isAttachedModeEnabled())
        context->checkBuffersAndListen();

      CArray<float, 1> data_tmp(data_k4, shape(data_Xsize), neverDeleteData);
      CArray<double, 1> data(data_Xsize);
      data = data_tmp;
      field->setData(data, tileid);

      CTimer::get("XIOS send field").suspend();
      CTimer::get("XIOS").suspend();
   }
   CATCH_DUMP_STACK

   void cxios_write_data_k41(const char* fieldid, int fieldid_size, float* data_k4, int data_Xsize, int tileid)
   TRY
   {
      std::string fieldid_str;
      if (!cstr2string(fieldid, fieldid_size, fieldid_str)) return;
      cxios_write_data_k41_hdl(CField::get(fieldid_str), data_k4, data_Xsize, tileid);
   }
   CATCH_DUMP_STACK


   void cxios_write_data_k42_hdl(CField* field, float* data_k4, int data_Xsize, int data_Ysize, int tileid)
   TRY
   {
      CTimer::get("XIOS").resume();
      CTimer::get("XIOS send field").resume();

      CContext* context = CContext::getCurrent();
      if (!context->hasServer && !context->client->isAttachedModeEnabled())
        context->checkBuffersAndListen();

      CArray<float, 2> data_tmp(data_k4, shape(data_Xsize, data_Ysize), neverDeleteData);
      CArray<double, 2> data(data_Xsize, data_Ysize);
      data = data_tmp;
      field->setData(data, tileid);

      CTimer::get("XIOS send field").suspend();
      CTimer::get("XIOS").suspend();
   }
   CATCH_DUMP_STACK

   void cxios_write_data_k42(const char* fieldid, int fieldid_size, float* data_k4, int data_Xsize, int data_Ysize, int tileid)
   TRY
   {
      std::string fieldid_str;
      if (!cstr2string(fieldid, fieldid_size, fieldid_str)) return;
      cxios_write_data_k42_hdl(CField::get(fieldid_str), data_k4, data_Xsize,data_Ysize, tileid);
   }
   CATCH_DUMP_STACK




   void cxios_write_data_k43_hdl(CField* field, float* data_k4, int data_Xsize, int data_Ysize, int data_Zsize, int tileid)
   TRY
   {
      CTimer::get("XIOS").resume();
      CTimer::get("XIOS send field").resume();

      CContext* context = CContext::getCurrent();
      if (!context->hasServer && !context->client->isAttachedModeEnabled())
        context->checkBuffersAndListen();

      CArray<float, 3> data_tmp(data_k4, shape(data_Xsize, data_Ysize, data_Zsize), neverDeleteData);
      CArray<double, 3> data(data_Xsize, data_Ysize, data_Zsize);
      data = data_tmp;
      field->setData(data, tileid);

      CTimer::get("XIOS send field").suspend();
      CTimer::get("XIOS").suspend();
    }
   CATCH_DUMP_STACK
   
   void cxios_write_data_k43(const char* fieldid, int fieldid_size, float* data_k4, int data_Xsize, int data_Ysize, int data_Zsize, int tileid)
   TRY
   {
      std::string fieldid_str;
      if (!cstr2string(fieldid, fieldid_size, fieldid_str)) return;
      cxios_write_data_k43_hdl(CField::get(fieldid_str), data_k4, data_Xsize,data_Ysize, data_Zsize, tileid);
    }
   CATCH_DUMP_STACK
   

   
   void cxios_write_data_k44_hdl(CField* field, float* data_k4,
                             int data_0size, int data_1size, int data_2size,
                             int data_3size, int tileid)
   TRY
   {
      CTimer::get("XIOS").resume();
      CTimer::get("XIOS send field").resume();

      CContext* context = CContext::getCurrent();
      if (!context->hasServer && !context->client->isAttachedModeEnabled())
        context->checkBuffersAndListen();

      CArray<float, 4> data_tmp(data_k4, shape(data_0size, data_1size, data_2size, data_3size), neverDeleteData);
      CArray<double, 4> data(data_0size, data_1size, data_2size, data_3size);
      data = data_tmp;
      field->setData(data, tileid);

      CTimer::get("XIOS send field").suspend();
      CTimer::get("XIOS").suspend();
    }
   CATCH_DUMP_STACK

   void cxios_write_data_k44(const char* fieldid, int fieldid_size, float* data_k4,
                             int data_0size, int data_1size, int data_2size,
                             int data_3size, int tileid)
   TRY
   {
      std::string fieldid_str;
      if (!cstr2string(fieldid, fieldid_size, fieldid_str)) return;
      cxios_write_data_k44_hdl(CField::get(fieldid_str), data_k4, data_0size, data_1size, data_2size, data_3size, tileid) ;
    }
   CATCH_DUMP_STACK




   void cxios_write_data_k45_hdl(CField* field, float* data_k4,
                             int data_0size, int data_1size, int data_2size,
                             int data_3size, int data_4size, int tileid)
   TRY
   {
      CTimer::get("XIOS").resume();
      CTimer::get("XIOS send field").resume();

      CContext* context = CContext::getCurrent();
      if (!context->hasServer && !context->client->isAttachedModeEnabled())
        context->checkBuffersAndListen();

      CArray<float, 5> data_tmp(data_k4, shape(data_0size, data_1size, data_2size, data_3size, data_4size), neverDeleteData);
      CArray<double, 5> data(data_0size, data_1size, data_2size, data_3size, data_4size);
      data = data_tmp;
      field->setData(data, tileid);

      CTimer::get("XIOS send field").suspend();
      CTimer::get("XIOS").suspend();
    }
   CATCH_DUMP_STACK

   void cxios_write_data_k45(const char* fieldid, int fieldid_size, float* data_k4,
                             int data_0size, int data_1size, int data_2size,
                             int data_3size, int data_4size, int tileid)
   TRY
   {
      std::string fieldid_str;
      if (!cstr2string(fieldid, fieldid_size, fieldid_str)) return;
      cxios_write_data_k45_hdl(CField::get(fieldid_str), data_k4, data_0size, data_1size, data_2size, data_3size, data_4size, tileid) ;
    }
   CATCH_DUMP_STACK



   void cxios_write_data_k46_hdl(CField* field, float* data_k4,
                             int data_0size, int data_1size, int data_2size,
                             int data_3size, int data_4size, int data_5size, int tileid)
   TRY
   {
      CTimer::get("XIOS").resume();
      CTimer::get("XIOS send field").resume();

      CContext* context = CContext::getCurrent();
      if (!context->hasServer && !context->client->isAttachedModeEnabled())
        context->checkBuffersAndListen();

      CArray<float, 6> data_tmp(data_k4, shape(data_0size, data_1size, data_2size, data_3size, data_4size, data_5size), neverDeleteData);
      CArray<double, 6> data(data_0size, data_1size, data_2size, data_3size, data_4size, data_5size);
      data = data_tmp;
      field->setData(data, tileid);

      CTimer::get("XIOS send field").suspend();
      CTimer::get("XIOS").suspend();
    }
   CATCH_DUMP_STACK

   void cxios_write_data_k46(const char* fieldid, int fieldid_size, float* data_k4,
                             int data_0size, int data_1size, int data_2size,
                             int data_3size, int data_4size, int data_5size, int tileid)
   TRY
   {
      std::string fieldid_str;
      if (!cstr2string(fieldid, fieldid_size, fieldid_str)) return;
      cxios_write_data_k46_hdl(CField::get(fieldid_str), data_k4, data_0size, data_1size, data_2size, data_3size, data_4size, data_5size, tileid) ;
    }
   CATCH_DUMP_STACK


   void cxios_write_data_k47_hdl(CField* field, float* data_k4,
                             int data_0size, int data_1size, int data_2size,
                             int data_3size, int data_4size, int data_5size,
                             int data_6size, int tileid)
   TRY
   {
      CTimer::get("XIOS").resume();
      CTimer::get("XIOS send field").resume();

      CContext* context = CContext::getCurrent();
      if (!context->hasServer && !context->client->isAttachedModeEnabled())
        context->checkBuffersAndListen();

      CArray<float, 7> data_tmp(data_k4, shape(data_0size, data_1size, data_2size, data_3size, data_4size, data_5size, data_6size), neverDeleteData);
      CArray<double, 7> data(data_0size, data_1size, data_2size, data_3size, data_4size, data_5size, data_6size);
      data = data_tmp;
      field->setData(data, tileid);

      CTimer::get("XIOS send field").suspend();
      CTimer::get("XIOS").suspend();
    }
   CATCH_DUMP_STACK

  void cxios_write_data_k47(const char* fieldid, int fieldid_size, float* data_k4,
                             int data_0size, int data_1size, int data_2size,
                             int data_3size, int data_4size, int data_5size,
                             int data_6size, int tileid)
   TRY
   {
      std::string fieldid_str;
      if (!cstr2string(fieldid, fieldid_size, fieldid_str)) return;
      cxios_write_data_k47_hdl(CField::get(fieldid_str), data_k4, data_0size, data_1size, data_2size, data_3size, data_4size,
                                data_5size, data_6size, tileid) ;
    }
   CATCH_DUMP_STACK


   // ---------------------- Lecture des données ------------------------------

   void cxios_read_data_k80_hdl(CField* field, double* data_k8, int data_Xsize)
   TRY
   {
      CTimer::get("XIOS").resume();
      CTimer::get("XIOS recv field").resume();

      CContext* context = CContext::getCurrent();
      if (!context->hasServer && !context->client->isAttachedModeEnabled())
        context->checkBuffersAndListen();

      CArray<double, 1> data(data_k8, shape(data_Xsize), neverDeleteData);
      field->getData(data);

      CTimer::get("XIOS recv field").suspend();
      CTimer::get("XIOS").suspend();
   }
   CATCH_DUMP_STACK

   void cxios_read_data_k80(const char* fieldid, int fieldid_size, double* data_k8, int data_Xsize)
   TRY
   {
      std::string fieldid_str;
      if (!cstr2string(fieldid, fieldid_size, fieldid_str)) return;
      cxios_read_data_k80_hdl(CField::get(fieldid_str), data_k8, data_Xsize) ;
   }
   CATCH_DUMP_STACK
   
   
   void cxios_read_data_k81_hdl(CField* field, double* data_k8, int data_Xsize)
   TRY
   {
      CTimer::get("XIOS").resume();
      CTimer::get("XIOS recv field").resume();

      CContext* context = CContext::getCurrent();
      if (!context->hasServer && !context->client->isAttachedModeEnabled())
        context->checkBuffersAndListen();

      CArray<double, 1> data(data_k8, shape(data_Xsize), neverDeleteData);
      field->getData(data);

      CTimer::get("XIOS recv field").suspend();
      CTimer::get("XIOS").suspend();
   }
   CATCH_DUMP_STACK

   void cxios_read_data_k81(const char* fieldid, int fieldid_size, double* data_k8, int data_Xsize)
   TRY
   {
      std::string fieldid_str;
      if (!cstr2string(fieldid, fieldid_size, fieldid_str)) return;
      cxios_read_data_k81_hdl(CField::get(fieldid_str), data_k8, data_Xsize) ;
   }
   CATCH_DUMP_STACK

   void cxios_read_data_k82_hdl(CField* field, double* data_k8, int data_Xsize, int data_Ysize)
   TRY
   {
      CTimer::get("XIOS").resume();
      CTimer::get("XIOS recv field").resume();

      CContext* context = CContext::getCurrent();
      if (!context->hasServer && !context->client->isAttachedModeEnabled())
        context->checkBuffersAndListen();

      CArray<double, 2>data(data_k8, shape(data_Xsize, data_Ysize), neverDeleteData);
      field->getData(data);

      CTimer::get("XIOS recv field").suspend();
      CTimer::get("XIOS").suspend();
   }
   CATCH_DUMP_STACK

   void cxios_read_data_k82(const char* fieldid, int fieldid_size, double* data_k8, int data_Xsize, int data_Ysize)
   TRY
   {
      std::string fieldid_str;
      if (!cstr2string(fieldid, fieldid_size, fieldid_str)) return;
      cxios_read_data_k82_hdl(CField::get(fieldid_str), data_k8, data_Xsize, data_Ysize) ;
   }
   CATCH_DUMP_STACK


   void cxios_read_data_k83_hdl(CField* field, double* data_k8, int data_Xsize, int data_Ysize, int data_Zsize)
   TRY
   {
      CTimer::get("XIOS").resume();
      CTimer::get("XIOS recv field").resume();

      CContext* context = CContext::getCurrent();
      if (!context->hasServer && !context->client->isAttachedModeEnabled())
        context->checkBuffersAndListen();

      CArray<double, 3>data(data_k8, shape(data_Xsize, data_Ysize, data_Zsize), neverDeleteData);
      field->getData(data);

      CTimer::get("XIOS recv field").suspend();
      CTimer::get("XIOS").suspend();
   }
   CATCH_DUMP_STACK


   void cxios_read_data_k83(const char* fieldid, int fieldid_size, double* data_k8, int data_Xsize, int data_Ysize, int data_Zsize)
   TRY
   {
      std::string fieldid_str;
      if (!cstr2string(fieldid, fieldid_size, fieldid_str)) return;
      cxios_read_data_k83_hdl(CField::get(fieldid_str), data_k8, data_Xsize, data_Ysize, data_Zsize) ;
   }
   CATCH_DUMP_STACK

   void cxios_read_data_k84_hdl(CField* field, double* data_k8,
                            int data_0size, int data_1size, int data_2size,
                            int data_3size)
   TRY
   {
      CTimer::get("XIOS").resume();
      CTimer::get("XIOS recv field").resume();

      CContext* context = CContext::getCurrent();
      if (!context->hasServer && !context->client->isAttachedModeEnabled())
        context->checkBuffersAndListen();

      CArray<double, 4>data(data_k8, shape(data_0size, data_1size, data_2size, data_3size), neverDeleteData);
      field->getData(data);

      CTimer::get("XIOS recv field").suspend();
      CTimer::get("XIOS").suspend();
   }
   CATCH_DUMP_STACK

   void cxios_read_data_k84(const char* fieldid, int fieldid_size, double* data_k8,
                            int data_0size, int data_1size, int data_2size,
                            int data_3size)
   TRY
   {
      std::string fieldid_str;
      if (!cstr2string(fieldid, fieldid_size, fieldid_str)) return;
      cxios_read_data_k84_hdl(CField::get(fieldid_str), data_k8, data_0size, data_1size, data_2size, data_3size) ;
   }
   CATCH_DUMP_STACK

   void cxios_read_data_k85_hdl(CField* field, double* data_k8,
                            int data_0size, int data_1size, int data_2size,
                            int data_3size, int data_4size)
   TRY
   {
      CTimer::get("XIOS").resume();
      CTimer::get("XIOS recv field").resume();

      CContext* context = CContext::getCurrent();
      if (!context->hasServer && !context->client->isAttachedModeEnabled())
        context->checkBuffersAndListen();

      CArray<double, 5>data(data_k8, shape(data_0size, data_1size, data_2size, data_3size, data_4size), neverDeleteData);
      field->getData(data);

      CTimer::get("XIOS recv field").suspend();
      CTimer::get("XIOS").suspend();
   }
   CATCH_DUMP_STACK

   void cxios_read_data_k85(const char* fieldid, int fieldid_size, double* data_k8,
                            int data_0size, int data_1size, int data_2size,
                            int data_3size, int data_4size)
   TRY
   {
      std::string fieldid_str;
      if (!cstr2string(fieldid, fieldid_size, fieldid_str)) return;
      cxios_read_data_k85_hdl(CField::get(fieldid_str), data_k8, data_0size, data_1size, data_2size, data_3size, data_4size) ;
   }
   CATCH_DUMP_STACK

   void cxios_read_data_k86_hdl(CField* field, double* data_k8,
                            int data_0size, int data_1size, int data_2size,
                            int data_3size, int data_4size, int data_5size)
   TRY
   {
      CTimer::get("XIOS").resume();
      CTimer::get("XIOS recv field").resume();

      CContext* context = CContext::getCurrent();
      if (!context->hasServer && !context->client->isAttachedModeEnabled())
        context->checkBuffersAndListen();

      CArray<double, 6>data(data_k8, shape(data_0size, data_1size, data_2size, data_3size, data_4size, data_5size), neverDeleteData);
      field->getData(data);

      CTimer::get("XIOS recv field").suspend();
      CTimer::get("XIOS").suspend();
   }
   CATCH_DUMP_STACK

   void cxios_read_data_k86(const char* fieldid, int fieldid_size, double* data_k8,
                            int data_0size, int data_1size, int data_2size,
                            int data_3size, int data_4size, int data_5size)
   TRY
   {
      std::string fieldid_str;
      if (!cstr2string(fieldid, fieldid_size, fieldid_str)) return;
      cxios_read_data_k86_hdl(CField::get(fieldid_str), data_k8, data_0size, data_1size, data_2size, data_3size, data_4size, data_5size) ;
   }
   CATCH_DUMP_STACK

   void cxios_read_data_k87_hdl(CField* field, double* data_k8,
                            int data_0size, int data_1size, int data_2size,
                            int data_3size, int data_4size, int data_5size,
                            int data_6size)
   TRY
   {
      CTimer::get("XIOS").resume();
      CTimer::get("XIOS recv field").resume();

      CContext* context = CContext::getCurrent();
      if (!context->hasServer && !context->client->isAttachedModeEnabled())
        context->checkBuffersAndListen();

      CArray<double, 7>data(data_k8, shape(data_0size, data_1size, data_2size, data_3size, data_4size, data_5size, data_6size), neverDeleteData);
      field->getData(data);

      CTimer::get("XIOS recv field").suspend();
      CTimer::get("XIOS").suspend();
   }
   CATCH_DUMP_STACK

   void cxios_read_data_k87(const char* fieldid, int fieldid_size, double* data_k8,
                            int data_0size, int data_1size, int data_2size,
                            int data_3size, int data_4size, int data_5size,
                            int data_6size)
   TRY
   {
      std::string fieldid_str;
      if (!cstr2string(fieldid, fieldid_size, fieldid_str)) return;
      cxios_read_data_k87_hdl(CField::get(fieldid_str), data_k8, data_0size, data_1size, data_2size, data_3size, data_4size, data_5size, data_6size) ;
   }
   CATCH_DUMP_STACK






   void cxios_read_data_k40_hdl(CField* field, float* data_k4, int data_Xsize)
   TRY
   {
      CTimer::get("XIOS").resume();
      CTimer::get("XIOS recv field").resume();

      CContext* context = CContext::getCurrent();
      if (!context->hasServer && !context->client->isAttachedModeEnabled())
        context->checkBuffersAndListen();

      CArray<double, 1> data(data_Xsize);
      field->getData(data);
      CArray<float, 1> data_tmp(data_k4, shape(data_Xsize), neverDeleteData);
      data_tmp = data;

      CTimer::get("XIOS recv field").suspend();
      CTimer::get("XIOS").suspend();
   }
   CATCH_DUMP_STACK

   void cxios_read_data_k40(const char* fieldid, int fieldid_size, float* data_k4, int data_Xsize)
   TRY
   {
      std::string fieldid_str;
      if (!cstr2string(fieldid, fieldid_size, fieldid_str)) return;
      cxios_read_data_k40_hdl(CField::get(fieldid_str), data_k4, data_Xsize) ;
   }
   CATCH_DUMP_STACK



   void cxios_read_data_k41_hdl(CField* field, float* data_k4, int data_Xsize)
   TRY
   {
      CTimer::get("XIOS").resume();
      CTimer::get("XIOS recv field").resume();

      CContext* context = CContext::getCurrent();
      if (!context->hasServer && !context->client->isAttachedModeEnabled())
        context->checkBuffersAndListen();

      CArray<double, 1> data(data_Xsize);
      field->getData(data);
      CArray<float, 1> data_tmp(data_k4, shape(data_Xsize), neverDeleteData);
      data_tmp = data;

      CTimer::get("XIOS recv field").suspend();
      CTimer::get("XIOS").suspend();
   }
   CATCH_DUMP_STACK

   void cxios_read_data_k41(const char* fieldid, int fieldid_size, float* data_k4, int data_Xsize)
   TRY
   {
      std::string fieldid_str;
      if (!cstr2string(fieldid, fieldid_size, fieldid_str)) return;
      cxios_read_data_k41_hdl(CField::get(fieldid_str), data_k4, data_Xsize) ;
   }
   CATCH_DUMP_STACK




   void cxios_read_data_k42_hdl(CField* field, float* data_k4, int data_Xsize, int data_Ysize)
   TRY
   {
      CTimer::get("XIOS").resume();
      CTimer::get("XIOS recv field").resume();

      CContext* context = CContext::getCurrent();
      if (!context->hasServer && !context->client->isAttachedModeEnabled())
        context->checkBuffersAndListen();

      CArray<double, 2> data(data_Xsize, data_Ysize);
      field->getData(data);
      CArray<float, 2> data_tmp(data_k4, shape(data_Xsize, data_Ysize), neverDeleteData);
      data_tmp = data;

      CTimer::get("XIOS recv field").suspend();
      CTimer::get("XIOS").suspend();
   }
   CATCH_DUMP_STACK

   void cxios_read_data_k42(const char* fieldid, int fieldid_size, float* data_k4, int data_Xsize, int data_Ysize)
   TRY
   {
      std::string fieldid_str;
      if (!cstr2string(fieldid, fieldid_size, fieldid_str)) return;
      cxios_read_data_k42_hdl(CField::get(fieldid_str), data_k4, data_Xsize, data_Ysize) ;
   }
   CATCH_DUMP_STACK



   void cxios_read_data_k43_hdl(CField* field, float* data_k4, int data_Xsize, int data_Ysize, int data_Zsize)
   TRY
   {
      CTimer::get("XIOS").resume();
      CTimer::get("XIOS recv field").resume();

      CContext* context = CContext::getCurrent();
      if (!context->hasServer && !context->client->isAttachedModeEnabled())
        context->checkBuffersAndListen();

      CArray<double, 3> data(data_Xsize, data_Ysize, data_Zsize);
      field->getData(data);
      CArray<float, 3> data_tmp(data_k4, shape(data_Xsize, data_Ysize, data_Zsize), neverDeleteData);
      data_tmp = data;

      CTimer::get("XIOS recv field").suspend();
      CTimer::get("XIOS").suspend();
    }
   CATCH_DUMP_STACK

   void cxios_read_data_k43(const char* fieldid, int fieldid_size, float* data_k4, int data_Xsize, int data_Ysize, int data_Zsize)
   TRY
   {
      std::string fieldid_str;
      if (!cstr2string(fieldid, fieldid_size, fieldid_str)) return;
      cxios_read_data_k43_hdl(CField::get(fieldid_str), data_k4,data_Xsize, data_Ysize, data_Zsize) ;
    }
   CATCH_DUMP_STACK


   void cxios_read_data_k44_hdl(CField* field, float* data_k4,
                            int data_0size, int data_1size, int data_2size,
                            int data_3size)
   TRY
   {
      CTimer::get("XIOS").resume();
      CTimer::get("XIOS recv field").resume();

      CContext* context = CContext::getCurrent();
      if (!context->hasServer && !context->client->isAttachedModeEnabled())
        context->checkBuffersAndListen();

      CArray<double, 4> data(data_0size, data_1size, data_2size, data_3size);
      field->getData(data);
      CArray<float, 4> data_tmp(data_k4, shape(data_0size, data_1size, data_2size, data_3size), neverDeleteData);
      data_tmp = data;

      CTimer::get("XIOS recv field").suspend();
      CTimer::get("XIOS").suspend();
    }
   CATCH_DUMP_STACK

   void cxios_read_data_k44(const char* fieldid, int fieldid_size, float* data_k4,
                            int data_0size, int data_1size, int data_2size,
                            int data_3size)
   TRY
   {
      std::string fieldid_str;
      if (!cstr2string(fieldid, fieldid_size, fieldid_str)) return;
      cxios_read_data_k44_hdl(CField::get(fieldid_str), data_k4, data_0size, data_1size, data_2size, data_3size) ;
    }
   CATCH_DUMP_STACK



   void cxios_read_data_k45_hdl(CField* field, float* data_k4,
                            int data_0size, int data_1size, int data_2size,
                            int data_3size, int data_4size)
   TRY
   {
      CTimer::get("XIOS").resume();
      CTimer::get("XIOS recv field").resume();

      CContext* context = CContext::getCurrent();
      if (!context->hasServer && !context->client->isAttachedModeEnabled())
        context->checkBuffersAndListen();

      CArray<double, 5> data(data_0size, data_1size, data_2size, data_3size, data_4size);
      field->getData(data);
      CArray<float, 5> data_tmp(data_k4, shape(data_0size, data_1size, data_2size, data_3size, data_4size), neverDeleteData);
      data_tmp = data;

      CTimer::get("XIOS recv field").suspend();
      CTimer::get("XIOS").suspend();
    }
   CATCH_DUMP_STACK

   void cxios_read_data_k45(const char* fieldid, int fieldid_size, float* data_k4,
                            int data_0size, int data_1size, int data_2size,
                            int data_3size, int data_4size)
   TRY
   {
      std::string fieldid_str;
      if (!cstr2string(fieldid, fieldid_size, fieldid_str)) return;
      cxios_read_data_k45_hdl(CField::get(fieldid_str), data_k4, data_0size, data_1size, data_2size, data_3size, data_4size) ;
    }
   CATCH_DUMP_STACK


   void cxios_read_data_k46_hdl(CField* field, float* data_k4,
                            int data_0size, int data_1size, int data_2size,
                            int data_3size, int data_4size, int data_5size)
   TRY
   {
      CTimer::get("XIOS").resume();
      CTimer::get("XIOS recv field").resume();

      CContext* context = CContext::getCurrent();
      if (!context->hasServer && !context->client->isAttachedModeEnabled())
        context->checkBuffersAndListen();

      CArray<double, 6> data(data_0size, data_1size, data_2size, data_3size, data_4size, data_5size);
      field->getData(data);
      CArray<float, 6> data_tmp(data_k4, shape(data_0size, data_1size, data_2size, data_3size, data_4size, data_5size), neverDeleteData);
      data_tmp = data;

      CTimer::get("XIOS recv field").suspend();
      CTimer::get("XIOS").suspend();
    }
   CATCH_DUMP_STACK

   void cxios_read_data_k46(const char* fieldid, int fieldid_size, float* data_k4,
                            int data_0size, int data_1size, int data_2size,
                            int data_3size, int data_4size, int data_5size)
   TRY
   {
      std::string fieldid_str;
      if (!cstr2string(fieldid, fieldid_size, fieldid_str)) return;
      cxios_read_data_k46_hdl(CField::get(fieldid_str), data_k4, data_0size, data_1size, data_2size, data_3size, data_4size, data_5size) ;
    }
   CATCH_DUMP_STACK



   void cxios_read_data_k47_hdl(CField* field, float* data_k4,
                            int data_0size, int data_1size, int data_2size,
                            int data_3size, int data_4size, int data_5size,
                            int data_6size)
   TRY
   {
      CTimer::get("XIOS").resume();
      CTimer::get("XIOS recv field").resume();

      CContext* context = CContext::getCurrent();
      if (!context->hasServer && !context->client->isAttachedModeEnabled())
        context->checkBuffersAndListen();

      CArray<double, 7> data(data_0size, data_1size, data_2size, data_3size, data_4size, data_5size, data_6size);
      field->getData(data);
      CArray<float, 7> data_tmp(data_k4, shape(data_0size, data_1size, data_2size, data_3size, data_4size, data_5size, data_6size), neverDeleteData);
      data_tmp = data;

      CTimer::get("XIOS recv field").suspend();
      CTimer::get("XIOS").suspend();
    }
   CATCH_DUMP_STACK
 
   void cxios_read_data_k47(const char* fieldid, int fieldid_size, float* data_k4,
                            int data_0size, int data_1size, int data_2size,
                            int data_3size, int data_4size, int data_5size,
                            int data_6size)
   TRY
   {
      std::string fieldid_str;
      if (!cstr2string(fieldid, fieldid_size, fieldid_str)) return;
      cxios_read_data_k47_hdl(CField::get(fieldid_str), data_k4, data_0size, data_1size, data_2size, data_3size, data_4size, data_5size, data_6size) ;
    }
   CATCH_DUMP_STACK

} // extern "C"
