#ifndef ONE_PIECE_HYBRIDIZER_H
#define ONE_PIECE_HYBRIDIZER_H

#include "Hybridizer.h"
#include "Genotype.h"
#include "HybridGenotype.h"

#include <string>
#include <vector>
using namespace std;

class OnePieceHybridizer : public Hybridizer
{

  public:

    // Returns a random hybrid
    virtual Genotype* createRandomHybrid
      (Genotype const* parent_1, Genotype const* parent_2) const;

    // Returns all possible hybrids
    vector<Genotype*> createAllHybrids
      (Genotype const* parent_1, Genotype const* parent_2) const;

    // Returns the hybrid where parent_2 replaces parent_1 in specified region
    Genotype* createHybrid
      (Genotype const* parent_1, Genotype const* parent_2,
      int start_pos, int size) const;

  private:

    inline string replaceRegion
      (string const& string_1, string const& string_2,
      int start_pos, int size) const
      { return string(string_1).replace
          (start_pos, size, string_2, start_pos, size); }

};

#endif
