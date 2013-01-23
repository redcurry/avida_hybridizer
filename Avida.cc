#include "Avida.h"
#include "Genotype.h"

#include <cstdlib>
#include <fstream>
#include <sstream>
using namespace std;

Avida::Avida(string avida_dir) :
  m_AvidaDir(avida_dir), m_ConfigDir(avida_dir),
  m_AvidaCommandName(DEFAULT_AVIDA_COMMAND_NAME),
  m_ConfigFileName(DEFAULT_CONFIG_FILE_NAME),
  m_InstSetFileName(DEFAULT_INST_SET_FILE_NAME),
  m_EventsFileName(DEFAULT_EVENTS_FILE_NAME),
  m_AnalyzeFileName(DEFAULT_ANALYZE_FILE_NAME),
  m_EnvironmentFileName(DEFAULT_ENVIRONMENT_FILE_NAME),
  m_StartCreatureFileName(DEFAULT_START_CREATURE_FILE_NAME)
{
}

Avida::Avida(string avida_dir, string config_dir) :
  m_AvidaDir(avida_dir), m_ConfigDir(config_dir),
  m_AvidaCommandName(DEFAULT_AVIDA_COMMAND_NAME),
  m_ConfigFileName(DEFAULT_CONFIG_FILE_NAME),
  m_InstSetFileName(DEFAULT_INST_SET_FILE_NAME),
  m_EventsFileName(DEFAULT_EVENTS_FILE_NAME),
  m_AnalyzeFileName(DEFAULT_ANALYZE_FILE_NAME),
  m_EnvironmentFileName(DEFAULT_ENVIRONMENT_FILE_NAME),
  m_StartCreatureFileName(DEFAULT_START_CREATURE_FILE_NAME)
{
}

void Avida::addGenotype(Genotype* genotype)
{
  m_Genotypes.push_back(genotype);
}

void Avida::addGenotypes(vector<Genotype*> const& genotypes)
{
  int n = genotypes.size();
  for(int i = 0; i < n; i++)
    m_Genotypes.push_back(genotypes[i]);
}

void Avida::calcFitness(Genotype* genotype) const
{
  // Put the genotype in a list
  vector<Genotype*> genotypes;
  genotypes.push_back(genotype);

  // Calculate its fitness
  calcFitness(genotypes);
  genotype->setFitness(genotypes[0]->getFitness());
}

void Avida::calcFitness(vector<Genotype*> const& genotypes) const
{
  int n_genotypes = genotypes.size();

  if(n_genotypes == 0)
    return;

  // Fitness and viability will be calculated
  vector<string> requested_info;
  requested_info.push_back("fitness");
  requested_info.push_back("viable");

  // Calculate fitness and viability
  analyze_info const& info = calcInfo(genotypes, requested_info);
  vector<string> const& fitnesses = info.find("fitness")->second;
  vector<string> const& viability = info.find("viable")->second;

  // Set the calculated fitness for each genotype
  for(int i = 0; i < n_genotypes; i++)
  {
    double fitness = atof(fitnesses[i].c_str());
    int viable = atoi(viability[i].c_str());
    genotypes[i]->setFitness(fitness * viable);
  }
}

analyze_info Avida::calcInfo(vector<Genotype*> const& genotypes,
  vector<string> const& requested_info) const
{
  // Calculate the requested info using Avida in analyze mode
  createSequenceFile(genotypes);
  createAnalyzeFile(requested_info);
  runAvidaAnalyze();

  // Read the calculated info from an output file
  analyze_info const& info =
    readRequestedInfo(SEQS_INFO_FILE_NAME, requested_info);

  // Delete temporary files
  deleteInfoFiles();

  return info;
}

// Create a sequence file and write the sequences to it
void Avida::createSequenceFile(vector<Genotype*> const& genotypes) const
{
  ofstream seqs_file(SEQS_FILE_NAME);

  // Write header
  seqs_file << "#filetype genotype_data\n";
  seqs_file << "#format sequence\n";

  // Write each sequence
  int n_genotypes = genotypes.size();
  for(int i = 0; i < n_genotypes; i++)
    seqs_file << genotypes[i] << "\n";

  seqs_file.close();
}

// Create an analyze file and write commands to it
void Avida::createAnalyzeFile(vector<string> const& requested_info) const
{
  ofstream analyze_file(m_AnalyzeFileName.c_str());

  // Write analyze commands
  analyze_file << "load " SEQS_FILE_NAME "\n";
  analyze_file << "recalc\n";
  analyze_file << "detail " SEQS_INFO_FILE_NAME;

  // Write requested info
  int n_requested_info = requested_info.size();
  for(int i = 0; i < n_requested_info; i++)
    analyze_file << " " << requested_info[i];

  analyze_file.close();
}

// Run Avida in analyze mode
void Avida::runAvidaAnalyze() const
{
  string command = completeAvidaPath(m_AvidaCommandName) +
    " -c " + completeConfigPath(m_ConfigFileName) +
    " -set INST_SET " + completeConfigPath(m_InstSetFileName) +
    " -set EVENT_FILE " + completeConfigPath(m_EventsFileName) +
    " -set ANALYZE_FILE " + m_AnalyzeFileName + // In current directory
    " -set ENVIRONMENT_FILE " + completeConfigPath(m_EnvironmentFileName) +
    " -set START_CREATURE " + completeConfigPath(m_StartCreatureFileName) +
    " -set ANALYZE_MODE 1 " +
    " -set DATA_DIR . > /dev/null";

  system(command.c_str());
}

analyze_info Avida::readRequestedInfo
  (string info_file_path, vector<string> const& requested_info) const
{
  int n_requested_info = requested_info.size();

  // Initialize info "dictionary"
  analyze_info info;
  for(int i = 0; i < n_requested_info; i++)
    info[requested_info[i]] = vector<string>();

  // Open the Avida-generated info file
  ifstream info_file(info_file_path.c_str());

  while(!info_file.eof())
  {
    // Read line-by-line because lines will contain comments,
    // starting with a '#', or blank lines that must be skipped
    string line;
    getline(info_file, line);

    // Avoid comments and blank lines
    if(line.find("#") != 0 && line.length() > 0)
    {
      // Will read space-delimited info
      istringstream line_stream(line);

      for(int i = 0; i < n_requested_info; i++)
      {
        string value;
        line_stream >> value;
        info[requested_info[i]].push_back(value);
      }
    }
  }

  info_file.close();

  return info;
}

void Avida::deleteInfoFiles() const
{
  remove(SEQS_FILE_NAME);
  remove(SEQS_INFO_FILE_NAME);
  remove(m_AnalyzeFileName.c_str());
}
