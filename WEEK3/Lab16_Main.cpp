#include "Lab16_TB.h"

int sc_main(int sc_argc, char* sc_argv[]) {

	sc_set_stop_mode(SC_STOP_IMMEDIATE);

	apb_mem_tb tb("tb");

	sc_start(); // invoke the simulator

	return 0;
}
