#include "HybridIO.h"
#include "Genotype.h"
#include "HybridGenotype.h"

#include <iostream>
#include <vector>
#include <string>
using namespace std;

vector<Genotype*> HybridIO::readHybrids(istream& in,
  Genotype*& ancestor, Genotype*& parent_1, Genotype*& parent_2) const
{
  // Read the ancestor
  string ancestor_str;
  in >> ancestor_str;
  ancestor = new Genotype(ancestor_str);

  // Read parent 1
  string parent_1_str;
  in >> parent_1_str;
  parent_1 = new Genotype(parent_1_str, ancestor);

  // Read parent 2
  string parent_2_str;
  in >> parent_2_str;
  parent_2 = new Genotype(parent_2_str, ancestor);

  // Read the number of hybrids
  int n_hybrids;
  in >> n_hybrids;

  // Read the hybrids
  vector<Genotype*> hybrids;
  for(int i = 0; i < n_hybrids; i++)
  {
    // Read the sequence
    string hybrid_str;
    in >> hybrid_str;

    // Read the length of parental region 1
    int n_region_1;
    in >> n_region_1;

    // Read parental region 1
    vector<int> region_1;
    for(int j = 0; j < n_region_1; j++)
    {
      int pos;
      in >> pos;
      region_1.push_back(pos);
    }

    // Read the length of parental region 2
    int n_region_2;
    in >> n_region_2;

    // Read parental region 2
    vector<int> region_2;
    for(int j = 0; j < n_region_2; j++)
    {
      int pos;
      in >> pos;
      region_2.push_back(pos);
    }

    // Construct the hybrid and add it to the list
    HybridGenotype* hybrid = new HybridGenotype
      (hybrid_str, ancestor, parent_1, parent_2, region_1, region_2);
    hybrids.push_back(hybrid);
  }

  return hybrids;
}

void HybridIO::writeHybrids(ostream& out,
  Genotype const* ancestor, Genotype const* parent_1, Genotype const* parent_2,
  vector<Genotype*> const& hybrids) const
{
  int n_hybrids = hybrids.size();

  // Write the ancestor and parents
  out << ancestor << "\n";
  out << parent_1 << "\n";
  out << parent_2 << "\n";

  // Write the number of hybrids
  out << n_hybrids << "\n";

  // Write each hybrid (including parental regions)
  for(int i = 0; i < n_hybrids; i++)
  {
    HybridGenotype* hybrid = (HybridGenotype*)hybrids[i];

    // Write sequence
    out << hybrid << "\n";

    // Write parental region 1
    vector<int> const& region_1 = hybrid->getParent1Region();
    int n_region_1 = region_1.size();
    out << n_region_1 << "\n";
    for(int j = 0; j < n_region_1; j++)
      out << region_1[j] << "\n";

    // Write parental region 2
    vector<int> const& region_2 = hybrid->getParent2Region();
    int n_region_2 = region_2.size();
    out << n_region_2 << "\n";
    for(int j = 0; j < n_region_2; j++)
      out << region_2[j] << "\n";
  }
}
