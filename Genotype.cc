#include "Genotype.h"

Genotype::Genotype(string sequence) :
  m_Sequence(sequence),
  m_Fitness(-1.0),
  m_Ancestor(this)
{
}

Genotype::Genotype(string sequence, Genotype const* ancestor) :
  m_Sequence(sequence),
  m_Fitness(-1.0),
  m_Ancestor(ancestor)
{
}

Genotype::Genotype(Genotype const* genotype) :
  m_Sequence(genotype->m_Sequence),
  m_Fitness(genotype->m_Fitness),
  m_Ancestor(genotype->m_Ancestor)
{
}

Genotype::Genotype(Genotype const* genotype, Genotype const* ancestor) :
  m_Sequence(genotype->m_Sequence),
  m_Fitness(genotype->m_Fitness),
  m_Ancestor(ancestor)
{
}

vector<int> Genotype::getMutations() const
{
  vector<int> mutations;

  int length = m_Sequence.length();
  for(int i = 0; i < length; i++)
    if(m_Sequence[i] != m_Ancestor->m_Sequence[i])
      mutations.push_back(i);

  return mutations;
}
