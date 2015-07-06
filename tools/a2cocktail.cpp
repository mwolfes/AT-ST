#include <iostream>
#include <string>
#include <sstream>
#include <vector>


#include "A2Cocktail.h"

#include "anyoption.h"



using namespace std;

static unsigned long numEvents;
static unsigned int  numBins = 48;
static double Emin = 1.42;
static double Emax = 1.58;
static string outfile;
static bool doBulk = true;
static bool saveUnstable = true;
static vector<string> datafiles({});

void ParseCmdLine(int argc, char** argv ) {


    AnyOption opt;

    opt.setVerbose();
    opt.autoUsagePrint(true);

    string usage;
    usage += "usage: " + string(argv[0])+ "\n"
            +  "            [--noBulk] [--noUnstable] \n"
            +  "            [--numEnergyBins|-n <n = 48>] \n"
            +  "            [--datafiles 'file1 [file2 ...]']\n"
            +  "            [--Emin <Emin = 1.42>] [--Emax <Emax = 1.58>]\n"
            +  "            --numEvents|-N <N> --outfile|-o <outfile>\n\n"
            +  "  Generates a cocktail for A2 Experiments using Pluto reactions and stores it to outfile.root.\n"
            +  "  Defaults represent EPT - settings, bulk decay enabled and unstable particles will be stored.\n"
			+  "  \n"
			+  "  The A2 Cocktail generator comes with precompiled crosssections. You can provide your own in\n"
			+  "  datafiles with following syntax:\n"
			+  "  \n"
			+  "     # comment blahh blubb\n"
			+  "     Particle particle1a [particle1b] [particle1c] # comment2\n"
			+  "     PhotonEnergy cross-section\n"
			+  "        ⋮\n"
			+  "     [Particle particle2a [particle2b] [particle2c]\n"
			+  "     PhotonEnergy cross-section\n"
			+  "        ⋮ ]\n"
			+  "      ⋮\n";

    opt.addUsage( usage.c_str());

    opt.setOption("outfile",'o');
    opt.setOption("numEvents",'N');
    opt.setOption("numEnergyBins",'n');
    opt.setOption("Emin");
    opt.setOption("Emax");
    opt.setOption("datafiles");
    opt.setFlag("noBulk");
    opt.setFlag("noUnstable");

    opt.setFlag("help");


    //    opt.processFile(CFG_FILE);


    opt.processCommandArgs( argc, argv );

    //-- Mandatory arguments ---
    if ( opt.getValue("outfile") )
        outfile = opt.getValue("outfile");
    else {
        opt.printUsage();
        exit(0);
    }

    if ( opt.getValue("numEvents") )
        numEvents = atoi(opt.getValue("numEvents"));
    else {
        opt.printUsage();
        exit(0);
    }


    //-- options ---
    if( opt.getFlag("--help") ) {
        opt.printUsage();
        exit(0);
    }
    if (opt.getValue("datafiles"))
    {
        stringstream dfiles;
        dfiles << opt.getValue("datafiles");
        string filestring;
        while ( dfiles >> filestring )
            datafiles.push_back(filestring);
    }
    if ( opt.getValue("Emin") )
        Emin = atof(opt.getValue("Emin"));
    if ( opt.getValue("Emax") )
        Emax = atof(opt.getValue("Emax"));
    if ( opt.getValue("numEnergyBins") )
        numBins = atoi(opt.getValue("numEnergyBins"));
    saveUnstable = ( NULL == opt.getValue("noUnstable") );
    doBulk = ( NULL == opt.getValue("noBulk") );
}

int main( int argc, char** argv ) {
    ParseCmdLine( argc, argv);
    A2Cocktail cocktail(outfile, Emin, Emax, numBins,
                        saveUnstable, doBulk,
                        datafiles
                        );
    cout << cocktail.Sample(numEvents) << endl;
    cocktail.Finish();
}


