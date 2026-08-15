#include "utilities.h"

#include <nlohmann/json.hpp>

#include <ctime>
#include <stdexcept>

namespace {
std::string formatTimestamp(std::time_t t) {
    std::tm tm = {};
    localtime_r(&t, &tm);
    char buf[32];
    strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M", &tm);
    return std::string(buf);
}
}  // namespace

Block::Block(int index, const BlockData& data, const std::string& previousHash,
             std::time_t timestamp, int nonce, const std::string& hash)
    : m_index(index), m_data(data), m_previousHash(previousHash),
      m_timestamp(timestamp), m_nonce(nonce), m_hash(hash) {}

Block::Block(int index, const BlockData& data, const std::string& previousHash)
    : m_index(index), m_data(data), m_previousHash(previousHash),
      m_timestamp(time(nullptr)), m_nonce(0) {
    m_hash = calculateHash();
}

std::string Block::calculateHash() const {
    std::string input = std::to_string(m_index)
                      + std::to_string(m_timestamp)
                      + m_data.toString()
                      + m_previousHash
                      + std::to_string(m_nonce);
    return HashManager::sha256(input);
}

void Block::mineBlock(int difficulty) {
    std::string target(difficulty, '0');
    do {
        ++m_nonce;
        m_hash = calculateHash();
    } while (m_hash.substr(0, difficulty) != target);
}

std::string Block::toJson() const {
    nlohmann::json j;
    j["index"] = m_index;
    j["timestamp"] = m_timestamp;
    j["previousHash"] = m_previousHash;
    j["nonce"] = m_nonce;
    j["hash"] = m_hash;
    j["data"]["action"] = auditActionToString(m_data.action);
    j["data"]["entryId"] = m_data.entryId;
    j["data"]["timestamp"] = m_data.timestamp;
    j["data"]["metadata"] = m_data.metadata;
    return j.dump();
}

Block Block::fromJson(const std::string& jsonStr) {
    nlohmann::json j = nlohmann::json::parse(jsonStr);

    BlockData data;
    data.action = auditActionFromString(j["data"].value("action", std::string()));
    data.entryId = j["data"].value("entryId", std::string());
    data.timestamp = j["data"].value("timestamp", std::time_t(0));
    data.metadata = j["data"].value("metadata", std::string());

    return Block(
        j.value("index", 0),
        data,
        j.value("previousHash", std::string()),
        j.value("timestamp", std::time_t(0)),
        j.value("nonce", 0),
        j.value("hash", std::string())
    );
}

int Block::getIndex() const { return m_index; }

const BlockData& Block::getData() const { return m_data; }

const std::string& Block::getPreviousHash() const { return m_previousHash; }

std::time_t Block::getTimestamp() const { return m_timestamp; }

int Block::getNonce() const { return m_nonce; }

const std::string& Block::getHash() const { return m_hash; }
