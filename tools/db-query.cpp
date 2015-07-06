/**
 * @file show-cocktail-xsections.cpp
 * @author Martin Wolfes
 * @date 18.3.2015
 */

#include <iostream>
#include <sstream>
#include <string>

#include "A2Channels.h"
#include "A2Cocktail.h"


#include "TTree.h"
#include "TFile.h"
#include "TApplication.h"
#include "TH1D.h"


using namespace std;

int main( int argc, char** argv ){



    string particle;
    double E;
    if (argc == 3){
        particle = argv[1];
        E = atof(argv[2]);
    } else {
        cerr << " Usage: db-query <decay-name|total> E/GeV" << endl;
        return 1;
    }

//    A2ChannelManager acm({"/opt/AT-AT/common/14001Decays.dat"});
    A2ChannelManager acm;

    //for (auto& c: acm.GetChannels()){
        //cout << c << endl;
    //}

    if ( particle == "total"){
        cout << acm.TotalXsection(E) << endl;
        return 0;
    }

    cout << acm.Xsection(particle,E) << endl;

    return 0;

}
