//
// Created by rainm on 2021/1/7.
//

#include <string>

#include "error_listener.h"

void error_listener::syntaxError(Recognizer *recognizer, Token *offendingSymbol, size_t line, size_t charPositionInLine,
                                 const std::string &msg, std::exception_ptr e) {
    errors.emplace_back(syntax_error_item{line, charPositionInLine, msg});
}

void
error_listener::reportAmbiguity(Parser *recognizer, const DFA &dfa, size_t startIndex, size_t stopIndex, bool exact,
                                const antlrcpp::BitSet &ambigAlts, ATNConfigSet *configs) {
}

void
error_listener::reportAttemptingFullContext(Parser *recognizer, const DFA &dfa, size_t startIndex, size_t stopIndex,
                                            const antlrcpp::BitSet &conflictingAlts, ATNConfigSet *configs) {
}

void error_listener::reportContextSensitivity(Parser *recognizer, const DFA &dfa, size_t startIndex, size_t stopIndex,
                                              size_t prediction, ATNConfigSet *configs) {
}
