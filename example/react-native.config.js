const path = require('path');
const pak = require('../package.json');

module.exports = {
  assets: ['./assets/effects'],
  dependencies: {
    [pak.name]: {
      root: path.join(__dirname, '..'),
    },
  },
};
