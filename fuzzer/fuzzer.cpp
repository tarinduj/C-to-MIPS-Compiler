#include "run.hpp"
#include <cinttypes>
#include <cstddef>
#include <cstdio>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  const char* input_file = "_temp.c";
  const char* args[] = { "c-to-mips", input_file, "-o", "_temp.mps", "-c" };

  // TODO: write `size` bytes of `data` to a file named `input_file`,
  FILE *file = fopen(input_file, "w");
  fwrite(data, sizeof(uint8_t), size, file);
  fclose(file);

  //  then invoke the `run` method of the compile with `args`
  const char* compiler_path = "/mnt/disks/data/tarindu/fuzz/build/c-to-mips";
  const char* compile_flag = "-c";
  const char* argv[] = {
    (const char*)compiler_path,
    (const char*)input_file,
    (const char*)compile_flag,
    NULL
  };

  run(3, argv);

  return 0;
}
