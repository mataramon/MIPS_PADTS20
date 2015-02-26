int main()
{
	volatile short a = 0;
	volatile short b = 0;
	int i;

	for (i = 0; i < 10; i++) {
	  a = a + (a + 1);
	}
	b = a;
	__asm__ volatile("syscall");

	return 0;
}
