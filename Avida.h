#ifndef AVIDA_H
#define AVIDA_H

#include "Genotype.h"

#include <vector>
#include <string>
#include <map>
using namespace std;

// Default Avida command to run
#define DEFAULT_AVIDA_COMMAND_NAME       "avida"

// Default configuration file names
#define DEFAULT_CONFIG_FILE_NAME         "avida.cfg"
#define DEFAULT_INST_SET_FILE_NAME       "instset-heads-sex.cfg"
#define DEFAULT_EVENTS_FILE_NAME         "events.cfg"
#define DEFAULT_ANALYZE_FILE_NAME        "analyze.cfg"
#define DEFAULT_ENVIRONMENT_FILE_NAME    "environment.cfg"
#define DEFAULT_START_CREATURE_FILE_NAME "default-heads-sex.org"

// Temporary file names for analyze mode
#define SEQS_FILE_NAME      "seqs.dat"
#define SEQS_INFO_FILE_NAME "seqs_info.dat"

// Dictionary where the key is an info label (like "fitness")
// and the value is a list of calculated values for each sequence
typedef map< string, vector<string> > analyze_info;

class Avida
{

  public:

    Avida(string avida_dir);
    Avida(string avida_dir, string config_dir);

    void addGenotype(Genotype* genotypes);
    void addGenotypes(vector<Genotype*> const& genotypes);

    inline void clearGenotypes()
      { m_Genotypes = vector<Genotype*>(); }

    inline void calcFitness()
      { calcFitness(m_Genotypes); }
    inline void calcFitnessAndClear()
      { calcFitness(); clearGenotypes(); }

    void calcFitness(Genotype* genotype) const;
    void calcFitness(vector<Genotype*> const& genotypes) const;

    inline void setAvidaDir(string avida_dir)
      { m_AvidaDir = avida_dir; }
    inline string getAvidaDir() const
      { return m_AvidaDir; }

    inline void setAvidaCommandName(string avida_command_name)
      { m_AvidaCommandName = avida_command_name; }
    inline string getAvidaCommandName() const
      { return m_AvidaCommandName; }

    inline void setConfigFileName(string config_file_name)
      { m_ConfigFileName = config_file_name; }
    inline string getConfigFileName() const
      { return m_ConfigFileName; }

    inline void setInstSetFileName(string inst_set_file_name)
      { m_InstSetFileName = inst_set_file_name; }
    inline string getInstSetFileName() const
      { return m_InstSetFileName; }

    inline void setEventsFileName(string events_file_name)
      { m_EventsFileName = events_file_name; }
    inline string getEventsFileName() const
      { return m_EventsFileName; }

    inline void setAnalyzeFileName(string analyze_file_name)
      { m_AnalyzeFileName = analyze_file_name; }
    inline string getAnalyzeFileName() const
      { return m_AnalyzeFileName; }

    inline void setEnvironmentFileName(string environment_file_name)
      { m_EnvironmentFileName = environment_file_name; }
    inline string getEnvironmentFileName() const
      { return m_EnvironmentFileName; }

    inline void setStartCreatureFileName(string start_creature_file_name)
      { m_StartCreatureFileName = start_creature_file_name; }
    inline string getStartCreatureFileName() const
      { return m_StartCreatureFileName; }

  private:

    analyze_info calcInfo(vector<Genotype*> const& genotypes,
      vector<string> const& requested_info) const;

    void createSequenceFile(vector<Genotype*> const& genotypes) const;

    void createAnalyzeFile(vector<string> const& requested_info) const;

    void runAvidaAnalyze() const;

    analyze_info readRequestedInfo
      (string info_file_name, vector<string> const& requested_info) const;

    void deleteInfoFiles() const;

    inline string completeAvidaPath(string file_name) const
      { return m_AvidaDir + "/" + file_name; }
    inline string completeConfigPath(string file_name) const
      { return m_ConfigDir + "/" + file_name; }

    // Vector holding genotypes for fitness calculation
    vector<Genotype*> m_Genotypes;

    // Directories for the Avida command and configuration files
    string m_AvidaDir;
    string m_ConfigDir;

    // Name of the Avida command
    string m_AvidaCommandName;

    // Names of the configuration files
    string m_ConfigFileName;
    string m_InstSetFileName;
    string m_EventsFileName;
    string m_AnalyzeFileName;
    string m_EnvironmentFileName;
    string m_StartCreatureFileName;

};

#endif
