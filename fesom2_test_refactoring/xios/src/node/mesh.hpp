/*!
  \file mesh.hpp
  \author Olga Abramkina
  \brief Declaration of class CMesh.
*/

#ifndef __XIOS_CMesh__
#define __XIOS_CMesh__
 
#include "array_new.hpp"
#include "dht_auto_indexing.hpp"

namespace xios {
  
   /// ////////////////////// Déclarations ////////////////////// ///

   class CMesh;

   ///--------------------------------------------------------------

/*!
  \class CMesh
  \brief CMesh class.
*/ 
  class CMesh
  {
  
    public:

      CMesh(void);
      ~CMesh(void);
    
      int nbNodesGlo;
      int nbEdgesGlo;

      int node_start;
      int node_count;
      int edge_start;
      int edge_count;

      bool nodesAreWritten;
      bool edgesAreWritten;
      bool facesAreWritten;
      
      CArray<double, 1> node_lon;
      CArray<double, 1> node_lat;
      
      CArray<double, 1> edge_lon;
      CArray<double, 1> edge_lat;
      CArray<int, 2> edge_nodes;

      CArray<double, 1> face_lon;
      CArray<double, 1> face_lat;
      CArray<int, 2> face_nodes;
      CArray<int, 2> face_edges;
      CArray<int, 2> edge_faces;
      CArray<int, 2> face_faces;

      void createMesh(const CArray<double, 1>&, const CArray<double, 1>&,
                      const CArray<double, 2>&, const CArray<double, 2>& );
                        
      void createMeshEpsilon(const MPI_Comm&,
                             const CArray<double, 1>&, const CArray<double, 1>&,
                             const CArray<double, 2>&, const CArray<double, 2>& );

      void getGlobalNghbFaces(const int, const MPI_Comm&, const CArray<int, 1>&,
                              const CArray<double, 2>&, const CArray<double, 2>&,
                              CArray<int, 2>&);

      void getLocalNghbFaces(const int, const CArray<int, 1>&,
                             const CArray<double, 2>&, const CArray<double, 2>&,
                             CArray<int, 2>&, CArray<int, 1>&);
            
      static CMesh* getMesh(StdString, int);

    private:

      typedef std::pair<double, double> pairDouble;
      typedef std::pair<int, int> pairInt;

      int nbNodes_;
      int nbEdges_;
      int nbFaces_;

      static std::map <StdString, CMesh> meshList;
      static std::map <StdString, vector<int> > domainList;
      CClientClientDHTSizet* pNodeGlobalIndex;                    // pointer to a map <nodeHash, nodeIdxGlo>
      CClientClientDHTSizet* pEdgeGlobalIndex;                    // pointer to a map <edgeHash, edgeIdxGlo>
      void getGloNghbFacesNodeType(const MPI_Comm&, const CArray<int, 1>&, const CArray<double, 2>&, const CArray<double, 2>&, CArray<int, 2>&);
      void getGloNghbFacesEdgeType(const MPI_Comm&, const CArray<int, 1>&, const CArray<double, 2>&, const CArray<double, 2>&, CArray<int, 2>&);
      void getLocNghbFacesNodeType(const CArray<int, 1>&, const CArray<double, 2>&, const CArray<double, 2>&, CArray<int, 2>&, CArray<int, 1>&);
      void getLocNghbFacesEdgeType(const CArray<int, 1>&, const CArray<double, 2>&, const CArray<double, 2>&, CArray<int, 2>&, CArray<int, 1>&);

      vector<size_t> createHashes (const double, const double);

  }; 

} // namespace xios

#endif //__XIOS_CMesh__
