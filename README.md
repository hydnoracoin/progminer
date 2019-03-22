# progminer (ethminer fork with ProgPoW implementation)

![progminer](progminer.png)

> Ethereum ProgPoW miner with OpenCL, CUDA and stratum support

**Progminer** is an ProgPoW GPU mining worker: with progminer you can mine every coin which relies on an ProgPoW Proof of Work thus including Ethereum ProgPoW and others. This is the actively maintained version of progminer. It originates from [ethminer](https://github.com/ethereum-mining/ethminer) project. Check the original [ProgPoW](https://github.com/ifdefelse/progpow) implementation and [EIP-1057](https://eips.ethereum.org/EIPS/eip-1057) for specification.

## Features

* Open source ProgPoW miner software for miners.
* OpenCL mining
* Nvidia CUDA mining
* realistic benchmarking against arbitrary epoch/DAG/blocknumber
* on-GPU DAG generation
* stratum mining without proxy
* OpenCL devices picking
* farm failover (getwork + stratum)
* Ethereum-based ProgPoW implementations supported only, doesn't support previous ethash version or Bitcoin-based forks.


## Table of Contents

* [Install](#install)
* [Usage](#usage)
    * [Examples connecting to pools](#examples-connecting-to-pools)
* [Build](#build)
    * [Continuous Integration and development builds](#continuous-integration-and-development-builds)
    * [Building from source](#building-from-source)
* [Maintainers & Authors](#maintainers--authors)
* [Contribute](#contribute)

## Install

## Usage

The **progminer** is a command line program. This means you launch it either
from a Windows command prompt or Linux console, or create shortcuts to
predefined command lines using a Linux Bash script or Windows batch/cmd file.
For a full list of available command, please run:

```sh
progminer --help
```

Note that Progminer doesn't support mining Bitcoin-based ProgPoW implementations such as Bitcoin Interest, etc. (See https://github.com/gangnamtestnet/progminer/issues/9 for more information)

### Examples connecting to pools

Connecting to [progpool.pro](https://progpool.pro):

`./progminer -P stratum1+tcp://0xaa16a61dec2d3e260cd1348e48cd259a5fb03f49.test@progpool.pro:8008` or

`progminer.exe -P stratum1+tcp://0xaa16a61dec2d3e260cd1348e48cd259a5fb03f49.test@progpool.pro:8008`

## Build

### Continuous Integration and development builds

| CI          | OS       | Status  | Development builds |
| ----------- | -------- | -----   | -----------------  |
| AppVeyor    | Windows  | ![AppVeyor](https://img.shields.io/appveyor/ci/jean-m-cyr/progminer/master.svg) | ✓ Build artifacts available for all PRs and branches |

The AppVeyor system automatically builds a Windows .exe for every commit. The latest version is always available [on the landing page](https://ci.appveyor.com/project/jean-m-cyr/progminer) or you can [browse the history](https://ci.appveyor.com/project/jean-m-cyr/progminer/history) to access previous builds.

To download the .exe on a build under `Job name` select the CUDA version you use, choose `Artifacts` then download the zip file.

### Building from source

See [docs/BUILD.md](docs/BUILD.md) for build/compilation details.

## Maintainers & Authors

## Contribute

All bug reports, pull requests and code reviews are very much welcome.


## License

Licensed under the [GNU General Public License, Version 3](LICENSE).

