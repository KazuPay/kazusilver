// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2015 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.
//
// KazuSilver

#include "chainparams.h"
#include "consensus/merkle.h"

#include "tinyformat.h"
#include "util.h"
#include "utilstrencodings.h"
#include "streams.h"

#include <assert.h>

#include <boost/assign/list_of.hpp>

#include "chainparamsseeds.h"

static CBlock CreateGenesisBlock(const char* pszTimestamp, const CScript& genesisOutputScript, uint32_t nTime, uint32_t nNonce, uint32_t nBits, int32_t nVersion, const CAmount& genesisReward)
{
    CMutableTransaction txNew;
    txNew.nVersion = 1;
    txNew.vin.resize(1);
    txNew.vout.resize(1);
    txNew.vin[0].scriptSig = CScript() << CScriptNum(0) << CScriptNum(42) << std::vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
    // txNew.vout[0].scriptPubKey.clear();
    txNew.vout[0].nValue = genesisReward;
    txNew.vout[0].scriptPubKey.clear();
    txNew.strDZeel = "KazuSilver genesis block";

    CBlock genesis;
    genesis.nTime    = nTime;
    genesis.nBits    = nBits;
    genesis.nNonce   = nNonce;
    genesis.nVersion = nVersion;
    genesis.vtx.push_back(txNew);
    genesis.vtx[0].nTime = nTime;
    genesis.vtx[0].UpdateHash();
    genesis.hashPrevBlock.SetNull();
    genesis.hashMerkleRoot = BlockMerkleRoot(genesis);
    return genesis;
}

/**
 * Build the genesis block. Note that the output of its generation
 * transaction cannot be spent since it did not originally exist in the
 * database.
 *
 * CBlock(hash=000000000019d6, ver=1, hashPrevBlock=00000000000000, hashMerkleRoot=4a5e1e, nTime=1231006505, nBits=1d00ffff, nNonce=2083236893, vtx=1)
 *   CTransaction(hash=4a5e1e, ver=1, vin.size=1, vout.size=1, nLockTime=0)
 *     CTxIn(COutPoint(000000, -1), coinbase 04ffff001d0104455468652054696d65732030332f4a616e2f32303039204368616e63656c6c6f72206f6e206272696e6b206f66207365636f6e64206261696c6f757420666f722062616e6b73)
 *     CTxOut(nValue=50.00000000, scriptPubKey=0x5F1DF16B2B704C8A578D0B)
 *   vMerkleTree: 4a5e1e
 */
static CBlock CreateGenesisBlock(uint32_t nTime, uint32_t nNonce, uint32_t nBits, int32_t nVersion, const CAmount& genesisReward)
{
    const char* pszTimestamp = "Former CIA Officer: Value Of US Dollar To Plummet In Coming Reset";
    const CScript genesisOutputScript = CScript() << ParseHex("04ef5108f13e2b2781b839ea78a1ee1cb90d8fc17dcc67028e92e65223ea77f8bc8d8e4d1191f37a20ad20f326912de6e1c2e7469251a106d2a3fd55e26262d6df") << OP_CHECKSIG;
    return CreateGenesisBlock(pszTimestamp, genesisOutputScript, nTime, nNonce, nBits, nVersion, genesisReward);
}

static CBlock CreateGenesisBlockTestnet(uint32_t nTime, uint32_t nNonce, uint32_t nBits, int32_t nVersion, const CAmount& genesisReward)
{
    const char* pszTimestamp = "We Should Still See Higher Silver Prices In The Days Ahead";
    const CScript genesisOutputScript = CScript() << ParseHex("042d3e1dcb8ea3148cfdb5407383201fc0223585b25ed55ded659c0bde3a49cbc79d4ac1210d38a4766f6bb68431b273b6d5347955135502726b0743948cee36d1") << OP_CHECKSIG;
    return CreateGenesisBlock(pszTimestamp, genesisOutputScript, nTime, nNonce, nBits, nVersion, genesisReward);
}

/**
 * Main network
 */
/**
 * What makes a good checkpoint block?
 * + Is surrounded by blocks with reasonable timestamps
 *   (no blocks before with a timestamp after, none after with
 *    timestamp before)
 * + Contains no strange transactions
 */

class CMainParams : public CChainParams {
public:
    CMainParams() {
        strNetworkID = "main";
        consensus.nSubsidyHalvingInterval = 2000; // Not used
        consensus.nMajorityEnforceBlockUpgrade = 750;
        consensus.nMajorityRejectBlockOutdated = 950;
        consensus.nMajorityWindow = 1000;
        consensus.BIP34Height = 0;
        consensus.BIP34Hash = uint256S("0x00002f5951af86d668369e0c2ca13ba2e3ecbab9eb00ee5a94e5ee49d8a2918e"); // Add genesis here
        consensus.powLimit = ArithToUint256(~arith_uint256(0) >> 16);
        consensus.nPowTargetTimespan = 30;
        consensus.nPowTargetSpacing = 30;
        consensus.fPowAllowMinDifficultyBlocks = false;
        consensus.fPowNoRetargeting = false;
        consensus.nRuleChangeActivationThreshold = 15120; // 75% of 20160
        consensus.nMinerConfirmationWindow = 20160;
        consensus.nStakeMinAge = 60 * 60 * 2;	// minimum for coin age: 2 hours
        consensus.nTargetSpacing = 30; // Blocktime: 30 secs
        consensus.nStakeCombineThreshold = 1000 * COIN;
        consensus.nStakeSplitThreshold = 2 * consensus.nStakeCombineThreshold;
        consensus.nDailyBlockCount =  (24 * 60 * 60) / consensus.nTargetSpacing;
        consensus.nModifierInterval = 10 * 60; // time to elapse before new modifier is computed
        consensus.nTargetTimespan = 25 * 30;
        consensus.nLastPOWBlock = 2000;
        consensus.nBlocksPerVotingCycle = 2880 * 7; // 7 Days
        consensus.nMinimumQuorum = 0.5;
        consensus.nQuorumVotes = consensus.nBlocksPerVotingCycle * consensus.nMinimumQuorum;
        consensus.nVotesAcceptProposal = 0.7;
        consensus.nVotesRejectProposal = 0.7;
        consensus.nVotesAcceptPaymentRequest = 0.7;
        consensus.nVotesRejectPaymentRequest = 0.7;
        consensus.nCommunityFundMinAge = 50;
        consensus.nProposalMinimalFee = 5000000000;
        consensus.sigActivationTime = 1512990000;
        consensus.nCoinbaseTimeActivationHeight = 2000;
        consensus.nBlockSpreadCFundAccumulation = 500;
        consensus.nCommunityFundAmount = 0.25 * COIN;
        consensus.nCommunityFundAmountV2 = 0.5 * COIN;
        consensus.nCyclesProposalVoting = 6;
        consensus.nCyclesPaymentRequestVoting = 8;
        consensus.nPaymentRequestMaxVersion = 2;
        consensus.nProposalMaxVersion = 2;
        consensus.nMaxFutureDrift = 60;

        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].bit = 28;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nStartTime = 1199145601; // January 1, 2008
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nTimeout = 1230767999; // December 31, 2008

        // Deployment of BIP68, BIP112, and BIP113.
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].bit = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nStartTime = 0; // May 1st, 2016
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nTimeout = 999999999999ULL; // May 1st, 2017

        // Deployment of SegWit (BIP141 and BIP143)
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].bit = 4;
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].nStartTime = 0; // May 1st, 2017
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].nTimeout = 999999999999ULL; // May 1st, 2018

        // Deployment of SegWit (BIP141 and BIP143)
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT_LEGACY].bit = 1;
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT_LEGACY].nStartTime = 0; // May 1st, 2017
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT_LEGACY].nTimeout = 999999999999ULL; // May 1st, 2018

        consensus.vDeployments[Consensus::DEPLOYMENT_CSV_LEGACY].bit = 2;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV_LEGACY].nStartTime = 0; // May 1st, 2016
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV_LEGACY].nTimeout = 999999999999ULL; // May 1st, 2018

        // Deployment of Community Fund
        consensus.vDeployments[Consensus::DEPLOYMENT_COMMUNITYFUND].bit = 6;
        consensus.vDeployments[Consensus::DEPLOYMENT_COMMUNITYFUND].nStartTime = 0; // May 1st, 2017
        consensus.vDeployments[Consensus::DEPLOYMENT_COMMUNITYFUND].nTimeout = 999999999999ULL; // May 1st, 2019

        // Deployment of Community Fund Accumulation
        consensus.vDeployments[Consensus::DEPLOYMENT_COMMUNITYFUND_ACCUMULATION].bit = 7;
        consensus.vDeployments[Consensus::DEPLOYMENT_COMMUNITYFUND_ACCUMULATION].nStartTime = 0; // May 1st, 2018
        consensus.vDeployments[Consensus::DEPLOYMENT_COMMUNITYFUND_ACCUMULATION].nTimeout = 999999999999ULL; // May 1st, 2019

        // Deployment of NTP Sync
        consensus.vDeployments[Consensus::DEPLOYMENT_NTPSYNC].bit = 8;
        consensus.vDeployments[Consensus::DEPLOYMENT_NTPSYNC].nStartTime = 0; // May 1st, 2018
        consensus.vDeployments[Consensus::DEPLOYMENT_NTPSYNC].nTimeout = 999999999999ULL; // May 1st, 2019

        // Deployment of Community Fund Accumulation Spread(NPIP-0003)
        consensus.vDeployments[Consensus::DEPLOYMENT_COMMUNITYFUND_ACCUMULATION_SPREAD].bit = 14;
        consensus.vDeployments[Consensus::DEPLOYMENT_COMMUNITYFUND_ACCUMULATION_SPREAD].nStartTime = 0; // May 1st, 2018
        consensus.vDeployments[Consensus::DEPLOYMENT_COMMUNITYFUND_ACCUMULATION_SPREAD].nTimeout = 999999999999ULL; // May 1st, 2019

        // Increate in Community Fund Accumulation Ammonut (NPIP-0004)
        consensus.vDeployments[Consensus::DEPLOYMENT_COMMUNITYFUND_AMOUNT_V2].bit = 16;
        consensus.vDeployments[Consensus::DEPLOYMENT_COMMUNITYFUND_AMOUNT_V2].nStartTime = 0; // Aug 1st, 2018
        consensus.vDeployments[Consensus::DEPLOYMENT_COMMUNITYFUND_AMOUNT_V2].nTimeout = 999999999999ULL; // Aug 1st, 2019


        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 32-bit integer with any alignment.
         */
        pchMessageStart[0] = 0xa1;
        pchMessageStart[1] = 0xc7;
        pchMessageStart[2] = 0xd9;
        pchMessageStart[3] = 0x9b;
        nDefaultPort = 33445;
        nPruneAfterHeight = 100000;
        bnProofOfWorkLimit = arith_uint256(~arith_uint256() >> 16);

        genesis = CreateGenesisBlock(1546910187, 244658, 0x1f00ffff, 1, 0); // update nonce - 2nd value

	    consensus.hashGenesisBlock = genesis.GetHash();

        assert(consensus.hashGenesisBlock == uint256S("0x00002f5951af86d668369e0c2ca13ba2e3ecbab9eb00ee5a94e5ee49d8a2918e")); // todo change
        assert(genesis.hashMerkleRoot == uint256S("0xb39908dcb561c5c197f3eec9a1665494b96b846686d0606d358de7ba09b2df33")); // updated

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,63); // 63 = S
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,85);
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,150);
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x04)(0x88)(0xC3)(0xB7).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x04)(0x88)(0xC9)(0xE1).convert_to_container<std::vector<unsigned char> >();

        vSeeds.push_back(CDNSSeedData("silverseed.kazuexplore.com", "silverseed2.kazuexplore.com"));

        vFixedSeeds = std::vector<SeedSpec6>(pnSeed6_main, pnSeed6_main + ARRAYLEN(pnSeed6_main));

        fMiningRequiresPeers = true;
        fDefaultConsistencyChecks = false;
        fRequireStandard = true;
        fMineBlocksOnDemand = false;
        fTestnetToBeDeprecatedFieldRPC = false;

        checkpointData = (CCheckpointData) {
            boost::assign::map_list_of
            ( 0, uint256S("0x00002f5951af86d668369e0c2ca13ba2e3ecbab9eb00ee5a94e5ee49d8a2918e"))
            ( 2, uint256S("0x372573b0c6aaece7b0a93fb35cee8c8ba4689ae4d627bad6edd961daf84c0145")),
            1546924164, // * UNIX timestamp of last checkpoint block
            2,    // * total number of transactions between genesis and last checkpoint
                        //   (the tx=... number in the SetBestChain debug.log lines)
            7000        // * estimated number of transactions per day after checkpoint
        };
    }
};
static CMainParams mainParams;

/**
 * Testnet (v3)
 */
class CTestNetParams : public CChainParams {
public:
    CTestNetParams() {
        strNetworkID = "test";
        consensus.nSubsidyHalvingInterval = 210000;
        consensus.nMajorityEnforceBlockUpgrade = 750;
        consensus.nMajorityRejectBlockOutdated = 950;
        consensus.nMajorityWindow = 1000;
        consensus.BIP34Height = 0;
        consensus.BIP34Hash = uint256S("0x0000230ae43bcba253c50a0887379c75f2dbe9b26dfb47d51d2557189a9cbc4f"); // put testnet genesis here
        consensus.powLimit = ArithToUint256(~arith_uint256(0) >> 16);
        consensus.nPowTargetTimespan = 30;
        consensus.nPowTargetSpacing = 30;
        consensus.fPowAllowMinDifficultyBlocks = false;
        consensus.fPowNoRetargeting = false;
        consensus.nRuleChangeActivationThreshold = 300; // 75% of 400
        consensus.nMinerConfirmationWindow = 400;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].bit = 28;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nStartTime = 1199145601; // January 1, 2008
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nTimeout = 1230767999; // December 31, 2008
        consensus.nStakeMinAge = 2;	// minimum for coin age: 2 seconds
        consensus.nTargetSpacing = 30; // Blocktime: 30 secs
        consensus.nStakeCombineThreshold = 1000 * COIN;
        consensus.nStakeSplitThreshold = 2 * consensus.nStakeCombineThreshold;
        consensus.nDailyBlockCount =  (24 * 60 * 60) / consensus.nTargetSpacing;
        consensus.nModifierInterval = 10 * 60; // time to elapse before new modifier is computed
        consensus.nTargetTimespan = 25 * 30;
        consensus.nLastPOWBlock = 100000;
        consensus.nBlocksPerVotingCycle = 180; // 1.5 hours
        consensus.nMinimumQuorum = 0.5;
        consensus.nQuorumVotes = consensus.nBlocksPerVotingCycle * consensus.nMinimumQuorum;
        consensus.nVotesAcceptProposal = 0.7;
        consensus.nVotesRejectProposal = 0.7;
        consensus.nVotesAcceptPaymentRequest = 0.7;
        consensus.nVotesRejectPaymentRequest = 0.7;
        consensus.nCommunityFundMinAge = 5;
        consensus.nProposalMinimalFee = 10000;
        consensus.sigActivationTime = 1512826692;
        consensus.nCoinbaseTimeActivationHeight = 30000;
        consensus.nBlockSpreadCFundAccumulation = 500;
        consensus.nCommunityFundAmount = 0.25 * COIN;
        consensus.nCommunityFundAmountV2 = 0.5 * COIN;
        consensus.nCyclesProposalVoting = 4;
        consensus.nCyclesPaymentRequestVoting = 4;
        consensus.nPaymentRequestMaxVersion = 2;
        consensus.nProposalMaxVersion = 2;
        consensus.nMaxFutureDrift = 60;

        // Deployment of BIP68, BIP112, and BIP113.
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].bit = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nStartTime = 0; // May 1st, 2016
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nTimeout = 999999999999ULL; // May 1st, 2019

        // Deployment of SegWit (BIP141 and BIP143)
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].bit = 4;
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].nStartTime = 0; // May 1st, 2017
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].nTimeout = 999999999999ULL; // May 1st, 2019

        // Deployment of Community Fund
        consensus.vDeployments[Consensus::DEPLOYMENT_COMMUNITYFUND].bit = 6;
        consensus.vDeployments[Consensus::DEPLOYMENT_COMMUNITYFUND].nStartTime = 0; // May 1st, 2017
        consensus.vDeployments[Consensus::DEPLOYMENT_COMMUNITYFUND].nTimeout = 999999999999ULL; // May 1st, 2019

        // Deployment of Community Fund Accumulation
        consensus.vDeployments[Consensus::DEPLOYMENT_COMMUNITYFUND_ACCUMULATION].bit = 7;
        consensus.vDeployments[Consensus::DEPLOYMENT_COMMUNITYFUND_ACCUMULATION].nStartTime = 0; // May 1st, 2018
        consensus.vDeployments[Consensus::DEPLOYMENT_COMMUNITYFUND_ACCUMULATION].nTimeout = 999999999999ULL; // May 1st, 2019

        // Deployment of NTP Sync
        consensus.vDeployments[Consensus::DEPLOYMENT_NTPSYNC].bit = 8;
        consensus.vDeployments[Consensus::DEPLOYMENT_NTPSYNC].nStartTime = 0; // May 1st, 2018
        consensus.vDeployments[Consensus::DEPLOYMENT_NTPSYNC].nTimeout = 999999999999ULL; // May 1st, 2019

        // Deployment of Community Fund Accumulation Spread(NPIP-0003)
        consensus.vDeployments[Consensus::DEPLOYMENT_COMMUNITYFUND_ACCUMULATION_SPREAD].bit = 14;
        consensus.vDeployments[Consensus::DEPLOYMENT_COMMUNITYFUND_ACCUMULATION_SPREAD].nStartTime = 0; // May 1st, 2018
        consensus.vDeployments[Consensus::DEPLOYMENT_COMMUNITYFUND_ACCUMULATION_SPREAD].nTimeout = 999999999999ULL; // May 1st, 2019

        // Increate in Community Fund Accumulation Ammonut (NPIP-0004)
        consensus.vDeployments[Consensus::DEPLOYMENT_COMMUNITYFUND_AMOUNT_V2].bit = 16;
        consensus.vDeployments[Consensus::DEPLOYMENT_COMMUNITYFUND_AMOUNT_V2].nStartTime = 0; // Aug 1st, 2018
        consensus.vDeployments[Consensus::DEPLOYMENT_COMMUNITYFUND_AMOUNT_V2].nTimeout = 999999999999ULL; // Aug 1st, 2019

        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 32-bit integer with any alignment.
         */
        pchMessageStart[0] = 0x39;
        pchMessageStart[1] = 0xa1;
        pchMessageStart[2] = 0xc1;
        pchMessageStart[3] = 0xd5;
        nDefaultPort = 15556;
        nPruneAfterHeight = 1000;
        bnProofOfWorkLimit = arith_uint256(~arith_uint256() >> 16);
    
        uint32_t nTimestamp = 1546910188;
        uint256 hashGenesisBlock = uint256S("0x0000230ae43bcba253c50a0887379c75f2dbe9b26dfb47d51d2557189a9cbc4f"); // todo - update
        uint256 hashMerkleRoot = uint256S("0x5f48ff7b4ef2d72db0f40e512b6c9f67164d57aa92fff3fac0bf1726bb1eba3a"); // todo generate/update
        uint32_t nNonce = 286911; //update
	    
        genesis = CreateGenesisBlockTestnet(nTimestamp, nNonce, 0x1d00ffff, 1, 0);
        consensus.hashGenesisBlock = genesis.GetHash();
	    
        if (true && (genesis.GetHash() != hashGenesisBlock || genesis.hashMerkleRoot != hashMerkleRoot))
        {
            printf("recalculating params for testnet.\n");
            printf("old testnet genesis nonce: %d\n", genesis.nNonce);
            printf("old testnet genesis hash:  %s\n", hashGenesisBlock.ToString().c_str());
            // deliberately empty for loop finds nonce value.
            for(; genesis.GetHash() > consensus.powLimit; genesis.nNonce++){ }
            printf("new testnet genesis merkle root: %s\n", genesis.hashMerkleRoot.ToString().c_str());
            printf("new testnet genesis nonce: %d\n", genesis.nNonce);
            printf("new testnet genesis hash: %s\n", genesis.GetHash().ToString().c_str());
        }

        vSeeds.push_back(CDNSSeedData("testsilverseed.kazuexplore.com", "testsilverseed2.kazuexplore.com"));

        assert(consensus.hashGenesisBlock == hashGenesisBlock);
        assert(genesis.hashMerkleRoot == hashMerkleRoot);

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,111);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,196);
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,239);
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x40)(0x88)(0x2C)(0xCA).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x40)(0x88)(0xD1)(0x4F).convert_to_container<std::vector<unsigned char> >();

        vFixedSeeds = std::vector<SeedSpec6>(pnSeed6_test, pnSeed6_test + ARRAYLEN(pnSeed6_test));

        fMiningRequiresPeers = true;
        fDefaultConsistencyChecks = false;
        fRequireStandard = false;
        fMineBlocksOnDemand = false;
        fTestnetToBeDeprecatedFieldRPC = true;

        checkpointData = (CCheckpointData) {
            boost::assign::map_list_of
            ( 0,     hashGenesisBlock),
            1546910188, // * UNIX timestamp of last checkpoint block
            0,          // * total number of transactions between genesis and last checkpoint
                        //   (the tx=... number in the SetBestChain debug.log lines)
            7000         // * estimated number of transactions per day after checkpoint
        };

    }
};
static CTestNetParams testNetParams;

/**
 * Devnet (v3)
 */
class CDevNetParams : public CChainParams {
public:
    CDevNetParams() {
        strNetworkID = "dev";
        consensus.nSubsidyHalvingInterval = 210000;
        consensus.nMajorityEnforceBlockUpgrade = 750;
        consensus.nMajorityRejectBlockOutdated = 950;
        consensus.nMajorityWindow = 1000;
        consensus.BIP34Height = 0;
        consensus.BIP34Hash = uint256S("0x000026eff60670c77d64685fdd65ec67d5833fd84695fad3198bea2059c19104");
        consensus.powLimit = ArithToUint256(~arith_uint256(0) >> 16);
        consensus.nPowTargetTimespan = 30;
        consensus.nPowTargetSpacing = 30;
        consensus.fPowAllowMinDifficultyBlocks = false;
        consensus.fPowNoRetargeting = false;
        consensus.nRuleChangeActivationThreshold = 75; // 75% of 400
        consensus.nMinerConfirmationWindow = 100;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].bit = 28;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nStartTime = 1199145601; // January 1, 2008
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nTimeout = 1230767999; // December 31, 2008
        consensus.nStakeMinAge = 2;	// minimum for coin age: 2 seconds
        consensus.nTargetSpacing = 30; // Blocktime: 30 secs
        consensus.nStakeCombineThreshold = 1000 * COIN;
        consensus.nStakeSplitThreshold = 2 * consensus.nStakeCombineThreshold;
        consensus.nDailyBlockCount =  (24 * 60 * 60) / consensus.nTargetSpacing;
        consensus.nModifierInterval = 10 * 60; // time to elapse before new modifier is computed
        consensus.nTargetTimespan = 25 * 30;
        consensus.nLastPOWBlock = 100000;
        consensus.nBlocksPerVotingCycle = 180; // 1.5 hours
        consensus.nMinimumQuorum = 0.5;
        consensus.nQuorumVotes = consensus.nBlocksPerVotingCycle * consensus.nMinimumQuorum;
        consensus.nVotesAcceptProposal = 0.7;
        consensus.nVotesRejectProposal = 0.7;
        consensus.nVotesAcceptPaymentRequest = 0.7;
        consensus.nVotesRejectPaymentRequest = 0.7;
        consensus.nCommunityFundMinAge = 5;
        consensus.nProposalMinimalFee = 10000;
        consensus.sigActivationTime = 1512826692;
        consensus.nCoinbaseTimeActivationHeight = 0;
        consensus.nBlockSpreadCFundAccumulation = 500;
        consensus.nCommunityFundAmount = 0.25 * COIN;
        consensus.nCommunityFundAmountV2 = 0.5 * COIN;
        consensus.nCyclesProposalVoting = 4;
        consensus.nCyclesPaymentRequestVoting = 4;
        consensus.nPaymentRequestMaxVersion = 2;
        consensus.nProposalMaxVersion = 2;
        consensus.nMaxFutureDrift = 60000;

        // Deployment of BIP68, BIP112, and BIP113.
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].bit = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nStartTime = 1462060800; // May 1st, 2016
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nTimeout = 1556668800; // May 1st, 2019

        // Deployment of SegWit (BIP141 and BIP143)
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].bit = 5;
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].nStartTime = 1493424000; // May 1st, 2017
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].nTimeout = 1556668800; // May 1st, 2019

        // Deployment of Community Fund
        consensus.vDeployments[Consensus::DEPLOYMENT_COMMUNITYFUND].bit = 6;
        consensus.vDeployments[Consensus::DEPLOYMENT_COMMUNITYFUND].nStartTime = 1493424000; // May 1st, 2017
        consensus.vDeployments[Consensus::DEPLOYMENT_COMMUNITYFUND].nTimeout = 1556668800; // May 1st, 2019
	    
        // Deployment of NTP Sync
        consensus.vDeployments[Consensus::DEPLOYMENT_NTPSYNC].bit = 8;
        consensus.vDeployments[Consensus::DEPLOYMENT_NTPSYNC].nStartTime = 1525132800; // May 1st, 2018
        consensus.vDeployments[Consensus::DEPLOYMENT_NTPSYNC].nTimeout = 1556712000; // May 1st, 2019

        // Deployment of Community Fund Accumulation
        consensus.vDeployments[Consensus::DEPLOYMENT_COMMUNITYFUND_ACCUMULATION].bit = 7;
        consensus.vDeployments[Consensus::DEPLOYMENT_COMMUNITYFUND_ACCUMULATION].nStartTime = 1525132800; // May 1st, 2018
        consensus.vDeployments[Consensus::DEPLOYMENT_COMMUNITYFUND_ACCUMULATION].nTimeout = 1556712000; // May 1st, 2019

        // Deployment of Community Fund Accumulation Spread(NPIP-0003)
        consensus.vDeployments[Consensus::DEPLOYMENT_COMMUNITYFUND_ACCUMULATION_SPREAD].bit = 14;
        consensus.vDeployments[Consensus::DEPLOYMENT_COMMUNITYFUND_ACCUMULATION_SPREAD].nStartTime = 1525132800; // May 1st, 2018
        consensus.vDeployments[Consensus::DEPLOYMENT_COMMUNITYFUND_ACCUMULATION_SPREAD].nTimeout = 1556712000; // May 1st, 2019

        // Increate in Community Fund Accumulation Ammonut (NPIP-0004)
        consensus.vDeployments[Consensus::DEPLOYMENT_COMMUNITYFUND_AMOUNT_V2].bit = 16;
        consensus.vDeployments[Consensus::DEPLOYMENT_COMMUNITYFUND_AMOUNT_V2].nStartTime = 1533081600; // Aug 1st, 2018
        consensus.vDeployments[Consensus::DEPLOYMENT_COMMUNITYFUND_AMOUNT_V2].nTimeout = 1564617600; // Aug 1st, 2019


        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 32-bit integer with any alignment.
         */
        pchMessageStart[0] = 0xa8;
        pchMessageStart[1] = 0xb3;
        pchMessageStart[2] = 0x89;
        pchMessageStart[3] = 0xfa;
        nDefaultPort = 18886;
        nPruneAfterHeight = 1000;
        bnProofOfWorkLimit = arith_uint256(~arith_uint256() >> 16);

        // To create a new devnet:
        //
        // 1) Replace nTimestamp with current timestamp.
        uint32_t nTimestamp = 1525248575;
        // 2) Rebuild
        // 3) Launch daemon. It'll calculate the new parameters.
        // 4) Update the following variables with the new values:
        uint256 hashGenesisBlock = uint256S("0x000026eff60670c77d64685fdd65ec67d5833fd84695fad3198bea2059c19104");
        uint256 hashMerkleRoot = uint256S("0xdaf6febad461825e6ad9a0e5cae9ac977111bcf6860f233ee245ccb8013951d3");
        uint32_t nNonce = 2043262147;
        // 5) Rebuild. Launch daemon.
        // 6) Generate first block using RPC command "./kazusilver-cli generate 1"

        genesis = CreateGenesisBlockTestnet(nTimestamp, nNonce, 0x1d00ffff, 1, 0);
        consensus.hashGenesisBlock = genesis.GetHash();

        if (true && (genesis.GetHash() != hashGenesisBlock || genesis.hashMerkleRoot != hashMerkleRoot))
        {
            printf("recalculating params for devnet.\n");
            printf("old devnet genesis merkle root:  0x%s\n\n", hashMerkleRoot.ToString().c_str());
            printf("old devnet genesis nonce: %d\n", genesis.nNonce);
            printf("old devnet genesis hash:  0x%s\n\n", hashGenesisBlock.ToString().c_str());
            // deliberately empty for loop finds nonce value.
            for(; genesis.GetHash() > consensus.powLimit; genesis.nNonce++){ }
            printf("new devnet genesis merkle root: 0x%s\n", genesis.hashMerkleRoot.ToString().c_str());
            printf("new devnet genesis nonce: %d\n", genesis.nNonce);
            printf("new devnet genesis hash: 0x%s\n", genesis.GetHash().ToString().c_str());
            printf("use the new values to update CDevNetParams class in src/chainparams.cpp\n");
        }

        vSeeds.push_back(CDNSSeedData("devnet.kazuexplore.com", "devseed.kazuexplore.com"));

        assert(consensus.hashGenesisBlock == hashGenesisBlock);
        assert(genesis.hashMerkleRoot == hashMerkleRoot);

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,111);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,196);
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,239);
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x40)(0x88)(0x2B)(0xE1).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x40)(0x88)(0xDA)(0x4E).convert_to_container<std::vector<unsigned char> >();

        vFixedSeeds = std::vector<SeedSpec6>(pnSeed6_dev, pnSeed6_dev + ARRAYLEN(pnSeed6_dev));

        fMiningRequiresPeers = false;
        fDefaultConsistencyChecks = false;
        fRequireStandard = false;
        fMineBlocksOnDemand = true;
        fTestnetToBeDeprecatedFieldRPC = true;

        checkpointData = (CCheckpointData) {
            boost::assign::map_list_of
            ( 0,     hashGenesisBlock),
            1515437594, // * UNIX timestamp of last checkpoint block
            0,          // * total number of transactions between genesis and last checkpoint
                        //   (the tx=... number in the SetBestChain debug.log lines)
            7000         // * estimated number of transactions per day after checkpoint
        };

    }
};
static CDevNetParams devNetParams;

/**
 * Regression test
 */
class CRegTestParams : public CChainParams {
public:
    CRegTestParams() {
        strNetworkID = "regtest";
        consensus.nSubsidyHalvingInterval = 210000;
        consensus.nMajorityEnforceBlockUpgrade = 750;
        consensus.nMajorityRejectBlockOutdated = 950;
        consensus.nMajorityWindow = 1000;
        consensus.BIP34Height = 900000;
        consensus.BIP34Hash = uint256S("0xecb7444214d068028ec1fa4561662433452c1cbbd6b0f8eeb6452bcfa1d0a7d6");
        consensus.powLimit = ArithToUint256(~arith_uint256(0) >> 1);
        consensus.nPowTargetTimespan = 30;
        consensus.nPowTargetSpacing = 30;
        consensus.fPowAllowMinDifficultyBlocks = false;
        consensus.fPowNoRetargeting = false;
        consensus.nRuleChangeActivationThreshold = 75; // 75% of 100
        consensus.nMinerConfirmationWindow = 100;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].bit = 28;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nStartTime = 1199145601; // January 1, 2008
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nTimeout = 1230767999; // December 31, 2008
        consensus.nStakeMinAge = 2;	// minimum for coin age: 2 seconds
        consensus.nTargetSpacing = 30; // Blocktime: 30 secs
        consensus.nStakeCombineThreshold = 1000 * COIN;
        consensus.nStakeSplitThreshold = 2 * consensus.nStakeCombineThreshold;
        consensus.nDailyBlockCount =  (24 * 60 * 60) / consensus.nTargetSpacing;
        consensus.nModifierInterval = 10 * 60; // time to elapse before new modifier is computed
        consensus.nTargetTimespan = 25 * 30;
        consensus.nLastPOWBlock = 100000;
        consensus.nBlocksPerVotingCycle = 180; // 1.5 hours
        consensus.nMinimumQuorum = 0.5;
        consensus.nQuorumVotes = consensus.nBlocksPerVotingCycle * consensus.nMinimumQuorum;
        consensus.nVotesAcceptProposal = 0.7;
        consensus.nVotesRejectProposal = 0.7;
        consensus.nVotesAcceptPaymentRequest = 0.7;
        consensus.nVotesRejectPaymentRequest = 0.7;
        consensus.nCommunityFundMinAge = 5;
        consensus.nProposalMinimalFee = 10000;
        consensus.sigActivationTime = 0;
        consensus.nCoinbaseTimeActivationHeight = 0;
        consensus.nBlockSpreadCFundAccumulation = 10;
        consensus.nCommunityFundAmount = 0.25 * COIN;
        consensus.nCommunityFundAmountV2 = 0.5 * COIN;
        consensus.nCyclesProposalVoting = 4;
        consensus.nCyclesPaymentRequestVoting = 4;
        consensus.nPaymentRequestMaxVersion = 2;
        consensus.nProposalMaxVersion = 2;
        consensus.nMaxFutureDrift = 60000;

        // Deployment of BIP68, BIP112, and BIP113.
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].bit = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nStartTime = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nTimeout = 2556712000;

        // Deployment of SegWit (BIP141 and BIP143)
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].bit = 5;
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].nStartTime = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].nTimeout = 2556712000;

        // Deployment of Community Fund
        consensus.vDeployments[Consensus::DEPLOYMENT_COMMUNITYFUND].bit = 6;
        consensus.vDeployments[Consensus::DEPLOYMENT_COMMUNITYFUND].nStartTime = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_COMMUNITYFUND].nTimeout = 2556712000;

        // Deployment of Community Fund Accumulation
        consensus.vDeployments[Consensus::DEPLOYMENT_COMMUNITYFUND_ACCUMULATION].bit = 7;
        consensus.vDeployments[Consensus::DEPLOYMENT_COMMUNITYFUND_ACCUMULATION].nStartTime = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_COMMUNITYFUND_ACCUMULATION].nTimeout = 2556712000;

        // Deployment of NTP Sync
        consensus.vDeployments[Consensus::DEPLOYMENT_NTPSYNC].bit = 8;
        consensus.vDeployments[Consensus::DEPLOYMENT_NTPSYNC].nStartTime = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_NTPSYNC].nTimeout = 2556712000;

        // Deployment of Community Fund Accumulation Spread(NPIP-0003)
        consensus.vDeployments[Consensus::DEPLOYMENT_COMMUNITYFUND_ACCUMULATION_SPREAD].bit = 14;
        consensus.vDeployments[Consensus::DEPLOYMENT_COMMUNITYFUND_ACCUMULATION_SPREAD].nStartTime = 1525132800; // May 1st, 2018
        consensus.vDeployments[Consensus::DEPLOYMENT_COMMUNITYFUND_ACCUMULATION_SPREAD].nTimeout = 1556712000; // May 1st, 2019

        // Increate in Community Fund Accumulation Ammonut (NPIP-0004)
        consensus.vDeployments[Consensus::DEPLOYMENT_COMMUNITYFUND_AMOUNT_V2].bit = 16;
        consensus.vDeployments[Consensus::DEPLOYMENT_COMMUNITYFUND_AMOUNT_V2].nStartTime = 1533081600; // Aug 1st, 2018
        consensus.vDeployments[Consensus::DEPLOYMENT_COMMUNITYFUND_AMOUNT_V2].nTimeout = 1564617600; // Aug 1st, 2019

        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 32-bit integer with any alignment.
         */
        pchMessageStart[0] = 0x7d;
        pchMessageStart[1] = 0x11;
        pchMessageStart[2] = 0xb7;
        pchMessageStart[3] = 0x89;
        nDefaultPort = 18886;
        nPruneAfterHeight = 1000;
        bnProofOfWorkLimit = arith_uint256(~arith_uint256() >> 16);

        uint32_t nTimestamp = GetTimeNow();
        uint256 hashGenesisBlock = uint256S("0x0000e01b12644af6917e5aada637a609dd9590ad6bdc4828cd8df95258d85c02");
        uint256 hashMerkleRoot = uint256S("0x2d9101b87fe7b9deaea41849c1f3bed71e060739147802a238fe968f75ad0fd9");
        uint32_t nNonce = 2043184832;

        genesis = CreateGenesisBlockTestnet(nTimestamp, nNonce, 0x1d00ffff, 1, 0);
        consensus.hashGenesisBlock = genesis.GetHash();

        if ((genesis.GetHash() != hashGenesisBlock || genesis.hashMerkleRoot != hashMerkleRoot))
        {
            nTimestamp = GetTimeNow();
            // deliberately empty for loop finds nonce value.
            for(; genesis.GetHash() > consensus.powLimit; genesis.nNonce++){ }
            hashGenesisBlock = genesis.GetHash();
            nNonce = genesis.nNonce;
            hashMerkleRoot = genesis.hashMerkleRoot;
        }

        vSeeds.push_back(CDNSSeedData("testnav.community", "testseed.nav.community"));
        vSeeds.push_back(CDNSSeedData("testkazusilver.org", "testseed.kazusilver.org"));

        consensus.hashGenesisBlock = genesis.GetHash();

        assert(consensus.hashGenesisBlock == hashGenesisBlock);
        assert(genesis.hashMerkleRoot == hashMerkleRoot);

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,111);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,196);
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,239);
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x40)(0x88)(0x2B)(0xE1).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x40)(0x88)(0xDA)(0x4E).convert_to_container<std::vector<unsigned char> >();

        vFixedSeeds = std::vector<SeedSpec6>(pnSeed6_test, pnSeed6_test + ARRAYLEN(pnSeed6_test));

        fMiningRequiresPeers = false;
        fDefaultConsistencyChecks = false;
        fRequireStandard = false;
        fMineBlocksOnDemand = true;
        fTestnetToBeDeprecatedFieldRPC = true;

        checkpointData = (CCheckpointData) {
            boost::assign::map_list_of
            ( 0,         hashGenesisBlock),
            nTimestamp, // * UNIX timestamp of last checkpoint block
            0,          // * total number of transactions between genesis and last checkpoint
                        //   (the tx=... number in the SetBestChain debug.log lines)
            7000        // * estimated number of transactions per day after checkpoint
        };

    }
};
static CRegTestParams regTestParams;

static CChainParams *pCurrentParams = 0;

const CChainParams &Params() {
    assert(pCurrentParams);
    return *pCurrentParams;
}

CChainParams& Params(const std::string& chain)
{
    if (chain == CBaseChainParams::MAIN)
            return mainParams;
    else if (chain == CBaseChainParams::TESTNET)
            return testNetParams;
    else if (chain == CBaseChainParams::DEVNET)
            return devNetParams;
    else if (chain == CBaseChainParams::REGTEST)
            return regTestParams;
    else
        throw std::runtime_error(strprintf("%s: Unknown chain %s.", __func__, chain));
}

void SelectParams(const std::string& network)
{
    SelectBaseParams(network);
    pCurrentParams = &Params(network);
}
