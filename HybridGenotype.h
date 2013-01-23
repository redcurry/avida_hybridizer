#ifndef HYBRID_GENOTYPE_H
#define HYBRID_GENOTYPE_H

#include "Genotype.h"

class HybridGenotype : public Genotype
{

  public:

    HybridGenotype(string sequence, Genotype const* ancestor,
      Genotype const* parent1, Genotype const* parent2,
      vector<int> const& parent1Region, vector<int> const& parent2Region);

    inline Genotype const* getParent1() const
      { return m_Parent1; }
    inline Genotype const* getParent2() const
      { return m_Parent2; }

    inline vector<int> const& getParent1Region() const
      { return m_Parent1Region; }
    inline vector<int> const& getParent2Region() const
      { return m_Parent2Region; }

    static void deleteHybrids(vector<Genotype*> const& hybrids);

  private:

    HybridGenotype(string sequence);
    HybridGenotype(string sequence, Genotype* ancestor);

    Genotype const* m_Parent1;
    Genotype const* m_Parent2;

    vector<int> m_Parent1Region;
    vector<int> m_Parent2Region;

};

#endif
