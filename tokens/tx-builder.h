#pragma once
#include "tokens-misc.h"
#include "emp-sh2pc/emp-sh2pc.h"
#include "sha256.h"
#include "constants.h"

using namespace emp;

/* validates closing transactions against a wallet
 * for each transaction:
 * 0. check that balances are correct
 * 1. check that wallet key is integrated correctly
 * 2. check that source is correct
 *    for close_tx_merch, source is txid_merch
 *    for close_tx_escrow, source is txid_escrow
 *
 * \param[in] w     			: wallet object
 * \param[in] close_tx_escrow   : (private) bits of new close transaction (spends from escrow). no more than 1024 bits.
 * \param[in] close_tx_merch    : (private) bits of new close transaction (spends from merchant close transaction). No more than 1024 bits.
 *
 * \return b 	: success bit
 */
void validate_transactions(State_d new_state_d,
  BitcoinPublicKey_d cust_escrow_pub_key_d, BitcoinPublicKey_d cust_payout_pub_key_d, PublicKeyHash_d cust_child_publickey_hash_d,
  BitcoinPublicKey_d merch_escrow_pub_key_d, BitcoinPublicKey_d merch_dispute_key_d, BitcoinPublicKey_d merch_payout_pub_key_d,
  PublicKeyHash_d merch_publickey_hash_d, Integer escrow_digest[8], Integer merch_digest[8], Balance_d fee_cc_d, Integer k[64], Integer H[8], Balance_d val_cpfp_d, Integer self_delay_d, Constants constants);