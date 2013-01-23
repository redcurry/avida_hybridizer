#include "Hybridizer.h"

// Returns n random hybrids
vector<Genotype*> Hybridizer::createRandomHybrids
  (Genotype const* parent_1, Genotype const* parent_2, int n) const
{
  vector<Genotype*> hybrids;

  while(n-- > 0)
  {
    Genotype* hybrid = createRandomHybrid(parent_1, parent_2);
    hybrids.push_back(hybrid);
  }

  return hybrids;
}
