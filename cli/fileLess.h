#ifndef BLOSSOM_CORE_CLI_FILELESS_HANDLER
#define BLOSSOM_CORE_CLI_FILELESS_HANDLER

#include <iostream>
#include "core/Blossom.h"

using namespace std;

void showHelpMessage() {
	cout << "Usage: blossom <file> [options]" << endl << endl
		<< "Options:" << endl
		<< "--v[ersion]: Shows the version of blossom related softwares / programs." << endl
		<< "--i[nfo]: Shows your Blossom's distribution information." << endl
		<< "--h[elp]: Shows the Blossom CLI's help message." << endl;
}

void showVersionMessage() {
	cout << "Blossom Core v" << VERSION;
}


#endif 
