#!/bin/env node

const path = require('path');
const {GstPlayer} = require('.');

const player = new GstPlayer();
player.uri = 'file://' + path.resolve(process.argv[2]);
player.play();

setTimeout(() => {}, 10000);
