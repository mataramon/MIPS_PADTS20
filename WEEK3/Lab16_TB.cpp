#include "Lab16_TB.h"

SC_HAS_PROCESS(apb_mem_tb);
apb_mem_tb::apb_mem_tb(sc_module_name instname)
: sc_module(instname)
, ram("ram", 256)
, chan("chan")
, clock("clock", sc_time(CLOCK_PERIOD, SC_NS))
{
	SC_CTHREAD(process, clock);

	ram.PCLK(clock);
	ram.PRESETn(PRESETn);
	ram.PSEL(PSEL);
	ram.PENABLE(PENABLE);
	ram.PADDR(PADDR);
	ram.PWRITE(PWRITE);
	ram.PWDATA(PWDATA);
	ram.PRDATA(PRDATA);

	chan.PSEL(PSEL);
	chan.PENABLE(PENABLE);
	chan.PADDR(PADDR);
	chan.PWRITE(PWRITE);
	chan.PWDATA(PWDATA);
	chan.PRDATA(PRDATA);

	PRESETn.write(1);
}

void apb_mem_tb::process(void)
{
	int data_rd;
	PRESETn.write(0);
	wait();
	PRESETn.write(1);

	chan.write(0x10, 0xdeadbeef);
	chan.write(0x20, 0x12345678);

	data_rd = chan.read(0x10);
	data_rd = chan.read(0x20);
	sc_stop();
}
