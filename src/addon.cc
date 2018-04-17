/*
 * Copyright 2018 Humanity
 */

#include <gst/gst.h>
#include "player.h"

NAN_MODULE_INIT(Init) {
  gst_init(nullptr, nullptr);

  Nan::Set(target, Nan::New("GstPlayer").ToLocalChecked(), Player::Init());
}

NODE_MODULE(addon, Init)
