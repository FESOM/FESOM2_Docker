
#ifndef __FIELD_IMPL_HPP__
#define __FIELD_IMPL_HPP__

#include "xios_spl.hpp"
#include "field.hpp"
#include "context.hpp"
#include "grid.hpp"
#include "timer.hpp"
#include "array_new.hpp"
#include "source_filter.hpp"
#include "store_filter.hpp"


namespace xios {

  template <int N>
  void CField::setData(const CArray<double, N>& _data, int tileid)
  TRY
  {
    if (clientSourceFilter)
    {
      if (check_if_active.isEmpty() || (!check_if_active.isEmpty() && (!check_if_active) || isActive(true)))
      {
	if ( info.getLevel()>100  )
	{
	  const double* array = _data.dataFirst();
	  int numElements( _data.numElements() );
	  checkSumLike( array, numElements, true );
	}
        if (tileid > -1)
          clientSourceFilter->streamTile(CContext::getCurrent()->getCalendar()->getCurrentDate(), _data, tileid); // tiled domain
        else
          clientSourceFilter->streamData(CContext::getCurrent()->getCalendar()->getCurrentDate(), _data);
      }
    }
    else if (instantDataFilter)
      ERROR("void CField::setData(const CArray<double, N>& _data)",
            << "Impossible to receive data from the model for a field [ id = " << getId() << " ] with a reference or an arithmetic operation.");
  }
  CATCH_DUMP_ATTR

  template <int N>
  void CField::getData(CArray<double, N>& _data) const
  TRY
  {
    if (storeFilter)
    {
      CDataPacket::StatusCode status = storeFilter->getData(CContext::getCurrent()->getCalendar()->getCurrentDate(), _data);
      if ( info.getLevel()>100  )
      {
	const double* array = _data.dataFirst();
	int numElements( _data.numElements() );
	checkSumLike( array, numElements, false );
      }

      if (status == CDataPacket::END_OF_STREAM)
        ERROR("void CField::getData(CArray<double, N>& _data) const",
              << "Impossible to access field data, all the records of the field [ id = " << getId() << " ] have been already read.");
    }
    else
    {
      ERROR("void CField::getData(CArray<double, N>& _data) const",
            << "Impossible to access field data, the field [ id = " << getId() << " ] does not have read access.");
    }
  }
  CATCH

  void CField::checkSumLike( const double* array, int numElements, bool output ) const
  {
    int rk = CContext::getCurrent()->client->clientRank;
    int sz = CContext::getCurrent()->client->clientSize;
    MPI_Comm comm = CContext::getCurrent()->client->intraComm;
    
    double localSum( 0. );
    double error( 0. );
    unsigned long long checkSum( 0 );
    for ( int i=0 ; i<numElements ; i++ ) {
      bool contributes( true );      
      if ( (!output) && ( !default_value.isEmpty() ) )
      {
	if ( fabs(array[i]) > 0)
	  if ( fabs(array[i]-default_value.getValue())/array[i] < 2e-16 )
	    contributes = false;
      }
      if (contributes)
      {
        double y = array[i] - error;
        double t = localSum + y;
        error = (t - localSum) - y;
        localSum = t;

        checkSum += *((unsigned long long*)(&array[i]));
        checkSum = checkSum%LLONG_MAX;
      }
    }

    double globalSum( 0. );
    unsigned long long globalCheck( 0 );

    if ( rk ==0 )
    {
      MPI_Status status;
      globalSum = localSum; // rank 0 contribution
      globalCheck = checkSum;
      for ( int irk = 1 ; irk < sz ; irk++ )
      {
    	MPI_Recv( &localSum, 1, MPI_DOUBLE, irk, 0, comm, &status );
    	double y = localSum - error;
    	double t = globalSum + y;
    	error = (t - globalSum) - y;
    	globalSum = t;
    
    	MPI_Recv( &checkSum, 1, MPI_UNSIGNED_LONG_LONG, irk, 1, comm, &status );
        globalCheck += checkSum;
        globalCheck = globalCheck%LLONG_MAX;
      }
    }
    else
    {
      MPI_Send( &localSum, 1, MPI_DOUBLE, 0, 0, comm );
      MPI_Send( &checkSum, 1, MPI_UNSIGNED_LONG_LONG, 0, 1, comm );
    }
    
    if ( rk == 0 )
    {
      info(100) << setprecision(DBL_DIG);
      if (output )
	info(100) << "Check Output key field for : " << getId() << ", key =  " << globalCheck << ", sum = " << globalSum << endl;
      else
	info(100) << "Check Input key field for : " << getId() << ", key =  " << globalCheck << ", sum = " << globalSum << endl;
      info(100) << setprecision(6);
    }
  }
  
} // namespace xios

#endif
