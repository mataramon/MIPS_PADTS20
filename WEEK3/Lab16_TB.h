#ifndef _LAB16_TB_H_
#define _LAB16_TB_H_

#include <systemc.h>
#include "Lab16_APB_RAM.h"
#include "Lab16_APB_CH.h"

class apb_mem_tb : public sc_module {
private:
	void process(void);
	apb_ram ram;
	// Define your custom APB Channel
	// Example: sc_apb_ch<data_t, addr_t> chan;
	//apb_channel chan;
	sc_apb_ch<data_t, addr_t> chan;
	sc_clock clock;

	// Reset
	sc_signal<bool> PRESETn;

	// Input Ports
	sc_signal<bool> PSEL;
	sc_signal<bool> PENABLE;
	sc_signal<addr_t> PADDR;
	sc_signal<bool> PWRITE;
	sc_signal<data_t> PWDATA;

	// Output Ports
	sc_signal<data_t> PRDATA;

public:
	apb_mem_tb(sc_module_name instname);
};

#endif // _LAB16_TB_H_
