#include "PID.h"
#include <test.h>
#include "serial.h"


int test_PID_reset(void)
{
  dbgprintf(&SD3, "=================================\r\n");
  int res = 1;
  PID_t test_PID = {.error = {10, 5, 100, 1}};

  PID_reset(&test_PID);

  if(test_PID.error.P == test_PID.error.D && test_PID.error.D == test_PID.error.I &&
  test_PID.error.I == test_PID.error.prev_P && test_PID.error.prev_P == 0)
    dbgprintf(&SD3, "TEST RESET OK\r\n");
  else
  {
    res = -1;
    dbgprintf(&SD3, "TEST RESET FAILED\r\n");
  }

  dbgprintf(&SD3, "TEST PID RESET END\r\n");

  return res;
}

int test_PID_err_calc(void)
{
  dbgprintf(&SD3, "=================================\r\n");
  int res = 1;
  PID_t test_PID = {.error = {0, 0, 0, 0}};
  float setpoint = 5.1f;
  float current_point = 1.6f;
  PID_err_calc (&test_PID.error, setpoint, current_point);

  if(test_PID.error.P == (setpoint - current_point))
    dbgprintf(&SD3, "TEST ERROR OK\r\n");
  else
  {
    res = -1;
    dbgprintf(&SD3, "TEST ERROR FAILED\r\n");
  }


  dbgprintf(&SD3, "TEST PID ERROR END\r\n");
  return res;
}

int test_PID_out(void)
{
  dbgprintf(&SD3, "=================================\r\n");
  double check_1 = 250;
  double check_2 = 350;
  double check_3 = 850;
  int res = 1;

  PID_t test_PID ={
          .error = {50, 0, 0, 0},
          .coef = {5, 0, 0}
  };

  double out = PID_out(&test_PID, 0.1f);
  if(out == check_1)
    dbgprintf(&SD3, "TEST OUT1 OK\r\n");
  else
  {
    res = -1;
    dbgprintf(&SD3, "TEST OUT1 FAILED\r\n");
  }
  test_PID.error.prev_P = 0;
  test_PID.error.I = 0;
  test_PID.error.D = 0;
  test_PID.coef.ki = 20;

  out = PID_out(&test_PID, 0.1f);
  if(out == check_2)
    dbgprintf(&SD3, "TEST OUT2 OK\r\n");
  else
  {
    res = -1;
    dbgprintf(&SD3, "TEST OUT2 FAILED\r\n");
  }

  test_PID.error.prev_P = 0;
  test_PID.error.I = 0;
  test_PID.error.D = 0;
  test_PID.coef.kd = 1;

  out = PID_out(&test_PID, 0.1f);
  if(out == check_3)
    dbgprintf(&SD3, "TEST OUT3 OK\r\n");
  else
  {
    res = -1;
    dbgprintf(&SD3, "TEST OUT3 FAILED\r\n");
  }

  dbgprintf(&SD3, "TEST PID OUT END\r\n");

  dbgprintf(&SD3, "=================================\r\n");

  return res;

}

void test_PID()
{
  int res = 0;
  dbgprintf(&SD3, "PID TESTS START\r\n");
  res += test_PID_reset();
  res += test_PID_err_calc();
  res += test_PID_out();

  if(res == 3)
    dbgprintf(&SD3, "ALL PID TESTS PASS\r\n");
  else
    dbgprintf(&SD3, "PID TESTS FAILED\r\n");

}

