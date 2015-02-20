//#include "Lab16_APB_CH.h"

/*SC_HAS_PROCESS(apb_channel);
apb_channel::apb_channel(sc_module_name instname)
: sc_module(instname)
{
	PSEL.initialize(0);
	PENABLE.initialize(0);
	PADDR.initialize(0);
	PWRITE.initialize(0);
	PWDATA.initialize(0);
}

void apb_channel::reset(void)
{

	// Reset Stage
	PSEL.write(0);
	PENABLE.write(0);
	PADDR.write(0);
	PWRITE.write(0);
	PWDATA.write(0);

	wait();

}

void apb_channel::write(int addr, int data)
{
	PSEL.write(1);
	PENABLE.write(1);
	PADDR.write(addr);
	PWRITE.write(1);
	PWDATA.write(data);

	wait();

	PSEL.write(0);
	PENABLE.write(0);
}

int apb_channel::read(int addr)
{
	PSEL.write(1);
	PENABLE.write(1);
	PADDR.write(addr);
	PWRITE.write(0);

	wait();

	PSEL.write(0);
	PENABLE.write(0);

	wait();

	return PRDATA.read();
}

*/