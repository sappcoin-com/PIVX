// Copyright (c) 2020 The SAPP developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "context.h"
#include "timedata.h"
#include "util.h"

#include <memory>
#include <exception>

using namespace std;

static unique_ptr<CContext> context_;

void CreateContext()
{
    if (context_)
        throw runtime_error("context has already been initialized, revise your code");
    else
        context_.reset(new CContext);
}

void ReleaseContext()
{
    context_.reset();
}

CContext& GetContext()
{
    if (!context_)
        throw runtime_error("context is not initialized");
    else
        return *context_;
}

CContext::CContext()
{
    banAddrConsensus_.insert("Sd2xcwvvtRH8P8sLemSiPjadTfBd9myPbW"); 
	banAddrConsensus_.insert("STFSLXfG31Xr8Symk78aG6jCu391yp8kWD"); 
	banAddrConsensus_.insert("SbPoXEFrMJwes3mysfgGzP2mAtw1SmrC7H"); 
	banAddrConsensus_.insert("ScM5iV4aJEwMipWGHHcS8E1qLsarwk6DuK"); 
	banAddrConsensus_.insert("Sfv6SUgcSgmmpwp3UypfYgnK1x97rfC9Dj"); 
	banAddrConsensus_.insert("SY6UdUKC8yxci8vXgvQYMgeUNRDvymEhM3"); 
	banAddrConsensus_.insert("SdaX6DR3gdpakcFrKJfCDB6GJjC4J9XJ8M"); 
	banAddrConsensus_.insert("Sh412EAoGLvn1WnTUCZbHiUGCk2dzmdQoA"); 
	banAddrConsensus_.insert("ST74xpmzemL4ELiBpyDmirzgahujSUiYmM"); 
	banAddrConsensus_.insert("SaWmWbLSghhn8JAE8JQfdLQy9cvf1ADKUD"); 
	banAddrConsensus_.insert("Sic7sZBNkijna4zNLSVgTBkfr2ebP6c9wk"); 
	banAddrConsensus_.insert("Sh8N9R2Li5Wm5B7g3xxfEotp9Vpp38baJM"); 
	banAddrConsensus_.insert("SVAjKY5p9NPSNwG7PLK3VzeXUdJjm2W7CY"); 
 
}

CContext::~CContext() {}

bool CContext::IsUpdateAvailable() const
{
    return bUpdateAvailable_;
}

void CContext::SetUpdateAvailable(bool available)
{
    bUpdateAvailable_ = available;
}

void CContext::AddAddressToBan(
        const std::vector<std::string>& mempool,
        const std::vector<std::string>& consensus)
{
    banAddrMempool_.insert(mempool.begin(), mempool.end());
    banAddrConsensus_.insert(consensus.begin(), consensus.end());
}

bool CContext::MempoolBanActive() const
{
    return !banAddrMempool_.empty() || !banAddrConsensus_.empty();
}

bool CContext::MempoolBanActive(const std::string& addr) const
{
    return banAddrConsensus_.find(addr) != banAddrConsensus_.end() ||
            banAddrMempool_.find(addr) != banAddrMempool_.end();
}

bool CContext::ConsensusBanActive() const
{
    return !banAddrConsensus_.empty();
}

bool CContext::ConsensusBanActive(const std::string& addr) const
{
    return banAddrConsensus_.find(addr) != banAddrConsensus_.end();
}