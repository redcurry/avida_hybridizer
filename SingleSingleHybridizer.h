#ifndef SINGLE_SINGLE_HYBRIDIZER_H
#define SINGLE_SINGLE_HYBRIDIZER_H

#include "Hybridizer.h"
#include "Genotype.h"
#include "HybridGenotype.h"

#include <vector>
using namespace std;

class SingleSingleHybridizer : public Hybridizer
{

  public:

    // Returns one random hybrid
    virtual Genotype* createRandomHybrid
      (Genotype const* parent_1, Genotype const* parent_2) const;

  private:

    int vectorRandomChoice(vector<int> const& list) const;

};

#endif
