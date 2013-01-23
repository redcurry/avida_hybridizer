#ifndef SINGLE_ALL_HYBRIDIZER_H
#define SINGLE_ALL_HYBRIDIZER_H

#include "Hybridizer.h"
#include "Genotype.h"
#include "HybridGenotype.h"

#include <vector>
using namespace std;

class SingleAllHybridizer : public Hybridizer
{

  public:

    SingleAllHybridizer(bool allow_replace);

    // Returns a random hybrid
    Genotype* createRandomHybrid
      (Genotype const* parent_1, Genotype const* parent_2) const;

  private:

    int pickParent1Mutation
      (vector<int> const& mutns_1, vector<int> const& mutns_2) const;

    int vectorChoice(vector<int> const& v) const;
    vector<int> vectorDifference
      (vector<int> const& v1, vector<int> const& v2) const;

    bool m_AllowReplace;

};

#endif
