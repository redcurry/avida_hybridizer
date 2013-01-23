#include "UnlinkedHybridizer.h"

// Returns a hybrid such that the probability of inheriting
// a mutation from parent_1 or parent_2 is the same
Genotype* UnlinkedHybridizer::createRandomHybrid
  (Genotype const* parent_1, Genotype const* parent_2) const
{
  int length = parent_1->getLength();
  Genotype const* ancestor = parent_1->getAncestor();

  vector<int> const& parent_1_mutations = parent_1->getMutations();
  vector<int> const& parent_2_mutations = parent_2->getMutations();

  int n_parent_1_mutations = parent_1_mutations.size();
  int n_parent_2_mutations = parent_2_mutations.size();

  vector<int> parent_1_region;
  vector<int> parent_2_region;

  string parent_1_str(parent_1->getSequence());
  string parent_2_str(parent_2->getSequence());

  string hybrid_str(ancestor->getSequence());

  for(int i = 0; i < length; i++)
  {
    if(rand() % 2 == 0)
    {
      hybrid_str[i] = parent_1_str[i];
      if(contains(parent_1_mutations, i))
        parent_1_region.push_back(i);
    }
    else
    {
      hybrid_str[i] = parent_2_str[i];
      if(contains(parent_2_mutations, i))
        parent_2_region.push_back(i);
    }
  }

  return new HybridGenotype(hybrid_str, ancestor,
    parent_1, parent_2, parent_1_region, parent_2_region);
}

bool UnlinkedHybridizer::contains(vector<int> const& list, int value) const
{
  int list_size = list.size();
  for(int i = 0; i < list_size; i++)
    if(list[i] == value)
      return true;
  return false;
}
