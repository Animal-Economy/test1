// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2012 The Bitcoin developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "assert.h"

#include "chainparams.h"
#include "main.h"
#include "util.h"

#include <boost/assign/list_of.hpp>

using namespace boost::assign;

struct SeedSpec6 {
    uint8_t addr[16];
    uint16_t port;
};

#include "chainparamsseeds.h"

//
// Main network
//

// Convert the pnSeeds6 array into usable address objects.
static void convertSeed6(std::vector<CAddress> &vSeedsOut, const SeedSpec6 *data, unsigned int count)
{
    // It'll only connect to one or two seed nodes because once it connects,
    // it'll get a pile of addresses with newer timestamps.
    // Seed nodes are given a random 'last seen time' of between one and two
    // weeks ago.
    const int64_t nOneWeek = 7*24*60*60;
    for (unsigned int i = 0; i < count; i++)
    {
        struct in6_addr ip;
        memcpy(&ip, data[i].addr, sizeof(ip));
        CAddress addr(CService(ip, data[i].port));
        addr.nTime = GetTime() - GetRand(nOneWeek) - nOneWeek;
        vSeedsOut.push_back(addr);
    }
}

class CMainParams : public CChainParams {
public:
    CMainParams() {
        // The message start string is designed to be unlikely to occur in normal data.
        // The characters are rarely used upper ASCII, not valid as UTF-8, and produce
        // a large 4-byte int at any alignment.
        pchMessageStart[0] = 0x7d;
        pchMessageStart[1] = 0x4f;
        pchMessageStart[2] = 0x8b;
        pchMessageStart[3] = 0x4d;
        nDefaultPort = 10712;
        nRPCPort = 12107;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 20);

        const char* pszTimestamp = "10.7.2016 at 8:34 Ljubljana time. Happy 4th birthday Taj!";
        std::vector<CTxIn> vin;
        vin.resize(1);
        vin[0].scriptSig = CScript() << 0 << CBigNum(42) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        std::vector<CTxOut> vout;
        vout.resize(1);
        vout[0].SetEmpty();
        CTransaction txNew(1, 1468132440, vin, vout, 0);
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
        genesis.nTime    = 1468132440;
        genesis.nBits    = bnProofOfWorkLimit.GetCompact();
        genesis.nNonce   = 897589;

		
        //// debug print
	bool regenesis = false;
	if (regenesis)
        {
            uint256 hashTarget = CBigNum().SetCompact(genesis.nBits).getuint256();
            while (genesis.GetHash() > hashTarget)
            {
                ++genesis.nNonce;
                if (genesis.nNonce == 0)
                {
                    printf("NONCE WRAPPED, incrementing time");
                    ++genesis.nTime;
                }
            }
            cout << "mainnet.genesis : \n" << genesis.ToString() << endl;
            cout << "mainnet.genesis.GetHash(): " << genesis.GetHash().ToString() << endl;
            cout << "mainnet.genesis.hashMerkleRoot: " << genesis.hashMerkleRoot.ToString() << endl;
            cout << "mainnet.genesis.nTime: " << genesis.nTime << endl;
            cout << "mainnet.genesis.nNonce: " << genesis.nNonce << endl;
        }

        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("0x00000b414afcc2b242531999ae4cc5e7279eaa1508aa72cb289cc175ebb1db2b"));
        assert(genesis.hashMerkleRoot == uint256("0xb9cae0f7e601dd820bc91144000efcc4a6883e1b4b39a4b2034c1b0f5e075a52"));

        vSeeds.push_back(CDNSSeedData("tajcoin.tech", "node1.tajcoin.tech"));
        vSeeds.push_back(CDNSSeedData("tajcoin.tech", "node2.tajcoin.tech"));
        vSeeds.push_back(CDNSSeedData("tajcoin.tech", "node3.tajcoin.tech"));
        vSeeds.push_back(CDNSSeedData("tajcoin.tech", "node4.tajcoin.tech"));
        vSeeds.push_back(CDNSSeedData("tajcoin.tech", "node5.tajcoin.tech"));
        vSeeds.push_back(CDNSSeedData("tajcoin.tech", "node6.tajcoin.tech"));
        vSeeds.push_back(CDNSSeedData("tajcoin.tech", "node7.tajcoin.tech"));
        vSeeds.push_back(CDNSSeedData("tajcoin.tech", "node8.tajcoin.tech"));
        vSeeds.push_back(CDNSSeedData("tajcoin.tech", "node9.tajcoin.tech"));
        
        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,65); // "7"
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,5); // "8"
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,111); // "s"
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x04)(0x88)(0xB2)(0x1E).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x04)(0x88)(0xAD)(0xE4).convert_to_container<std::vector<unsigned char> >();

        convertSeed6(vFixedSeeds, pnSeed6_main, ARRAYLEN(pnSeed6_main));

        nLastPOWBlock = 900000;
    }

    virtual const CBlock& GenesisBlock() const { return genesis; }
    virtual Network NetworkID() const { return CChainParams::MAIN; }

    virtual const vector<CAddress>& FixedSeeds() const {
        return vFixedSeeds;
    }
protected:
    CBlock genesis;
    vector<CAddress> vFixedSeeds;
};
static CMainParams mainParams;


//
// Testnet
//

class CTestNetParams : public CMainParams {
public:
    CTestNetParams() {
        // The message start string is designed to be unlikely to occur in normal data.
        // The characters are rarely used upper ASCII, not valid as UTF-8, and produce
        // a large 4-byte int at any alignment.
        pchMessageStart[0] = 0xa7;
        pchMessageStart[1] = 0x41;
        pchMessageStart[2] = 0xae;
        pchMessageStart[3] = 0x7c;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 8);
        nDefaultPort = 24452;
        nRPCPort = 24453;
        strDataDir = "testnet";

        // Modify the testnet genesis block so the timestamp is valid for a later start.
        genesis.nBits  = bnProofOfWorkLimit.GetCompact();
        genesis.nTime  = 1509181222;
        genesis.nNonce = 220;
	
	bool regenesis = false;
	if (regenesis)
        {
            uint256 hashTarget = CBigNum().SetCompact(genesis.nBits).getuint256();
            while (genesis.GetHash() > hashTarget)
            {
                ++genesis.nNonce;
                if (genesis.nNonce == 0)
                {
                    printf("NONCE WRAPPED, incrementing time");
                    ++genesis.nTime;
                }
            }
            cout << "testnet.genesis : \n" << genesis.ToString() << endl;
            cout << "testnet.genesis.GetHash(): " << genesis.GetHash().ToString() << endl;
            cout << "testnet.genesis.hashMerkleRoot: " << genesis.hashMerkleRoot.ToString() << endl;
            cout << "testnet.genesis.nTime: " << genesis.nTime << endl;
            cout << "testnet.genesis.nNonce: " << genesis.nNonce << endl;
        }

        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("0x00dca6b25fcf66a529361bd5e382831d34b82e3cdda8b320ecb6dd079917b430"));
        assert(genesis.hashMerkleRoot == uint256("0xe3cdf2d9d1d977e50cf9d39be6a91aeae5dae61d3ba6d5f82c7f7184c9da8523"));

        vFixedSeeds.clear();
        vSeeds.push_back(CDNSSeedData("Tajcoin1", "45.77.203.20"));
        vSeeds.push_back(CDNSSeedData("Tajcoin2", "45.77.197.236"));

        /** DEPRICATED IN QT 5.6+ (To compile on Qt5.5.1 and lower uncomment  */
        /*
        base58Prefixes[PUBKEY_ADDRESS] = list_of(111);
        base58Prefixes[SCRIPT_ADDRESS] = list_of(196);
        base58Prefixes[SECRET_KEY]     = list_of(239);
        base58Prefixes[EXT_PUBLIC_KEY] = list_of(0x04)(0x35)(0x87)(0xCF);
        base58Prefixes[EXT_SECRET_KEY] = list_of(0x04)(0x35)(0x83)(0x94);
        */
        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,111);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,196);
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,239);
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x04)(0x35)(0x87)(0xCF).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x04)(0x35)(0x83)(0x94).convert_to_container<std::vector<unsigned char> >();


        convertSeed6(vFixedSeeds, pnSeed6_test, ARRAYLEN(pnSeed6_test));

        nLastPOWBlock = 0x7fffffff;
    }
    virtual Network NetworkID() const { return CChainParams::TESTNET; }
};
static CTestNetParams testNetParams;




static CChainParams *pCurrentParams = &mainParams;

const CChainParams &Params() {
    return *pCurrentParams;
}

void SelectParams(CChainParams::Network network) {
    switch (network) {
        case CChainParams::MAIN:
            pCurrentParams = &mainParams;
            break;
        case CChainParams::TESTNET:
            pCurrentParams = &testNetParams;
            break;

        default:
            assert(false && "Unimplemented network");
            return;
    }
}

bool SelectParamsFromCommandLine() {

    bool fTestNet = GetBoolArg("-testnet", false);



    if (fTestNet) {
        SelectParams(CChainParams::TESTNET);
    } else {
        SelectParams(CChainParams::MAIN);
    }
    return true;
}
