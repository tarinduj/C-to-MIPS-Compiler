#include <cinttypes>
#include <cstddef>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  const char* input_file = "_temp.c";
  const char* args[] = { "c-to-mips", input_file, "-o", "_temp.mps", "-c" };

  // TODO: write `size` bytes of `data` to a file named `input_file`,
  //  then invoke the `run` method of the compile with `args`
  return 0;
}
