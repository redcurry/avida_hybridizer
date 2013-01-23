#ifndef HYBRIDIZER_H
#define HYBRIDIZER_H

#include "Genotype.h"

#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;

class Hybridizer
{

  public:

    Hybridizer()
      { srand(time(0)); }

    // Sets the random seed
    void setSeed(int seed)
      { srand(seed); }

    // Returns a random hybrid
    virtual Genotype* createRandomHybrid
      (Genotype const* parent_1, Genotype const* parent_2) const = 0;

    // Returns n random hybrids
    vector<Genotype*> createRandomHybrids
      (Genotype const* parent_1, Genotype const* parent_2, int n) const;

};

#endif
