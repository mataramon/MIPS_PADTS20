#ifndef _Lab16_APB_RAM_H_
#define _Lab16_APB_RAM_H_

#include <systemc.h>
#include "Lab16_Defs.h"

class apb_ram : public sc_module {

private:
	void process(void);
	int* mem;

public:
	// Clock
	sc_in_clk PCLK;

	// Reset
	sc_in<bool> PRESETn;

	// Input Ports
	sc_in<bool> PSEL;
	sc_in<bool> PENABLE;
	sc_in<addr_t> PADDR;
	sc_in<bool> PWRITE;
	sc_in<data_t> PWDATA;

	// Output Ports
	sc_out<data_t> PRDATA;

	// Constructor
	apb_ram(sc_module_name instname, int mem_size);
};

#endif // _Lab16_APB_RAM_H_
