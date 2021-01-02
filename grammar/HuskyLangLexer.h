
// Generated from grammar/HuskyLang.g4 by ANTLR 4.8

#pragma once


#include "antlr4-runtime.h"




class  HuskyLangLexer : public antlr4::Lexer {
public:
  enum {
    T__0 = 1, T__1 = 2, T__2 = 3, INT = 4, DOUBLE = 5, PI = 6, E = 7, POW = 8, 
    ID = 9, CHAR = 10, PLUS = 11, MINUS = 12, MULT = 13, DIV = 14, EQUAL = 15, 
    GTE = 16, GT = 17, LTE = 18, LT = 19, NEQ = 20, AND = 21, OR = 22, NOT = 23, 
    LPAR = 24, RPAR = 25, WS = 26, NL = 27
  };

  HuskyLangLexer(antlr4::CharStream *input);
  ~HuskyLangLexer();

  virtual std::string getGrammarFileName() const override;
  virtual const std::vector<std::string>& getRuleNames() const override;

  virtual const std::vector<std::string>& getChannelNames() const override;
  virtual const std::vector<std::string>& getModeNames() const override;
  virtual const std::vector<std::string>& getTokenNames() const override; // deprecated, use vocabulary instead
  virtual antlr4::dfa::Vocabulary& getVocabulary() const override;

  virtual const std::vector<uint16_t> getSerializedATN() const override;
  virtual const antlr4::atn::ATN& getATN() const override;

private:
  static std::vector<antlr4::dfa::DFA> _decisionToDFA;
  static antlr4::atn::PredictionContextCache _sharedContextCache;
  static std::vector<std::string> _ruleNames;
  static std::vector<std::string> _tokenNames;
  static std::vector<std::string> _channelNames;
  static std::vector<std::string> _modeNames;

  static std::vector<std::string> _literalNames;
  static std::vector<std::string> _symbolicNames;
  static antlr4::dfa::Vocabulary _vocabulary;
  static antlr4::atn::ATN _atn;
  static std::vector<uint16_t> _serializedATN;


  // Individual action functions triggered by action() above.

  // Individual semantic predicate functions triggered by sempred() above.

  struct Initializer {
    Initializer();
  };
  static Initializer _init;
};

