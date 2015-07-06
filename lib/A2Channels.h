/**
 * @file A2channels.h
 * 
 *
 */

#ifndef _A2CHANNELS_H
#define _A2CHANNELS_H

#ifndef __CINT__

#include <map>
#include <list>
#include <vector>
#include <string>

// ROOT
#include "Math/Interpolator.h"
#include "TH1.h"

// Pluto
#include "PDecayChannel.h"


using namespace std;


struct ParticleData{
    vector<double> Energies;
    vector<double> Xsections;
} ;

// Cross-section-list is a collection of named Particle data
using XsecList = map<string,ParticleData>;

class A2ChannelManager {
private:
    XsecList _XList;

    void unifyDecayName(string &decay)const;

    /**
     * @brief ParseFile reads provided file and fills internal database of this object.
     * @param filename
     * @return true if successfully parsed file
     *
     * Provide file with following syntax:
     *
     *    # comment blahh blubb
     *    Particle particle1a [particle1b] [particle1c] # comment2
     *    PhotonEnergy cross-section
     *       ⋮
     *    [Particle particle2a [particle2b] [particle2c]
     *    PhotonEnergy cross-section
     *       ⋮ ]
     *     ⋮
     *
     *
     */
    const bool ParseFile(const string& filename);

public:
    A2ChannelManager(vector<string> dataFiles = {});

    vector<string> GetChannels() const;

    double Xsection(const string& name, const double Egamma) const;
    double TotalXsection(const double &Egamma) const;            // mask out decays {list}

    PDecayChannel* GenerateDecays(const double& Energy);  // mask out decays {list}

    const XsecList& GetData() const
    {
        return _XList;
    }
};

#endif 

#endif 
