GCC_MIPS = mips-linux-gnu-gcc
COMPILER = mips-linux-gnu-gcc -S -static
GCC_MIPS_FLAGS = -static
EMULATOR = qemu-mips

clean:
	rm -rf our
	rm -rf ref
	rm -rf tmp

our/%: test_cases/%_driver.c test_cases/%.c
	mkdir -p -m a=rwx tmp
	mkdir -p -m a=rwx our
	$(COMPILER) test_cases/$*.c -o tmp/$*.s
	$(GCC_MIPS) $(GCC_MIPS_FLAGS) -c test_cases/$*_driver.c -o tmp/$*_driver.o 
	$(GCC_MIPS) $(GCC_MIPS_FLAGS) tmp/$*.s tmp/$*_driver.o -o our/$* 

ref/%: test_cases/%_driver.c test_cases/%.c
	mkdir -p -m a=rwx tmp
	mkdir -p -m a=rwx ref
	$(GCC_MIPS) $(GCC_MIPS_FLAGS) -S test_cases/$*.c -o tmp/$*.s
	$(GCC_MIPS) $(GCC_MIPS_FLAGS) -c test_cases/$*_driver.c -o tmp/$*_driver.o 
	$(GCC_MIPS) $(GCC_MIPS_FLAGS) tmp/$*.s tmp/$*_driver.o -o ref/$* 

test_%:
	@mkdir -p -m a=rwx ref
	@mkdir -p -m a=rwx our 
	@make -s ref/$*
	@make -s our/$*
	@$(EMULATOR) ref/$* || echo TEST $* IS BAD
	@$(EMULATOR) our/$* || echo TEST $* FAILED
	

