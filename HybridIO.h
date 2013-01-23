#ifndef HYBRID_IO_H
#define HYBRID_IO_H

#include "Genotype.h"
#include "HybridGenotype.h"

#include <iostream>
#include <vector>
#include <string>
using namespace std;

class HybridIO
{
  
  public:

    vector<Genotype*> readHybrids(istream& in,
      Genotype*& ancestor, Genotype*& parent_1, Genotype*& parent_2) const;

    void writeHybrids(ostream& out, Genotype const* ancestor,
      Genotype const* parent_1, Genotype const* parent_2,
      vector<Genotype*> const& hybrids) const;

};

#endif
