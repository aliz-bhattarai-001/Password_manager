#include "utilities.h"

#include <nlohmann/json.hpp>

#include <ctime>
#include <fstream>
#include <sstream>
#include <utility>

namespace {
std::string formatTimestamp(std::time_t t) {
    std::tm tm = {};
    localtime_r(&t, &tm);
    char buf[32];
    strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M", &tm);
    return std::string(buf);
}

bool chainIsValid(const std::vector<Block>& chain) {
    for (size_t i = 0; i < chain.size(); ++i) {
        if (chain[i].getHash() != chain[i].calculateHash()) {
            return false;
        }
        if (i > 0 && chain[i].getPreviousHash() != chain[i - 1].getHash()) {
            return false;
        }
    }
    return true;
}
}  // namespace

Blockchain::Blockchain() {
    m_chain.push_back(createGenesisBlock());
}

Block Blockchain::createGenesisBlock() {
    BlockData genesisData{AuditAction::VAULT_CREATED, "", time(nullptr), ""};
    Block genesis(0, genesisData, "0");
    genesis.mineBlock();
    return genesis;
}

void Blockchain::addBlock(const BlockData& data) {
    Block b(static_cast<int>(m_chain.size()), data, getLatestBlock().getHash());
    b.mineBlock();
    m_chain.push_back(b);
}

bool Blockchain::isChainValid() const {
    return chainIsValid(m_chain);
}

std::vector<std::string> Blockchain::getAuditLog() const {
    std::vector<std::string> log;
    log.reserve(m_chain.size());
    for (const Block& b : m_chain) {
        std::string line = "[#" + std::to_string(b.getIndex()) + "] "
                         + formatTimestamp(b.getTimestamp()) + " | "
                         + auditActionToString(b.getData().action) + " | id:"
                         + b.getData().entryId;
        log.push_back(line);
    }
    return log;
}

bool Blockchain::saveToFile(const std::string& filename) const {
    nlohmann::json arr = nlohmann::json::array();
    for (const Block& b : m_chain) {
        arr.push_back(nlohmann::json::parse(b.toJson()));
    }

    std::ofstream out(filename);
    if (!out.is_open()) {
        return false;
    }
    out << arr.dump(2);
    out.close();
    return out.good();
}

bool Blockchain::loadFromFile(const std::string& filename) {
    std::ifstream in(filename);
    if (!in.is_open()) {
        return false;
    }

    std::stringstream ss;
    ss << in.rdbuf();

    try {
        nlohmann::json arr = nlohmann::json::parse(ss.str());
        if (!arr.is_array()) {
            return false;
        }

        std::vector<Block> loaded;
        for (const auto& element : arr) {
            loaded.push_back(Block::fromJson(element.dump()));
        }

        if (!chainIsValid(loaded)) {
            return false;
        }

        m_chain = std::move(loaded);
        return true;
    } catch (const std::exception&) {
        return false;
    }
}

const std::vector<Block>& Blockchain::getChain() const { return m_chain; }

const Block& Blockchain::getLatestBlock() const { return m_chain.back(); }
