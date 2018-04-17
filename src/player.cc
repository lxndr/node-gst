/*
 * Copyright 2018 Humanity
 */

#include <vector>
#include <string>
#include "player.h"

static Nan::Persistent<v8::Function> constructor;

v8::Local<v8::Function> Player::Init() {
  auto tpl = Nan::New<v8::FunctionTemplate>(New);
  tpl->SetClassName(Nan::New("GstPlayer").ToLocalChecked());
  tpl->InstanceTemplate()->SetInternalFieldCount(1);

  Nan::SetPrototypeMethod(tpl, "play", Play);
  Nan::SetPrototypeMethod(tpl, "pause", Pause);
  Nan::SetPrototypeMethod(tpl, "stop", Stop);
  Nan::SetPrototypeMethod(tpl, "seek", Seek);
  Nan::SetPrototypeMethod(tpl, "close", Close);

  auto inst = tpl->InstanceTemplate();
  Nan::SetAccessor(inst, Nan::New("uri").ToLocalChecked(), UriGetter, UriSetter);
  Nan::SetAccessor(inst, Nan::New("duration").ToLocalChecked(), DurationGetter);
  Nan::SetAccessor(inst, Nan::New("position").ToLocalChecked(), PositionGetter);

  constructor.Reset(tpl->GetFunction());
  return tpl->GetFunction();
}


NAN_METHOD(Player::New) {
  if (info.IsConstructCall()) {
    auto self = new Player();
    self->Wrap(info.This());
    info.GetReturnValue().Set(info.This());
  } else {
    Nan::ThrowTypeError("Called as plain function is not permitted");
  }
}


Player::Player() {
  m_gst_player = gst_player_new(NULL, NULL);
}

Player::~Player() {
  OnClose();
}

void Player::OnClose() {
  gst_object_unref(m_gst_player);
}

NAN_METHOD(Player::Play) {
  auto self = Nan::ObjectWrap::Unwrap<Player>(info.Holder());
  gst_player_play(self->m_gst_player);
}

NAN_METHOD(Player::Pause) {
  auto self = Nan::ObjectWrap::Unwrap<Player>(info.Holder());
  gst_player_pause(self->m_gst_player);
}

NAN_METHOD(Player::Stop) {
  auto self = Nan::ObjectWrap::Unwrap<Player>(info.Holder());
  gst_player_stop(self->m_gst_player);
}

NAN_METHOD(Player::Seek) {
  auto self = Nan::ObjectWrap::Unwrap<Player>(info.Holder());

  if (info.Length() < 1) {
    Nan::ThrowTypeError("Argument #1 must be a number");
  }

  auto pos = info[0]->NumberValue();
  gst_player_seek(self->m_gst_player, static_cast<GstClockTime>(pos));
}

NAN_METHOD(Player::Close) {
  auto self = Nan::ObjectWrap::Unwrap<Player>(info.Holder());
  self->OnClose();
}


NAN_GETTER(Player::UriGetter) {
  auto self = Nan::ObjectWrap::Unwrap<Player>(info.Holder());
  auto uri = gst_player_get_uri(self->m_gst_player);
  info.GetReturnValue().Set(Nan::New((const char*) uri).ToLocalChecked());
  g_free(uri);
}

NAN_SETTER(Player::UriSetter) {
  auto self = Nan::ObjectWrap::Unwrap<Player>(info.Holder());
  Nan::Utf8String uri(value->ToString());
  gst_player_set_uri(self->m_gst_player, *uri);
  info.GetReturnValue().Set(true);
}

NAN_GETTER(Player::DurationGetter) {
  auto self = Nan::ObjectWrap::Unwrap<Player>(info.Holder());
  auto dur = gst_player_get_duration(self->m_gst_player);
  info.GetReturnValue().Set(static_cast<int32_t>(dur));
}

NAN_GETTER(Player::PositionGetter) {
  auto self = Nan::ObjectWrap::Unwrap<Player>(info.Holder());
  auto pos = gst_player_get_position(self->m_gst_player);
  info.GetReturnValue().Set(static_cast<double>(pos));
}
