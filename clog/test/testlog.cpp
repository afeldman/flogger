#include <clogg/logger.hpp>

int main(){

	TPRINTDBG("test DGB terminal output");
	TPRINTIFO("test INFO terminal output");
	TPRINTERR("test ERR terminal output");

	Logger::getLogger().setLogFile("testlogfile");

	PRINTDBG("DBG test");
	PRINTIFO("Info test");
	PRINTERR("Err test");

	return 0;
};

