#ifndef ERRLIB_ERR_H

#define ERRLIB_ERR_H

#define BUILD_ERR(no, reason) (Err)\
{\
  .err_no = no,\
  .err_ln = __LINE__,\
  .err_file = __FILE__,\
  .err_fn = __FUNCTION__,\
  .err_reason = reason\
}

typedef struct Err {
  int err_no;
  unsigned int err_ln;
  const char* err_fn;
  const char* err_file;
  const char* err_reason;
}Err;

#endif