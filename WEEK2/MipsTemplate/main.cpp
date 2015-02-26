#include "platform_mips.h"


int main(int argc, char **argv)
{

	printf("%s", argv[1]);
	platform_mips platform(argv[1], argv[2], argv[3]);

	platform.reset(platform.ereader.entry_ptr);
	cout<<"Platform reset"<<endl;
	
	platform.run();
	cout<<"Platform run"<<endl;

	platform.run_mips();
	cout<<"Platform run MIPS"<<endl;

	return 0;
}
