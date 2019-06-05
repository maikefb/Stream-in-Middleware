#include "usercall.hpp"

int init_server()
{
  parameters arg;
  arg.callnumber = SERVER_MASTER_INIT;
  //arg.p0 = (unsigned char *) port;
  return (int)invoke(&arg);
}

int init_client()
{
  parameters arg;
  arg.callnumber = CLIENT_MASTER_INIT;
  //arg.p0 = (unsigned char *) ip_server;
  //arg.p1 = (unsigned char *) port;
  return (int)invoke(&arg);
}

int stream_start()
{
  parameters arg;
  arg.callnumber = STREAM_START;
  return (int)invoke(&arg);
}

int stream_stop()
{
  parameters arg;
  arg.callnumber = STREAM_STOP;
  return (int)invoke(&arg);
}

int stream_q()
{
  parameters arg;
  arg.callnumber = STREAM_QT;
  return (int)invoke(&arg);
}

int photo_imed()
{
  parameters arg;
  arg.callnumber = PHOTO_IMED;
  return (int)invoke(&arg);
}

int photo_period_start(unsigned char period)
{
  parameters arg;
  arg.callnumber = PHOTO_PERIOD_START;
  arg.p0 = &period;
  return (int)invoke(&arg);
}

int photo_period_stop()
{
  parameters arg;
  arg.callnumber = PHOTO_PERIOD_STOP;
  return (int)invoke(&arg);
}

int video_start()
{
  parameters arg;
  arg.callnumber = VIDEO_START;
  return (int)invoke(&arg);
}

int video_stop()
{
  parameters arg;
  arg.callnumber = VIDEO_STOP;
  return (int)invoke(&arg);
}
