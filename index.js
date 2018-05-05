
var meritminer = require("./build/Release/meritminer");

class MeritMiner 
{
  StartMiner() {
    return meritminer.startMiner();
  }

}

module.exports = {
  MeritMiner
}
