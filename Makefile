CXX      = g++
CXXFLAGS = -std=c++17 -Wall -I.

SCALPEL_DIR = ../Scalpel
SCALPEL_SRC = $(SCALPEL_DIR)/tokenizer.cpp \
              $(SCALPEL_DIR)/sentence_segmenter.cpp \
              $(SCALPEL_DIR)/char_classes.cpp

MORPH_SRC = SYMBOLS/symbol.cpp \
            PIPELINE/text_pipeline.cpp

.PHONY: all clean

all: analyzer test_infra test_lex test_analyzer

# ── Main analyzer (Scalpel + morphology) ────────────────────────────────────
analyzer: main.cpp $(MORPH_SRC) $(SCALPEL_SRC)
	$(CXX) $(CXXFLAGS) -o $@ $^

# ── Infrastructure tests (FSA, FST, SymbolTable) ─────────────────────────────
test_infra: test_infrastructure.cpp SYMBOLS/symbol.cpp
	$(CXX) $(CXXFLAGS) -o $@ $^

# ── Lexicon + rules tests ─────────────────────────────────────────────────────
test_lex: test_lexicon_rules.cpp SYMBOLS/symbol.cpp $(PIPELINE_SRC)
	$(CXX) $(CXXFLAGS) -o $@ test_lexicon_rules.cpp SYMBOLS/symbol.cpp

# ── Comprehensive integration tests ──────────────────────────────────────────
test_analyzer: test_analyzer.cpp SYMBOLS/symbol.cpp
	$(CXX) $(CXXFLAGS) -o $@ test_analyzer.cpp SYMBOLS/symbol.cpp

clean:
	rm -f analyzer test_infra test_lex test_analyzer
