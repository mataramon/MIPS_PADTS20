#include "Lab16_APB_RAM.h"

SC_HAS_PROCESS(apb_ram);
apb_ram::apb_ram(sc_module_name instname, int mem_size)
: sc_module(instname)
{
	SC_CTHREAD(process, PCLK);
	async_reset_signal_is(PRESETn, false);

	mem = new int[mem_size];
}

void apb_ram::process(void)
{
	// Reset Stage
	PRDATA.write(0);

	wait();

	while (true) {
		if (PSEL & PENABLE) {
			if (PWRITE) {
				mem[PADDR.read().to_uint()] = PWDATA.read();
				cout << sc_time_stamp();
				printf(" - RAM: Data 0x%08X write to %d\n", PWDATA.read().to_uint(), PADDR.read().to_uint());
			}
			else {
				PRDATA.write(mem[PADDR.read().to_uint()]);
				cout << sc_time_stamp();
				printf(" - RAM: Data 0x%08X read from %d\n", mem[PADDR.read().to_uint()], PADDR.read().to_uint());
			}
		}
		wait();
	}
}
