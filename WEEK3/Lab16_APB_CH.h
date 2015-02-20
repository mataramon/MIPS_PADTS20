#ifndef _Lab16_APB_CH_H_
#define _Lab16_APB_CH_H_

#include <systemc.h>
#include "Lab16_Defs.h"

// Define of sc_generic_mem_if<T> interface
// template <class TDATA, class TADDR>
// class sc_generic_mem_if : virtual public sc_interface {
// public:
//	virtual WRITE FUNCTION = 0;
//	virtual READ FUNCTION = 0;
// };
template <class TDATA, class TADDR>
class sc_generic_mem_if: virtual public sc_interface{
	public:
		virtual void write(TDATA data, TADDR addr) = 0;
		virtual TDATA read(TADDR data) = 0;
};

// Define of sc_apb_ch<T> channel
// template <class TDATA, class TADDR>
// class sc_apb_ch : public sc_channel, public sc_generic_mem_if<TDATA, TADDR> {
//  public:
	// Define Input Ports
	// Define Output Ports
	// Define constructor
	// Define Write Virtual Function
	// Define Read Virtual Function
//};
template <class TDATA, class TADDR>
class sc_apb_ch: public sc_channel, public sc_generic_mem_if<TDATA, TADDR> {
	public:
		// Output ports 
	sc_out<bool> PSEL;
	sc_out<bool> PENABLE;
	sc_out<TADDR> PADDR;
	sc_out<bool> PWRITE;
	sc_out<TDATA> PWDATA;

	// Input ports
	sc_in<TDATA> PRDATA;

	explicit sc_apb_ch(sc_module_name instname): sc_channel (instname) {
		//Functions
		PSEL.initialize(0);
		PENABLE.initialize(0);
		PWRITE.initialize(0);
		PADDR.initialize(0);	
	}

	//WRITE
		virtual void write(TDATA data, TADDR addr){
			PSEL.write(1);
			PENABLE.write(1);
			PADDR.write(addr);
			PWRITE.write(1);
			PWDATA.write(data);

			wait();

			PSEL.write(0);
			PENABLE.write(0);
		}

		//READ
		virtual TDATA read(TADDR addr){
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
};


/*class apb_channel : public sc_module {

public:
	// Input Ports
	sc_out<bool> PSEL;
	sc_out<bool> PENABLE;
	sc_out<sc_uint<ADDR_W> > PADDR;
	sc_out<bool> PWRITE;
	sc_out<sc_uint<DATA_W> > PWDATA;

	// Output Ports
	sc_in<sc_uint<DATA_W> > PRDATA;

	// Constructor
	apb_channel(sc_module_name instname);

	// Member Funcitons
	void reset(void);
	int read(int addr);
	void write(int addr, int data);
}; */

#endif // _Lab16_APB_CH_H_
