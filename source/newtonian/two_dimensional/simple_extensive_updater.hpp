#ifndef SIMPLE_EXTENSIVE_UPDATER_HPP
#define SIMPLE_EXTENSIVE_UPDATER_HPP 1

#include "extensive_updater.hpp"

class SimpleExtensiveUpdater: public ExtensiveUpdater
{
public:

  void operator()
  (const vector<Extensive>& fluxes,
   const PhysicalGeometry& pg,
   const Tessellation& tess,
   const double dt,
   const CacheData& cd,
   const vector<ComputationalCell>& cells,
   vector<Extensive>& extensives) const;
};

#endif // SIMPLE_EXTENSIVE_UPDATER_HPP
