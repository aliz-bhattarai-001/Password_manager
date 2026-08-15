#include "utilities.h"
#include <cmath>
#include <cctype>
#include <fstream>
#include <algorithm>

std::vector<std::string> PasswordStrengthChecker::m_commonPasswords;
bool PasswordStrengthChecker::m_commonLoaded = false;

bool PasswordStrengthChecker::hasUppercase(const std::string& pwd) {
    for (char c : pwd) {
        if (std::isalpha(static_cast<unsigned char>(c)) &&
            std::isupper(static_cast<unsigned char>(c))) {
            return true;
        }
    }
    return false;
}

bool PasswordStrengthChecker::hasLowercase(const std::string& pwd) {
    for (char c : pwd) {
        if (std::isalpha(static_cast<unsigned char>(c)) &&
            std::islower(static_cast<unsigned char>(c))) {
            return true;
        }
    }
    return false;
}

bool PasswordStrengthChecker::hasDigit(const std::string& pwd) {
    for (char c : pwd) {
        if (std::isdigit(static_cast<unsigned char>(c))) {
            return true;
        }
    }
    return false;
}

bool PasswordStrengthChecker::hasSymbol(const std::string& pwd) {
    static const std::string SYMBOLS = "!@#$%^&*()_+-=[]{}|;:,.<>?";
    return pwd.find_first_of(SYMBOLS) != std::string::npos;
}

bool PasswordStrengthChecker::hasMinLength(const std::string& pwd, int min) {
    return static_cast<int>(pwd.size()) >= min;
}

bool PasswordStrengthChecker::hasNoRepeatingChars(const std::string& pwd) {
    if (pwd.size() < 3) return true;

    int repeatCount = 1;
    for (size_t i = 1; i < pwd.size(); ++i) {
        if (pwd[i] == pwd[i - 1]) {
            ++repeatCount;
            if (repeatCount >= 3) return false;
        } else {
            repeatCount = 1;
        }
    }
    return true;
}

bool PasswordStrengthChecker::hasNoSequentialChars(const std::string& pwd) {
    if (pwd.size() < 3) return true;

    int seqCount = 1;
    for (size_t i = 1; i < pwd.size(); ++i) {
        if (static_cast<unsigned char>(pwd[i]) ==
            static_cast<unsigned char>(pwd[i - 1]) + 1) {
            ++seqCount;
            if (seqCount >= 3) return false;
        } else {
            seqCount = 1;
        }
    }
    return true;
}

bool PasswordStrengthChecker::isCommonPassword(const std::string& pwd) {
    if (!m_commonLoaded) {
        std::ifstream file("assets/common_passwords.txt");
        if (file.is_open()) {
            std::string line;
            while (std::getline(file, line)) {
                if (!line.empty()) 
                {
                    m_commonPasswords.push_back(line);
                }
            }
        }
        m_commonLoaded = true;
    }

    std::string lowerPwd = pwd;
    std::transform(lowerPwd.begin(), lowerPwd.end(), lowerPwd.begin(),
                        [](unsigned char c) { return std::tolower(c); });

    for (const std::string& common : m_commonPasswords) {
        if (common.size() != lowerPwd.size()) 
        {
            continue;
        }

        std::string lowerCommon = common;
        std::transform(lowerCommon.begin(), lowerCommon.end(), lowerCommon.begin(),[](unsigned char c) 
        { 
            return std::tolower(c);
        });

        if (lowerCommon == lowerPwd) return true;
    }
    return false;
}

int PasswordStrengthChecker::getEntropyBits(const std::string& pwd) {
    int charsetSize = 0;
    if (hasLowercase(pwd)) charsetSize += 26;
    if (hasUppercase(pwd)) charsetSize += 26;
    if (hasDigit(pwd)) charsetSize += 10;
    if (hasSymbol(pwd)) charsetSize += 32;

    if (charsetSize == 0 || pwd.empty()) return 0;

    return static_cast<int>(std::floor(std::log2(charsetSize) * pwd.size()));
}

int PasswordStrengthChecker::calculateScore(const std::string& pwd) {
    int score = 0;

    score += static_cast<int>(pwd.size());

    if (hasUppercase(pwd)) score += 4;
    if (hasLowercase(pwd)) score += 4;
    if (hasDigit(pwd)) score += 4;
    if (hasSymbol(pwd)) score += 6;

    int classes = 0;
    if (hasUppercase(pwd)) ++classes;
    if (hasLowercase(pwd)) ++classes;
    if (hasDigit(pwd)) ++classes;
    if (hasSymbol(pwd)) ++classes;
    if (classes >= 3) score += 8;
    if (classes == 1) score -= 15;

    if (!hasMinLength(pwd, 12)) {
        score -= (12 - static_cast<int>(pwd.size())) * 10;
    }

    if (!hasNoRepeatingChars(pwd)) score -= 10;
    if (!hasNoSequentialChars(pwd)) score -= 10;
    if (isCommonPassword(pwd)) score -= 30;

    score += getEntropyBits(pwd) / 2;

    return std::max(0, std::min(100, score));
}

StrengthLevel PasswordStrengthChecker::scoreToLevel(int score) {
    if (score >= 80) return StrengthLevel::VERY_STRONG;
    if (score >= 60) return StrengthLevel::STRONG;
    if (score >= 40) return StrengthLevel::GOOD;
    if (score >= 20) return StrengthLevel::FAIR;
    return StrengthLevel::WEAK;
}

std::vector<std::string> PasswordStrengthChecker::collectFeedback(const std::string& pwd) {
    std::vector<std::string> feedback;

    if (!hasMinLength(pwd, 12)) feedback.push_back("Use at least 12 characters");
    if (!hasUppercase(pwd)) feedback.push_back("Add uppercase letters");
    if (!hasLowercase(pwd)) feedback.push_back("Add lowercase letters");
    if (!hasDigit(pwd)) feedback.push_back("Add numbers");
    if (!hasSymbol(pwd)) feedback.push_back("Add symbols like !@#$");
    if (!hasNoRepeatingChars(pwd)) feedback.push_back("Avoid repeating characters (e.g. aaa)");
    if (!hasNoSequentialChars(pwd)) feedback.push_back("Avoid sequences like abc or 123");
    if (isCommonPassword(pwd)) feedback.push_back("Avoid common passwords");

    return feedback;
}

PasswordStrengthResult PasswordStrengthChecker::check(const std::string& pwd) {
    PasswordStrengthResult result;
    result.score = calculateScore(pwd);
    result.level = scoreToLevel(result.score);
    result.feedback = collectFeedback(pwd);
    result.entropyBits = getEntropyBits(pwd);
    return result;
}