// Copyright (c) 2020 The SAPP developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef BITCOIN_CONTEXT_H
#define BITCOIN_CONTEXT_H

#include <set>
#include <string>
#include <memory>
#include <vector>

class CContext;

/**
 * Create and initialize unique global application context object.
 * Must be called from the main thread before any other thread started.
 * @throw runtime_error if context has already initialzied or any error occurs
 */
void CreateContext();

/**
 * Free resources allocated for context object.
 * Must be called from the main thread after all other threads completed.
 * @throw no exceptions
 */
void ReleaseContext();

/**
 * Returns unique application context object.
 * @throw runtime_error if context is not initialized
 * @return context reference
 */
CContext& GetContext();

/**
 * Context scope initializer. Automatically create/release context.
 */
struct ContextScopeInit
{
    ContextScopeInit() { CreateContext(); }

    ~ContextScopeInit() { ReleaseContext(); }

private:
    ContextScopeInit(const ContextScopeInit&);
    ContextScopeInit& operator=(const ContextScopeInit&);
};

/**
 * Unique global object that represents application context.
 * Initialized at the application startup and destroyed just before return from main.
 */
class CContext
{
public:
    CContext();

    ~CContext();

    /**
     * Add ColossusXT address to the ban list.
     * @param mempool list of ColossusXT address for mempool ban
     * @param consensus list of ColossusXT address for consensus ban
     */
    void AddAddressToBan(
            const std::vector<std::string>& mempool,
            const std::vector<std::string>& consensus);

    /**
     * Return true if there is at least one address for banning.
     */
    bool MempoolBanActive() const;

    /**
     * Return true if given address is banned.
     * @param addr ColossusXT address in base58 format
     */
    bool MempoolBanActive(const std::string& addr) const;

    /**
     * Return true if there is at least one address for banning.
     */
    bool ConsensusBanActive() const;

    /**
     * Return true if given address is banned.
     * @param addr ColossusXT address in base58 format
     */
    bool ConsensusBanActive(const std::string& addr) const;

private:
    CContext(const CContext&);
    CContext& operator=(const CContext&);

private:
	std::set<std::string> banAddrMempool_;
    std::set<std::string> banAddrConsensus_;
};

#endif // BITCOIN_CONTEXT_H