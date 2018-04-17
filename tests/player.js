const path = require('path');
const {expect} = require('chai');
const {GstPlayer} = require('..');

const track1 = 'file://' + path.resolve('tests/fixtures/bird-whistling.wav');

describe('GstPlayer', () => {
  let player = null;
  let media = null;

  it('creates new', () => {
    player = new GstPlayer();
  });

  it('sets uri', () => {
    player.uri = track1;
  });

  it('plays', done => {
    player.onstate = state => {
      if (state === 'playing') {
        done();
      }
    };

    player.onerror = error => {
      done(error);
    };

    player.play();
  });

  it('pauses', done => {
    player.onstate = state => {
      if (state === 'paused') {
        done();
      }
    };

    player.onerror = error => {
      done(error);
    };

    player.pause();
  });

  it('stops', done => {
    player.onstate = state => {
      if (state === 'stopped') {
        done();
      }
    };

    player.onerror = error => {
      done(error);
    };

    player.stop();
  });

  after(() => {
    player.close();
  });
});
