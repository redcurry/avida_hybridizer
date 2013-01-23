#include "SingleAllHybridizer.h"
#include "HybridGenotype.h"

#include <vector>
#include <set>
#include <algorithm>
#include <cstdlib>
#include <ctime>
using namespace std;

SingleAllHybridizer::SingleAllHybridizer(bool allow_replace)
  : m_AllowReplace(allow_replace)
{
}

Genotype* SingleAllHybridizer::createRandomHybrid
  (Genotype const* parent_1, Genotype const* parent_2) const
{
  // Get parental mutations
  vector<int> const& mutns_1 = parent_1->getMutations();
  vector<int> const& mutns_2 = parent_2->getMutations();

  // Pick a random mutation from parent_1
  int pos_1 = pickParent1Mutation(mutns_1, mutns_2);

  // Initialize the hybrid's sequence with parent_2's
  string hybrid_seq(parent_2->getSequence());

  // If no mutation could be picked, return hybrid as is
  if(pos_1 < 0)
    return new HybridGenotype(hybrid_seq, parent_1->getAncestor(),
      parent_1, parent_2, vector<int>(), vector<int>(mutns_2));

  // Introduce parent_1's mutation into hybrid
  hybrid_seq[pos_1] = parent_1->getSequence()[pos_1];

  // Define parental regions
  vector<int> region_1(1, pos_1);
  vector<int> const& region_2 = vectorDifference(mutns_2, region_1);

  return new HybridGenotype(hybrid_seq, parent_1->getAncestor(),
    parent_1, parent_2, region_1, region_2);
}

int SingleAllHybridizer::pickParent1Mutation
  (vector<int> const& mutns_1, vector<int> const& mutns_2) const
{
  if(m_AllowReplace)
  {
    if(mutns_1.empty())
      return -1;
    else
      return vectorChoice(mutns_1);
  }
  else
  {
    // If parent_1 mutations should not replace parent_2 mutations,
    // then remove parent_1 mutations that are also in parent_2
    vector<int> const& valid_mutns_1 = vectorDifference(mutns_1, mutns_2);
    if(valid_mutns_1.empty())
      return -1;
    else
      return vectorChoice(valid_mutns_1);
  }
}

int SingleAllHybridizer::vectorChoice(vector<int> const& v) const
{
  return v[rand() % v.size()];
}

vector<int> SingleAllHybridizer::vectorDifference
  (vector<int> const& v1, vector<int> const& v2) const
{
  vector<int> diff(v1.size());
  vector<int>::iterator diff_end;

  diff_end = set_difference
    (v1.begin(), v1.end(), v2.begin(), v2.end(), diff.begin());

  return vector<int>(diff.begin(), diff_end);
}
