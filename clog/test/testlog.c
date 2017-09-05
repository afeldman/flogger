#include <clogg/clogger.h>

int main(void) {

	int run = start_logging("./test.log");
	write_logging("testlog");
	stop_logging();

	return 0;
}
