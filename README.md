# merit-miner-node

Node library that wraps [libmeritminer](https://github.com/meritlabs/libmeritminer).

## Goals

- Easily usable by other node programs.
- Support connecting to a meritd instance.
- Support connecting to stratum pool.
- Support multithreaded cpu mining.
- Support gpu mining.

## Dependencies

- Install [libmeritminer](https://github.com/meritlabs/libmeritminer).

## Compiling

`npm build .`

## Install Locally

`npm link`

## Use Local Install

`npm link meritminer`

## Directories

| Files/Directories                      | Description           |
|:---------------------------------------|:----------------------|
| [native](native)                       | C++ Node Wrapper for libmeritminer.|
| [index.js](index.js)                   | Friendly interface to the wrapper.|


## License

Copyright (c) 2017-2018 The Merit Foundation developers
Distributed under the MIT software license, see the accompanying
file COPYING or http://www.opensource.org/licenses/mit-license.php.
