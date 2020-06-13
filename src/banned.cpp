#include "consensus/tx_verify.h"
#include "main.h"

typedef std::map<uint256, int> BannedInputs;

const BannedInputs bannedFunds = 
{
    {
	{ uint256("0xf6fdc5425d33b6cde35476a037841507155f28d71ff958ce70fddd756c4b43d9"), 0 },// Masternode exploiter collateral 1 - SQfMZVatpQR9b3KdKp992nxeEZNWkcz7d2
	{ uint256("0x63faf78e66594d32ee56a32b02193acf46e9bc1a972325e5a95d98567830f0df"), 0 },// Masternode exploiter collateral 2 - SNAgLi7pfHD6BDAkQQ74ixtT4o59wkqP8Y
	{ uint256("0x3f12c779a12aecbb8f1fdf3f49c856d05a4165a38f177e82baf1beda9b9be98a"), 1 },// Masternode exploiter collateral 3 - SS6ZgTuvafGX98YqeHdu79wpGrR1KxuqMw
	{ uint256("0xc83b3e6e04cb7279dffc60dcd3291311f67d2f464141879350e051f648631605"), 1 },// Masternode exploiter collateral 4 - SMoP6U7uazpLdqZ18GQFVNNuV77UTK16wh
	{ uint256("0x1e32c089cdccf9dc70eba01215ebd8c39112f05ad9a33c693e32e99501d64660"), 0 },// Masternode exploiter collateral 5 - SjfZFjCv2PxNKQeDgW1RmsFjSpq5PngaZc
	{ uint256("0x0eee74715dc9559cef292fda176831a9ae73ee58b8cd13ee4904e60061747e7e"), 0 },// Masternode exploiter collateral 6 - SPop7eX3kMjwojy1k1EHAqBoodhbski4tR
	{ uint256("0x40019734a82dc936ac32147fa22100280e2152175917a267192bc198b721ba2b"), 0 },// Masternode exploiter collateral 7 - Sf3KBrFqmD3PBHrwTpdsFgUTctEz9mQn5Z

    }
};

bool areBannedInputs(uint256 txid, int vout) {
  for (auto inputs : bannedFunds)
    if (inputs.first == txid && inputs.second == vout)
      return true;
  return false;
}
