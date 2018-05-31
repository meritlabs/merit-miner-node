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

Copyright (c) 2017-2018 The Merit Foundation
libmeritminer is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Foobar is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Foobar.  If not, see <http://www.gnu.org/licenses/>.
