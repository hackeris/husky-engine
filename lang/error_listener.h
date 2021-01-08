//
// Created by rainm on 2021/1/7.
//

#ifndef HUSKY_ENGINE_ERROR_LISTENER_H
#define HUSKY_ENGINE_ERROR_LISTENER_H

#include <string>
#include <vector>
#include <exception>
#include <numeric>

#include "antlr4-runtime.h"

using antlr4::dfa::DFA;
using antlr4::atn::ATNConfigSet;
using antlr4::Token;
using antlr4::Parser;
using antlr4::Recognizer;

struct syntax_error_item {
public:
    size_t line;
    size_t pos;
    std::string msg;

public:
    [[nodiscard]]
    std::string to_string() const {
        return std::string() + "Syntax error at " + std::to_string(line) + ":" + std::to_string(pos) + ", " + msg;
    }
};

class syntax_error : public std::runtime_error {
public:
    explicit syntax_error(const std::string &w) : std::runtime_error(w) {}
};

class error_listener : public antlr4::ANTLRErrorListener {
public:

    void syntaxError(Recognizer *recognizer, Token *offendingSymbol, size_t line,
                     size_t charPositionInLine, const std::string &msg, std::exception_ptr e) override;

    void reportAmbiguity(Parser *recognizer, const DFA &dfa, size_t startIndex, size_t stopIndex, bool exact,
                         const antlrcpp::BitSet &ambigAlts, ATNConfigSet *configs) override;

    void reportAttemptingFullContext(Parser *recognizer, const DFA &dfa, size_t startIndex, size_t stopIndex,
                                     const antlrcpp::BitSet &conflictingAlts, ATNConfigSet *configs) override;

    void reportContextSensitivity(Parser *recognizer, const DFA &dfa, size_t startIndex, size_t stopIndex,
                                  size_t prediction, ATNConfigSet *configs) override;

    [[nodiscard]]
    inline bool has_error() const { return !errors.empty(); }

    [[nodiscard]]
    inline const std::vector<syntax_error_item> &get_errors() const { return errors; }

    [[nodiscard]]
    syntax_error as_exception() const {
        std::string what = std::accumulate(errors.begin(), errors.end(),
                                           std::string(),
                                           [](const std::string &acc, const syntax_error_item &el) -> std::string {
                                               return acc.empty() ? el.to_string() : acc + "\n" + el.to_string();
                                           });
        return syntax_error(what);
    }

private:
    std::vector<syntax_error_item> errors;
};


#endif //HUSKY_ENGINE_ERROR_LISTENER_H
