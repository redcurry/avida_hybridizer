#include "HybridGenotype.h"

HybridGenotype::HybridGenotype(string sequence, Genotype const* ancestor,
  Genotype const* parent1, Genotype const* parent2,
  vector<int> const& parent1Region, vector<int> const& parent2Region) :
  Genotype(sequence, ancestor),
  m_Parent1(parent1), m_Parent2(parent2),
  m_Parent1Region(parent1Region), m_Parent2Region(parent2Region)
{
}

void HybridGenotype::deleteHybrids(vector<Genotype*> const& hybrids)
{
  int n_hybrids = hybrids.size();

  if(n_hybrids == 0)
    return;

  HybridGenotype* first_hybrid = (HybridGenotype*)hybrids[0];
  Genotype const* ancestor = first_hybrid->getAncestor();
  Genotype const* parent_1 = first_hybrid->getParent1();
  Genotype const* parent_2 = first_hybrid->getParent2();

  delete ancestor;
  delete parent_1;
  delete parent_2;

  for(int i = 0; i < n_hybrids; i++)
    delete hybrids[i];
}
