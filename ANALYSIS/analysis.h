#ifndef ANALYSIS_H
#define ANALYSIS_H

#include <string>
#include <vector>
#include "../LEXICON/lexeme.h"

/**
 * Analysis: Represents a complete morphological analysis of a word
 *
 * Components:
 *   1. Stem: The base form (lexeme)
 *   2. POS: Grammatical category
 *   3. Features: Morphological tags (+PL, +PAST, etc.)
 *   4. Weight: Ranking score (higher = more likely)
 *   5. Prefix: Optional derivational prefix (un-, re-, etc.)
 *   6. Derivation: Optional derivational suffix (-ness, -ly, etc.)
 */
class Analysis {
private:
    std::string stem_;
    PartOfSpeech pos_;
    std::vector<std::string> features_;

    // STEP 9: Ambiguity ranking weight
    float weight_ = 1.0f;

    // STEP 5: Optional prefix
    std::string prefix_;

    // STEP 6: Optional derivational suffix and derived POS
    std::string deriv_suffix_;
    PartOfSpeech derived_pos_ = PartOfSpeech::NOUN;

public:
    Analysis(const std::string& stem, PartOfSpeech pos,
             const std::vector<std::string>& features)
        : stem_(stem), pos_(pos), features_(features) {}

    // ========== Accessors ==========

    const std::string& stem() const { return stem_; }
    PartOfSpeech pos() const { return pos_; }
    const std::vector<std::string>& features() const { return features_; }

    // Weight
    float weight() const { return weight_; }
    void set_weight(float w) { weight_ = w; }

    // Prefix
    const std::string& prefix() const { return prefix_; }
    bool has_prefix() const { return !prefix_.empty(); }
    void set_prefix(const std::string& p) { prefix_ = p; }

    // Derivation
    const std::string& deriv_suffix() const { return deriv_suffix_; }
    PartOfSpeech derived_pos() const { return derived_pos_; }
    bool is_derivational() const { return !deriv_suffix_.empty(); }
    void set_derivation(const std::string& suffix, PartOfSpeech derived) {
        deriv_suffix_ = suffix;
        derived_pos_ = derived;
    }

    /**
     * to_string: Format analysis in standard linguistic notation
     */
    std::string to_string() const {
        std::string result;
        if (!prefix_.empty()) result += prefix_ + "- + ";
        result += stem_ + " +" + pos_to_string(pos_);
        for (const auto& feat : features_) {
            result += " " + feat;
        }
        if (!deriv_suffix_.empty()) {
            result += " [" + deriv_suffix_ + " ->" + pos_to_string(derived_pos_) + "]";
        }
        return result;
    }

    /**
     * Equality: includes prefix and derivation fields
     */
    bool operator==(const Analysis& other) const {
        if (stem_ != other.stem_ || pos_ != other.pos_) return false;
        if (prefix_ != other.prefix_) return false;
        if (deriv_suffix_ != other.deriv_suffix_) return false;
        if (features_.size() != other.features_.size()) return false;
        for (size_t i = 0; i < features_.size(); i++) {
            if (features_[i] != other.features_[i]) return false;
        }
        return true;
    }

    bool operator!=(const Analysis& other) const {
        return !(*this == other);
    }
};

#endif // ANALYSIS_H
