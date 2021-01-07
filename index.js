/*
 * Copyright (c) 2017-2021 The Merit Foundation
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either vedit_refsion 3 of the License, or
 * (at your option) any later vedit_refsion.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * In addition, as a special exception, the copyright holders give 
 * permission to link the code of portions of this program with the 
 * Botan library under certain conditions as described in each 
 * individual source file, and distribute linked combinations 
 * including the two.
 *
 * You must obey the GNU General Public License in all respects for 
 * all of the code used other than Botan. If you modify file(s) with 
 * this exception, you may extend this exception to your version of the 
 * file(s), but you are not obligated to do so. If you do not wish to do 
 * so, delete this exception statement from your version. If you delete 
 * this exception statement from all source files in the program, then 
 * also delete it here.
 */
var meritminer = require("./build/Release/meritminer");

class MeritMiner 
{
  SetAgent(software, version) {
    return meritminer.setAgent(software, version);
  }

  StartMiner(workers, threads, gpu_devices) {
    return meritminer.startMiner(workers, threads, gpu_devices);
  }

  StopMiner() {
    return meritminer.stopMiner();
  }
  
  ConnectToStratum(url, address) {
    return meritminer.connectToStratum(url,address);
  }

  DisconnectStratum() {
    return meritminer.disconnectStratum();
  }

  IsStratumConnected() {
    return meritminer.isStratumConnected();
  }

  IsStratumRunning() {
    return meritminer.isStratumRunning();
  }
  
  IsMinerRunning() {
    return meritminer.isMinerRunning();
  }

  IsStratumStopping() {
    return meritminer.isStratumStopping();
  }
  
  IsMinerStopping() {
    return meritminer.isMinerStopping();
  }

  NumberOfCores() {
    return meritminer.numberOfCores();
  }

  NumberOfGPUs() {
    return meritminer.numberOfGPUs();
  }

  FreeMemoryOnDevice() {
    return meritminer.freeMemoryOnDevice();
  }

  MinerStats() {
    return meritminer.minerStats();
  }

  GPUsInfo() {
    return meritminer.gpusInfo();
  }
}

module.exports = {
  MeritMiner
}
