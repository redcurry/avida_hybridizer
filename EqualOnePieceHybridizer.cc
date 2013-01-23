#include "EqualOnePieceHybridizer.h"

// Returns a random hybrid
Genotype* EqualOnePieceHybridizer::createRandomHybrid
  (Genotype const* parent_1, Genotype const* parent_2) const
{
  int length = parent_1->getLength();
  int start_pos = rand() % length;
  int size = length / 2;
  return createHybrid(parent_1, parent_2, start_pos, size);
}

// Returns all possible hybrids
vector<Genotype*> EqualOnePieceHybridizer::createAllHybrids
  (Genotype const* parent_1, Genotype const* parent_2) const
{
  int length = parent_1->getLength();
  vector<Genotype*> hybrids;

  for(int start_pos = 0; start_pos < length; start_pos++)
  {
    int size = length / 2;
    hybrids.push_back(createHybrid(parent_1, parent_2, start_pos, size));
  }

  return hybrids;
}

// Returns a recombinant such that the specified
// region of parent_2 replaces that of parent_1
Genotype* EqualOnePieceHybridizer::createHybrid
  (Genotype const* parent_1, Genotype const* parent_2,
  int start_pos, int size) const
{
  int length = parent_1->getLength();
  Genotype const* ancestor = parent_1->getAncestor();

  vector<int> const& parent_1_mutations = parent_1->getMutations();
  vector<int> const& parent_2_mutations = parent_2->getMutations();

  int n_parent_1_mutations = parent_1_mutations.size();
  int n_parent_2_mutations = parent_2_mutations.size();

  vector<int> parent_1_region;
  vector<int> parent_2_region;

  string hybrid_string;

  // Handle wrap-around
  if(start_pos + size > length)
  {
    start_pos = start_pos - (length - size);
    size = length - size;

    int end_pos = start_pos + size;

    for(int i = 0; i < n_parent_1_mutations; i++)
      if(start_pos <= parent_1_mutations[i] && parent_1_mutations[i] < end_pos)
        parent_1_region.push_back(parent_1_mutations[i]);

    for(int i = 0; i < n_parent_2_mutations; i++)
      if(parent_2_mutations[i] < start_pos || parent_2_mutations[i] >= end_pos)
        parent_2_region.push_back(parent_2_mutations[i]);

    hybrid_string = replaceRegion
      (parent_2->getSequence(), parent_1->getSequence(), start_pos, size);
  }
  else
  {
    int end_pos = start_pos + size;

    for(int i = 0; i < n_parent_2_mutations; i++)
      if(start_pos <= parent_2_mutations[i] && parent_2_mutations[i] < end_pos)
        parent_2_region.push_back(parent_2_mutations[i]);

    for(int i = 0; i < n_parent_1_mutations; i++)
      if(parent_1_mutations[i] < start_pos || parent_1_mutations[i] >= end_pos)
        parent_1_region.push_back(parent_1_mutations[i]);

    hybrid_string = replaceRegion
      (parent_1->getSequence(), parent_2->getSequence(), start_pos, size);
  }

  return new HybridGenotype(hybrid_string, ancestor,
    parent_1, parent_2, parent_1_region, parent_2_region);
}
