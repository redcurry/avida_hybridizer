#include "SingleSingleHybridizer.h"

Genotype* SingleSingleHybridizer::createRandomHybrid
  (Genotype const* parent_1, Genotype const* parent_2) const
{
  string parent_1_seq(parent_1->getSequence());
  string parent_2_seq(parent_2->getSequence());

  // Initialize the hybrid sequence with the ancestor's
  string hybrid_seq(parent_1->getAncestor()->getSequence());

  // Pick a random mutation from parent_1
  vector<int> const& mutns_1 = parent_1->getMutations();
  int pos_1 = vectorRandomChoice(mutns_1);

  // Substitute parent_1 mutation into hybrid
  vector<int> region_1;
  if(pos_1 >= 0)
  {
    hybrid_seq[pos_1] = parent_1_seq[pos_1];
    region_1.push_back(pos_1);
  }

  // Pick a random mutation from parent_2
  vector<int> const& mutns_2 = parent_2->getMutations();
  int pos_2 = vectorRandomChoice(mutns_2);

  // Substitute parent_2 mutation into hybrid
  vector<int> region_2;
  if(pos_2 >= 0)
  {
    hybrid_seq[pos_2] = parent_2_seq[pos_2];
    region_2.push_back(pos_2);
  }

  return new HybridGenotype(hybrid_seq, parent_1->getAncestor(),
    parent_1, parent_2, region_1, region_2);
}

int SingleSingleHybridizer::vectorRandomChoice(vector<int> const& list) const
{
  int n = list.size();

  if(n > 0)
    return list[rand() % n];
  else
    return -1;
}
