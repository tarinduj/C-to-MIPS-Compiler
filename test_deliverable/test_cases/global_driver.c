extern int driver_file_int;
int test_file_int = 42;

int get_test_file_int();
int main()
{
	return (driver_file_int + get_test_file_int()) != 89;
}