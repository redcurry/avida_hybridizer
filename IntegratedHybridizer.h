#ifndef INTEGRATED_HYBRIDIZER_H
#define INTEGRATED_HYBRIDIZER_H

#include "Hybridizer.h"
#include "Genotype.h"
#include "HybridGenotype.h"

#include <vector>
using namespace std;

class IntegratedHybridizer : public Hybridizer
{

  public:

    // Returns a random hybrid
    virtual Genotype* createRandomHybrid
      (Genotype const* parent_1, Genotype const* parent_2) const;

  private:

    bool contains(vector<int> const& list, int value) const;

};

#endif
