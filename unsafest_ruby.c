#include <ruby.h>
#include <sys/mman.h>

VALUE
execute(VALUE self, VALUE arg1)
{
  int code_length = RARRAY_LEN(arg1);
  unsigned char *code = malloc(code_length);

  for(int i=0; i<code_length; i++){
    VALUE object = RARRAY_PTR(arg1)[i];
    code[i] = NUM2INT(object);
  }

  void *instructions = mmap(0, code_length, PROT_WRITE | PROT_EXEC, MAP_ANON | MAP_PRIVATE, -1, 0);
  memcpy(instructions, code, code_length);

  int (*function)() = instructions;
  int result = function();

  free(code);
  munmap(instructions, code_length);

  return INT2NUM(result);
}

void
Init_unsafest_ruby()
{
  VALUE unsafe_class = rb_define_class("UnsafestRuby", rb_cObject);
  rb_define_singleton_method(unsafe_class, "execute", execute, 1);
}
