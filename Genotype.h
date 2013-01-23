#ifndef GENOTYPE_H
#define GENOTYPE_H

#include <string>
#include <vector>
#include <ostream>
using namespace std;

class Genotype
{

  public:

    Genotype(string sequence);
    Genotype(string sequence, Genotype const* ancestor);
    Genotype(Genotype const* genotype);
    Genotype(Genotype const* genotype, Genotype const* ancestor);

    inline void setSequence(string sequence)
      { m_Sequence = sequence; }
    inline string const& getSequence() const
      { return m_Sequence; }

    inline void setFitness(double fitness)
      { m_Fitness = fitness; }
    inline double getFitness() const
      { return m_Fitness; }
    inline double calcRelativeFitness() const
      { return m_Fitness / m_Ancestor->m_Fitness; }

    inline void setAncestor(Genotype const* ancestor)
      { m_Ancestor = ancestor; }
    inline Genotype const* getAncestor() const
      { return m_Ancestor; }

    inline int getLength() const
      { return m_Sequence.length(); }

    vector<int> getMutations() const;

    inline void setLocus(int pos, int inst)
      { m_Sequence[pos] = inst; }
    inline char getLocus(int pos) const
      { return m_Sequence[pos]; }

    friend ostream& operator<<(ostream& out, Genotype const* genotype);

  private:

    string m_Sequence;
    double m_Fitness;
    Genotype const* m_Ancestor;

};

inline ostream& operator<<(ostream& out, Genotype const* genotype)
  { return out << genotype->m_Sequence; }

#endif
