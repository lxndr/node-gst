/*
 * Copyright 2018 Humanity
 */

#ifndef SRC_PLAYER_H_
#define SRC_PLAYER_H_

#include <uv.h>
#include <nan.h>
#include <gst/gst.h>
#include <gst/player/player.h>

class Player : public Nan::ObjectWrap {
 public:
  static v8::Local<v8::Function> Init();

 private:
  explicit Player();
  ~Player();
  void OnClose();

  static NAN_METHOD(New);
  static NAN_METHOD(Play);
  static NAN_METHOD(Pause);
  static NAN_METHOD(Stop);
  static NAN_METHOD(Seek);
  static NAN_METHOD(Close);

  static NAN_GETTER(UriGetter);
  static NAN_SETTER(UriSetter);
  static NAN_GETTER(DurationGetter);
  static NAN_GETTER(PositionGetter);

 private:
  GstPlayer* m_gst_player;
};

#endif  // SRC_PLAYER_H_
