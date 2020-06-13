#include "consensus/tx_verify.h"
#include "main.h"

bool areBannedInputs(uint256 txid, int vout);