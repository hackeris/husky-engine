
// Generated from grammar/HuskyLang.g4 by ANTLR 4.8

#pragma once


#include "antlr4-runtime.h"




class  HuskyLangParser : public antlr4::Parser {
public:
  enum {
    T__0 = 1, T__1 = 2, T__2 = 3, INT = 4, DOUBLE = 5, PI = 6, E = 7, POW = 8, 
    ID = 9, CHAR = 10, PLUS = 11, MINUS = 12, MULT = 13, DIV = 14, EQUAL = 15, 
    GTE = 16, GT = 17, LTE = 18, LT = 19, NEQ = 20, AND = 21, OR = 22, NOT = 23, 
    LPAR = 24, RPAR = 25, WS = 26, NL = 27
  };

  enum {
    RuleStatement = 0, RuleExpression = 1, RuleLogical = 2, RuleCompare = 3, 
    RulePlusOrMinus = 4, RuleMultOrDiv = 5, RuleUnary = 6, RulePowr = 7, 
    RuleAtom = 8, RuleArgList = 9, RuleIdentifier = 10, RuleLiteral = 11
  };

  HuskyLangParser(antlr4::TokenStream *input);
  ~HuskyLangParser();

  virtual std::string getGrammarFileName() const override;
  virtual const antlr4::atn::ATN& getATN() const override { return _atn; };
  virtual const std::vector<std::string>& getTokenNames() const override { return _tokenNames; }; // deprecated: use vocabulary instead.
  virtual const std::vector<std::string>& getRuleNames() const override;
  virtual antlr4::dfa::Vocabulary& getVocabulary() const override;


  class StatementContext;
  class ExpressionContext;
  class LogicalContext;
  class CompareContext;
  class PlusOrMinusContext;
  class MultOrDivContext;
  class UnaryContext;
  class PowrContext;
  class AtomContext;
  class ArgListContext;
  class IdentifierContext;
  class LiteralContext; 

  class  StatementContext : public antlr4::ParserRuleContext {
  public:
    StatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    StatementContext() = default;
    void copyFrom(StatementContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  ToExpressionContext : public StatementContext {
  public:
    ToExpressionContext(StatementContext *ctx);

    ExpressionContext *expression();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  StatementContext* statement();

  class  ExpressionContext : public antlr4::ParserRuleContext {
  public:
    ExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    ExpressionContext() = default;
    void copyFrom(ExpressionContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  ToLogicalContext : public ExpressionContext {
  public:
    ToLogicalContext(ExpressionContext *ctx);

    LogicalContext *logical();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  ExpressionContext* expression();

  class  LogicalContext : public antlr4::ParserRuleContext {
  public:
    LogicalContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    LogicalContext() = default;
    void copyFrom(LogicalContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  LogicalOpContext : public LogicalContext {
  public:
    LogicalOpContext(LogicalContext *ctx);

    antlr4::Token *op = nullptr;
    LogicalContext *logical();
    CompareContext *compare();
    antlr4::tree::TerminalNode *AND();
    antlr4::tree::TerminalNode *OR();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  ToCompareContext : public LogicalContext {
  public:
    ToCompareContext(LogicalContext *ctx);

    CompareContext *compare();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  LogicalContext* logical();
  LogicalContext* logical(int precedence);
  class  CompareContext : public antlr4::ParserRuleContext {
  public:
    CompareContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    CompareContext() = default;
    void copyFrom(CompareContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  ToPlusOrMinusContext : public CompareContext {
  public:
    ToPlusOrMinusContext(CompareContext *ctx);

    PlusOrMinusContext *plusOrMinus();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  CompareOpContext : public CompareContext {
  public:
    CompareOpContext(CompareContext *ctx);

    antlr4::Token *op = nullptr;
    CompareContext *compare();
    PlusOrMinusContext *plusOrMinus();
    antlr4::tree::TerminalNode *EQUAL();
    antlr4::tree::TerminalNode *NEQ();
    antlr4::tree::TerminalNode *GT();
    antlr4::tree::TerminalNode *GTE();
    antlr4::tree::TerminalNode *LT();
    antlr4::tree::TerminalNode *LTE();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  CompareContext* compare();
  CompareContext* compare(int precedence);
  class  PlusOrMinusContext : public antlr4::ParserRuleContext {
  public:
    PlusOrMinusContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    PlusOrMinusContext() = default;
    void copyFrom(PlusOrMinusContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  ToMultOrDivContext : public PlusOrMinusContext {
  public:
    ToMultOrDivContext(PlusOrMinusContext *ctx);

    MultOrDivContext *multOrDiv();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  AddSubOpContext : public PlusOrMinusContext {
  public:
    AddSubOpContext(PlusOrMinusContext *ctx);

    antlr4::Token *op = nullptr;
    PlusOrMinusContext *plusOrMinus();
    MultOrDivContext *multOrDiv();
    antlr4::tree::TerminalNode *PLUS();
    antlr4::tree::TerminalNode *MINUS();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  PlusOrMinusContext* plusOrMinus();
  PlusOrMinusContext* plusOrMinus(int precedence);
  class  MultOrDivContext : public antlr4::ParserRuleContext {
  public:
    MultOrDivContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    MultOrDivContext() = default;
    void copyFrom(MultOrDivContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  ToUnaryContext : public MultOrDivContext {
  public:
    ToUnaryContext(MultOrDivContext *ctx);

    UnaryContext *unary();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  MultiDivOpContext : public MultOrDivContext {
  public:
    MultiDivOpContext(MultOrDivContext *ctx);

    antlr4::Token *op = nullptr;
    MultOrDivContext *multOrDiv();
    PowrContext *powr();
    antlr4::tree::TerminalNode *MULT();
    antlr4::tree::TerminalNode *DIV();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  MultOrDivContext* multOrDiv();
  MultOrDivContext* multOrDiv(int precedence);
  class  UnaryContext : public antlr4::ParserRuleContext {
  public:
    UnaryContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    UnaryContext() = default;
    void copyFrom(UnaryContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  UnaryOpContext : public UnaryContext {
  public:
    UnaryOpContext(UnaryContext *ctx);

    antlr4::Token *op = nullptr;
    PowrContext *powr();
    antlr4::tree::TerminalNode *MINUS();
    antlr4::tree::TerminalNode *NOT();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  ToPowerContext : public UnaryContext {
  public:
    ToPowerContext(UnaryContext *ctx);

    PowrContext *powr();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  UnaryContext* unary();

  class  PowrContext : public antlr4::ParserRuleContext {
  public:
    PowrContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    PowrContext() = default;
    void copyFrom(PowrContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  ToAtomContext : public PowrContext {
  public:
    ToAtomContext(PowrContext *ctx);

    AtomContext *atom();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  PowerContext : public PowrContext {
  public:
    PowerContext(PowrContext *ctx);

    antlr4::Token *op = nullptr;
    PowrContext *powr();
    AtomContext *atom();
    antlr4::tree::TerminalNode *POW();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  PowrContext* powr();
  PowrContext* powr(int precedence);
  class  AtomContext : public antlr4::ParserRuleContext {
  public:
    AtomContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    AtomContext() = default;
    void copyFrom(AtomContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  FuncCallContext : public AtomContext {
  public:
    FuncCallContext(AtomContext *ctx);

    HuskyLangParser::IdentifierContext *functionName = nullptr;
    antlr4::tree::TerminalNode *LPAR();
    antlr4::tree::TerminalNode *RPAR();
    IdentifierContext *identifier();
    ArgListContext *argList();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  BracesContext : public AtomContext {
  public:
    BracesContext(AtomContext *ctx);

    antlr4::tree::TerminalNode *LPAR();
    ExpressionContext *expression();
    antlr4::tree::TerminalNode *RPAR();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  ToIdentifierContext : public AtomContext {
  public:
    ToIdentifierContext(AtomContext *ctx);

    IdentifierContext *identifier();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  ToLiteralContext : public AtomContext {
  public:
    ToLiteralContext(AtomContext *ctx);

    LiteralContext *literal();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  ArrayIndexContext : public AtomContext {
  public:
    ArrayIndexContext(AtomContext *ctx);

    HuskyLangParser::IdentifierContext *indexable = nullptr;
    HuskyLangParser::ExpressionContext *index = nullptr;
    IdentifierContext *identifier();
    ExpressionContext *expression();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  AtomContext* atom();

  class  ArgListContext : public antlr4::ParserRuleContext {
  public:
    ArgListContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ExpressionContext *expression();
    ArgListContext *argList();


    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ArgListContext* argList();
  ArgListContext* argList(int precedence);
  class  IdentifierContext : public antlr4::ParserRuleContext {
  public:
    IdentifierContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *ID();


    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  IdentifierContext* identifier();

  class  LiteralContext : public antlr4::ParserRuleContext {
  public:
    LiteralContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    LiteralContext() = default;
    void copyFrom(LiteralContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  ConstantPIContext : public LiteralContext {
  public:
    ConstantPIContext(LiteralContext *ctx);

    antlr4::tree::TerminalNode *PI();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  ConstantEContext : public LiteralContext {
  public:
    ConstantEContext(LiteralContext *ctx);

    antlr4::tree::TerminalNode *E();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  DoubleContext : public LiteralContext {
  public:
    DoubleContext(LiteralContext *ctx);

    antlr4::tree::TerminalNode *DOUBLE();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  IntContext : public LiteralContext {
  public:
    IntContext(LiteralContext *ctx);

    antlr4::tree::TerminalNode *INT();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  LiteralContext* literal();


  virtual bool sempred(antlr4::RuleContext *_localctx, size_t ruleIndex, size_t predicateIndex) override;
  bool logicalSempred(LogicalContext *_localctx, size_t predicateIndex);
  bool compareSempred(CompareContext *_localctx, size_t predicateIndex);
  bool plusOrMinusSempred(PlusOrMinusContext *_localctx, size_t predicateIndex);
  bool multOrDivSempred(MultOrDivContext *_localctx, size_t predicateIndex);
  bool powrSempred(PowrContext *_localctx, size_t predicateIndex);
  bool argListSempred(ArgListContext *_localctx, size_t predicateIndex);

private:
  static std::vector<antlr4::dfa::DFA> _decisionToDFA;
  static antlr4::atn::PredictionContextCache _sharedContextCache;
  static std::vector<std::string> _ruleNames;
  static std::vector<std::string> _tokenNames;

  static std::vector<std::string> _literalNames;
  static std::vector<std::string> _symbolicNames;
  static antlr4::dfa::Vocabulary _vocabulary;
  static antlr4::atn::ATN _atn;
  static std::vector<uint16_t> _serializedATN;


  struct Initializer {
    Initializer();
  };
  static Initializer _init;
};

