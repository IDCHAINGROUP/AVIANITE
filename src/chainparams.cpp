// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2015 The Bitcoin developers
// Copyright (c) 2014-2015 The Dash developers
//Copyright (c) 2015-2020 The PIVX developers
//Copyright (c) 2020 The avianitecoin developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "chainparams.h"

#include "chainparamsseeds.h"
#include "consensus/merkle.h"
#include "util.h"
#include "utilstrencodings.h"

#include <boost/assign/list_of.hpp>

#include <assert.h>

static CBlock CreateGenesisBlock(const char* pszTimestamp, const CScript& genesisOutputScript, uint32_t nTime, uint32_t nNonce, uint32_t nBits, int32_t nVersion, const CAmount& genesisReward)
{
    CMutableTransaction txNew;
    txNew.nVersion = 1;
    txNew.vin.resize(1);
    txNew.vout.resize(1);
    txNew.vin[0].scriptSig = CScript() << 486604799 << CScriptNum(4) << std::vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
    txNew.vout[0].nValue = genesisReward;
    txNew.vout[0].scriptPubKey = genesisOutputScript;

    CBlock genesis;
    genesis.vtx.push_back(txNew);
    genesis.hashPrevBlock.SetNull();
    genesis.nVersion = nVersion;
    genesis.nTime    = nTime;
    genesis.nBits    = nBits;
    genesis.nNonce   = nNonce;
    genesis.hashMerkleRoot = BlockMerkleRoot(genesis);
    return genesis;
}

static CBlock CreateGenesisBlock(uint32_t nTime, uint32_t nNonce, const char* pszTimestamp)
{
    uint32_t nBits = 0x1e0ffff0;
    int32_t nVersion = 1;
    const CAmount& genesisReward = 0.00000050 * COIN;
    const CScript genesisOutputScript = CScript() << ParseHex("04678afdb0fe5548271967f1a67130b7105cd6a828e03909a67962e0ea1f61deb649f6bc3f4cef38c4f35504e51ec112de5c384df7ba0b8d578a4c702b6bf11d5f") << OP_CHECKSIG;
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
static Checkpoints::MapCheckpoints mapCheckpoints =
    boost::assign::map_list_of(0, uint256S("00000c76d115b76f5b5d936902fc80ea73d2905fd5ffdbe9f3a8174863748c01"))
		(6753, uint256S("0x30a7755e67daaa92ffb46fcdd81effd76c0ab70577e6ed1a7684e36de8b4d041"))
		(11597, uint256S("0xa5d0d210fae36e8215ec7f0d28aefdb3779ac6fef3138dd0ae731d1541b1e2df"))
		(47321, uint256S("0x26ca701cc395b4f1530f467253b93c28af2ba762cdfe562ef283f077d8810343"))
		(88066, uint256S("0x29f3ae026e9aa6021963a3d74047c8c219780b8713314e0f680edc4e271706d9"))
		(147251, uint256S("0x7125535bef0a6645584ca755e0f8257bcfbcf9e395abf3eb8c95cca16f1011bb"))
		(205873, uint256S("0x34489cb9498f36582241551ad8da44eb90a0986bea2111dad73cd64b20de2db1"))
		(268912, uint256S("0x24c1966e107f52403bbd3a94584c94dbc17d7d014459d5763e65ac2daa193048"))
		(344753, uint256S("0x1793b5bcbd447c21da3328e5073890da9f2471edceb12d7ea5da051be57555ba"))
		(378836, uint256S("0x4a4046b06478fd20e9d0b2b9da888a99640fed80d7e78479d74e961a007b70e3"))
		(379820, uint256S("0x767f282ecd4e43530f18470975b4eff83bb87f3a3f0daaa80fc2c3dff22659b3"))
		(380000, uint256S("0x6edbd3f0f78b7ceb4c52def034d3e23b9e45a0b8ec9041fd8e27fc450ec850fa"))
		(381000, uint256S("0x3525b1d8c7d8d2eeb69a6e696adbfb1d347567abd76a436681afe38df2827fce"))
		(382500, uint256S("0x6bbe30cbb5dbcfdc533190e02ccc22fbfb3c70d87c3756fdf23e2b342ce26144"))
		(384700, uint256S("0xce1928836821b93fd9934da4ffaa54c1de5c0c39ac9c77c82577c91b237cd5cf"))
		(385620, uint256S("0x227db4bf676afb6f80ed0881ac4a54c60afb8803b651a1d8da0bc5cd6ab63146"))
		(386520, uint256S("0xe3c29aeb1d53f3c7ebe41fae4b35af36337f316f4ade140f6a3013a248758c59"))
		(388650, uint256S("0xb5f6056018bb268a254bfabb7bc8ef48d100828140f41e256e0dead8d642efc4"))
		(389400, uint256S("0x573d1814fa9477f2ea70a7c41f4146b3c9f94e3c256d4ca27311243292ac2d8b"));

static const Checkpoints::CCheckpointData data = {
    &mapCheckpoints,
    1642743915, // * UNIX timestamp of last checkpoint block
    702872,          // * total number of transactions between genesis and last checkpoint
                //   (the tx=... number in the SetBestChain debug.log lines)
    2000        // * estimated number of transactions per day after checkpoint
};

static Checkpoints::MapCheckpoints mapCheckpointsTestnet =
    boost::assign::map_list_of(0, uint256S("0x001"))
 ;
static const Checkpoints::CCheckpointData dataTestnet = {
    &mapCheckpointsTestnet,
    1610066000,
    0,
    250};

static Checkpoints::MapCheckpoints mapCheckpointsRegtest =
    boost::assign::map_list_of(0, uint256S("0x001"));
static const Checkpoints::CCheckpointData dataRegtest = {
    &mapCheckpointsRegtest,
    1610068000,
    0,
    100};


class CMainParams : public CChainParams
{
public:
    CMainParams()
    {
        networkID = CBaseChainParams::MAIN;
        strNetworkID = "main";

        genesis = CreateGenesisBlock(1621013738, 428172, "Israel steps up strikes on Gaza amid fears of ground invasion");
        consensus.hashGenesisBlock = genesis.GetHash();
        assert(consensus.hashGenesisBlock == uint256("00000c76d115b76f5b5d936902fc80ea73d2905fd5ffdbe9f3a8174863748c01"));
        assert(genesis.hashMerkleRoot == uint256("12851f0f109baa38b157a4453d014e482cfa924ff963fbf9d36b04f212b41838"));
 
        consensus.fPowAllowMinDifficultyBlocks = false;
        consensus.powLimit   = ~UINT256_ZERO >> 20;   // avianitecoin starting difficulty is 1 / 2^12
        consensus.posLimitV1 = ~UINT256_ZERO >> 24;
        consensus.posLimitV2 = ~UINT256_ZERO >> 20;
        consensus.nBudgetCycleBlocks = 43200;       // approx. 1 every 30 days
        consensus.nBudgetFeeConfirmations = 6;      // Number of confirmations for the finalization fee
        consensus.nCoinbaseMaturity = 100;
        consensus.nFutureTimeDriftPoW = 7200;
        consensus.nFutureTimeDriftPoS = 180;
        consensus.nMasternodeCountDrift = 20;       // num of MN we allow the see-saw payments to be off by
        consensus.nMaxMoneyOut = 50000000 * COIN;
        consensus.nPoolMaxTransactions = 3;
        consensus.nProposalEstablishmentTime = 60 * 60 * 24;    // must be at least a day old to make it into a budget
        consensus.nStakeMinAge = 60 * 60;
        consensus.nStakeMinDepth = 100;
        consensus.nTargetTimespan = 40 * 60;
        consensus.nTargetTimespanV2 = 30 * 60;
        consensus.nTargetSpacing = 1 * 60;
        consensus.nTimeSlotLength = 15;
        consensus.devAddress = "EeujdRYWzyfcSaJzVj3QiPEborRgCS7nd4";
				
        // spork keys
        consensus.strSporkPubKey = "04e1ae4c16334bfd5a8d369982dd0652a724ab3726904f268d34e9fb8bfa37ecb0a0f65b612f46f6cf1517985b7046943690fd458ed9b0897753822702578ca934";
        consensus.strSporkPubKeyOld = "04e1ae4c16334bfd5a8d369982dd0652a724ab3726904f268d34e9fb8bfa37ecb0a0f65b612f46f6cf1517985b7046943690fd458ed9b0897753822702578ca934";
        consensus.nTime_EnforceNewSporkKey = 1610064000;
        consensus.nTime_RejectOldSporkKey = 1610060000;

        // height-based activations
        consensus.height_last_PoW = 1000;
        consensus.height_start_BIP65 = 1003;
        consensus.height_start_MessSignaturesV2 = 1030;  // height_start_TimeProtoV2
        consensus.height_start_StakeModifierNewSelection = 1;
        consensus.height_start_StakeModifierV2 = 1001;
        consensus.height_start_TimeProtoV2 = 1030;

        // Network upgrades
        consensus.vUpgrades[Consensus::BASE_NETWORK].nActivationHeight = Consensus::NetworkUpgrade::ALWAYS_ACTIVE;
        consensus.vUpgrades[Consensus::UPGRADE_TESTDUMMY].nActivationHeight = Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT;
        consensus.vUpgrades[Consensus::UPGRADE_PURPLE_FENIX].nActivationHeight = Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT;

        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 4-byte int at any alignment.
         */
        pchMessageStart[0] = 0xaf;
        pchMessageStart[1] = 0x74;
        pchMessageStart[2] = 0x2c;
        pchMessageStart[3] = 0x1e;
        nDefaultPort = 6662;

        vSeeds.emplace_back("108.61.220.138", "108.61.220.138", true);
        vSeeds.emplace_back("2001:19f0:6001:23b7:5400:03ff:fe5b:93c7", "2001:19f0:6001:23b7:5400:03ff:fe5b:93c7", true);
        vSeeds.emplace_back("207.246.102.131", "207.246.102.131", true);
        vSeeds.emplace_back("2001:19f0:6001:14e6:5400:03ff:fe5b:93c8", "2001:19f0:6001:14e6:5400:03ff:fe5b:93c8", true);
        vSeeds.emplace_back("45.77.68.89", "45.77.68.89", true);
        vSeeds.emplace_back("2001:19f0:6001:540f:5400:03ff:fe5b:93c9", "2001:19f0:6001:540f:5400:03ff:fe5b:93c9", true);
        vSeeds.emplace_back("45.76.168.47", "45.76.168.47", true);
        vSeeds.emplace_back("2001:19f0:6001:52df:5400:03ff:fe5b:93ca", "2001:19f0:6001:52df:5400:03ff:fe5b:93ca", true);
        vSeeds.emplace_back("62.171.153.102", "62.171.153.102", true);
        vSeeds.emplace_back("165.22.74.51", "165.22.74.51", true);
        vSeeds.emplace_back("2a02:c207:2027:4883:6f83::16", "2a02:c207:2027:4883:6f83::16", true);
        vSeeds.emplace_back("2a02:c205:2028:7704:a27::5", "2a02:c205:2028:7704:a27::5", true); 

        // Note that of those with the service bits flag, most only support a subset of possible options
        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 33);  // AVIAN addresses start with 'E'
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 8);   // AVIAN script addresses start with '4'
        base58Prefixes[STAKING_ADDRESS] = std::vector<unsigned char>(1, 60); // AVIAN private keys start with 'R'
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 212);
        // AVIAN BIP32 pubkeys start with 'xpub' (Bitcoin defaults)
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x04)(0x88)(0xB2)(0x1E).convert_to_container<std::vector<unsigned char> >();
        // AVIAN BIP32 prvkeys start with 'xprv' (Bitcoin defaults)
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x04)(0x88)(0xAD)(0xE4).convert_to_container<std::vector<unsigned char> >();
        // BIP44 coin type is from https://github.com/satoshilabs/slips/blob/master/slip-0044.md
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x00)(0x00)(0x77).convert_to_container<std::vector<unsigned char> >();

        vFixedSeeds = std::vector<SeedSpec6>(pnSeed6_main, pnSeed6_main + ARRAYLEN(pnSeed6_main));
    }

    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return data;
    }

};
static CMainParams mainParams;

/**
 * Testnet (v3)
 */
class CTestNetParams : public CMainParams
{
public:
    CTestNetParams()
    {
        networkID = CBaseChainParams::TESTNET;
        strNetworkID = "test";
/*
//! Modify the TESTNET genesis block so the timestamp is valid for a later start.
*/
        genesis = CreateGenesisBlock(1610066000, 0, "Lorem ipsum dolor sit amet, consectetur adipiscing elit");        
        consensus.hashGenesisBlock = genesis.GetHash();
	//assert(consensus.hashGenesisBlock == uint256S("0x001"));
        //assert(genesis.hashMerkleRoot == uint256S("0x001"));

        consensus.fPowAllowMinDifficultyBlocks = true;
        consensus.powLimit   = ~UINT256_ZERO >> 14;   // avianitecoin starting difficulty is 1 / 2^12
        consensus.posLimitV1 = ~UINT256_ZERO >> 24;
        consensus.posLimitV2 = ~UINT256_ZERO >> 20;
        consensus.nBudgetCycleBlocks = 43200;       // approx. 1 every 30 days
        consensus.nBudgetFeeConfirmations = 6;      // Number of confirmations for the finalization fee
        consensus.nCoinbaseMaturity = 60;
        consensus.nFutureTimeDriftPoW = 7200;
        consensus.nFutureTimeDriftPoS = 180;
        consensus.nMasternodeCountDrift = 20;       // num of MN we allow the see-saw payments to be off by
        consensus.nMaxMoneyOut = 99000000 * COIN;
        consensus.nPoolMaxTransactions = 3;
        consensus.nProposalEstablishmentTime = 60 * 60 * 24;    // must be at least a day old to make it into a budget
        consensus.nStakeMinAge = 60 * 60;
        consensus.nStakeMinDepth = 100;
        consensus.nTargetTimespan = 40 * 60;
        consensus.nTargetTimespanV2 = 30 * 60;
        consensus.nTargetSpacing = 1 * 60;
        consensus.nTimeSlotLength = 15;
        consensus.devAddress = "RSGQZGPGzxMNQkNB5KPPbEDuEPaJytMY6q";

        // spork keys
        consensus.strSporkPubKey = "04678afdb0fe5548271967f1a67130b7105cd6a828e03909a67962e0ea1f61deb649f6bc3f4cef38c4f35504e51ec112de5c384df7ba0b8d578a4c702b6bf11d5f";
        consensus.strSporkPubKeyOld = "046f781df141e6ab82ca37ddb745803e2d4744137dcfdccd4e8f1e308e2001738e450e35a92828e85b99e18d88f4b78f7fe4eaf1072d91a06b82e44f02a4e425b2";
        consensus.nTime_EnforceNewSporkKey = 1610066000;
        consensus.nTime_RejectOldSporkKey = 1610060000;

        // height based activations
        consensus.height_last_PoW = 1000;
        consensus.height_start_BIP65 = 851019;                  // Block v5: d1ec8838ba8f644e78dd4f8e861d31e75457dfe607b31deade30e806b5f46c1c
        consensus.height_start_MessSignaturesV2 = 1347000;      // height_start_TimeProtoV2
        consensus.height_start_StakeModifierNewSelection = 51197;
        consensus.height_start_StakeModifierV2 = 1214000;       // Block v6: 1822577176173752aea33d1f60607cefe9e0b1c54ebaa77eb40201a385506199
        consensus.height_start_TimeProtoV2 = 1347000;           // Block v7: 30c173ffc09a13f288bf6e828216107037ce5b79536b1cebd750a014f4939882

        // Network upgrades
        consensus.vUpgrades[Consensus::BASE_NETWORK].nActivationHeight =
                Consensus::NetworkUpgrade::ALWAYS_ACTIVE;
        consensus.vUpgrades[Consensus::UPGRADE_TESTDUMMY].nActivationHeight =
                Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT;
        consensus.vUpgrades[Consensus::UPGRADE_PURPLE_FENIX].nActivationHeight =
                Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT;

        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 4-byte int at any alignment.
         */
        
        pchMessageStart[0] = 0xf3;
        pchMessageStart[1] = 0x24;
        pchMessageStart[2] = 0x9a;
        pchMessageStart[3] = 0x5f;
        nDefaultPort = 8452;

        vFixedSeeds.clear();
        vSeeds.clear();
        
        // nodes with support for servicebits filtering should be at the top

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 75); // AVIAN addresses start with 'X'
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 4); // AVIAN script addresses start with '3'
        base58Prefixes[STAKING_ADDRESS] = std::vector<unsigned char>(1, 80); // AVIAN private keys start with 'Z'
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 212);
        // AVIAN BIP32 pubkeys start with 'xpub' (Bitcoin defaults)
	base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x04)(0x88)(0xB2)(0x1E).convert_to_container<std::vector<unsigned char> >();
	// AVIAN BIP32 prvkeys start with 'xprv' (Bitcoin defaults)
	base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x04)(0x88)(0xAD)(0xE4).convert_to_container<std::vector<unsigned char> >();
	// BIP44 coin type is from https://github.com/satoshilabs/slips/blob/master/slip-0044.md
	base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x00)(0x00)(0x77).convert_to_container<std::vector<unsigned char> >();

        vFixedSeeds = std::vector<SeedSpec6>(pnSeed6_test, pnSeed6_test + ARRAYLEN(pnSeed6_test));
    }

    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return dataTestnet;
    }
};
static CTestNetParams testNetParams;

/**
 * Regression test
 */
class CRegTestParams : public CTestNetParams
{
public:
    CRegTestParams()
    {
        networkID = CBaseChainParams::REGTEST;
        strNetworkID = "regtest";
/*
//! Modify the REGTEST genesis block so the timestamp is valid for a later start.
*/
        genesis = CreateGenesisBlock(1610068000, 0, "Lorem ipsum dolor sit amet, consectetur adipiscing elit");        
        consensus.hashGenesisBlock = genesis.GetHash();
	//assert(consensus.hashGenesisBlock == uint256S("0x001"));
        //assert(genesis.hashMerkleRoot == uint256S("0x001"));

        consensus.fPowAllowMinDifficultyBlocks = true;
        consensus.powLimit   = ~UINT256_ZERO >> 14;   // avianitecoin starting difficulty is 1 / 2^12
        consensus.posLimitV1 = ~UINT256_ZERO >> 24;
        consensus.posLimitV2 = ~UINT256_ZERO >> 20;
        consensus.nBudgetCycleBlocks = 43200;       // approx. 1 every 30 days
        consensus.nBudgetFeeConfirmations = 6;      // Number of confirmations for the finalization fee
        consensus.nCoinbaseMaturity = 30;
        consensus.nFutureTimeDriftPoW = 7200;
        consensus.nFutureTimeDriftPoS = 180;
        consensus.nMasternodeCountDrift = 20;       // num of MN we allow the see-saw payments to be off by
        consensus.nMaxMoneyOut = 99000000 * COIN;
        consensus.nPoolMaxTransactions = 3;
        consensus.nProposalEstablishmentTime = 60 * 60 * 24;    // must be at least a day old to make it into a budget
        consensus.nStakeMinAge = 60 * 60;
        consensus.nStakeMinDepth = 100;
        consensus.nTargetTimespan = 40 * 60;
        consensus.nTargetTimespanV2 = 30 * 60;
        consensus.nTargetSpacing = 1 * 60;
        consensus.nTimeSlotLength = 15;
        consensus.devAddress = "RSGQZGPGzxMNQkNB5KPPbEDuEPaJytMY6q";

        /* Spork Key for RegTest:
        WIF private key: 932HEevBSujW2ud7RfB1YF91AFygbBRQj3de3LyaCRqNzKKgWXi
        private key hex: bd4960dcbd9e7f2223f24e7164ecb6f1fe96fc3a416f5d3a830ba5720c84b8ca
        Address: yCvUVd72w7xpimf981m114FSFbmAmne7j9
        */
        consensus.strSporkPubKey = "046f781df141e6ab82ca37ddb745803e2d4744137dcfdccd4e8f1e308e2001738e450e35a92828e85b99e18d88f4b78f7fe4eaf1072d91a06b82e44f02a4e425b2";
        consensus.strSporkPubKeyOld = "";
        consensus.nTime_EnforceNewSporkKey = 1610068000;
        consensus.nTime_RejectOldSporkKey = 1610060000;

        // height based activations
        consensus.height_last_PoW = 350;
        consensus.height_start_BIP65 = 851019;              // Not defined for regtest. Inherit TestNet value.
        consensus.height_start_MessSignaturesV2 = 1;
        consensus.height_start_StakeModifierNewSelection = 0;
        consensus.height_start_StakeModifierV2 = 251;       // start with modifier V2 on regtest
        consensus.height_start_TimeProtoV2 = 999999999;

        // Network upgrades
        consensus.vUpgrades[Consensus::BASE_NETWORK].nActivationHeight =
                Consensus::NetworkUpgrade::ALWAYS_ACTIVE;
        consensus.vUpgrades[Consensus::UPGRADE_TESTDUMMY].nActivationHeight =
                Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT;
        consensus.vUpgrades[Consensus::UPGRADE_PURPLE_FENIX].nActivationHeight =
                Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT;

        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 4-byte int at any alignment.
         */

        pchMessageStart[0] = 0xaa;
        pchMessageStart[1] = 0xcb;
        pchMessageStart[2] = 0x7c;
        pchMessageStart[3] = 0xad;
        nDefaultPort = 8552;

        vFixedSeeds.clear(); //! Testnet mode doesn't have any fixed seeds.
        vSeeds.clear();      //! Testnet mode doesn't have any DNS seeds.
    }

    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return dataRegtest;
    }

    void UpdateNetworkUpgradeParameters(Consensus::UpgradeIndex idx, int nActivationHeight)
    {
        assert(idx > Consensus::BASE_NETWORK && idx < Consensus::MAX_NETWORK_UPGRADES);
        consensus.vUpgrades[idx].nActivationHeight = nActivationHeight;
    }
};
static CRegTestParams regTestParams;

static CChainParams* pCurrentParams = 0;

const CChainParams& Params()
{
    assert(pCurrentParams);
    return *pCurrentParams;
}

CChainParams& Params(CBaseChainParams::Network network)
{
    switch (network) {
    case CBaseChainParams::MAIN:
        return mainParams;
    case CBaseChainParams::TESTNET:
        return testNetParams;
    case CBaseChainParams::REGTEST:
        return regTestParams;
    default:
        assert(false && "Unimplemented network");
        return mainParams;
    }
}

void SelectParams(CBaseChainParams::Network network)
{
    SelectBaseParams(network);
    pCurrentParams = &Params(network);
}

bool SelectParamsFromCommandLine()
{
    CBaseChainParams::Network network = NetworkIdFromCommandLine();
    if (network == CBaseChainParams::MAX_NETWORK_TYPES)
        return false;

    SelectParams(network);
    return true;
}

void UpdateNetworkUpgradeParameters(Consensus::UpgradeIndex idx, int nActivationHeight)
{
    regTestParams.UpdateNetworkUpgradeParameters(idx, nActivationHeight);
}
