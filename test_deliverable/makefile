GCC_MIPS = mips-linux-gnu-gcc
COMPILER = ../bin/c_compiler -c
GCC_MIPS_FLAGS = -static -pedantic -ansi 
EMULATOR = qemu-mips

clean:
	rm -rf our
	rm -rf ref
	rm -rf tmp_ref
	rm -rf tmp_our


our/%: test_cases/%_driver.c test_cases/%.c
	mkdir -p -m a=rwx tmp_our
	mkdir -p -m a=rwx our
	$(COMPILER) test_cases/$*.c -o tmp_our/$*.s
	$(GCC_MIPS) $(GCC_MIPS_FLAGS) -c test_cases/$*_driver.c -o tmp_our/$*_driver.o 
	$(GCC_MIPS) $(GCC_MIPS_FLAGS) tmp_our/$*.s tmp_our/$*_driver.o -o our/$*
	#$(GCC_MIPS) $(GCC_MIPS_FLAGS) -o tmp_our/$*.o - c tmp_our/$*.s
	#$(GCC_MIPS) $(GCC_MIPS_FLAGS) -o our/$* tmp_our/$*.o test_cases/$*_driver.c

ref/%: test_cases/%_driver.c test_cases/%.c
	mkdir -p -m a=rwx tmp_ref
	mkdir -p -m a=rwx ref
	$(GCC_MIPS) $(GCC_MIPS_FLAGS) -S test_cases/$*.c -o tmp_ref/$*.s
	$(GCC_MIPS) $(GCC_MIPS_FLAGS) -c test_cases/$*_driver.c -o tmp_ref/$*_driver.o 
	$(GCC_MIPS) $(GCC_MIPS_FLAGS) tmp_ref/$*.s tmp_ref/$*_driver.o -o ref/$* 

test_%:
	@mkdir -p -m a=rwx ref
	@mkdir -p -m a=rwx our 
	@make -s ref/$*
	@make -s our/$*
	@$(EMULATOR) ref/$* || echo TEST $* IS BAD
	@$(EMULATOR) our/$* || echo TEST $* FAILED
	

